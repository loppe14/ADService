#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>
//#ifndef GLOBAL_LOG
//#define GLOBAL_LOG
//	namespace global
//	{
//		QString _globalStrLog;
//		bool _globalTimeStamp;
//	}
//#endif
class ILogger : public QObject
{
	Q_OBJECT
protected:
	bool _timeStamp;
public:
	ILogger(bool timeStamp,QObject *parent);
	virtual void log(const QString&);
	bool timeStamp();
	void setTimeStamp(bool);
signals:
	void logged();

};


class StrLog : ILogger
{
	
protected:
	QString _strLog;
public:
	StrLog(bool timeStamp, QObject* parent = nullptr);
	StrLog(QString& strLog, bool timeStap = true, QObject* parent = nullptr);
	void log(const QString& msg) override;
	QString getLog() const;
};


//class GlobalStrLog : ILogger
//{
//protected:
//	GlobalStrLog(bool timeStamp, QObject* parent);
//	GlobalStrLog(QString& strLog, bool timeStap, QObject* parent);
//public:
//
//    void log(const QString& msg);
//	static QString getLog();
//};
//
//
//template<class LogStrategy>
//class Logger  : public LogStrategy
//{
//
//public:
//	Logger(QString logStr = "", bool ts = true, QObject* parent = nullptr) :
//		LogStrategy(logStr,ts,parent)
//	{}
//	~Logger()
//	{}
//
//};
