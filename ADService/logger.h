#pragma once
#include <qobject.h>
#include <qdatetime.h>
class Logger : public QObject
{
	Q_OBJECT
	bool _timeStamp;
	QString _str;
public:
	explicit Logger(bool timeStamp = true, QObject* parent = nullptr);
	QString getLog() const;
public slots:
	void log(const QString& msg,bool timeStamp=true);
signals:
	void logged(const QString& msg);

};
class StaticLogger :public QObject
{
	//Q_OBJECT
	static QString _str;
	static bool _timeStamp;
public:
	static QString getLog();
	static void setTimeStamp(bool);
//public slots:
    static void log(const std::string &);
//signals:
	static void logged(const QString&);
};
