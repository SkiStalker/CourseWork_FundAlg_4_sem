#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "Essence.h"
#include "Content.h"


class Cargo
{
public:
	Cargo();
	Cargo(const int & ID, const std::string& name, const Essence& sender,
 const Essence& receiver,
		const int& ownCost, const std::vector<Content>& contents);

	const int& getID() const;
	void setID(const int& ID);

	const std::string getName() const;
	void setName(const std::string& name);

	const Essence& getSender() const;
	void setSender(const Essence& sender);

	const Essence& getReceiver() const;
	void setReceiver(const Essence& reciever);

	const std::vector<Content>& getContent() const;

	void addContent(const Content& content);

	std::string print() const;


	friend std::istream& operator >> (std::istream& stream, Cargo& obj);
	friend std::ostream& operator << (std::ostream& stream, const Cargo& obj);
private:
	int ID;
	std::string name;
	Essence sender;
	Essence receiver;
	int ownCost;
	std::vector<Content> contents;
};
