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

    Q_INVOKABLE int lookup(const QString &key) const;
    void insert(const QString &key) {
        bool existed = m_data.contains(key);

        if (existed) {
            m_data[key] += 1;
        } else {
            beginInsertRows(QModelIndex(), m_keys.size(), m_keys.size());
            m_keys.append(key);
            m_data.insert(key, 1);
            endInsertRows();
        }

        // Sort descending by value
        std::sort(m_keys.begin(), m_keys.end(), [this](const QString &a, const QString &b) {
            return m_data[a] > m_data[b];
        });
    }

    void insertNoUpdate(const QString &key) {
        bool existed = m_data.contains(key);

        if (existed) {
            m_data[key] += 1;
        } else {
            beginInsertRows(QModelIndex(), m_keys.size(), m_keys.size());
            m_keys.append(key);
            m_data.insert(key, 1);
            endInsertRows();
        }
    }
    Q_INVOKABLE void clear();

    void forceUpdate() {

        std::sort(m_keys.begin(), m_keys.end(), [this](const QString &a, const QString &b) {
            return m_data[a] > m_data[b];
        });

        beginResetModel();
        endResetModel();
        emit keysChanged();
    }

    QStringList keys() const;

signals:
    void keysChanged();

private:
    QHash<QString, int> m_data;
    QStringList m_keys;
};

#endif // MYMAPMODEL_H
