#include "qtldap.h"
QtLdapI::QtLdapI(QObject* parent/*=nullptr*/)
	:QObject(parent),
	pLdap(nullptr),
	curState(Announced)
{
}

int QtLdapI::handle_lres(ULONG _res, const char* msg)
{
	if (_res != LDAP_SUCCESS) {
		errorString = QString::fromWCharArray((wchar_t*)ldap_err2string(_res));
		errorString.push_front(msg);
		return 0;
	}
	return 1;
}
const QString& QtLdapI::error_string() { return errorString; }

//ULONG  QtLdapI::init(const QString& url, ULONG port)
//{
//	ULONG lres;
//	pLdap = nullptr;
//	pLdap = ldap_init((PWSTR)url.toStdWString().c_str(), port);
//	if (pLdap == nullptr) {
//		qCritical() << "ldap_init() error:";
//		return 0;
//	}
//	lres = ldap_connect(pLdap,connectionTime);
//	if (!handle_lres(lres, "ldap_connect() error: ")) return 0;
//	lres = ldap_set_option(pLdap, LDAP_OPT_PROTOCOL_VERSION, (int *)LDAP_VERSION3);
//	if (!handle_lres(lres, "ldap_set_oprion_error: ")) return 0;
//	isConnected = true;
//	return 1; //success
//}	
/*ULONG QtLdapI::close() {
	if (isConnected) {
		ULONG lres=ldap_unbind(pLdap);
		if (!handle_lres(lres, "ldap_unbid() error: "))
			return 0;
	}
	return 1;
}*/
int QtLdapI::close()
{
	if (pLdap == nullptr) return 1;
	if (!handle_lres(ldap_unbind(pLdap), "ldap_unbind() error: "))
		return 0;
	pLdap = nullptr;
	return 1;
}
QtLdapI::~QtLdapI() {}
QtLdap::QtLdap(QObject* parent/*=nullptr*/) :QtLdapI(parent) {}
int QtLdap::init(const QString& url, ULONG port /*= LDAP_PORT*/)
{
	if (curState != Announced)
		close();
	pLdap = nullptr;
	PWSTR wUrl = url == "" ? nullptr : (PWSTR)url.toStdWString().c_str();
	pLdap = ldap_initW(wUrl, port);
	if (pLdap == nullptr)
	{
		errorString = "ldap_init() error.";
		return 0;
	}
	curState = Initialized;
	return 1;


}
int QtLdap::bind(const QString& dn, const QString& passw, BindAuth authMech)
{
	PWSTR wDn = dn == "" ? nullptr : (PWSTR)dn.toStdWString().c_str();
	PWSTR wPassw = passw == "" ? nullptr : (PWSTR)dn.toStdWString().c_str();
	if (!handle_lres(ldap_bind_sW(pLdap, wDn, wPassw, authMech), "ldap_simple_bind() error: "))
		return 0;
	curState = Binded;
	return 1;
}

QtLdap::~QtLdap()
{
	close();
}