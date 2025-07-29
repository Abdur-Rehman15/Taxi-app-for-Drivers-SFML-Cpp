#pragma once
#include<iostream>
using namespace std;

class location 
{
private:

    string Ride_Destination;
    string destination; //only for using cascading call (otherwise no use)
    string pickup_Location;
    int longitude; //xcor
    int latitude; //ycor

public:

    location() { Ride_Destination = "N/A"; longitude = 0; latitude = 2; pickup_Location = "N/A"; };

    void setLongitude(int xcor) { longitude = xcor; }

    void setLatitude(int ycor) { latitude = ycor; }

    int getLongitude() { return longitude; }

    int getLatitude() { return latitude; }

    void decreaseLatitude() { latitude--; }

    void increaseLatitude() { latitude++; }

    void decreaseLongitude() { longitude--; }

    void increaseLongitude() { longitude++; }

    location& setDestination() { this->Ride_Destination = this->destination;; return *this; }
    
    string getDestination() { return Ride_Destination; }

    string getPickupLocation() { return pickup_Location; }

    void GenerateDestinationPoint(int& Dest_x, int& Dest_y, int currentPosition[15][15])
    {
        int seed = time(0);
        srand(seed);

        while (1)
        {
            Dest_x = rand() % 14;
            Dest_y = rand() % 14;

            if (currentPosition[Dest_y][Dest_x] == 2 && Dest_y > 2)
                break;
        }
    }

    location& assignDestination(int dest_x, int dest_y)
    {
        cout << "dest_x" << dest_x << endl;
        cout << "dest_y" << dest_y << endl;

        if ((dest_x >= 3 && dest_x <= 5) && dest_y >= 0 && dest_y <= 4)
            this->destination= "Faisal Town";

        else if ((dest_x >= 3 && dest_x <= 5) && dest_y >= 6 && dest_y <= 9)
            this->destination = "Wapda Town";

        else if ((dest_x >= 3 && dest_x <= 5) && dest_y >= 11 && dest_y <= 14)
            this->destination = "Iqbal Town";

        else if ((dest_x >= 7 && dest_x <= 9) && dest_y >= 0 && dest_y <= 4)
            this->destination = "Valencia Town";

        else if ((dest_x >= 7 && dest_x <= 9) && dest_y >= 6 && dest_y <= 11)
            this->destination = "Khayaban-e-Amin";

        else if ((dest_x >= 7 && dest_x <= 9) && dest_y >= 13 && dest_y <= 14)
            this->destination = "DHA";

        else if ((dest_x >= 11 && dest_x <= 14) && dest_y >= 0 && dest_y <= 3)
            this->destination = "Lake City";

        else if ((dest_x >= 11 && dest_x <= 14) && dest_y >= 5 && dest_y <= 14)
            this->destination = "Bahria Town";

        return *this;

    }

    bool IsDestinationReached(int xcor, int ycor, int Dest_x, int Dest_y, int pick_x, int pick_y)
    {
        bool check = true;
            
        if (ycor + 1 == Dest_y && xcor == Dest_x || ycor - 1 == Dest_y && xcor == Dest_x || ycor == Dest_y && xcor + 1 == Dest_x || ycor == Dest_y && xcor - 1 == Dest_x)
            return false;
        return true;
    }

    bool IsPassengerPicked(int xcor, int ycor, int Dest_x, int Dest_y)
    {
        if (ycor + 1 == Dest_y && xcor == Dest_x || ycor - 1 == Dest_y && xcor == Dest_x || ycor == Dest_y && xcor + 1 == Dest_x || ycor == Dest_y && xcor - 1 == Dest_x)
            return false;
        return true;

    }

    void Assign_Pickup_Location(int& dest_y, int& dest_x,int currentPosition[15][15])
    {
        bool check = true;

        do
        {
            dest_x = rand() % 14;
            dest_y = rand() % 14;

            if (currentPosition[dest_x][dest_y] == 2 && dest_x > 2)
            {
                cout << "pick x" << dest_x << endl;
                cout << "pick y" << dest_y << endl;

                if ((dest_x >= 3 && dest_x <= 5) && dest_y >= 0 && dest_y <= 4)
                    this->pickup_Location = "Faisal Town";

                else if ((dest_x >= 3 && dest_x <= 5) && dest_y >= 6 && dest_y <= 9)
                    this->pickup_Location = "Wapda Town";

                else if ((dest_x >= 3 && dest_x <= 5) && dest_y >= 11 && dest_y <= 14)
                    this->pickup_Location = "Iqbal Town";

                else if ((dest_x >= 7 && dest_x <= 9) && dest_y >= 0 && dest_y <= 4)
                    this->pickup_Location = "Valencia Town";

                else if ((dest_x >= 7 && dest_x <= 9) && dest_y >= 6 && dest_y <= 11)
                    this->pickup_Location = "Khayaban-e-Amin";

                else if ((dest_x >= 7 && dest_x <= 9) && dest_y >= 13 && dest_y <= 14)
                    this->pickup_Location = "DHA";

                else if ((dest_x >= 11 && dest_x <= 14) && dest_y >= 0 && dest_y <= 3)
                    this->pickup_Location = "Lake City";

                else if ((dest_x >= 11 && dest_x <= 14) && dest_y >= 5 && dest_y <= 14)
                    this->pickup_Location = "Bahria Town";

                check = false;
            }
            
        } while (check || (this->Ride_Destination == this->pickup_Location));
    }

    ~location() { cout << "location object destroyed\n"; }
};