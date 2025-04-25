#include "MyMapModel.h"

MyMapModel::MyMapModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MyMapModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_keys.size();
}

QVariant MyMapModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_keys.size())
        return {};

    const QString &key = m_keys.at(index.row());

    switch (role) {
        case KeyRole:
            return key;
        case ValueRole:
            return m_data.value(key);
        default:
            return {};
    }
}

QHash<int, QByteArray> MyMapModel::roleNames() const
{
    return {
        { KeyRole, "key" },
        { ValueRole, "value" }
    };
}

int MyMapModel::lookup(const QString &key) const
{
    return m_data.value(key, -1); // Return -1 if not found
}

void MyMapModel::insert(const QString &key)
{
    auto it = m_data.find(key);
    if(it != m_data.end()) {
        it.value() = it.value() + 1;
    } else {
        beginInsertRows(QModelIndex(), m_keys.size(), m_keys.size());
        m_keys.append(key);
        m_data.insert(key, 1);
        endInsertRows();
        emit keysChanged();
    }
    emit dataChanged(index(0), index(m_keys.size() - 1));
}

void MyMapModel::clear()
{
    beginResetModel();
    m_data.clear();
    m_keys.clear();
    endResetModel();
    emit keysChanged();
}

QStringList MyMapModel::keys() const
{
    return m_keys;
}
