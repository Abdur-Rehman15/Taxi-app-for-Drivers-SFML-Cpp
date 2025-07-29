#pragma once
#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include "DriverDetails.h"
using namespace std;

class userDetails
{
private:

    string userName;
    string password;

public:

    userDetails(string name = "N/A", string pass = "") { userName = name, password = pass; }

    void setUsername(string name) { userName = name; };

    void setPassword(string pass) { password = pass; };

    string getUsername() { return userName; }
    string getPassword() { return password; }

    bool userAuthenticationForLogin(const string name, const string pass)
    {

        if (name.length() == 0 || pass.length() == 0)
            return false;

        ifstream file("User Details.txt");
        string username, password;
        if (!file.is_open())
        {
            return false;
        }
        while (getline(file, username))
        {
           if (username == name)
           {
               getline(file, password);

              if (password == pass)
              {
                   file.close();
                   return true;
              }
           }
            
        }
        file.close();
        return false;
    }

    bool changeUsername(const string oldName, const string newName)
    {
        string userName, password;
        fstream read, write, newAccount, accountRead,oldname,newname;
        read.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt", ios::in);
        
        if (!read.is_open())
        {
            cout << "read file culd not open" << endl;
            read.close(); return false;
        }
        
        write.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", ios::out);

        if (!write.is_open())
        {
            cout << "Error: Unable to open output file 'temp.txt'" << endl;
            write.close();
            return false;
        }

        while (getline(read, userName))
        {
            getline(read, password);

            if (oldName == userName)
            {
                write << newName << endl;
                write << password << endl;
            }
            else
            {
                write << userName << endl;
                write << password << endl;
            }
        }

        read.close();
        write.close();
        
        if (remove("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt") != 0) { cout << "could not remove user details.txt\n"; return false; }
            Sleep(1000);
            if (rename("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt") != 0) { cout << "could not rename temp and user details\n"; return false; }
              
        accountRead.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Account Details.txt", ios::in);
        newAccount.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Temp.txt", ios::out);

        string username, fullname, phone, typee, model, regno, waste; int AGE;

        while (getline(accountRead, username)) //ye boht ajeeb tareeqy sy set hua he..isko nhi cherna
        {
            if (oldName == username)
            {
                cout << "here in comparison";
                newAccount << newName << endl;
                continue;
            }
            newAccount << username << endl;
        }

        accountRead.close();
        newAccount.close();

        if (remove("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Account Details.txt") != 0) { cout << "could not remove account details.txt\n"; return false; }
        if (rename("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Temp.txt", "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Account Details.txt") != 0) { cout << "could not rename Temp and account details\n"; return false; }

        string old = "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\" + oldName + ".txt";
        string neew = "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\" + newName + ".txt";

        cout << "\nold file: " << old << endl;
        cout << "new file: " << neew << endl;
        cout << "old file: " << old.c_str() << endl;
        cout << "new file: " << neew.c_str() << endl;

        oldname.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\" + oldName + ".txt", ios::in);
        newname.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\" + newName + ".txt", ios::out);

        if (oldname.is_open())
        {
            while (getline(oldname, username))
            {
                newname << username << endl;
            }
        }
        oldname.close();
        newname.close();

        if (remove(old.c_str()) != 0) { cout << "could not remove old name file\n"; return false; }
        if (rename(old.c_str(), neew.c_str()) != 0)
        {
            perror("Error renaming file");
            return false;
        }

        return true;
    }

    bool changePassword(string Name, const string newPass)
    {
        string userName, password;
        fstream read, write;

        read.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt", ios::in);
        if (!read.is_open())
        {
            return false;
        }
        write.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", ios::out);
        if (!write.is_open())
        {
            cout << "Error: Unable to open output file 'temp.txt'" << endl;
            read.close(); // Close the input file before returning
            return false;
        }

        while (getline(read, userName))
        {
            cout << "outside pass" << endl;
            cout << "username: " << userName << endl;

            if (Name == userName)
            {
                cout << "inside pass" << endl;
                write << userName << endl;
                write << newPass << endl;
                getline(read, password);
                continue;
            }
            write << userName << endl;

            getline(read, password);
            cout << "password: " << password << endl;
            write << password << endl;

        }
        read.close();
        write.close();

        if (remove("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt") != 0) { cout << "could not remove user details.\n"; return false; }
        if(rename("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt")!=0) { perror("could not rename user details and temp.txt.\n"); return false; }
         return true;
     
    }

    bool deleteAccount(const string username)
    {
        string userName, password;
        fstream read, write;

        read.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt", ios::in);

        if (!read.is_open())
            return false;

        write.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", ios::out);
        if (!write.is_open())
        {
            cout << "Error: Unable to open output file 'temp.txt'" << endl;
            read.close(); // Close the input file before returning
            return false;
        }

        while (getline(read, userName))
        {
            Sleep(10);
            getline(read, password);

            if (username != userName)
            {
                write << userName << endl;
                write << password << endl;
            }
        }
        Sleep(100);
        read.close();
        Sleep(100);
        write.close();
        
        Sleep(300);

            remove("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt");
            Sleep(100);
            rename("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\User Details.txt");

            Sleep(100);
            write.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", ios::out);
            Sleep(100);
            read.open("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Account Details.txt", ios::in);

            if (!read.is_open())return false;
            if (!write.is_open())return false;

            while (getline(read, userName))
            {
                if (username == userName)
                {
                    for (int i = 0; i < 7; i++)getline(read, userName);
                    continue;
                }
                write << userName << endl;
            }
            Sleep(100);
            write.close();
            Sleep(100);
            read.close();

            Sleep(100);

            if (remove("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Account Details.txt") != 0) { cout << "couldn't remove account details in delete account.\n"; return false; }
            Sleep(100);
            if (rename("C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\temp.txt", "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\Account Details.txt") != 0) { cout << "could not rename temp and account details in delete account.\n"; return false; }

            string name = "C:\\Users\\Dell\\Desktop\\fast cpp\\SFML bingo\\" + username + ".txt";

            Sleep(100);

            remove(name.c_str());

        //delete Driver;
    }
};