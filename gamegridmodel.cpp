#include "gamegridmodel.h"

GameGridModel::GameGridModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    m_storage = TileStorage::getInstance();
}

QModelIndex GameGridModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex GameGridModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int GameGridModel::rowCount(const QModelIndex &parent) const
{
    return m_storage->requiredGridHeight();
}

int GameGridModel::columnCount(const QModelIndex &parent) const
{
    return m_storage->requiredGridWidth();
}

QVariant GameGridModel::data(const QModelIndex &index, int role) const
{
    if( hasIndex(index.row(), index.column()) )
    {
        switch( role )
        {
        case TileLetterRole:
            return m_storage->tileAt(index.column(), index.row());
        case TilePointsRole:
            return QVariant(int(1));
        case TileIndexEmptyRole:
            return m_storage->locationIsEmpty(index.column(), index.row());
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QHash<int, QByteArray> GameGridModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TileLetterRole] = "letter";
    roles[TilePointsRole] = "points";
    roles[TileIndexEmptyRole] = "slotIsEmpty";
    return roles;
}
