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
    enum Error {
        TilesDetached = -4,
        StartWordNotOnStartTile = -3,
        TilesNotInSameRowColumn = -2,
        TilesNotInSameWord = -1,
        NoTiles = 0,
        NoError = 1
    };
    Q_ENUM(Error)
    static QObject* tileStorageProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
    int gridWidth() const;
    int gridHeight() const;
    Tile tileAt(int row, int column) const;
    Q_INVOKABLE TileStorage::Error checkErrors() const;
    Q_INVOKABLE QStringList checkInvalidWords() const;
signals:
    void tileUpdated(int row, int column);
    void rowsWillBeAdded(int begin, int end);
    void rowsAdded();
    void columnsWillBeAdded(int begin, int end);
    void columnsAdded();
public slots:
    void lockTiles();
    void addTile(int row, int column, QString text);
    void removeTile(int row, int column);
private:
    typedef QList<Tile> TileRow;
    typedef QList<TileRow> TileGrid;
    void advance();
    void reframe();
    int countOfLockedTiles() const;
    int countOfProposalTiles() const;
    int columnOfProposalTiles() const;
    int rowOfProposalTiles() const;
    bool columnContainsProposalTiles(int column) const;
    bool rowContainsProposalTiles(int row) const;
    bool proposalTileColumnHasSpaces(int column) const;
    bool proposalTileRowHasSpaces(int row) const;
    bool proposalTileNextToLockedtileExists() const;
    bool isAdjacentToLockedtile(int row, int column) const;
    const Tile findStart() const;
    int getFirstX() const;
    int getFirstY() const;
    int getLastX() const;
    int getLastY() const;
    void appendColumns(int numOfNewColumns);
    void prependColumns(int numOfNewColumns);
    void appendRows(int numOfNewRows);
    void prependRows(int numOfNewRows);
    bool hasNonEmptyTile(const TileRow &tileRow) const;
    explicit TileStorage(QObject *parent = nullptr);
    static TileStorage* s_instance;
    TileGrid m_grid;
};

#endif // TILESTORAGE_H
