#ifndef TILESTORAGE_H
#define TILESTORAGE_H

#include <QObject>
class Tile {
public:
    Tile();
    QChar getChar() const;
    int getX() const;
    int getY() const;
    void setPos(int newX, int newY);
private:
    int m_xPos;
    int m_yPos;
    QChar m_char;
};

class TileStorage : public QObject
{
    Q_OBJECT
public:
    static TileStorage* getInstance();
    int requiredGridWidth() const;
    int requiredGridHeight() const;
    bool locationIsEmpty(int xPos, int yPos) const;
    QChar tileAt(int xPos, int yPos) const;
private:
    explicit TileStorage(QObject *parent = nullptr);
    static TileStorage* s_instance;
    QList<Tile> m_availableTiles;
    QList<Tile> m_gridTiles;
};

#endif // TILESTORAGE_H
