#include "RoutePoint.h"

RoutePoint::RoutePoint() : RoutePoint(0, nullptr, 0, 0, 0, 0, TransportType::None)
{
}

RoutePoint::RoutePoint(const int& ID, const Cargo* curCargo, const int& senderPointID, const int& receiverPointID,
	time_t sendTime, time_t rcvTime, TransportType transportType) :
	ID(ID), curCargo(curCargo), senderPointID(senderPointID), receiverPointID(receiverPointID),
	sendTime(sendTime), rcvTime(rcvTime), transportType(transportType)
{
}

const int& RoutePoint::getID() const
{
	return ID;
}

void RoutePoint::setID(const int& ID)
{
	this->ID = ID;
}

const int& RoutePoint::getSenderPointID() const
{
	return this->senderPointID;
}

void RoutePoint::setSenderPointID(const int& senderPoint)
{
	this->senderPointID = senderPoint;
}

const int& RoutePoint::getReceiverPoint() const
{
	return receiverPointID;
}

void RoutePoint::setReceiverPointID(const int& receiverPoint)
{
	this->receiverPointID = receiverPoint;
}

const time_t RoutePoint::getSendTime() const
{
	return sendTime;
}

void RoutePoint::setSendTime(const time_t& sendTime)
{
	this->sendTime = sendTime;
}

const time_t RoutePoint::getRcvTime() const
{
	return rcvTime;
}

void RoutePoint::setRcvTime(const time_t& rcvTime)
{
	this->rcvTime = rcvTime;
}

const Cargo* RoutePoint::getCargo() const
{
	return curCargo;
}

void RoutePoint::setCargo(const Cargo* cargo)
{
	this->curCargo = cargo;
}

std::istream& operator>>(std::istream& stream, RoutePoint& obj)
{
	stream >> obj.ID;
	stream >> obj.sendTime;
	stream >> obj.rcvTime;
	stream >> obj.senderPointID;
	stream >> obj.receiverPointID;
	int tp = 0;
	stream >> tp;
	obj.transportType = (RoutePoint::TransportType)tp;
	obj.curCargo = nullptr;
	return stream;
}

std::ostream& operator<<(std::ostream& stream, RoutePoint& obj)
{
	stream << obj.ID;
	stream << " ";
	stream << obj.sendTime;
	stream << " ";
	stream << obj.rcvTime;
	stream << " ";
	stream << obj.senderPointID;
	stream << " ";
	stream << obj.receiverPointID;
	stream << " ";
	int tp = (int)obj.transportType;
	stream << tp;
	stream << " ";
	return stream;
}
