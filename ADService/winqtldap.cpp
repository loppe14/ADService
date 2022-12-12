#include "winqtldap.h"
WinQtLdap::WinQtLdap(QObject* parent /*=nullptr*/) :
	QtLdap(parent),
	_pLdap(nullptr)
{
}

int WinQtLdap::ldapInit(const QString& url, ulong port)
{
	PWSTR pUrl = url == "" ? NULL : (PWCHAR)(url.toStdWString().data());
	_pLdap = ldap_initW(pUrl, port);
	if (!_pLdap)
	{
		_errorString = "ldap_init() error.";
		return 0;
	}
	int ldap_ver = 3;
	if (!handle_res(ldap_set_optionW(_pLdap, LDAP_OPT_PROTOCOL_VERSION, &ldap_ver), "error while setting ldap version: "))
	{ 
		return 0;
	}
	return 1;
}
int WinQtLdap::sasl_bind(const QString& dn, const QString& passw)
{
	PWSTR pDn = dn == "" ? nullptr : (PWCHAR)dn.toStdWString().c_str();
	PWSTR wPassw = passw == "" ? nullptr : (PWCHAR)dn.toStdWString().c_str();
	QString str = "GSSAPI";
	BERVAL ber;
	BERVAL* ser = nullptr;
	ber.bv_val = (PCHAR)str.toStdWString().c_str();
	ber.bv_len = sizeof(str.toStdWString().c_str());

	if (!handle_res(ldap_sasl_bind_sW(_pLdap, pDn, const_cast<wchar_t*>(str.toStdWString().c_str()),
		&ber, nullptr, nullptr,&ser), "ldap_sasl_bind() error: "))
	{
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
int WinQtLdap::bind(const QString& dn, const QString& passw, LdapConfig::BindAuth authMech)
{

	PWSTR pDn    = PWCHAR(dn.toStdWString().data());
	PWSTR pPassw = PWCHAR(dn.toStdWString().data());
	if (dn == "")
	{
		pDn    =  NULL ;
		pPassw =  NULL ;
	}

	switch (authMech)
	{
	case LdapConfig::SimpleBind:
		if (!handle_res(ldap_simple_bindW(_pLdap, pDn, pPassw), "ldap_simple_bind() error: "))
			return 0;
		break;
	case LdapConfig::DigestBind:
		if (!pDn) 
		{
			qDebug() << "Binding as current user ";
			if (!handle_res(ldap_bind_sW(_pLdap, NULL, NULL, LDAP_AUTH_DIGEST),
				"ldap_digest_bind() error: "))
				return 0;
		}
		else
		{
			qDebug() << "Binding as another user ";
			_SEC_WINNT_AUTH_IDENTITY_W identity;
			identity.Domain = (unsigned short*)config->_hostname.toStdWString().data();
			identity.DomainLength = config->_hostname.size();//not including the terminating null character
			identity.Password = (unsigned short*)pPassw;
			identity.PasswordLength = passw.size();//not including the terminating null character
			identity.User = (unsigned short*)pDn;
			identity.UserLength = dn.size();
			identity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
			if (!handle_res(ldap_bind_sW(_pLdap, NULL, (PWCHAR)&identity, LDAP_AUTH_DIGEST), "ldap_digest_bind() error: "))
				return 0;
		}
		break;

	}
	return 1;
}
int WinQtLdap::connect(uint connectsec, uint connectmsec)
{
	l_timeval t;
	t.tv_sec = connectsec;
	t.tv_usec = connectmsec;
	if(!handle_res(ldap_connect(_pLdap,&t), "ldap_connect() error: "))
		return 0;
	WCHAR *out;
	if (!handle_res(ldap_get_optionW(_pLdap, LDAP_OPT_HOST_NAME,&out), "GetDomainNameError "))
	{
		return 0;
	}
	config->_hostname = QString::fromWCharArray(const_cast<const wchar_t *>(out));
	return 1;

}
int WinQtLdap::search(const QString& baseDN, const QString& filter,QLdapEntryList* searchResults)
{
    LDAPMessage* searchResultMsg = nullptr;

	if (!handle_res(ldap_search_ext_sW(_pLdap,
		(PWCHAR)(baseDN.toStdWString().data()),
		LDAP_SCOPE_SUBTREE,
		(PWCHAR)(filter.toStdWString().data()),
		nullptr,
		0,
		nullptr,
		nullptr,
		nullptr,
		LDAP_NO_LIMIT,
		&searchResultMsg
	), "ldap_search() error: ")) 
		return 0;

	ULONG eCount = ldap_count_entries(_pLdap, searchResultMsg);
	if (eCount == -1) {
		_errorString = "ldap_count_entries() error.";
		return 0;
	}
    qDebug() << "Search results count = " << eCount;

    ULONG rCount = ldap_count_references(_pLdap, searchResultMsg);
	if (rCount == -1) {
		_errorString = "ldap_count_references() error.";
		return 0;
	}
    qDebug() << "Search results ref = " << rCount;


    LDAPMessage* pMsg = nullptr;

    QLdapEntryList results;
	LDAPMessage* entry = ldap_first_entry(_pLdap, searchResultMsg);
	while ((entry))
	{
		QLdapEntry	   qlEntry;
		WCHAR *dn = ldap_get_dnW(_pLdap, entry);
		qlEntry["dn"] = QString::fromWCharArray(dn);
		ldap_memfreeW(dn);
		BerElement* pBer = nullptr;
		WCHAR* attribute = ldap_first_attributeW(_pLdap, entry, &pBer);
		while ((attribute))
		{
			berval **vals = ldap_get_values_lenW(_pLdap, entry, attribute);
			for (int pos = 0; pos < ldap_count_values_len(vals); pos++)
				qlEntry[QString::fromWCharArray(attribute)] = vals[pos]->bv_val;
			ldap_value_free_len(vals);
			attribute = ldap_next_attributeW(_pLdap, entry, pBer);
		};
		ldap_memfreeW(attribute);
		LDAPMessage * new_entry = ldap_next_entry(_pLdap, entry);
		ldap_msgfree(entry);
		entry = new_entry;
		results.push_back(qlEntry);
	};
	*searchResults = results;
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
