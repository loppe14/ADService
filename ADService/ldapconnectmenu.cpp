#include "ldapconnectmenu.h"
class
{
};
LdapConnectMenu::LdapConnectMenu(QWidget* parent/*=nullptr*/)
	:QWidget(parent)
{
	setupUi(this);
	connect(AnonRadio, &QRadioButton::toggled, this, [=](bool st)
		{
			if (st) BindBox->setEnabled(false);
			else BindBox->setEnabled(true);
		}
	);
}

//int LdapConnectMenu::connect2ldap()
//{
//	//logText->insertPlainText("connecting to " + urlLine->text() + "...\n");
//	if (!ldapSession->init(urlLine->text())) {
//		//logText->insertPlainText(ldapSession->error_string());
//		return 0;
//	}
//	if (!ldapSession->bind(userLine->text(), passwLine->text(), QtLdap::SimpleBind))
//	{
//		//logText->insertPlainText(ldapSession->error_string());
//		return 0;
//	}
//	return 1;
//}