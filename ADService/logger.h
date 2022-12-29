#pragma once
#include <qobject.h>
#include <qdatetime.h>
#include "singletonHolder.h"
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
using StaticLogger = SingletonHolder<Logger>;
