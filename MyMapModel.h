#ifndef MYMAPMODEL_H
#define MYMAPMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDebug>
class MyMapModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList keys READ keys NOTIFY keysChanged)

public:
    explicit MyMapModel(QObject *parent = nullptr);

    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE int lookup(const QString &key) const;
    Q_INVOKABLE void insert(const QString &key);
    Q_INVOKABLE void clear();

    QStringList keys() const;

signals:
    void keysChanged();

private:
    QHash<QString, int> m_data;
    QStringList m_keys;
};

#endif // MYMAPMODEL_H
