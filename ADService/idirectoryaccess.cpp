#include "idirectoryaccess.h"
IDirectoryAccess::~IDirectoryAccess() {}
ServersRep::ServersRep(const QString &hn)
	:_hostname(hn)
{}
ServersRep::~ServersRep() {}
DirectoryAccess::DirectoryAccess(const State& st) : curState(st) {}
DirectoryAccess::DirectoryAccess() :curState(State::Announced) {}
QString DirectoryAccess::getErrorString()
{
	return errorString;
}
IDirectoryAccess::State DirectoryAccess::getCurState()
{
	return curState;
}
