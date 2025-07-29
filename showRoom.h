#pragma once
#include<iostream>
using namespace std;

class showRoom
{
private:

	string vehicleType;
	int No_of_vehicles;


public:

	showRoom(string vehicle = "N/A", int number = 0) { vehicleType = vehicle; No_of_vehicles = number; }

	virtual void setVehicleType(string vehicletype) = 0;

	~showRoom() { cout << "ShowRoom object destroyed.\n"; }

};
