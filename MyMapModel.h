#ifndef MYMAPMODEL_H
#define MYMAPMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDebug>
#include <QSortFilterProxyModel>
class LimitRowsProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
    Q_PROPERTY(int limit READ limit WRITE setLimit NOTIFY limitChanged)
public:
    explicit LimitRowsProxyModel(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

    int limit() const { return m_limit; }
    void setLimit(int limit) {
        if (m_limit == limit)
            return;
        m_limit = limit;
        invalidateFilter();
        emit limitChanged();
    }

signals:
    void limitChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        return sourceRow < m_limit;
    }

private:
    int m_limit = 15;
};

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

    int lookup(const QString &key) const;
    void insert(const QString &key);

    void insertNoUpdate(const QString &key);
    void clear();

    void forceUpdate();

    QStringList keys() const;

signals:
    void keysChanged();

private:
    QHash<QString, int> m_data;

    // при очень сильном желании ускорить процесс, можно использовать priority_queue
    QStringList m_keys;
};

#endif // MYMAPMODEL_H
