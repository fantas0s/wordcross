#include "tilestorage.h"
#include "testingstate.h"
#include <QDebug>

TileStorage* TileStorage::s_instance = nullptr;

TileStorage::TileStorage(QObject *parent) : QObject(parent)
{
    for (int row = 0 ; row < 13 ; ++row) {
        TileRow rowToAdd;
        for (int column = 0 ; column < 13 ; ++column) {
            if (row==6 && column==6) {
                rowToAdd.append(Tile::startTile());
            } else {
                rowToAdd.append(Tile());
            }
        }
        m_grid.append(rowToAdd);
    }
}

QObject* TileStorage::tileStorageProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    if (!s_instance) {
        s_instance = new TileStorage();
    }
    return s_instance;
}

int TileStorage::gridWidth() const
{
    return m_grid[0].length();
}

int TileStorage::gridHeight() const
{
    return m_grid.length();
}

Tile TileStorage::tileAt(int row, int column) const
{
    if (row < m_grid.length()) {
        const TileRow& tileRow = m_grid.at(row);
        if (column < tileRow.length()) {
            return tileRow.at(column);
        }
    }
    return Tile();
}

TileStorage::Error TileStorage::checkErrors() const
{
    if (countOfProposalTiles() == 0) {
        return NoTiles;
    }
    if (findStart().getState() == Tile::State::Empty) {
        return StartWordNotOnStartTile;
    }
    const int row = rowOfProposalTiles();
    const int column = columnOfProposalTiles();
    if (row < 0) {
        /* Not on same row */
        if (column < 0) {
            /* And not on same column either. */
            return TilesNotInSameRowColumn;
        } else {
            /* one same column. Check that there are no spaces */
            if (proposalTileColumnHasSpaces(column)) {
                return TilesNotInSameWord;
            }
            /* Else OK */
        }
    } else {
        /* one same row. Check that there are no spaces */
        if (proposalTileRowHasSpaces(row)) {
            return TilesNotInSameWord;
        }
        /* Else OK */
    }
    if (countOfLockedTiles() > 0) {
        if (!proposalTileNextToLockedtileExists()) {
            return TilesDetached;
        }
        /* else OK */
    }
    return NoError;
}

QStringList TileStorage::checkInvalidWords() const
{
    return QStringList();
}

void TileStorage::lockTiles()
{
    advance();
    reframe();
}

void TileStorage::addTile(int row, int column, QString text)
{
    if (tileAt(row, column).getState() == Tile::State::Empty) {
        TileRow& tileRow = m_grid[row];
        tileRow[column] = Tile(text[0]);
        emit tileUpdated(row, column);
    }
}

void TileStorage::removeTile(int row, int column)
{
    if (tileAt(row, column).getState() != Tile::State::Empty) {
        TileRow& tileRow = m_grid[row];
        tileRow[column] = Tile();
        emit tileUpdated(row, column);
    }
}

void TileStorage::advance()
{
    for (int row = 0 ; row < gridHeight() ; ++row) {
        TileRow& tileRow = m_grid[row];
        for (int column = 0 ; column < tileRow.size() ; ++column) {
            if (tileRow[column].levelUp()) {
                emit tileUpdated(row, column);
            }
        }
    }
}

void TileStorage::reframe()
{
    const int columnsToEnd = getLastX() - (gridWidth()-8);
    const int rowsToEnd = getLastY() - (gridHeight()-8);
    const int columnsToBeginning = 7 - getFirstX();
    const int rowsToBeginning = 7 - getFirstY();
    if (columnsToEnd > 0) {
        appendColumns(columnsToEnd);
    }
    if (rowsToEnd > 0) {
        appendRows(rowsToEnd);
    }
    if (columnsToBeginning > 0) {
        prependColumns(columnsToBeginning);
    }
    if (rowsToBeginning > 0) {
        prependRows(rowsToBeginning);
    }
}

int TileStorage::countOfLockedTiles() const
{
    int lockedCount = 0;
    for (const TileRow& tileRow : m_grid) {
        for (const Tile& tile : tileRow) {
            if ((tile.getState() == Tile::State::Recent) ||
                (tile.getState() == Tile::State::Old)){
                lockedCount++;
            }
        }
    }
    return lockedCount;
}

int TileStorage::countOfProposalTiles() const
{
    int proposalCount = 0;
    for (const TileRow& tileRow : m_grid) {
        for (const Tile& tile : tileRow) {
            if (tile.getState() == Tile::State::Proposal) {
                proposalCount++;
            }
        }
    }
    return proposalCount;
}

int TileStorage::columnOfProposalTiles() const
{
    int retVal = -1;
    for (int column = 0 ; column < gridWidth() ; ++column) {
        if (columnContainsProposalTiles(column)) {
            if (retVal < 0) {
                retVal = column;
            } else {
                /* At least two columns with proposal tiles. */
                retVal= -1;
                break;
            }
        }
    }
    return retVal;
}

int TileStorage::rowOfProposalTiles() const
{
    int retVal = -1;
    for (int row = 0 ; row < gridHeight() ; ++row) {
        if (rowContainsProposalTiles(row)) {
            if (retVal < 0) {
                retVal = row;
            } else {
                /* At least two rows with proposal tiles. */
                retVal= -1;
                break;
            }
        }
    }
    return retVal;
}

bool TileStorage::columnContainsProposalTiles(int column) const
{
    for (const TileRow& tileRow : m_grid) {
        const Tile& tile = tileRow.at(column);
        if (tile.getState() == Tile::State::Proposal) {
            return true;
        }
    }
    return false;
}

