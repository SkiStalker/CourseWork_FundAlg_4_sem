#include "LogisticsÑompany.h"

LogisticsÑompany::LogisticsÑompany(DataBaseType tp): dataBase(nullptr)
{
    this->tp = tp;
    switch (tp)
    {
    case LogisticsÑompany::DataBaseType::AVLTree:
        dataBase = new DateBaseByAVLTree();
        break;
    case LogisticsÑompany::DataBaseType::Map:
        dataBase = new DateBaseByMap();
        break;
    default:
        break;
    }
}

LogisticsÑompany::LogisticsÑompany(const LogisticsÑompany& obj)
{
    switch (obj.tp)
    {
    case LogisticsÑompany::DataBaseType::AVLTree:
        dataBase = new DateBaseByAVLTree();
        break;
    case LogisticsÑompany::DataBaseType::Map:
        dataBase = new DateBaseByMap();
        break;
    default:
        break;
    }
}

LogisticsÑompany& LogisticsÑompany::operator=(const LogisticsÑompany& obj)
{
    switch (obj.tp)
    {
    case LogisticsÑompany::DataBaseType::AVLTree:
        dataBase = new DateBaseByAVLTree();
        break;
    case LogisticsÑompany::DataBaseType::Map:
        dataBase = new DateBaseByMap();
        break;
    default:
        break;
    }
    return *this;
}

LogisticsÑompany::~LogisticsÑompany()
{
}

void LogisticsÑompany::loadDataFromFile(const std::string path)
{
    dataBase->assignStorage(path);
}

void LogisticsÑompany::addCargoRoute(const CargoRoute& cargoRoute)
{
    dataBase->appendEntity(cargoRoute);
}

void LogisticsÑompany::deleteCargoRoute(const CargoRoute& cargoRoute)
{
    dataBase->deleteEntity(cargoRoute);
}

void LogisticsÑompany::changeCargoRoute(const CargoRoute& cargoRoute)
{
    dataBase->changeEntity(cargoRoute);
}

const Cargo& LogisticsÑompany::findCargoByID(const int& ID)
{
    return dataBase->findEntityByID(ID).getCargo();
}

const vector<const Cargo*> LogisticsÑompany::findCargoBySenderName(const std::string& senderName)
{
    CargoRoute tmp;
    Cargo ctmp;
    ctmp.setSender(Essence(senderName));
    tmp.setCargo(ctmp);
    auto preRes = dataBase->findEntities(tmp, [](const CargoRoute& left, const CargoRoute& right) {return left.getCargo().getSender().getName()
        == right.getCargo().getSender().getName(); });

    vector<const Cargo*> result;
    for (auto obj : preRes)
    {
        result.push_back(&obj->getCargo());
    }
    return result;
}

const vector<const Cargo*> LogisticsÑompany::findCargoByReceiverName(const std::string& receiverName)
{
    CargoRoute tmp;
    Cargo ctmp;
    ctmp.setReceiver(Essence(receiverName));
    tmp.setCargo(ctmp);
    auto preRes = dataBase->findEntities(tmp, [](const CargoRoute& left, const CargoRoute& right) { return left.getCargo().getReceiver().getName()
        == right.getCargo().getReceiver().getName(); });

    vector<const Cargo*> result;
    for (auto obj : preRes)
    {
        result.push_back(&obj->getCargo());
    }
    return result;
}

const vector<const Cargo*> LogisticsÑompany::findCargoByRoutePointID(const int& routePointID)
{
    CargoRoute tmp;
    RoutePoint rtmp;
    rtmp.setID(routePointID);
    tmp.addRoutePoint(rtmp);
    auto preRes = dataBase->findEntities(tmp, [](const CargoRoute& left, const CargoRoute& right) 
        {
            for(auto& point : left.getRoutePoints())
                if (point.getID() == right.getStartPoint().getID())
                {
                    return true;
                }
            return false;
        });

    vector<const Cargo*> result;
    for (auto obj : preRes)
    {
        result.push_back(&obj->getCargo());
    }
    return result;
}
