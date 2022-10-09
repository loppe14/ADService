#include "logger.h"
ILogger::ILogger(bool ts, QObject *parent) : _timeStamp(ts), QObject(parent) {}
void ILogger::log(const QString& msg) { emit logged(); }
void ILogger::setTimeStamp(bool ts) { _timeStamp=ts; }
bool ILogger::timeStamp() { return _timeStamp; }
StrLog::StrLog(QString& strLog, bool timeStamp/* = true*/, QObject* parent/* = nullptr*/) :
	_strLog(strLog),
	ILogger(timeStamp, parent)
{
}
StrLog::StrLog(bool timeStamp/* = true*/, QObject* parent/* = nullptr*/) :
		ILogger(timeStamp, parent)
{
}
void StrLog::log(const QString& msg)
{
	_strLog.push_back((_timeStamp ? QTime::currentTime().toString()+ " ":"") + msg + "\n");
	ILogger::log(msg);
}
QString StrLog::getLog() const { return _strLog; }

//GlobalStrLog::GlobalStrLog(QString& strLog, bool timeStamp = true, QObject* parent = nullptr) :
//	ILogger(parent)
//{
//	global::_globalStrLog    = strLog;
//	global::_globalTimeStamp = timeStamp;
//}
//void GlobalStrLog::log(const QString& msg)
//{
//	global::_globalStrLog.push_back((global::_globalTimeStamp ? QTime::currentTime().toString() + " " : "") + msg + "\n");
//	ILogger::log(msg);
//}
//QString GlobalStrLog::getLog()
//{
//	return global::_globalStrLog;
//}
