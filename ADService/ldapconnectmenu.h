#pragma once
#include <qdialog.h>
#include "ui_ldapconnectmenu.h"
#include "qtldap.h"
#include "logger.h"
class LdapConnectMenu :public QWidget, Ui::LdapConnectMenu
{
	Q_OBJECT;
public:
	LdapConnectMenu(QWidget* parent = nullptr);
};

