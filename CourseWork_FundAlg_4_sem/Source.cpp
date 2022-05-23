#include <iostream>
#include "DefaultDataGenerator.h"
#include "LogisticsÑompany.h"

using namespace std;

int main()
{
	DefaultDataGenerator generator;
	generator.generate("data.dat", 100);

	cout << "Data generated" << endl;
	LogisticsÑompany logcompany(LogisticsÑompany::DataBaseType::AVLTree);

	logcompany.loadDataFromFile("data.dat");
	cout << "Data loaded" << endl;

	cout << "1 : Find cargo by ID" << endl <<
		"2 : Find cargo by sender name" << endl <<
		"3 : Find cargo by receiver name" << endl <<
		"4 : Find cargo by route point ID" << endl <<
		"5 : Exit" << endl;

	string buf;
	bool working = true;
	while (working)
	{
		cout << "Enter operation number : ";
		getline(cin,buf);
		if (buf == "1")
		{
			cout << "Enter ID : ";
			string strID;
			getline(cin,strID);
			int ID = stoi(strID);
			if (!ID)
			{
				cout << "Incorrect input" << endl;
				continue;
			}
			else
			{
				try
				{
					cout << logcompany.findCargoByID(ID).print() << endl;
				}
				catch (NETreeException e)
				{
					cout << e.what() << endl;
				}
			}
		}
		else if (buf == "2")
		{
			cout << "Enter sender name : ";
			string name;
			getline(cin,name);
			for (auto cargo : logcompany.findCargoBySenderName(name))
			{
				cout << cargo->print() << endl;
			}
		}
		else if (buf == "3")
		{
			cout << "Enter receiver name : ";
			string name;
			getline(cin, name);
			for (auto cargo : logcompany.findCargoByReceiverName(name))
			{
				cout << cargo->print() << endl;
			}
		}
		else if (buf == "4")
		{
			cout << "Enter route point ID : ";
			string strID;
			getline(cin, strID);
			int ID = stoi(strID);
			if (!ID)
			{
				cout << "Incorrect input" << endl;
				continue;
			}
			else
			{
				for (auto cargo : logcompany.findCargoByRoutePointID(ID))
				{
					cout << cargo->print() << endl;
				}
			}
		}
		else if (buf == "5")
		{
			working = false;
		}
		else
		{
			cout << "Incorrect input" << endl;
		}
	}
	return 0;
}