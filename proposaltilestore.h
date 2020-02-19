#ifndef PROPOSALTILESTORE_H
#define PROPOSALTILESTORE_H
#include "tile.h"
#include <QObject>
#include <QList>

class ProposalTileStore : public QObject
{
    Q_OBJECT
public:
    static ProposalTileStore* getInstance();
    int size() const;
    Tile tileAt(int idx) const;
private:
    explicit ProposalTileStore(QObject *parent = nullptr);
    static ProposalTileStore* s_instance;
    QList<Tile> m_list;
};

#endif // PROPOSALTILESTORE_H
