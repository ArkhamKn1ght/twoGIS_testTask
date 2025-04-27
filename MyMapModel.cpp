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

void MyMapModel::insert(const QString &key) {
    bool existed = m_data.contains(key);

    if (existed) {
        m_data[key] += 1;
    } else {
        beginInsertRows(QModelIndex(), m_keys.size(), m_keys.size());
        m_keys.append(key);
        m_data.insert(key, 1);
        endInsertRows();
    }

    std::sort(m_keys.begin(), m_keys.end(), [this](const QString &a, const QString &b) {
        return m_data[a] > m_data[b];
    });
}

void MyMapModel::insertNoUpdate(const QString &key) {
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


void MyMapModel::clear()
{
    beginResetModel();
    m_data.clear();
    m_keys.clear();
    endResetModel();
    emit keysChanged();
}

void MyMapModel::forceUpdate() {

    std::sort(m_keys.begin(), m_keys.end(), [this](const QString &a, const QString &b) {
        return m_data[a] > m_data[b];
    });

    beginResetModel();
    endResetModel();
    emit keysChanged();
}

QStringList MyMapModel::keys() const
{
    return m_keys;
}
