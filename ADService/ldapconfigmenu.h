#pragma once
#include <qdialog.h>
#include "qtldap.h"
#include "ObjFactory.h"
#include "ui_ldapconfigmenu.h"
class LdapConfigMenu :public QDialog, public Ui::ldapConfigMenu
{
	Q_OBJECT;
private:
	LdapConfig* _ldapConf;
public:
	LdapConfigMenu(ServerConfig *rep = nullptr,QWidget* parent = nullptr);
	LdapConfig* getLdapConfig() const { return _ldapConf; }
private slots:
	void setConfig();
};

