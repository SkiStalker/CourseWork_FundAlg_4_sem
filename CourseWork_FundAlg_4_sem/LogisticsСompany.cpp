#include "Logistics�ompany.h"

Logistics�ompany::Logistics�ompany(DataBaseType tp): dataBase(nullptr)
{
    this->tp = tp;
    switch (tp)
    {
    case Logistics�ompany::DataBaseType::AVLTree:
        dataBase = new DateBaseByAVLTree();
        break;
    case Logistics�ompany::DataBaseType::Map:
        dataBase = new DateBaseByMap();
        break;
    default:
        break;
    }
}

Logistics�ompany::Logistics�ompany(const Logistics�ompany& obj)
{
    switch (obj.tp)
    {
    case Logistics�ompany::DataBaseType::AVLTree:
        dataBase = new DateBaseByAVLTree();
        break;
    case Logistics�ompany::DataBaseType::Map:
        dataBase = new DateBaseByMap();
        break;
    default:
        break;
    }
}

Logistics�ompany& Logistics�ompany::operator=(const Logistics�ompany& obj)
{
    switch (obj.tp)
    {
    case Logistics�ompany::DataBaseType::AVLTree:
        dataBase = new DateBaseByAVLTree();
        break;
    case Logistics�ompany::DataBaseType::Map:
        dataBase = new DateBaseByMap();
        break;
    default:
        break;
    }
    return *this;
}

Logistics�ompany::~Logistics�ompany()
{
}

void Logistics�ompany::loadDataFromFile(const std::string path)
{
    dataBase->assignStorage(path);
}

void Logistics�ompany::addCargoRoute(const CargoRoute& cargoRoute)
{
    dataBase->appendEntity(cargoRoute);
}

void Logistics�ompany::deleteCargoRoute(const CargoRoute& cargoRoute)
{
    dataBase->deleteEntity(cargoRoute);
}

void Logistics�ompany::changeCargoRoute(const CargoRoute& cargoRoute)
{
    dataBase->changeEntity(cargoRoute);
}

const Cargo& Logistics�ompany::findCargoByID(const int& ID)
{
    return dataBase->findEntityByID(ID).getCargo();
}

const vector<const Cargo*> Logistics�ompany::findCargoBySenderName(const std::string& senderName)
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

const vector<const Cargo*> Logistics�ompany::findCargoByReceiverName(const std::string& receiverName)
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

const vector<const Cargo*> Logistics�ompany::findCargoByRoutePointID(const int& routePointID)
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
