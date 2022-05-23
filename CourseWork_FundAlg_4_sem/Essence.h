#pragma once
#include <string>
#include <iostream>


class Essence
{
public:
	Essence();
	Essence(const std::string& name);
	const std::string& getName() const;
	void setName(const std::string& name);


	friend std::istream& operator >> (std::istream& stream, Essence& obj);
	friend std::ostream& operator << (std::ostream& stream, const Essence& obj);
private:
	std::string name;
};

