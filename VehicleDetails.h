#pragma once
#include"showRoom.h"

#include<iostream>
#include<string>
using namespace std;

class vehicle:public showRoom
{
private:

    string type;
    int model;
    string registrationNumber;  //License Plate
    int enginePowerInCC;

public:

    vehicle() { type = "N/A"; model = 0; registrationNumber = "N/A"; enginePowerInCC = 0; }

    void setVehicleType(string vehicletype) { type = vehicletype; }

    void setVehicleModel(int Model) { model = Model; }

    void setVehicleRegNo(string regNo) { registrationNumber = regNo; }

    void setEnginePower(int power) { enginePowerInCC = power; }

    string getVehicleType() { return type; }

    string getVehicleRegNo() { return registrationNumber; }

    int getVehicleModel() { return model; }

    int get_Vehicle_Engine_Power() { return enginePowerInCC; }
   
};
