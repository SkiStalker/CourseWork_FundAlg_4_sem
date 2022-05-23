#pragma once
#include <exception>
#include <cstdlib>

#include "DataGenerator.h"

class DefaultDataGenerator : public DataGenerator
{
public:
	virtual void generate(const std::string path, int count) override;
};

