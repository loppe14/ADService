//#include "RDSessInterface.h"
//
//RDSessInterface::RDSessInterface()
//{}
//RDSessList::~RDSessList()
//{
//	while (!isEmpty())
//		delete takeFirst();
//}
//int RDSessInterface::enumerateSessions(RDSessList * list)
//{
//	list->clear();
//	WTS_SESSION_INFOW* pSessionInfo = NULL;
//	DWORD count;
//	if (!WTSEnumerateSessionsW(hServer, 0, 1, &pSessionInfo, &count)) {
//		WTSFreeMemory(pSessionInfo);
//		staticLogger::instance()->log("RDServer enumerate error: " + QString::number(GetLastError()));
//		return 0;
//	}
//	QList<RDsession*> list;
//	QString username;
//	for (size_t i = 0; i < count; i++)
//	{
//		LPWSTR pwUser = nullptr;
//		DWORD size = 0;
//		if (!WTSQuerySessionInformationW(hServer, pSessionInfo->SessionId, WTS_INFO_CLASS::WTSUserName, &pwUser, &size))
//		{
//			username = "error";
//			staticLogger::instance()->log("RDServer getting user error: " + QString::number(GetLastError()));
//		}
//		else
//			username = QString::fromWCharArray(pwUser, (ulong)size / sizeof(*pwUser));
//		list.push_back(new RDsession((ulong)pSessionInfo++->SessionId,
//			QString::fromWCharArray(pSessionInfo->pWinStationName),
//			username,
//			(RDsession::RDState)pSessionInfo->State, _hostname, this));
//	}
//	list = list;
//	//WTSFreeMemory(pSessionInfo);
//	return 1;
//}
//RDSessInterface::~RDSessInterface()
//{}
