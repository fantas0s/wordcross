#include "tilestorage.h"
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

bool TileStorage::isValid() const
{
    if (findStart().getState() == Tile::State::Empty) {
        return false;
    } else {
        return true;
    }
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
    for (int row = 0 ; row < m_grid.size() ; ++row) {
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

const Tile TileStorage::findStart() const
{
    for (int row = 0 ; row < m_grid.size() ; ++row) {
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
