#include "availabletilelistmodel.h"
#include <QDebug>

AvailableTileListModel::AvailableTileListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    m_storage = ProposalTileStore::getInstance();
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
