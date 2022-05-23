#pragma once
#include <string>
#include <fstream>
#include "CargoRoute.h"

class DataGenerator
{
public:
	virtual ~DataGenerator();
	virtual void generate(const std::string path, int count) = 0;
};

