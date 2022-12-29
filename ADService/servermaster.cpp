#include "servermaster.h"

ServerRepMaster::ServerRepMaster()
{}

ServerRepMaster::~ServerRepMaster()
{}
std::unique_ptr<ServerRep> ServerRepMaster::getRep(ReceivingMethod method)
{
	if (method == Unknown)
	{
		auto cMenu = std::make_unique<ChoiceRceivingMethod>();
		if (cMenu->exec() == QDialog::Rejected || cMenu->getMethod() == NotSelected
			|| cMenu->getMethod() == Unknown)
			return uptrFactory<ServerRep>::create(ServerRep::Invalid);
		else method = cMenu->getMethod();
	}
	if (method == LDAPMethod)
	{
		std::unique_ptr<LdapConfigMenu> lMenu = std::make_unique<LdapConfigMenu>();
		if (lMenu->exec() == QDialog::Accepted)
			return uptrFactory<QtLdap>::create(lMenu->getLdapConfig());
		return uptrFactory<ServerRep>::create(ServerRep::Invalid);
	}
	switch (method)
	{
	case ServerRepMaster::Localhost:
		return uptrFactory<LocalHostServ>::create();
		break;
	case ServerRepMaster::WTSMethod:
		return uptrFactory<WTS>::create();
		break;
	case ServerRepMaster::UserInput:
		return uptrFactory<UserServers>::create();
		break;
	default:
		return uptrFactory<ServerRep>::create(ServerRep::Invalid);
		break;
	}
}
