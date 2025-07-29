#pragma once
#include <iostream>
#include <string>
#include<fstream>
using namespace std;

bool isDigits(string phoneNumber)
{
	int size = phoneNumber.length();
	if (size != 11)
	{
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		if (phoneNumber[i] < '0' || phoneNumber[i] > '9')
		{
			return false;
		}
	}
	return true;
}

bool isAge(string Age)
{
	int size = Age.length();
	if (size > 2 || size == 1)
	{
		return false;
	}
	if (Age[0] < '1' || Age[0] > '6')
	{
		return false;
	}
	if (Age[1] < '0' || Age[1] > '9')
	{
		return false;
	}
	if ((Age[0] == '1' && Age[1] < '8') || (Age[0] == '6' && Age[1] != '0'))
	{
		return false;
	}
	return true;
}

bool isModel(string model)
{
	int size = model.length();
	if (size != 4)
		return false;
	for (int i = 0; i < size; i++)
	{
		if (model[i] < '0' || model[i] > '9')
			return false;
	}
	if (model[0] != '2')
		return false;
	if (model[1] != '0')
		return false;
	if (model[2] < '0' || model[2] > '2')
		return false;
	if (model[2] == '0' && model[3] < '7')
		return false;
	if (model[2] == '2' && model[3] > '4')
		return false;
	return true;
}

bool isUserUnique(string Username)
{
	if (Username == "")return false;

	fstream userDetails;
	userDetails.open("User Details.txt", ios::in);
	if (!userDetails.is_open()) { cout << "could not open user detials file for authenticating user.\n"; return false; }
	else
	{
		string line;
		while (getline(userDetails, line))
		{
			if (line == Username)
			{
				userDetails.close();
				return false;
			}
		}
		userDetails.close();
		return true;
	}
	
}

bool isEngine(string Engine,string type)
{
	//for bike
	if (type == "bike" || type == "rickshaw")
	if (Engine == "70" || Engine == "100" || Engine == "125" || Engine == "150" || Engine == "250" || Engine == "350" || Engine == "500")
		return true;
	// for car
	if (type == "car")
	if (Engine == "660" || Engine == "800" || Engine == "1000" || Engine == "1300" || Engine == "1600" || Engine == "1800" || Engine == "2000")
		return true;
	return false;

}
bool isPassword(string password)
{
	if (password.length() == 0)
		return false;
	else
		return true;
}

bool isFirstName(string firstname)
{
	if (firstname.length() == 0)
		return false;
	else
		return true;
}

bool isLastName(string lastname)
{
	if (lastname.length() == 0)
		return false;
	else
		return true;
}


bool isRegistrationNo(string regNo)
{
	if (regNo.length() == 0)
		return false;
	else
		return true;
}

bool isVehicleType(string type)
{
	if (type.length() == 0)
		return false;
	else
		return true;
}

