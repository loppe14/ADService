#include "winqtldap.h"
WinQtLdap::WinQtLdap(QObject* parent /*=nullptr*/) :
	QtLdap(parent),
	_pLdap(NULL)
{
}

int WinQtLdap::init(const QString& url, ulong port)
{
	PSTR pUrl = url == "" ? NULL : (PSTR)url.toStdString().c_str();
	_pLdap = ldap_initA(pUrl, port);
	if (_pLdap == nullptr)
	{
		errorString = "ldap_init() error.";
		return 0;
	}
	return 1;
}
int WinQtLdap::sasl_bind(const QString& dn, const QString& passw)
{
	PSTR pDn = dn == "" ? NULL : (PSTR)dn.toStdString().c_str();
	PSTR wPassw = passw == "" ? NULL : (PSTR)dn.toStdString().c_str();
	QString str = "GSSAPI";
	BERVAL ber;
	BERVAL* ser = NULL;
	ber.bv_val = (PCHAR)str.toStdWString().c_str();
	ber.bv_len = sizeof(str.toStdWString().c_str());
	if (!handle_res(ldap_sasl_bind_sA(_pLdap, pDn, (PSTR)str.toStdString().c_str(), &ber, NULL, NULL,&ser), "ldap_sasl_bind() error: "))
	{
		return 0;
	}
	return 1;
}
int WinQtLdap::handle_res(ULONG _res, const char* msg)
{
	if (_res != LDAP_SUCCESS) {
		errorString = QString::fromWCharArray((wchar_t*)ldap_err2string(_res));
		errorString.push_front(msg);
		return 0;
	}
	return 1;
}
int WinQtLdap::bind(const QString& dn, const QString& passw, LdapConfig::BindAuth authMech)
{
	PSTR pDn = dn == "" ? NULL : (PSTR)dn.toStdString().c_str();
	PSTR pPassw = passw == "" ? NULL : (PSTR)dn.toStdString().c_str();
	switch (authMech)
	{
	case LdapConfig::SimpleBind:
		if (!handle_res(ldap_bind_sA(_pLdap, pDn, pPassw, LDAP_AUTH_SIMPLE), "ldap_simple_bind() error: "))
				return 0;
		break;
	case LdapConfig::DigestBind:
		if (!handle_res(ldap_bind_sA(_pLdap, pDn, pPassw, LDAP_AUTH_DIGEST), "ldap_simple_bind() error: "))
			return 0;
		break;

	}
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
int WinQtLdap::search(const QString& baseDN, const QString& filter,QLdapEntryList* searchResults)
{
    LDAPMessage* searchResultMsg;

	if (!handle_res(ldap_search_ext_sA(_pLdap,
		(char*)baseDN.toStdString().c_str(),
		LDAP_SCOPE_SUBTREE,
		(char*)filter.toStdString().c_str(),
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
		errorString = "ldap_count_entries() error.";
		return 0;
	}
    qDebug() << "Search results count = " << eCount;

    ULONG rCount = ldap_count_references(_pLdap, searchResultMsg);
	if (rCount == -1) {
		errorString = "ldap_count_references() error.";
		return 0;
	}
    qDebug() << "Search results ref = " << rCount;


    LDAPMessage* pMsg;

    QLdapEntryList results;
	LDAPMessage* entry = ldap_first_entry(_pLdap, searchResultMsg);
	while ((entry))
	{
		QLdapEntry	   qlEntry;
		char *dn = ldap_get_dnA(_pLdap, entry);
		qlEntry["dn"] = dn;
		ldap_memfreeA(dn);
		BerElement* pBer = NULL;
		char* attribute = ldap_first_attributeA(_pLdap, entry, &pBer);
		while ((attribute))
		{
			berval **vals = ldap_get_values_lenA(_pLdap, entry, attribute);
			for (int pos = 0; pos < ldap_count_values_len(vals); pos++)
				qlEntry[attribute] = vals[pos]->bv_val;
			ldap_value_free_len(vals);
			attribute = ldap_next_attributeA(_pLdap, entry, pBer);
		};
		ldap_memfreeA(attribute);
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
