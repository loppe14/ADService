#include "winqtldap.h"
WinQtLdap::WinQtLdap(QObject *parent /*=nullptr*/) : QtLdap(parent)
{
}

int WinQtLdap::init(const QString& url, ulong port)
{
	PWSTR wUrl = url == "" ? nullptr : (PWSTR)url.toStdWString().c_str();
	_pLdap = ldap_initW(wUrl, port);
	if (_pLdap == nullptr)
	{
		_errorString = "ldap_init() error.";
		return 0;
	}
	return 1;
}
int WinQtLdap::handle_res(ULONG _res, const char* msg)
{
	if (_res != LDAP_SUCCESS) {
		_errorString = QString::fromWCharArray((wchar_t*)ldap_err2string(_res));
		_errorString.push_front(msg);
		return 0;
	}
	return 1;
}
int WinQtLdap::bind(const QString& dn, const QString& passw, BindAuth authMech)
{
	PWSTR wDn = dn == "" ? nullptr : (PWSTR)dn.toStdWString().c_str();
	PWSTR wPassw = passw == "" ? nullptr : (PWSTR)dn.toStdWString().c_str();
	if (!handle_res(ldap_bind_sW(_pLdap, wDn, wPassw, authMech), "ldap_simple_bind() error: "))
		return 0;
	return 1;
}
int WinQtLdap::connect(uint connectsec, uint connectmsec)
{
	l_timeval t;
	t.tv_sec = connectsec;
	t.tv_usec = connectmsec;
	if(handle_res(ldap_connect(_pLdap,&t), "ldap_connect() error: "))
		return 0;
	return 1;

}
int WinQtLdap::unbind()
{

	if (_pLdap == nullptr) return 1;
	if (!handle_res(ldap_unbind(_pLdap), "ldap_unbind() error: "))
		return 0;
	_pLdap = nullptr;
	return 1;
}
WinQtLdap::~WinQtLdap()
{
	unbind();
}
