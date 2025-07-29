#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "RideLocation.h"
#include "Fare.h"
#include "RideDistance.h"
using namespace std;

class trips:public fare
{ //[passenger name] [destination] [distance traveled] [profit]
private:
    string passengerName;
    int totalTrips;

    vector<string> tripsHistory;
    ride *r = NULL;
    location *destination = NULL;

public:
    trips(float ratings = 0.0, ride* r1 = nullptr,int total=0) : r(r1),totalTrips(total){}

    void setPassengerName(string name) { passengerName = name; }

    float getEarningsFromTheNewTrip() { return calculateFare(r); } //inherited

    float getProfitFromTheNewTrip() { return calculateProfit(r); } //inherited

    float getTotalDistanceTraveledInTheNewTrip() { return r->getTotalDistanceTraveled(); }

    string getPassengerName() { return passengerName; }

    void display(ride *r1) override
    {
        cout << "Total Trips: " << totalTrips << endl;
        cout << "Total Profit: " << calculateProfit(r1) << endl;
        cout << "Total Distance Travelled: " << r1->getTotalDistanceTraveled() << endl;
    }

    bool saveTripDetails(string driverName, ride* r, location* destination, fare* fareRecordOfTheNewTrip) //save theek horha he
    {
        // driverName passengerName destination distanceTraveled profit

        fstream tripDetails;
        tripDetails.open(driverName + ".txt", ios::out | ios::app);
        if (tripDetails.is_open())
        {
            tripDetails << passengerName << ","
                        << destination->getDestination() << "," 
                        << to_string(r->getTotalDistanceTraveled()) << ","
                        << to_string(fareRecordOfTheNewTrip->calculateProfit(r)) << "\n";
            tripDetails.close();
            return true;
        }
        else
        {
            cout << "File can't be opened!" << endl;
            return false;
        }
    }

    ~trips()
    {
        if (r != nullptr)
        {
            delete r;
            r = nullptr;
        }
        tripsHistory.clear();
    }
};