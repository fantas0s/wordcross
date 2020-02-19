#include "proposaltilestore.h"
#include "charutils.h"
#include <QDebug>

ProposalTileStore* ProposalTileStore::s_instance = nullptr;

ProposalTileStore::ProposalTileStore(QObject *parent) : QObject(parent)
{
    for (int i = 0 ; i < 7 ; ++i) {
        m_list.append(Tile(CharUtils::getRandomChar()));
    }
}

ProposalTileStore* ProposalTileStore::getInstance()
{
    if (!s_instance) {
        s_instance = new ProposalTileStore();
    }
    return s_instance;
}

int ProposalTileStore::size() const
{
    return m_list.length();
}

Tile ProposalTileStore::tileAt(int idx) const
{
    if (idx < size()) {
        return m_list[idx];
    } else {
        qWarning() << Q_FUNC_INFO << "Invalid request idx:" << idx;
        return Tile();
    }
}
