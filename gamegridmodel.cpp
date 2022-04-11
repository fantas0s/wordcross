#include "gamegridmodel.h"
#include <QDebug>

GameGridModel::GameGridModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    m_storage = qobject_cast<TileStorage*>(TileStorage::tileStorageProvider(nullptr, nullptr));
    Q_ASSERT(m_storage);
    connect(m_storage, &TileStorage::tileUpdated, this, &GameGridModel::tileUpdated);
    connect(m_storage, &TileStorage::rowsWillBeAdded, this, &GameGridModel::rowsWillBeAdded);
    connect(m_storage, &TileStorage::rowsAdded, this, &GameGridModel::rowsAdded);
    connect(m_storage, &TileStorage::columnsWillBeAdded, this, &GameGridModel::columnsWillBeAdded);
    connect(m_storage, &TileStorage::columnsAdded, this, &GameGridModel::columnsAdded);
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
            return m_storage->tileAt(index.row(), index.column()).getChar();
        case TilePointsRole:
            return m_storage->tileAt(index.row(), index.column()).getPoints();
        case TileIndexEmptyRole:
            return m_storage->tileAt(index.row(), index.column()).getState() == Tile::State::Empty;
        case TileStartRole:
            return m_storage->tileAt(index.row(), index.column()).getStart();
        case RecentRole:
            return m_storage->tileAt(index.row(), index.column()).getState() == Tile::State::Recent;
        case NewRole:
            return m_storage->tileAt(index.row(), index.column()).getState() == Tile::State::Proposal;
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
    roles[RecentRole] = "isRecent";
    roles[NewRole] = "isNew";
    return roles;
}

void GameGridModel::tileUpdated(int row, int column)
{
    const QModelIndex updatedIndex = index(row, column);
    emit dataChanged(updatedIndex, updatedIndex);
}

void GameGridModel::rowsWillBeAdded(int begin, int end)
{
    beginInsertRows(QModelIndex(), begin, end);
}

void GameGridModel::rowsAdded()
{
    endInsertRows();
}

void GameGridModel::columnsWillBeAdded(int begin, int end)
{
    beginInsertColumns(QModelIndex(), begin, end);
}

void GameGridModel::columnsAdded()
{
    endInsertColumns();
}
