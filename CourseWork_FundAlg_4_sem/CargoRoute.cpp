#include "CargoRoute.h"

std::istream& operator>>(std::istream& stream, CargoRoute& obj)
{
	stream >> obj.cargo;
	int sz = 0;
	stream >> sz;
	for (int i = 0; i < sz; i++)
	{
		RoutePoint point;
		stream >> point;
		point.setCargo(&obj.cargo);
		obj.routePoints.push_back(point);
	}

	obj.curPoint = &obj.routePoints.front();
	return stream;
}

std::ostream& operator<<(std::ostream& stream, CargoRoute& obj)
{
	stream << obj.cargo;
	int sz = obj.routePoints.size();
	stream << sz;
	stream << " ";
	for (auto& point : obj.routePoints)
	{
		stream << point;
	}
	return stream;
}

const Cargo& CargoRoute::getCargo() const
{
	return cargo;
}

void CargoRoute::setCargo(const Cargo& cargo)
{
	this->cargo = cargo;
}

const RoutePoint& CargoRoute::getStartPoint() const
{
	return routePoints.front();
}

const RoutePoint& CargoRoute::getEndPoint() const
{
	return routePoints.back();
}


const RoutePoint& CargoRoute::getCurrentPoint() const
{
	return *curPoint;
}

void CargoRoute::setCurrentPoint(const RoutePoint& curPoint)
{
	*this->curPoint = curPoint;
}

void CargoRoute::addRoutePoint(const RoutePoint& routePoint)
{
	if (this->routePoints.empty())
	{
		routePoints.push_back(routePoint);
		curPoint = &routePoints.front();
	}
	else
	{
		RoutePoint& lastPoint = this->routePoints.back();
		if (routePoint.getSenderPointID() != lastPoint.getID())
		{
			throw std::exception();
			// TODO : invalid route points relations
		}
		else
		{
			lastPoint.setReceiverPointID(routePoint.getID());
			routePoints.push_back(routePoint);
		}
	}
}

const std::vector<RoutePoint>& CargoRoute::getRoutePoints() const
{
	return routePoints;
}
