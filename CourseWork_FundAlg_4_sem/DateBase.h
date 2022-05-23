#pragma once
#include <string>
#include <vector>
#include <functional>
#include <ctype.h>
#include "CargoRoute.h"

class DateBase
{
public:
	DateBase()
	{
	}

	virtual ~DateBase()
	{
	}

	virtual bool assignStorage(const std::string& dbPath) = 0;
	virtual void clearStorage() = 0;
	virtual void saveStorage() = 0;

	virtual CargoRoute& findEntityByID(const int& ID) = 0;
	virtual std::vector<CargoRoute*> findEntities(const CargoRoute& templateEntity,
		std::function<bool(const CargoRoute&, const CargoRoute&)>) = 0;
	virtual void appendEntity(const CargoRoute& entity) = 0;
	virtual void changeEntity(const CargoRoute& entity) = 0;
	virtual void deleteEntity(const CargoRoute& entity) = 0;

protected:
	std::string dbPath;
};

