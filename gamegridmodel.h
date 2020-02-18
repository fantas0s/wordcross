#ifndef GAMEGRIDMODEL_H
#define GAMEGRIDMODEL_H
#include <QAbstractItemModel>
#include "tilestorage.h"

class GameGridModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit GameGridModel(QObject *parent = nullptr);
    Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex &child) const override;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
private:
    enum {
        TileLetterRole = Qt::UserRole+1,
        TilePointsRole = Qt::UserRole+2,
        TileIndexEmptyRole = Qt::UserRole+3,
        TileStartRole = Qt::UserRole+4
    };
    TileStorage* m_storage;
};

#endif // GAMEGRIDMODEL_H
