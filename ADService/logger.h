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
	void log(const QString& msg);
signals:
	void logged(const QString& msg);

};

