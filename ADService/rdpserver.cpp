#include "rdpserver.h"
RDServer::RDServer(const QString &hostname, QObject *parent)
	: QObject(parent)
	, ServersRep(hostname)
	, hServer(nullptr)
{
	LPSTR long_string = (LPSTR)hostname.toStdString().c_str();
	hServer = WTSOpenServerA(long_string);
	if (!hServer)
	{
		qDebug() <<"RDServer error: "<< GetLastError();
	}
}
RDServer::RDServer(const ServersRep* rep, QObject* parent)
	:QObject(parent)
	, ServersRep(*rep)
	,hServer(nullptr)
{
	QString hn = rep->_hostname;
	LPSTR long_string = (LPSTR)hn.toStdString().c_str();
	hServer = WTSOpenServerA(long_string);
	if (!hServer)
	{
		qDebug() << "RDServer error: " << GetLastError();
	}
	qDebug() << "RDServer opened";

}
bool RDServer::updateSessions() {
	_sessions.clear();
	WTS_SESSION_INFOA *pSessionInfo = NULL;
	DWORD count;
	if (!WTSEnumerateSessionsA(hServer, 0, 1, &pSessionInfo, &count)) {
		WTSFreeMemory(pSessionInfo);
		return 0;
	}
	QVector<RDsession> list;
	//for (size_t i = 0; i < count; i++)
	//{
	//	list.push_back(RDsession((ulong)(*res)++->SessionId));
	//}
	_sessions = list;
	WTSFreeMemory(pSessionInfo);
	return 1;

}
QVector<RDsession> RDServer::sessions() {
	return _sessions;
}
RDServer::~RDServer()
{
	WTSCloseServer(hServer);

}
