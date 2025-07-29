#pragma once
#include <iostream>
#include "RideDistance.h"

using namespace std;

class fare
{
private:
 
    float avgRate_PerUnitDistance_In_NormalConditions;
    float avgRate_PerUnitDistance_In_SpecialConditions; // Special Conditions could include traffic, rough path, etc
    float fuelCharges;
    float tollTax; 
    float totalTollTaxCharged;
    float discount;
    float totalFare;
    float chargesPerKm;
    float maintenaceChargesPer1000KmTravelled;

    ride r1; //aggregation

public:
    fare()
    {
        avgRate_PerUnitDistance_In_NormalConditions = 0.0;   
        avgRate_PerUnitDistance_In_SpecialConditions = 0.0; 
        fuelCharges = 0.0;
        discount = 0.0;
        totalFare = 0.0;
        chargesPerKm = 0.0;
        tollTax = 50.0;
        totalTollTaxCharged = 0.0;
        maintenaceChargesPer1000KmTravelled = 0.0;
    }

    void set_ChargesPerKm_And_FuelCharges(string vehicleType) 
    {
        if (vehicleType == "car")
        {
            avgRate_PerUnitDistance_In_NormalConditions = 50;  
            avgRate_PerUnitDistance_In_SpecialConditions = 65; 
            fuelCharges = 20;
        }
        else if (vehicleType == "bike")
        {
            avgRate_PerUnitDistance_In_NormalConditions = 40;
            avgRate_PerUnitDistance_In_SpecialConditions = 55;
            fuelCharges = 15;
        }
        else if (vehicleType == "rickshaw")
        {
            avgRate_PerUnitDistance_In_NormalConditions = 30;
            avgRate_PerUnitDistance_In_SpecialConditions = 45;
            fuelCharges = 10;
        }
    }

    float calculateFare(ride *r1) //ye total charges hain jo display hongy
    {
        totalFare = (avgRate_PerUnitDistance_In_NormalConditions * r1->getNormalDistance())
            + (avgRate_PerUnitDistance_In_SpecialConditions * r1->getTrafficDistance())
            + totalTollTaxCharged;

        return totalFare;
    }

    virtual void display(ride *r1)
    {
        cout << "Passenger Name: " << endl;
        cout << "Distance Travelled (in km): " << r1->getTotalDistanceTraveled() << endl;
        cout << "Charges per km: " << avgRate_PerUnitDistance_In_NormalConditions << endl;
        cout << "Toll Tax: " << totalTollTaxCharged << endl;
        cout << "Traffic Surcharge: " << (avgRate_PerUnitDistance_In_SpecialConditions * r1->getTrafficDistance()) << endl;
        cout << "Total Charges: " << totalFare << endl;
        cout << "Fuel Price: " << fuelCharges << endl;
        cout << "Total Profit: " << calculateProfit(r1) << endl;
    }

    void setRates() { avgRate_PerUnitDistance_In_NormalConditions = 0.0; avgRate_PerUnitDistance_In_SpecialConditions = 0.0; }

    float getNormalCharges() { return avgRate_PerUnitDistance_In_NormalConditions; } //ye charges per km hain

    float calculateProfit(ride *r1) { return totalFare - (fuelCharges * r1->getTotalDistanceTraveled()) - totalTollTaxCharged /*- (maintenaceChargesPer1000KmTravelled / r1->getTotalDistanceTraveled() * 1000)*/; } //end pr total profit ha ye
    
    void updateTotalTollTaxCharged() { totalTollTaxCharged += tollTax; }

    float getTotalTaxCharged() { return totalTollTaxCharged; }

    float getTotalFuelConsumed(ride *r1) { return (fuelCharges * r1->getTotalDistanceTraveled()); }

    float getTollTax() { return tollTax; }

    float getFuelPrice() { return fuelCharges; }

    float getTrafficSurcharge(ride* r1) { return (totalFare - (avgRate_PerUnitDistance_In_NormalConditions * r1->getTotalDistanceTraveled())); }

};