#include "Content.h"

Content::Content() : Content("", 0.0)
{
}

Content::Content(const std::string& name, const double& weight) : name(name), weight(weight)
{
}

const std::string& Content::getName() const
{
	return name;
}

void Content::setName(const std::string& name)
{
	this->name = name;
}

const double Content::getWeight() const
{
	return weight;
}

void Content::setWeight(const double& weight)
{
	this->weight = weight;
}

std::istream& operator>>(std::istream& stream, Content& obj)
{
	stream >> obj.name;
	stream >> obj.weight;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Content& obj)
{
	stream << obj.name;
	stream << " ";
	stream << obj.weight;
	stream << " ";
	return stream;
}
