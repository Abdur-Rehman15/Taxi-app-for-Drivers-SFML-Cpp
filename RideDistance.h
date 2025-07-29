#pragma once
#include<iostream>
#include"RideLocation.h"
using namespace std;

class ride 
{
private:

    float totalDistanceTraveled;
    float actualDistanceTraveledInNormalSetting;
    float actualDistanceTraveledInSpecialSetting; // distance traveled in traffic, rough path, etc

    location* currentlocation;
    location* destination;

public:

    ride() { totalDistanceTraveled = 0.0; actualDistanceTraveledInNormalSetting = 0.0; actualDistanceTraveledInSpecialSetting = 0.0; currentlocation = NULL; destination = NULL; };

    void calculate_Total_Distance_Traveled() { totalDistanceTraveled = actualDistanceTraveledInNormalSetting + actualDistanceTraveledInSpecialSetting; };

    void calculatePathTraveled(int Traffic,location *currentLocation)
    {
        if (currentLocation->getLatitude() == Traffic)
            actualDistanceTraveledInSpecialSetting += 0.25;
        else
            actualDistanceTraveledInNormalSetting += 0.25;

    }; // The main function in the program. Updates variables based on the path taken by the user. Then invokes functions of the fare class to calculate the fare. Then stores all of this in the object of class trip. Ultimately, this gets stored in the travelHistory of the driver which is an array of objects of class trip and is a member of the class account which in turn is the parent class of class driver. Also involves file handling.
   
    float getTotalDistanceTraveled() { return totalDistanceTraveled; }

    float getNormalDistance() { return actualDistanceTraveledInNormalSetting; }

    float getTrafficDistance() { return actualDistanceTraveledInSpecialSetting; }

    void setTotalDistance(float distance) { actualDistanceTraveledInNormalSetting = distance; actualDistanceTraveledInSpecialSetting = distance; }

    ~ride() { delete currentlocation; delete destination; };
};