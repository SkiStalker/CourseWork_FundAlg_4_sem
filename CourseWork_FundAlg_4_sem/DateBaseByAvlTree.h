#pragma once
#include <fstream>
#include <exception>

#include "DateBase.h"
#include "AVLTree.h"
#include "DefaultComparator.h"


class DateBaseByAVLTree : public DateBase
{
public:
	DateBaseByAVLTree();
	~DateBaseByAVLTree();

	bool assignStorage(const std::string& dbPath) override;
	void clearStorage() override;
	void saveStorage() override;

	std::vector<CargoRoute*> findEntities(const CargoRoute& templateEntity,
		std::function<bool(const CargoRoute& templateEntity, const CargoRoute&)> compare) override;

	void appendEntity(const CargoRoute& entity) override;
	void changeEntity(const CargoRoute& entity) override;
	void deleteEntity(const CargoRoute& entity) override;
	CargoRoute& findEntityByID(const int& ID) override;


protected:
	AVLTree<int, CargoRoute*>* storage;
};
