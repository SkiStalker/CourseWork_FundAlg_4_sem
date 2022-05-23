#include "DateBaseByMap.h"

DateBaseByMap::DateBaseByMap()
{
	storage = new std::map<int, CargoRoute*>();
}

DateBaseByMap::~DateBaseByMap()
{
	delete storage;
}


bool DateBaseByMap::assignStorage(const std::string& dbPath)
{
	this->dbPath = dbPath;
	std::ifstream in(this->dbPath);

	if (!in.is_open())
		return false;

	while (!in.eof())
	{
		CargoRoute* newCargo = new CargoRoute();
		in >> *newCargo;
		storage->emplace(newCargo->getCargo().getID(), newCargo);
		while (isspace(in.peek()))
		{
			in.get();
		}
	}
	in.close();
	return true;
}

void DateBaseByMap::clearStorage()
{
	storage->clear();
}

void DateBaseByMap::saveStorage()
{
	std::ofstream out(dbPath);
	for (auto obj : *storage)
	{
		out << *obj.second;
	}
	out.close();
}

std::vector<CargoRoute*> DateBaseByMap::findEntities(const CargoRoute& templateEntity, std::function<bool(const CargoRoute&, const CargoRoute&)> compare)
{
	std::vector<CargoRoute*> result;

	for (auto obj : *storage)
	{
		if (compare(*obj.second, templateEntity))
		{
			result.push_back(obj.second);
		}
	}
	return result;
}

void DateBaseByMap::appendEntity(const CargoRoute& entity)
{
	storage->emplace(entity.getCargo().getID(), new CargoRoute(entity));
}

void DateBaseByMap::changeEntity(const CargoRoute& entity)
{
	auto res = storage->find(entity.getCargo().getID());
	if (res == storage->end())
	{
		throw std::exception();
		// TODO : Not exist entity exception
	}
	else
	{
		*res->second = entity;
	}
}

void DateBaseByMap::deleteEntity(const CargoRoute& entity)
{
	auto res = storage->find(entity.getCargo().getID());
	if (res == storage->end())
	{
		throw std::exception();
		// TODO : Not exist entity exception
	}
	else
	{
		storage->erase(res);
	}
}

CargoRoute& DateBaseByMap::findEntityByID(const int& ID)
{
	return *(*storage)[ID];
}