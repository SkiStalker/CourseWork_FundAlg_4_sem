#include "DateBaseByAvlTree.h"

DateBaseByAVLTree::DateBaseByAVLTree()
{
	storage = new AVLTree<int, CargoRoute*>(new DefaultComparator<int>());
}

DateBaseByAVLTree::~DateBaseByAVLTree()
{
	delete storage;
}

bool DateBaseByAVLTree::assignStorage(const std::string& dbPath)
{
	this->dbPath = dbPath;
	std::ifstream in(this->dbPath);

	if (!in.is_open())
		return false;

	while (!in.eof())
	{
		CargoRoute* newCargo = new CargoRoute();
		in >> *newCargo;
		(*storage) += {newCargo->getCargo().getID(), newCargo};
		while (std::isspace(in.peek()))
		{
			in.get();
		}
	}
	in.close();
	return true;
}

void DateBaseByAVLTree::clearStorage()
{
	storage->clearTree();
}

void DateBaseByAVLTree::saveStorage()
{
	std::ofstream out(dbPath);
	storage->infixTraversal([&out](const int&, CargoRoute* const& v, int)  { out << *v; });
	out.close();
}

std::vector<CargoRoute*> DateBaseByAVLTree::findEntities(const CargoRoute& templateEntity, std::function<bool(const CargoRoute&, const CargoRoute&)> compare)
{
	std::vector<CargoRoute*> objects;

	storage->infixTraversalIterative([&objects, &templateEntity, &compare](const int&, CargoRoute* const& v, int)
		{
			if (compare(*v, templateEntity))
				objects.push_back(v);
		});
	return objects;
}

void DateBaseByAVLTree::appendEntity(const CargoRoute& entity)
{
	(*storage) += {entity.getCargo().getID(), new CargoRoute(entity)};
}

void DateBaseByAVLTree::changeEntity(const CargoRoute& entity)
{
	*(*storage)[entity.getCargo().getID()] = entity;
}

void DateBaseByAVLTree::deleteEntity(const CargoRoute& entity)
{
	(*storage) -= {entity.getCargo().getID()};
}

CargoRoute& DateBaseByAVLTree::findEntityByID(const int& ID)
{
	return *(*storage)[ID];
}
