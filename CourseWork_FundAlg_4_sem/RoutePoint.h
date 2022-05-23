#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>

#include "Cargo.h"


class RoutePoint
{
public:
	enum class TransportType
	{
		None,
		Automotive,
		Railway,
		Marine,
		Aviation
	};

	RoutePoint();
	RoutePoint(const int& ID, const Cargo* curCargo, const int& senderPointID, const int& receiverPointID,
		time_t sendTime, time_t rcvTime, TransportType transportType);

	const int& getID() const;
	void setID(const int& ID);

	const int& getSenderPointID() const;
	void setSenderPointID(const int& senderPoint);

	const int& getReceiverPoint() const;
	void setReceiverPointID(const int& receiverPoint);

	const time_t getSendTime() const;
	void setSendTime(const time_t& sendTime);

	const time_t getRcvTime() const;
	void setRcvTime(const time_t& rcvTime);

	const Cargo* getCargo() const;

	void setCargo(const Cargo* cargo);


	friend std::istream& operator >> (std::istream& stream, RoutePoint& obj);
	friend std::ostream& operator << (std::ostream& stream, RoutePoint& obj);

private:
	int ID;
	const Cargo* curCargo;
	int senderPointID;
	int receiverPointID;
	time_t sendTime;
	time_t rcvTime;
	TransportType transportType;
};

