#include "Cargo.h"

Cargo::Cargo() : Cargo(0, "", Essence(), Essence(), 0, {})
{
}

Cargo::Cargo(const int & ID, const std::string& name,
 const Essence& sender,
    const Essence& receiver, const int& ownCost, const std::vector<Content>& contents):
    ID(ID), name(name), sender(sender), receiver(receiver), ownCost(ownCost), contents(contents)
{

}

const int& Cargo::getID() const
{
    return ID;
}

void Cargo::setID(const int& ID)
{
    this->ID = ID;
}

const std::string Cargo::getName() const
{
    return name;
}

void Cargo::setName(const std::string& name)
{
    this->name = name;
}

const Essence& Cargo::getSender() const
{
    return sender;
}

void Cargo::setSender(const Essence& sender)
{
    this->sender = sender;
}

const Essence& Cargo::getReceiver() const
{
    return receiver;
}

void Cargo::setReceiver(const Essence& reciever)
{
    this->receiver = reciever;
}

const std::vector<Content>& Cargo::getContent() const
{
    return contents;
}

void Cargo::addContent(const Content& content)
{
    contents.push_back(content);
}

std::string Cargo::print() const
{
    std::stringstream str;
    str << "{ \"ID\" : " << ID <<
        ", \"name\" : " << name 
        << ", \"ownCost\" : " << ownCost <<
        ", \"receiver\" : " << receiver << 
        ", \"sender\" : " << sender <<
        ",\"contents\" : [";
    for (int i = 0; i < contents.size(); i++)
    {
        str << contents[i];
        if (i != contents.size() - 1)
        {
            str << ", ";
        }
    }
    str << "]}";
    return str.str();
}

std::istream& operator>>(std::istream& stream, Cargo& obj)
{
    stream >> obj.ID;
    stream >> obj.name;
    stream >> obj.ownCost;
    stream >> obj.receiver;
    stream >> obj.sender;

    int sz = 0;
    stream >> sz;

    for (int i = 0; i < sz; i++)
    {
        Content tmp;
        stream >> tmp;
        obj.contents.push_back(tmp);
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Cargo& obj)
{
    stream << obj.ID;
    stream << " ";
    stream << obj.name;
    stream << " ";
    stream << obj.ownCost;
    stream << " ";
    stream << obj.receiver;
    stream << obj.sender;
    int sz = obj.contents.size();
    stream << sz;
    stream << " ";
    for (auto& content : obj.contents)
    {
        stream << content;
    }
    return stream;
}
