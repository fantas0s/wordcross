#include "gamegridmodel.h"
#include <QDebug>

GameGridModel::GameGridModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    m_storage = TileStorage::getInstance();
}

QModelIndex GameGridModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return createIndex(row, column);
}

QModelIndex GameGridModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int GameGridModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_storage->gridHeight();
}

int GameGridModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_storage->gridWidth();
}

QVariant GameGridModel::data(const QModelIndex &index, int role) const
{
    if( hasIndex(index.row(), index.column()) )
    {
        switch( role )
        {
        case TileLetterRole:
            return m_storage->tileAt(index.column(), index.row()).getChar();
        case TilePointsRole:
            return m_storage->tileAt(index.column(), index.row()).getPoints();
        case TileIndexEmptyRole:
            return !m_storage->tileAt(index.column(), index.row()).isValid();
        case TileStartRole:
            return m_storage->tileAt(index.column(), index.row()).getState() == Tile::Start;
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
    roles[TileStartRole] = "isStartSlot";
    return roles;
}
