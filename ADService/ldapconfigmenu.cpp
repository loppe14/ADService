#include "ldapconfigmenu.h"
class
{
};
LdapConfigMenu::LdapConfigMenu(ServersRep *rep, QWidget* parent/*=nullptr*/)
	:QDialog(parent)
	,sRep(rep)
{
	setupUi(this);

	LdapConfig* lData = dynamic_cast<LdapConfig*>(sRep);
	if (!sRep)
		throw(0);
	urlLine->setText(lData->_hostname);
	portLine->setText(QString::number(lData->port));
	dnLine->setText(lData->dn);
	passwLine->setText(lData->passw);
	



	connect(cancelPbt, &QPushButton::clicked, this, &QDialog::reject);
	connect(connectPbt, &QPushButton::clicked, this, [=]()
		{
			lData->_hostname = urlLine->text();
			lData->port      = portLine->text().toULong();
			lData->auth      = LdapConfig::SimpleBind; //i have to fix it
			lData->passw     = portLine->text();
			lData->dn	     = dnLine->text();
			lData->filter    = filterLine->text();
			lData->usingSasl = SSLCheck->isChecked();
			accept();

		});
	//if anonymous authentication is selected, then the dnand passw input fields are hidden
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
	currRadio->toggle();
	emit(currRadio->toggled(true));

}