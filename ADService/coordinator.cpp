#include "coordinator.h"
Coordinator::Coordinator(QObject *parent)
	: QObject(parent),
    _rdModel(newOpFactory<RDSessListModel>::create(this)),
	_sRep(nullptr),
    _window(nullptr)
{
}

void Coordinator::setAppWindow(AbstractAppWindow*w)
{
    _window = w;
    connect(w, &AbstractAppWindow::updateSess, this, &Coordinator::updateSessModel);
    connect(w, &AbstractAppWindow::switchServerReceivingMethod, this, &Coordinator::updateServerRep);
    _window->setModel(_rdModel);
}
int Coordinator::updateServerRep() {
    auto temp = ServerRepMaster::getRep();
    if (!temp || !temp->isValid())
        return 0;
    _sRep=std::move(temp);
    if (!_sRep->init())
    {
        StaticLogger::instance()->log("Error while initing server repository:\n"
            + _sRep->errorString());
        return 0;
    }
    return 1;
}
int Coordinator::updateSessModel() 
{
    if (!_sRep || _sRep->state() != ServerRep::Initialized)
        updateServerRep();
    if (!_sRep->isValid())
        return 0;
    auto tempList = uptrFactory<ServerList>::create();
    if (!_sRep->getServers(tempList.get()))
    {
        StaticLogger::instance()->log("Error while getting servers:\n"
            + _sRep->errorString());
        return 0;
    }
    _rdServers.clear();
    for (auto i : *tempList)
    {
        auto ps = newOpFactory<RDServer>::create(i->hostname());
        if (!ps->updateSessions())
        {
            StaticLogger::instance()->log("Error while getting sessions from "+ps->hostname() );
            continue;
        }
        ps->updateSessions();
        _rdModel->setSessionList(ps->sessions(), _rdModel->rowCount());
        _rdServers.insert(i->hostname(),std::move(ps));
    }
    return 1;
}
