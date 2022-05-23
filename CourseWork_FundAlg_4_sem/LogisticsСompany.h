#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <string>

#include "CargoRoute.h"
#include "DateBase.h"
#include "DateBaseByAvlTree.h"
#include "DateBaseByMap.h"
#include "DefaultComparator.h"

class Logistics—ompany
{
public:
	enum class DataBaseType
	{
		None,
		AVLTree,
		Map
	};

	Logistics—ompany(DataBaseType tp);
	Logistics—ompany(const Logistics—ompany& obj);
	Logistics—ompany& operator=(const Logistics—ompany& obj);

	~Logistics—ompany();

	void loadDataFromFile(const std::string path);

	void addCargoRoute(const CargoRoute& cargoRoute);

	void deleteCargoRoute(const CargoRoute& cargoRoute);

	void changeCargoRoute(const CargoRoute& cargoRoute);

	const Cargo& findCargoByID(const int& ID);

	const vector<const Cargo*> findCargoBySenderName(const std::string& senderName);

	const vector<const Cargo*> findCargoByReceiverName(const std::string& receiverName);

	const vector<const Cargo*> findCargoByRoutePointID(const int& routePointID);

protected:
	DateBase* dataBase;
	DataBaseType tp = DataBaseType::None;
};
