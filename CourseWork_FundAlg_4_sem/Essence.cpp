#include "Essence.h"

Essence::Essence() : Essence("")
{
}

Essence::Essence(const std::string& name) : name(name)
{
}

const std::string& Essence::getName() const
{
	return name;
}

void Essence::setName(const std::string& name)
{
	this->name = name;
}

std::istream& operator>>(std::istream& stream, Essence& obj)
{
	stream >> obj.name;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Essence& obj)
{
	stream << obj.name;
	stream << " ";
	return stream;
}
