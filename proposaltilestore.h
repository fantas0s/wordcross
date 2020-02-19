#ifndef PROPOSALTILESTORE_H
#define PROPOSALTILESTORE_H
#include "tile.h"
#include <QObject>
#include <QList>

class QQmlEngine;
class QJSEngine;

class ProposalTileStore : public QObject
{
    Q_OBJECT
public:
    static QObject* proposalTileStoreProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
    int size() const;
    Tile tileAt(int idx) const;
signals:
    void beginRowInsertion(int,int);
    void endRowInsertion();
    void beginRowRemoval(int, int);
    void endRowRemoval();
public slots:
    void appendTile(QChar tileLetter);
    void removeTile(int idx);
private:
    explicit ProposalTileStore(QObject *parent = nullptr);
    static ProposalTileStore* s_instance;
    QList<Tile> m_list;
};

#endif // PROPOSALTILESTORE_H
