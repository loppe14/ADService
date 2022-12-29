#include "ldapconfigmenu.h"
LdapConfigMenu::LdapConfigMenu(ServerConfig *rep, QWidget* parent/*=nullptr*/)
	:QDialog(parent)
	{
	setupUi(this);
	if(rep) {
		urlLine->setText(rep->hostname());
		LdapConfig* lData = dynamic_cast<LdapConfig*>(rep);
		if (lData) {
			portLine->setText(QString::number(lData->port()));
			dnLine->setText(lData->dn());
			passwLine->setText(lData->passw());
		}
	}

	connect(cancelPbt, &QPushButton::clicked, this, &QDialog::reject);
	connect(connectPbt, &QPushButton::clicked, this,&QDialog::accept);
	//if anonymous authentication is selected, then the dn and passw input fields are hidden
	connect(getHostnameCheck, &QCheckBox::toggled, this, [=](bool st)
		{
			if (st)
			{
				urlLine->setText("");
				urlLine->setEnabled(false);
			}
			else
				urlLine->setEnabled(true);
		});
	connect(currRadio, &QRadioButton::toggled, this, [=](bool st)
		{
			if (st) {
				bindBox->setEnabled(false);
				dnLine->setText("");
				passwLine->setText("");
			}
			else bindBox->setEnabled(true);
		}
	);
	connect(anonRadio, &QRadioButton::toggled, this, [=](bool st)
		{
			if (st) {
				bindBox->setEnabled(false);
				dnLine->setText("");
				passwLine->setText("");
			}
			else bindBox->setEnabled(true);
		}
	);
	currRadio->toggle();
	emit(currRadio->toggled(true));

}
void LdapConfigMenu::setConfig()
{
	_ldapConf = newOpFactory<LdapConfig>::create(
		urlLine->text(),
		portLine->text().toULong(),
		passwLine->text(),
		dnLine->text(),
		digestRadio->isChecked() || currRadio->isChecked() ?
		LdapConfig::DigestBind :
		LdapConfig::SimpleBind,
		filterLine->text(),
		saslCheck->isChecked()
	);
}