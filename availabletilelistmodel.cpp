#include "availabletilelistmodel.h"
#include <QDebug>

AvailableTileListModel::AvailableTileListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    m_storage = qobject_cast<ProposalTileStore*>(ProposalTileStore::proposalTileStoreProvider(nullptr, nullptr));
    Q_ASSERT(m_storage);
    connect(m_storage, &ProposalTileStore::beginRowInsertion, this, &AvailableTileListModel::beginRowInsertion);
    connect(m_storage, &ProposalTileStore::endRowInsertion, this, &AvailableTileListModel::endRowInsertion);
    connect(m_storage, &ProposalTileStore::beginRowRemoval, this, &AvailableTileListModel::beginRowRemoval);
    connect(m_storage, &ProposalTileStore::endRowRemoval, this, &AvailableTileListModel::endRowRemoval);
}

QModelIndex AvailableTileListModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column);
}

QModelIndex AvailableTileListModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int AvailableTileListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_storage->size();
}

QVariant AvailableTileListModel::data(const QModelIndex &index, int role) const
{
    if( hasIndex(index.row(), index.column()) )
    {
        switch( role )
        {
        case TileLetterRole:
            return m_storage->tileAt(index.row()).getChar();
        case TilePointsRole:
            return m_storage->tileAt(index.row()).getPoints();
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QHash<int, QByteArray> AvailableTileListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TileLetterRole] = "letter";
    roles[TilePointsRole] = "points";
    return roles;
}

void AvailableTileListModel::beginRowInsertion(int firstIdx, int lastIdx)
{
    beginInsertRows(QModelIndex(), firstIdx, lastIdx);
}

void AvailableTileListModel::endRowInsertion()
{
    endInsertRows();
}

void AvailableTileListModel::beginRowRemoval(int firstIdx, int lastIdx)
{
    beginRemoveRows(QModelIndex(), firstIdx, lastIdx);
}

void AvailableTileListModel::endRowRemoval()
{
    endRemoveRows();
}
