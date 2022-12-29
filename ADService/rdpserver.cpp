#include "rdpserver.h"
RDServer::RDServer(const QString &hostname, QObject *parent)
	: QObject(parent)
	, ServerConfig(hostname)
	, hServer(nullptr)
{
	hServer = WTSOpenServerW(const_cast<wchar_t*>(hostname.toStdWString().c_str()));
	if (!hServer)
	{
		staticLogger::instance()->log("RDServer error: " + QString::number(GetLastError()));
	}
}
RDsession::RDsession(ulong id, const QString& station,const QString& user,
	const RDState & state, const QString& server, QObject* parent)
	:QObject(parent),
	_id(id),
	_station(station),
	_state(state),
	_user(user),
	_server(server)
{}
RDServer::RDServer(const ServerConfig* rep, QObject* parent)
	:QObject(parent)
	, ServerConfig(*rep)
	,hServer(nullptr)
{
	hServer = WTSOpenServerW(const_cast<wchar_t*>(rep->hostname().toStdWString().c_str()));
	if (!hServer)
	{
		staticLogger::instance()->log("RDServer error: " + QString::number(GetLastError()));
	}

}
bool RDServer::updateSessions() {
	_sessions.clear();
	WTS_SESSION_INFOW *pSessionInfo = NULL;
	DWORD count;
	if (!WTSEnumerateSessionsW(hServer, 0, 1, &pSessionInfo, &count)) {
		WTSFreeMemory(pSessionInfo);
		staticLogger::instance()->log("RDServer enumerate error: " + QString::number(GetLastError()));
		return 0;
	}
	QList<RDsession*> list;
	QString username;
	for (size_t i = 0; i < count; i++)
	{
		LPWSTR pwUser = nullptr;
		DWORD size=0;
		if (!WTSQuerySessionInformationW(hServer, pSessionInfo->SessionId, WTS_INFO_CLASS::WTSUserName, &pwUser, &size))
		{
			username = "error";
			staticLogger::instance()->log("RDServer getting user error: " + QString::number(GetLastError()));
		}
		else
			username = QString::fromWCharArray(pwUser,(ulong)size/sizeof(*pwUser));
		list.push_back(new RDsession((ulong)pSessionInfo++->SessionId,
			QString::fromWCharArray(pSessionInfo->pWinStationName),
			username,
			(RDsession::RDState)pSessionInfo->State,hostname(), this));
	}
	_sessions = list;
	//WTSFreeMemory(pSessionInfo);
	return 1;

}
QList<RDsession*> RDServer::sessions() const{
	return _sessions;
}
RDServer::~RDServer()
{
	WTSCloseServer(hServer);

}
