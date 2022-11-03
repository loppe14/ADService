#include "userservers.h"

UserServers::UserServers(QWidget *parent)
	: QDialog(parent)
	,DirectoryAccess(State::Announced)
{
	setupUi(this);
}
int UserServers::init(ServersRep*)
{
	exec();
	QString text = inputField->toPlainText();
	_list = inputField->toPlainText().split(u';',Qt::SkipEmptyParts);
	if (_list.size() == 0)
	{
		errorString="Empty server field received";
		return 0;
	}
	curState=Initialized;
	return 1;
	
}
ServerList UserServers::getServerNames()
{
	return _list;
}
UserServers::~UserServers()
{

}
