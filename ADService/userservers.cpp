#include "userservers.h"

UserServers::UserServers(QWidget *parent)
	: QDialog(parent)
	,DirectoryAccess(State::Announced)
	,_list(ServerList())
{
	setupUi(this);
}
int UserServers::init(ServerConfig*)
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
	_curState=Initialized;
	return 1;
	
}
int UserServers::getServerNames(ServerList *list)
{
	 *list = _list;
	 return 1;

}
UserServers::~UserServers()
{

}
