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
