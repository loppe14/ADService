#pragma once

#include <QDialog>
#include "ui_userservers.h"
#include "logger.h"
#include "serverlogic.h"
class UserServers  : public QDialog, public Ui::userServers, public ServerRep
{
	Q_OBJECT;
	ServerList _list;
public:
	UserServers(QWidget *parent=nullptr);
	int getServers(ServerList* list) override;
	int init() override;
	~UserServers();
private slots:
	void setList();
};
