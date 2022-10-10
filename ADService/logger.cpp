#include "logger.h"
Logger::Logger(bool timeStamp /*=true*/, QObject* parent/*=nullptr*/)
	:_timeStamp(timeStamp)
	, QObject(parent) {}
QString Logger::getLog() const
{
	return _str;
}
void Logger::log(const QString& msg)
{
	_str.push_back((_timeStamp ?
		QTime::currentTime().toString():"") + msg);
	emit(logged(msg));
}