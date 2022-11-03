#pragma once
#include <qdialog.h>
#include <qwidget.h>
#include "qtldap.h"
#include "ui_ldapconfigmenu.h"
class LdapConfigMenu :public QDialog, Ui::ldapConfigMenu
{
	Q_OBJECT;
private:
	ServersRep *sRep;
public:
	LdapConfigMenu(ServersRep *rep,QWidget* parent = nullptr);
signals:
	void transfer_data();
};

