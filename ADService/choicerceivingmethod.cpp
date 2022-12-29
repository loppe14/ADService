#include "choicerceivingmethod.h"
ChoiceRceivingMethod::ChoiceRceivingMethod(QWidget *parent)
	: QDialog(parent)
	, _method(ServerRepMaster::Unknown)
{
	setupUi(this);
	connect(okButton, &QPushButton::clicked, this, &ChoiceRceivingMethod::setMethod);
	connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
	connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);


}
void ChoiceRceivingMethod::setMethod()
{
    _method = ServerRepMaster::Unknown;
	exec();
	if (wtsRadio->isChecked())
		_method = ServerRepMaster::WTSMethod;
	else if(userRadio->isChecked())
		_method = ServerRepMaster::UserInput;
	else if(ldapRadio->isChecked())
		_method = ServerRepMaster::LDAPMethod;
	else if(currentRadio->isChecked())
		_method = ServerRepMaster::Localhost;

};
ServerRepMaster::ReceivingMethod ChoiceRceivingMethod::getMethod() const
{
	return _method;
}


ChoiceRceivingMethod::~ChoiceRceivingMethod(){}
