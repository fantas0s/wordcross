#ifndef GAMEGRIDMODEL_H
#define GAMEGRIDMODEL_H
#include <QAbstractTableModel>
#include "tilestorage.h"

class GameGridModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GameGridModel(QObject *parent = nullptr);
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
private slots:
    void tileUpdated(int row, int column);
private:
    enum {
        TileLetterRole = Qt::UserRole+1,
        TilePointsRole,
        TileIndexEmptyRole,
        TileStartRole,
        RecentRole,
        NewRole
    };
    TileStorage* m_storage;
};

#endif // GAMEGRIDMODEL_H
