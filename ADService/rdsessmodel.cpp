#include "rdsessmodel.h"

RDSessListModel::RDSessListModel(QObject *parent)
	: QAbstractListModel(parent)
{
	_roleNames[UserNameRole] = "userName";
	_roleNames[IdRole]       = "id";
	_roleNames[StateRole]    = "st";
	_roleNames[ServerRole] = "server";

}
bool RDSessListModel::setSessionList(const QList<RDsession*>& list, int row)
{
	if (!insertRows(row, list.size(), QModelIndex()))return false;
	_sessions = list;
	emit dataChanged(index(row, 0), index(row + list.size()-1,0));
	return true;
}
int RDSessListModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
	return _sessions.size();
}
//QModelIndex RDSessListModel::index(int row, int column, const QModelIndex& parent) const
//{
//	return createIndex(row, column, nullptr);
//}
//int RDSessListModel::columnCount(const QModelIndex& parent) const
//{
//	return 1;
//}
//QModelIndex RDSessListModel::parent(const QModelIndex& index) const
//{
//	return QModelIndex();
//}

QVariant RDSessListModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid()) return QVariant();
	RDsession* indexSess = _sessions.at(index.row());
	switch (role)
	{
		case UserNameRole:return indexSess->user();  break;
		case StateRole:   return indexSess->StrState(); break;
		case IdRole:	  return QString::number(indexSess->id());break;
		case ServerRole:  return indexSess->server(); break;
		default: return QVariant();
			break;
	}
}
bool RDSessListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::EditRole) {
		_sessions.replace(index.row(), value.value<RDsession*>());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}
bool RDSessListModel::insertRows(int row, int count, const QModelIndex& parent ) 
{
	if (parent.isValid())
		return false;
	emit beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		_sessions.insert(row, 0);
	}
	emit endInsertRows();
	emit rowChanged();
	return true;
}


Qt::ItemFlags RDSessListModel::flags(const QModelIndex& index) const
{
	return QAbstractItemModel::flags(index);
}
QHash<int, QByteArray> RDSessListModel::roleNames() const
{
	return _roleNames;
}

RDSessListModel::~RDSessListModel()
{}
