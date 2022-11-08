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
	qDebug() << loggedMsg;
	emit(logged(loggedMsg));
}

QString StaticLogger::_str = "";
bool StaticLogger::_timeStamp = true;


QString StaticLogger::getLog() { return _str; }
void StaticLogger::setTimeStamp(bool st) {_timeStamp=st; }
void StaticLogger::log(const std::string& msg)
{
	QString loggedMsg;
	loggedMsg =QString::fromStdString((_timeStamp ?
		QTime::currentTime().toString().toStdString() : "") + msg);
	_str.push_back(loggedMsg);
}