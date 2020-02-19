#ifndef AVAILABLETILELISTMODEL_H
#define AVAILABLETILELISTMODEL_H
#include <QAbstractListModel>
#include "proposaltilestore.h"

class AvailableTileListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AvailableTileListModel(QObject *parent = nullptr);
    Q_INVOKABLE QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex &child) const override;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
private slots:
    void beginRowInsertion(int firstIdx, int lastIdx);
    void endRowInsertion();
    void beginRowRemoval(int firstIdx, int lastIdx);
    void endRowRemoval();
private:
    enum {
        TileLetterRole = Qt::UserRole+1,
        TilePointsRole = Qt::UserRole+2
    };
    ProposalTileStore* m_storage;
};

#endif // AVAILABLETILELISTMODEL_H
