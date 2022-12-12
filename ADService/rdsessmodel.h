#pragma once

#include <QAbstractListModel>
#include "rdpserver.h"
class RDSessListModel  : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(int count READ rowCount NOTIFY rowChanged)
	//the roles mapping to be used by QML
	QHash<int, QByteArray> _roleNames;
	QList<RDsession*>	   _sessions;
protected: 	
	QHash<int, QByteArray> roleNames() const override;
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
public:
	enum RoleNames {
		IdRole = Qt::UserRole,
		UserNameRole = Qt::UserRole + 2,
		StateRole = Qt::UserRole + 4,
		ServerRole = Qt::UserRole + 5
	};
	RDSessListModel(QObject* parent = nullptr);
	//bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	//int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	//QModelIndex QAbstractItemModel::parent(const QModelIndex& index) const override;
	bool setSessionList(const QList<RDsession*>& list, int row = 0);
	//QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	int rowCount(const QModelIndex& parent=QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	~RDSessListModel();
signals:
	void rowChanged();
};
