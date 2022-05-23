#include "DefaultDataGenerator.h"

void DefaultDataGenerator::generate(const std::string path, int count)
{
	std::ofstream out(path, std::ofstream::binary);
	if (!out.is_open())
	{
		throw std::exception();
		// TODO : can not open file exception
	}

	int cnt = 0;
	while (cnt < count)
	{
		cnt += (rand() + rand());
	}

	if (cnt > count)
	{
		cnt = count;
	}

	for (int i = 0; i < cnt; i++)
	{
		CargoRoute newCargoRoute;

		// Create new cargo
		Cargo newCargo;
		newCargo.setID(i + 1);
		newCargo.setName("Cargo_" + std::to_string(i));
		newCargo.setSender(Essence("Sender_" + std::to_string(i)));
		newCargo.setReceiver(Essence("Receiver_" + std::to_string(i)));
		newCargoRoute.setCargo(newCargo);


		// Create route points
		int cntRoutePoints = rand() % 15 + 2;
		for (int j = 0; j < cntRoutePoints; j++)
		{
			RoutePoint newRoutePoint;

			// Offset by count
			newRoutePoint.setID(cnt + j);


			newRoutePoint.setSendTime(time(0) + j);
			newRoutePoint.setRcvTime(time(0) + j + 5);

			if (j != 0)
			{
				newRoutePoint.setSenderPointID(cnt + j - 1);
			}

			if (j != (cntRoutePoints - 1))
			{
				newRoutePoint.setReceiverPointID(cnt + j + 1);
			}

			newCargoRoute.addRoutePoint(newRoutePoint);
		}

		out << newCargoRoute;
	}
}
