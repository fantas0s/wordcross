#ifndef TILESTORAGE_H
#define TILESTORAGE_H
#include "tile.h"
#include <QObject>
#include <QList>

class QQmlEngine;
class QJSEngine;

class TileStorage : public QObject
{
    Q_OBJECT
public:
    static QObject* tileStorageProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
    int gridWidth() const;
    int gridHeight() const;
    Tile tileAt(int xPos, int yPos) const;
    void advance();
private:
    typedef QList<Tile> TileRow;
    typedef QList<TileRow> TileGrid;
    explicit TileStorage(QObject *parent = nullptr);
    static TileStorage* s_instance;
    TileGrid m_grid;
};

#endif // TILESTORAGE_H