bool TileStorage::rowContainsProposalTiles(int row) const
{
    const TileRow& tileRow = m_grid.at(row);
    for (const Tile& tile : tileRow) {
        if (tile.getState() == Tile::State::Proposal) {
            return true;
        }
    }
    return false;
}

bool TileStorage::proposalTileColumnHasSpaces(int column) const
{
    TestingState state;
    for (const TileRow& tileRow : m_grid) {
        const Tile& tile = tileRow.at(column);
        state.stateChange(tile);
        if (!state.isValid()) {
            break;
        }
    }
    return !state.isValid();
}

bool TileStorage::proposalTileRowHasSpaces(int row) const
{
    const TileRow& tileRow = m_grid.at(row);
    TestingState state;
    for (const Tile& tile : tileRow) {
        state.stateChange(tile);
        if (!state.isValid()) {
            break;
        }
    }
    return !state.isValid();
}

bool TileStorage::proposalTileNextToLockedtileExists() const
{
    for (int row = 0 ; row < gridHeight() ; ++row) {
        const TileRow& tileRow = m_grid.at(row);
        for (int column = 0 ; column < gridWidth() ; ++column) {
            const Tile& tile = tileRow.at(column);
            if (tile.getState() == Tile::State::Proposal) {
                if (isAdjacentToLockedtile(row, column)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool TileStorage::isAdjacentToLockedtile(int row, int column) const
{
    Tile currentTile = tileAt(row-1, column);
    if ((currentTile.getState() == Tile::State::Old) ||
        (currentTile.getState() == Tile::State::Recent)) {
        return true;
    }
    currentTile = tileAt(row+1, column);
    if ((currentTile.getState() == Tile::State::Old) ||
        (currentTile.getState() == Tile::State::Recent)) {
        return true;
    }
    currentTile = tileAt(row, column-1);
    if ((currentTile.getState() == Tile::State::Old) ||
        (currentTile.getState() == Tile::State::Recent)) {
        return true;
    }
    currentTile = tileAt(row, column+1);
    if ((currentTile.getState() == Tile::State::Old) ||
        (currentTile.getState() == Tile::State::Recent)) {
        return true;
    }
    return false;
}

const Tile TileStorage::findStart() const
{
    for (int row = 0 ; row < gridHeight() ; ++row) {
        const TileRow& tileRow = m_grid.at(row);
        for (int column = 0 ; column < tileRow.size() ; ++column) {
            if (tileRow.at(column).getStart()) {
                return tileRow.at(column);
            }
        }
    }
    /* We have already replaced start. Just return a tile. */
    return Tile('Q');
}

int TileStorage::getFirstX() const
{
    int smallestX = gridWidth();
    for (const TileRow& tileRow : m_grid) {
        for (int column = 0 ; column < gridWidth() ; ++column) {
            if (tileRow.at(column).getState() != Tile::State::Empty) {
                if (column < smallestX) {
                    smallestX = column;
                }
                break;
            }
        }
    }
    return smallestX;
}

int TileStorage::getFirstY() const
{
    for (int row = 0 ; row < gridHeight() ; ++row) {
        const TileRow& tileRow = m_grid.at(row);
        if (hasNonEmptyTile(tileRow)) {
            return row;
        }
    }
    return gridHeight()-1;
}

int TileStorage::getLastX() const
{
    int greatestX = 0;
    for (const TileRow& tileRow : m_grid) {
        for (int column = gridWidth()-1 ; column >= 0 ; --column) {
            if (tileRow.at(column).getState() != Tile::State::Empty) {
                if (column > greatestX) {
                    greatestX = column;
                }
                break;
            }
        }
    }
    return greatestX;
}

int TileStorage::getLastY() const
{
    for (int row = gridHeight()-1 ; row >= 0 ; --row) {
        const TileRow& tileRow = m_grid.at(row);
        if (hasNonEmptyTile(tileRow)) {
            return row;
        }
    }
    return 0;
}

void TileStorage::appendColumns(int numOfNewColumns)
{
    emit columnsWillBeAdded(gridWidth(), gridWidth() + numOfNewColumns - 1);
    for (TileRow& tileRow : m_grid) {
        for (int count = 0 ; count < numOfNewColumns ; ++count) {
            tileRow.append(Tile());
        }
    }
    emit columnsAdded();
}

void TileStorage::prependColumns(int numOfNewColumns)
{
    emit columnsWillBeAdded(0, numOfNewColumns - 1);
    for (TileRow& tileRow : m_grid) {
        for (int count = 0 ; count < numOfNewColumns ; ++count) {
            tileRow.prepend(Tile());
        }
    }
    emit columnsAdded();
}

void TileStorage::appendRows(int numOfNewRows)
{
    emit rowsWillBeAdded(gridHeight(), gridHeight() + numOfNewRows - 1);
    TileRow newRow;
    for (int column = 0 ; column < gridWidth() ; ++column) {
        newRow.append(Tile());
    }
    for (int count = 0 ; count < numOfNewRows ; ++count) {
        m_grid.append(newRow);
    }
    emit rowsAdded();
}

void TileStorage::prependRows(int numOfNewRows)
{
    emit rowsWillBeAdded(0, numOfNewRows - 1);
    TileRow newRow;
    for (int column = 0 ; column < gridWidth() ; ++column) {
        newRow.append(Tile());
    }
    for (int count = 0 ; count < numOfNewRows ; ++count) {
        m_grid.prepend(newRow);
    }
    emit rowsAdded();
}

bool TileStorage::hasNonEmptyTile(const TileRow &tileRow) const
{
    for (const Tile& tile : tileRow) {
        if (tile.getState() != Tile::State::Empty) {
            return true;
        }
    }
    return false;
}
