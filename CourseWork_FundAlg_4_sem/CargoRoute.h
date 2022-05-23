#pragma once
#include "RoutePoint.h"

#include <fstream>


class CargoRoute
{
public:
	friend std::istream& operator >> (std::istream& stream, CargoRoute& obj);
	friend std::ostream& operator << (std::ostream& stream, CargoRoute& obj);

	const Cargo& getCargo() const;
	void setCargo(const Cargo& cargo);

	const RoutePoint& getStartPoint() const;

	const RoutePoint& getEndPoint() const;

	const RoutePoint& getCurrentPoint() const;
	void setCurrentPoint(const RoutePoint& curPoint);

	void addRoutePoint(const RoutePoint& routePoint);

	const std::vector<RoutePoint>& getRoutePoints() const;

private:
	Cargo cargo;
	std::vector<RoutePoint> routePoints;
	RoutePoint* curPoint;
};

