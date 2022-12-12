#include "idirectoryaccess.h"
IDirectoryAccess::~IDirectoryAccess() {}
ServerConfig::ServerConfig(const QString &hn)
	:_hostname(hn)
{}
ServerConfig::~ServerConfig() {}
DirectoryAccess::DirectoryAccess(const State& st) : _curState(st) {}
DirectoryAccess::DirectoryAccess() :_curState(State::Announced) {}
QString DirectoryAccess::getErrorString() const
{
	return _errorString;
}
IDirectoryAccess::State DirectoryAccess::getCurState() const
{
	return _curState;
}
QString DirectoryAccess::getHostname() const
{
	return _config->_hostname;
}