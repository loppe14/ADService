#pragma once

#include <QDialog>
#include "ui_userservers.h"
#include "idirectoryaccess.h"
class UserServers  : public QDialog, public Ui::userServers, public DirectoryAccess
{
	Q_OBJECT;
	ServerList _list;
public:
	UserServers(QWidget *parent=nullptr);
	int init(ServerConfig*)   override;
	int getServerNames(ServerList *) override;
	~UserServers();
};
