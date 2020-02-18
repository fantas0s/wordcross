#include "tilestorage.h"
#include <QRandomGenerator>
static QRandomGenerator rand_gen;

TileStorage* TileStorage::s_instance = nullptr;

TileStorage::TileStorage(QObject *parent) : QObject(parent)
{
    for (int i = 0 ; i < 13 ; ++i) {
        TileRow rowToAdd;
        for (int j = 0 ; j < 13 ; ++j) {
            if (i==6 && j==6) {
                rowToAdd.append(Tile::startTile());
            } else {
                rowToAdd.append(Tile());
            }
        }
        m_grid.append(rowToAdd);
    }
}

TileStorage* TileStorage::getInstance()
{
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

Tile TileStorage::tileAt(int xPos, int yPos) const
{
    return m_grid[yPos][xPos];
}
