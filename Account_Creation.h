#pragma once
#include <iostream>
#include <string>
#include<fstream>

#include "Trips.h"
#include "RideLocation.h"
#include"UserDetails.h"
#include"VehicleDetails.h"

using namespace std;

class account
{
private:

    string firstName;
    string lastName;
    string fullName;
    string phoneNumber;
    int age;

    userDetails u1; //composition
    vehicle* v1 = NULL;

public:

    account(string firstname = "", string lastname = "", string fullname = "N/A", string phoneumber = "0", int AGE = 0, userDetails* U1 = NULL, vehicle* V1 = NULL) { firstName = firstname; lastName = lastname; fullName = fullname; phoneNumber = phoneumber; age = AGE; v1 = V1; }

    //account(string, string, int, int, int, float, location) {};
    //account(const account&) {};
    void setUsername(string username) { u1.setUsername(username); }
    void setPassword(string pass) { u1.setPassword(pass); };

    string getUsername() { return u1.getUsername(); }
    string getPassword() { return u1.getPassword(); }

    void set_firstName(string first) { firstName = first; };
    void set_lastName(string last) { lastName = last; };
    void setFullName(string full) { fullName = full; }
    void set_phoneNumber(string phone) { phoneNumber = phone; };
    void set_age(int Age) { age = Age; };

    bool userAuthenticationForLogin(const string name, const string pass)
    {
        if (u1.userAuthenticationForLogin(name, pass))return true;

        return false;
    }

    bool changeUsername(const string oldName, const string newName)
    {
        if (u1.changeUsername(oldName, newName))return true;
        return false;
    }

    bool changePassword(string Name, const string newPass)
    {
        if (u1.changePassword(Name, newPass))return true;
        return false;
    }

    bool deleteAccount(const string username)
    {
        if (u1.deleteAccount(username))return true;
        return false;
    }


    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    string getFull_Name() { return fullName; };

    string get_phoneNumber() { return phoneNumber; };

    int get_age() { return age; };

    void saveAccount(fstream& AccountDetails, fstream& UserDetails, vehicle* v1)
    {
        AccountDetails.open("Account Details.txt", ios::out | ios::app);

        if (!AccountDetails.is_open())cout << "Could not save New Account Details.";

        else
        {
            AccountDetails.seekg(ios::end);
            AccountDetails << this->getUsername() << endl;
            AccountDetails << firstName << " " << lastName << endl;
            AccountDetails << phoneNumber << endl;
            AccountDetails << age << endl;
            AccountDetails << v1->getVehicleType() << endl;
            AccountDetails << v1->getVehicleModel() << endl;
            AccountDetails << v1->getVehicleRegNo() << endl;
            AccountDetails << v1->get_Vehicle_Engine_Power() << endl << endl;
            Sleep(100);
        }

        AccountDetails.close();

        Sleep(300);

        UserDetails.open("User Details.txt", ios::out | ios::app);

        if (!UserDetails.is_open())cout << "Could not save New Account Details.";

        else
        {
            UserDetails.seekg(ios::end);
            UserDetails << this->getUsername() << endl;
            UserDetails << this->getPassword() << endl << endl << endl << endl;
            Sleep(100);

        }

        UserDetails.close();

    }

    void setAccountDetails(fstream& AccountDetails, vehicle* v1, string enteredUsername)
    {

        AccountDetails.open("Account Details.txt", ios::in);

        if (!AccountDetails.is_open())cout << "Could not save New Account Details.";

        else 
        {
            string username, fullname, phone, typee, model, regno, waste; int AGE;

            AccountDetails.seekg(0, ios::beg);

            while (getline(AccountDetails, username)) 
            {
                if (enteredUsername == username)
                {
                    this->setUsername(username);
                    getline(AccountDetails, fullname);
                    this->setFullName(fullname);
                    getline(AccountDetails, phone);
                    this->set_phoneNumber(phone);
                    AccountDetails >> AGE;
                    this->set_age(AGE);
                    getline(AccountDetails, typee);

                    getline(AccountDetails, model);
                    v1->setVehicleType(model);
                    getline(AccountDetails, waste);
                    getline(AccountDetails, regno);
                    v1->setVehicleRegNo(regno);

                    break;
                }
            }
        }
        Sleep(200);
        AccountDetails.close();
    }

    ~account() {  delete v1; }
};
