#pragma once
#include <map>
#include <fstream>
#include <exception>

#include "DateBase.h"

class DateBaseByMap : public DateBase
{
public:
	DateBaseByMap();
	~DateBaseByMap() override;

	bool assignStorage(const std::string& dbPath) override;
	void clearStorage() override;
	void saveStorage() override;

	std::vector<CargoRoute*> findEntities(const CargoRoute& templateEntity,
		std::function<bool(const CargoRoute& templateEntity, const CargoRoute&)> compare) override;

	CargoRoute& findEntityByID(const int& ID) override;

	void appendEntity(const CargoRoute& entity) override;
	void changeEntity(const CargoRoute& entity) override;
	void deleteEntity(const CargoRoute& entity) override;


protected:
	std::map<int, CargoRoute*>* storage;
};
