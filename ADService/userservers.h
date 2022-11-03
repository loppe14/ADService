#pragma once

#include <QDialog>
#include "ui_userservers.h"
#include "idirectoryaccess.h"
class UserServers  : public QDialog, public Ui::userServers, public DirectoryAccess
{
	Q_OBJECT;
	ServerList _list;
public:
	UserServers(QWidget *parent);
	int init(ServersRep*)   override;
	ServerList getServerNames() override;
	~UserServers();
};
