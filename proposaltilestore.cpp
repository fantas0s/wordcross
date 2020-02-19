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

QObject* ProposalTileStore::proposalTileStoreProvider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
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
    if ((idx >= 0) && (idx < size())) {
        return m_list[idx];
    } else {
        qWarning() << Q_FUNC_INFO << "Invalid request idx:" << idx;
        return Tile();
    }
}

void ProposalTileStore::appendTile(QChar tileLetter)
{
    emit beginRowInsertion(m_list.size(),m_list.size());
    m_list.append(Tile(tileLetter));
    emit endRowInsertion();
}

void ProposalTileStore::removeTile(int idx)
{
    if ((idx >= 0) && (idx < size())) {
        emit beginRowRemoval(idx,idx);
        m_list.removeAt(idx);
        emit endRowRemoval();
    } else {
        qWarning() << Q_FUNC_INFO << "Invalid request idx:" << idx;
    }
}
