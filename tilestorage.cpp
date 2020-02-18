#include "tilestorage.h"
#include <QRandomGenerator>
static QRandomGenerator rand_gen;

TileStorage* TileStorage::s_instance = nullptr;

Tile::Tile()
{
    m_char = QChar('A'+rand_gen.generate()%26);
    m_xPos = -1;
    m_yPos = -1;
}
QChar Tile::getChar() const
{
    return m_char;
}

int Tile::getX() const
{
    return m_xPos;
}

int Tile::getY() const
{
    return m_yPos;
}

void Tile::setPos(int newX, int newY)
{
    m_xPos = newX;
    m_yPos = newY;
}

TileStorage::TileStorage(QObject *parent) : QObject(parent)
{
    for (int i = 0 ; i < 7 ; ++i) {
        Tile tileToAdd;
        m_availableTiles.append(tileToAdd);
    }
    for (int i = 0 ; i < 7 ; ++i) {
        Tile tileToAdd;
        tileToAdd.setPos(10, 7 + i);
        m_gridTiles.append(tileToAdd);
        tileToAdd = Tile();
        tileToAdd.setPos(7 + i, 10);
        m_gridTiles.append(tileToAdd);
    }
}

TileStorage* TileStorage::getInstance()
{
    if (!s_instance) {
        s_instance = new TileStorage();
    }
    return s_instance;
}

int TileStorage::requiredGridWidth() const
{
    int xMax = -1;
    for (Tile tile : m_gridTiles) {
        if (tile.getX() > xMax) {
            xMax = tile.getX();
        }
    }
    return xMax + 8;
}

int TileStorage::requiredGridHeight() const
{
    int yMax = -1;
    for (Tile tile : m_gridTiles) {
        if (tile.getY() > yMax) {
            yMax = tile.getY();
        }
    }
    return yMax + 8;
}

bool TileStorage::locationIsEmpty(int xPos, int yPos) const
{
    for (Tile tile : m_gridTiles) {
        if ((tile.getX() == xPos) &&
            (tile.getY() == yPos)) {
            return false;
        }
    }
    return true;
}

QChar TileStorage::tileAt(int xPos, int yPos) const
{
    for (Tile tile : m_gridTiles) {
        if ((tile.getX() == xPos) &&
            (tile.getY() == yPos)) {
            return tile.getChar();
        }
    }
    return '\0';
}
