#pragma once
#include <qdialog.h>
#include "qtldap.h"
#include "ui_ldapconfigmenu.h"
class LdapConfigMenu :public QDialog, Ui::ldapConfigMenu
{
	Q_OBJECT;
private:
	ServerConfig *sRep;
public:
	LdapConfigMenu(ServerConfig *rep,QWidget* parent = nullptr);
signals:
	void transfer_data();
};

