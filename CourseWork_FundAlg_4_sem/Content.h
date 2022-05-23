#pragma once
#include <string>
#include <iostream>

class Content
{
public:
	Content();
	Content(const std::string& name, const double& weight);
	const std::string& getName() const;
	void setName(const std::string& name);
	const double getWeight() const;
	void setWeight(const double& weight);

	friend std::istream& operator >> (std::istream& stream, Content& obj);
	friend std::ostream& operator << (std::ostream& stream, const Content& obj);

private:
	std::string name;
	double weight;
};

