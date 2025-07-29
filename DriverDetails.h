#pragma once
#include <iostream>
#include <sstream>
#include<fstream>
#include <vector>
#include <string>
#include "Account_Creation.h"
#include "VehicleDetails.h"
#include "Trips.h"
#include"RideDistance.h"
#include"Fare.h"

using namespace std;

class driver

{

private:
    
    int totalTrips;
    float totalEarnings;
    float totalProfit;
    float totalDistanceTraveledInWholeCareer;
    float avgRatings;
    vector<float> ratingsHistory;
    vehicle* vehicleDetails;

    ride* r1 = NULL;
    fare* f1 = NULL;

    vector<trips>  tripsRecord; //association
    vector<string> tripsPreliminaryDetails;
    

public:
    driver(int t_trips = 0, float t_earnings = 0, float profit = 0.0, float ratings = 0, float totaldistance = 0, vehicle* vehicledet = NULL, ride* r1 = NULL, fare* f1 = NULL)
    {
         totalTrips = t_trips;
         totalEarnings = t_earnings;
         totalProfit = profit;
         avgRatings = ratings;
         totalDistanceTraveledInWholeCareer = totaldistance;
         vehicleDetails = vehicledet;
         f1 = NULL; r1 = NULL;
    }
    
    driver(const driver &driver1)
    {
        this->totalTrips = driver1.totalTrips;
        this->totalEarnings = driver1.totalEarnings;
        this->totalProfit = driver1.totalProfit;
        this->avgRatings = driver1.avgRatings;
        vehicleDetails = new vehicle();
        vehicleDetails = driver1.vehicleDetails; // Overload to make a deep copy
        for (int i = 0; i < totalTrips; i++)
        {
            ratingsHistory.push_back(driver1.ratingsHistory[i]);
            tripsRecord.push_back(driver1.tripsRecord[i]); // Overload to make a deep copy
        }
    }

     void setTotalTrips(int trips) { totalTrips = trips; }
     void setTotalProfit(float profit) { totalProfit = profit; }
     void setTotalDistance(float distance) { totalDistanceTraveledInWholeCareer = distance; }

    int getTotalTrips() { return totalTrips; }
    float getTotalDistanceTravelled() { return totalDistanceTraveledInWholeCareer; }
    float getTotalEarnings() { return totalEarnings; }
    float getAvgRatings() { return avgRatings; }
    float getTotalProfit() { return totalProfit; }

    void updateTripsRecord(const string username, ride* r1, fare* f1)
    {
        fstream read, update;;
        read.open(username + ".txt", ios::in);
        if (!read.is_open())cout << "ERROR. File could not be updated" << endl;

        else
        {
            read >> totalTrips >> totalDistanceTraveledInWholeCareer >> totalProfit;
            totalTrips++;
            totalDistanceTraveledInWholeCareer += r1->getTotalDistanceTraveled();
            totalProfit += f1->calculateProfit(r1);
        }

        update.open("temp.txt", ios::out);
        update << totalTrips << endl << totalDistanceTraveledInWholeCareer << endl << totalProfit;
        string line;
        while (getline(read, line))
        {
            update << line << endl;
        }
        update.close();
        read.close();

        string filename = username + ".txt";

        if (remove(filename.c_str()) != 0) { cout << "old file for updating trips record could not be removed.\n"; return; }
        if (rename("temp.txt", filename.c_str()) != 0) { cout << "could not rename file for updating trips record.\n"; return; }

    }

    void create_TripsHistoryFile_Of_NewUser(const string newUsername)
    {
        fstream newFile;

        newFile.open(newUsername + ".txt", ios::out);
        if (!newFile.is_open())cout << "ERROR. New file could not be created";

        else
        {
            newFile << 0 << endl //total trips
                << 0 << endl //total distance travelled
                << 0 << endl; //total earnings (profit)
        }
        newFile.close();

    }

    bool readTripDetailsOfACertainUser(const string certainDriver)
    {
        fstream tripDetails;
        tripDetails.open(certainDriver + ".txt", ios::in);
        if (tripDetails.is_open())
        {
            string line;
            int totalTrips;
            float totalDistance, totalEarnings;

            tripDetails >> totalTrips >> totalDistance >> totalEarnings;

            tripsPreliminaryDetails.clear();

            while (getline(tripDetails, line))
            {
                //[driver name] [passenger name] [destination] [distance traveled] [profit]
                stringstream ss(line);

                string pName, Destination, Distance, Profit, tripInfo;

                getline(ss, pName, ',');//Tokenize for passenger name
                getline(ss, Destination, ',');//Tokenize for destination
                getline(ss, Distance, ',');//Tokenize for distance
                getline(ss, Profit);//Tokenize for profit
                tripInfo += ("Passenger Name: " + pName + "   Destination: " + Destination + "\n" + "    Distance: " + Distance + "km" + "       Profit: Rs." + Profit);
                tripsPreliminaryDetails.push_back(tripInfo);

            }
            Sleep(300);
            tripDetails.close();
            return true;
        }
        else
        {
            cout << "File can't be openeddd!" << endl;
            return false;
        }
    }

    void setTripDetails(const string username)
    {
        fstream setDetails;

        setDetails.open(username + ".txt", ios::in);
        if (!setDetails.is_open())cout << "ERROR. setdetails file not opened." << endl;

        else
        {
            int totalTrips;
            float totalDistance, totalEarnings;

            setDetails >> totalTrips >> totalDistance >> totalEarnings;

            setTotalTrips(totalTrips);
            setTotalProfit(totalEarnings);
            setTotalDistance(totalDistance);
        }

        setDetails.close();

    }

    friend ostream& operator<<(ostream& COUT, const driver& Driver) //operator overloading
    {
        COUT << "\n\n\n\n";
        for (int i = 1; i < Driver.tripsPreliminaryDetails.size(); i++)
        {
            COUT << i << ": ";
            COUT << Driver.tripsPreliminaryDetails[i] << endl << endl;
        }
        return COUT;
    }

    // Function to convert trips class object to string
    std::string toString() const {
        std::ostringstream oss;
        oss << *this; // Utilize the overloaded << operator
        return oss.str();
    }

    void printDriverExperienceDetails()
    {
        cout << endl
            << endl
            << "Experience Details: " << endl;
        cout << "Total trips: " << totalTrips << endl;
        cout << "Total earnings: " << totalEarnings << endl;
        cout << "Average Ratings: " << avgRatings << endl;
    }

    ~driver() { cout << "driver object deleted\n"; }
};
