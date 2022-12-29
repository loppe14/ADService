#include "userservers.h"

UserServers::UserServers(QWidget *parent)
	: QDialog(parent)
	,ServerRep(State::Announced)
	,_list(ServerList())
{
	setupUi(this);
}
int UserServers::init()
{
	exec();
	QString text = inputField->toPlainText();
	text = text.simplified(); text.replace(" ", "");
	_list = text.split(u';',Qt::SkipEmptyParts);
	if (_list.size() == 0)
	{
		_errorString="Empty server field received";
		return 0;
	}
	_state=Initialized;
	return 1;
	
}
int UserServers::getServers(ServerList* list)
{
	 *list = _list;
	 return 1;

}
UserServers::~UserServers()
{

}
