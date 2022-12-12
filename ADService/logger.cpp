#include "logger.h"
Logger::Logger(bool timeStamp /*=true*/, QObject* parent/*=nullptr*/)
	:_timeStamp(timeStamp)
	, QObject(parent) {}
QString Logger::getLog() const
{
	return _str;
}
void Logger::log(const QString &msg, bool timeStamp)
{
	QString loggedMsg;
	loggedMsg=(_timeStamp&&timeStamp ?
		QTime::currentTime().toString()+" " : "") + msg;
	_str.push_back(loggedMsg);
	emit(logged(loggedMsg));
}

