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
