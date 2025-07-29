#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include<sstream>
#include <string>
#include<cstdlib>
#include<ctime>
#include<windows.h>

#include"Account_Creation.h"
#include"DriverDetails.h"
#include"Fare.h"
#include"RideDistance.h"
#include"Trips.h"
#include"UserDetails.h"
#include"VehicleDetails.h"
#include"checks.h"

const int MAP_SIZE = 15;
const int SQUARE_SIZE = 30;

using namespace std;

//========================OOP CONCEPTS USED============================

// user details class object is being used as COMPOSITION in account class

// ride class and fare class are in AGGREGATION

// driver class has trips class in vector<> showing ASSOCIATION between them

// trips class is inherited by fare class showing INHERITANCE

// in driver class, << operator is OVERLOADED

// objects POINTERS are created in classes where suitable

// fare class has a function display() which is being overriden by trips class display() function showing POLYMORPHISM

// ENCAPSULATION is used in every class via private data members, furthermore getters, setters and other functions are used where necessary

// showRoom is ABSTRACT CLASS and vehicle class is being inherited by it

// CASCADED CALL on line 1001

//=====================================================================

bool isColliding(int xcor, int ycor, int currentPosition[15][15]) {
    if (xcor >= 0 && xcor < MAP_SIZE && ycor >= 0 && ycor < MAP_SIZE) {
        if (currentPosition[ycor][xcor] == 0 || currentPosition[ycor][xcor] == 2)
            return false; // Return true if cell is empty (accessible)
    }
    return true; // Return false if coordinates are out of bounds
}

int main() 
{

//==============CLASSES OBJECTS=========================

    location l1;
    ride r1;
    fare f1;
    vehicle v1;
    account a1;
    trips t1;
    driver d1;

    int xcor = 0, ycor = 2;

    l1.setLongitude(xcor);
    l1.setLatitude(ycor);

//========================FILES===========================


    fstream Account_Details;
    fstream User_Details;


//========================================================


    // Calculate window size based on square size and array dimensions
    int windowSize = MAP_SIZE * SQUARE_SIZE;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "EMA Riders");

    int currentPosition[15][15] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } ,
                                    {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2 } ,
                                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } ,
                                    {2,2,2,2,2,1,2,2,2,2,1,2,2,2,2 } ,
                                    {0,0,0,0,2,1,2,0,0,2,1,2,0,0,0 } ,
                                    {2,2,2,2,2,1,2,2,2,2,1,2,2,2,2 } ,
                                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } ,
                                    {2,2,2,2,2,1,2,2,2,2,2,2,1,2,2 } ,
                                    {0,0,0,0,2,1,2,0,0,0,0,0,1,2,0 } ,
                                    {2,2,2,2,2,1,2,2,2,2,2,2,1,2,2 } ,
                                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } ,
                                    {2,2,2,2,1,2,2,2,2,2,2,2,2,2,2 } ,
                                    {2,2,2,2,1,2,2,2,2,2,2,2,2,2,2 } ,
                                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } ,
                                    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 } };
    
    float Km = 0;

    float scaleFactor = 1.09f;
    int Dest_x = 0, Dest_y = 0;
    int Pick_x = 0, Pick_y = 0;
    string destination;

    float displayDuration = 1.9f; // Adjust this value as needed
    
//===========================SOUND======================================

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("tap-notification-180637.wav")) {
        // Error loading audio file
        return 1;
    }
    
     // Create SFML sound
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::SoundBuffer engineStart;
    if (!engineStart.loadFromFile("car ignition.wav")) {
        // Error loading audio file
        return 1;
    }

    // Create SFML sound
    sf::Sound carEngineStart;
    carEngineStart.setBuffer(engineStart);

    sf::SoundBuffer FormSubmit;
    if (!FormSubmit.loadFromFile("form submit.mp3")) {
        // Error loading audio file
        return 1;
    }

    // Create SFML sound
    sf::Sound Formsubmit;
    Formsubmit.setBuffer(FormSubmit);

    sf::SoundBuffer MainMenuClick;
    if (!MainMenuClick.loadFromFile("main menu click.mp3")) {
        // Error loading audio file
        return 1;
    }

    // Create SFML sound
    sf::Sound MainMenuclick;
    MainMenuclick.setBuffer(MainMenuClick);

//=========================IMAGES========================================

    // Load car image
    sf::Texture carTexture;
    if (!carTexture.loadFromFile("car.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite car(carTexture);

    sf::Texture bikeTexture;
    if (!bikeTexture.loadFromFile("bike.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite bike(bikeTexture);

    sf::Texture rickshawTexture;
    if (!rickshawTexture.loadFromFile("rickshaw.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite rickshaw(rickshawTexture);

    sf::Texture passengerTexture;
    if (!passengerTexture.loadFromFile("rickshaw.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite passenger(passengerTexture);

    // Load car image
    sf::Texture carTraffic;
    if (!carTraffic.loadFromFile("traffic.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite cartraffic(carTraffic);

    // Load car image
    sf::Texture TollPlaza;
    if (!TollPlaza.loadFromFile("toll plaza.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite Tollplaza(TollPlaza);

    sf::Texture locationIcon;
    if (!locationIcon.loadFromFile("location icon.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite location(locationIcon);

    sf::Texture backGround;
    if (!backGround.loadFromFile("car map.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite background(backGround);

    sf::Texture backGroundPassenger;
    if (!backGroundPassenger.loadFromFile("car map passenger picked.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite backgroundpassenger(backGroundPassenger);

    sf::Texture Passenger;
    if (!Passenger.loadFromFile("passenger.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite passengerr(Passenger);

    sf::Texture LoginForm;
    if (!LoginForm.loadFromFile("login form.jpg")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite Loginform(LoginForm);

    sf::Texture Receipt;
    if (!Receipt.loadFromFile("receipt.jpg")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite receipt(Receipt);

    sf::Texture FindingRide;
    if (!FindingRide.loadFromFile("find ride.jpg")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite FindRide(FindingRide);

    sf::Texture RideName;
    if (!RideName.loadFromFile("ride request name.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite Ridename(RideName);

    sf::Texture MainMenuPage;
    if (!MainMenuPage.loadFromFile("main menu.jpg")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite MainMenupage(MainMenuPage);

    sf::Texture AccountDetailsDisplay;
    if (!AccountDetailsDisplay.loadFromFile("account details.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite AccountDetailsdisplay(AccountDetailsDisplay);

    sf::Texture CreateNewAccountForm;
    if (!CreateNewAccountForm.loadFromFile("create new account form.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite CreateNewAccountform(CreateNewAccountForm);

    sf::Texture SettingsPage;
    if (!SettingsPage.loadFromFile("settings page.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite Settingspage(SettingsPage);

    sf::Texture SettingsPageEmpty;
    if (!SettingsPageEmpty.loadFromFile("settings page empty.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite SettingsPageempty(SettingsPageEmpty);

    sf::Texture tripsHistory;
    if (!tripsHistory.loadFromFile("trips history.png")) {
        std::cerr << "Failed to load car image." << std::endl;
        return 1;
    }
    sf::Sprite Trips_history(tripsHistory);


//===============================FONT================================================

    sf::Font font;

    if (!font.loadFromFile("C:/users/dell/desktop/fast cpp/sfml bingo/x64/fonts/calibri.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }

    sf::Font font1;

    if (!font1.loadFromFile("C:/users/dell/desktop/fast cpp/sfml bingo/x64/fonts/Sprocket_BT.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }



//==========================TEXT DISPLAY=================================================

    sf::Text km("Kilometres: ", font, 20);
    km.setFillColor(sf::Color::Black);
    km.setPosition(10, 10);
    sf::Vector2f originalScale = km.getScale();

    sf::Text value("0.000", font, 20);
    value.setFillColor(sf::Color::Black);
    value.setPosition(130, 10); // Adjusted position to fit the window

    sf::Text usernameLabel("Username:", font, 20);
    usernameLabel.setFillColor(sf::Color::Black);
    usernameLabel.setPosition(50, 190);
    
    sf::Text Exit("Exit", font, 20);
    Exit.setFillColor(sf::Color::White);
    Exit.setPosition(587, 68);
    
    sf::Text passwordLabel("Password:", font, 20);
    passwordLabel.setFillColor(sf::Color::Black);
    passwordLabel.setPosition(50, 250);

    sf::Text loginButtonText("Login", font, 20);
    loginButtonText.setFillColor(sf::Color::White);
    loginButtonText.setPosition(220, 320);
        
    sf::Text CreateAccount("Create New Account", font, 20);
    CreateAccount.setFillColor(sf::Color::Black);
    CreateAccount.setPosition(165, 365);

    sf::Text Endride("Finish Ride", font, 20);
    Endride.setFillColor(sf::Color::White);
    Endride.setPosition(325, 17);
       
    sf::Text loginText("Logging In.....", font, 20);
    loginText.setFillColor(sf::Color::White);
    loginText.setPosition(50, 60);

    sf::Text PassengerName("", font1, 20);
    PassengerName.setFillColor(sf::Color::Black);
    PassengerName.setPosition(255, 205);

    sf::Text Destination("", font1, 20); //yahan map sy check krky assign krni ha destination
    Destination.setFillColor(sf::Color::Black);
    Destination.setPosition(255, 248);

    sf::Text PickupLocation("", font1, 20);
    PickupLocation.setFillColor(sf::Color::Black);
    PickupLocation.setPosition(250, 168);

    sf::Text WelcomeName("NAME", font, 23);
    WelcomeName.setFillColor(sf::Color::White);
    WelcomeName.setPosition(182, 25);

    sf::Text ReceiptClose("Close", font, 20);
    ReceiptClose.setFillColor(sf::Color::White);
    ReceiptClose.setPosition(308, 400);

    sf::Text AccountDetailsClose("Close", font, 20);
    AccountDetailsClose.setFillColor(sf::Color::White);
    AccountDetailsClose.setPosition(208, 370);

    sf::Text Trips_History("", font1, 16);
    Trips_History.setFillColor(sf::Color::Black);
    Trips_History.setPosition(17, 45);

    sf::Text Totaltrips("totr", font1, 15);
    Totaltrips.setFillColor(sf::Color::Black);
    Totaltrips.setPosition(154, 49);

    sf::Text totalProfitEarned("prof", font1, 15);
    totalProfitEarned.setFillColor(sf::Color::Black);
    totalProfitEarned.setPosition(328, 49);

    sf::Text TotaldistanceTravelled("dist", font1, 15);
    TotaldistanceTravelled.setFillColor(sf::Color::Black);
    TotaldistanceTravelled.setPosition(244, 89);

    sf::Text Trips_History_close("Close", font, 19);
    Trips_History_close.setFillColor(sf::Color::White);
    Trips_History_close.setPosition(205, 399);

///////////TRIP RECEIPT////////////////////

    
    sf::Text PassengerName_On_Receipt("", font, 20); //name
    PassengerName_On_Receipt.setFillColor(sf::Color::Black);
    PassengerName_On_Receipt.setPosition(230, 73);

    sf::Text TravelledDistance("", font, 20);
    TravelledDistance.setFillColor(sf::Color::Black);
    TravelledDistance.setPosition(299, 120);

    sf::Text ChargesPerKm("", font, 20);
    ChargesPerKm.setFillColor(sf::Color::Black);
    ChargesPerKm.setPosition(200, 158);

    sf::Text Toll_Tax_Charges("Rs. 0", font, 20); //toll tax
    Toll_Tax_Charges.setFillColor(sf::Color::Black);
    Toll_Tax_Charges.setPosition(135, 200);

    sf::Text TrafficSurcharge("", font, 20); //traffic surcharge
    TrafficSurcharge.setFillColor(sf::Color::Black);
    TrafficSurcharge.setPosition(220, 247);

    sf::Text TotalCharges("", font, 20);
    TotalCharges.setFillColor(sf::Color::Black);
    TotalCharges.setPosition(200, 289);

    sf::Text FuelPrice("", font, 20);
    FuelPrice.setFillColor(sf::Color::Black);
    FuelPrice.setPosition(155, 330);

    sf::Text Profit("", font, 20);
    Profit.setFillColor(sf::Color::Black);
    Profit.setPosition(175, 377);

///////////ACCOUNT DETAILS//////////////

    sf::Text AccountName("namee", font, 20);
    AccountName.setFillColor(sf::Color::Black);
    AccountName.setPosition(165, 80);

    sf::Text AccountUserName("usernamee", font, 20);
    AccountUserName.setFillColor(sf::Color::Black);
    AccountUserName.setPosition(185, 125);

    sf::Text AccountAge("agee", font, 20);
    AccountAge.setFillColor(sf::Color::Black);
    AccountAge.setPosition(150, 176);

    sf::Text AccountPhoneNo("numberr", font, 20);
    AccountPhoneNo.setFillColor(sf::Color::Black);
    AccountPhoneNo.setPosition(185, 225);

    sf::Text AccountVehicleType("carr", font, 20);
    AccountVehicleType.setFillColor(sf::Color::Black);
    AccountVehicleType.setPosition(203, 274);

    sf::Text AccountVehicleRegNo("leb12", font, 20);
    AccountVehicleRegNo.setFillColor(sf::Color::Black);
    AccountVehicleRegNo.setPosition(230, 323);

/////////////////////////////////////////////////


    sf::Text displayText("", font, 20);
    displayText.setFillColor(sf::Color::Red);
    displayText.setPosition(160, 150);

    sf::Text RideNext("NEXT", font, 20);
    RideNext.setFillColor(sf::Color::White);
    RideNext.setPosition(205, 300);

    sf::Text Rideaccept("ACCEPT", font, 20);
    Rideaccept.setFillColor(sf::Color::Black);
    Rideaccept.setPosition(267, 299);

    sf::Text Ridedecline("DECLINE", font, 20);
    Ridedecline.setFillColor(sf::Color::Black);
    Ridedecline.setPosition(82, 299);

    sf::Text AccountDetails("Account Details", font, 23);
    AccountDetails.setFillColor(sf::Color::Black);
    AccountDetails.setPosition(183, 130);

    sf::Text TripsHistory("Trips History", font, 23);
    TripsHistory.setFillColor(sf::Color::Black);
    TripsHistory.setPosition(183, 220);

    sf::Text Settings("Settings", font, 23);
    Settings.setFillColor(sf::Color::Black);
    Settings.setPosition(204, 305);

    sf::Text FindRideMain("Find Ride", font, 22);
    FindRideMain.setFillColor(sf::Color::White);
    FindRideMain.setPosition(183, 398);

    sf::Text Firstname("First Name:", font, 18);
    Firstname.setFillColor(sf::Color::Black);
    Firstname.setPosition(15,60);

    sf::Text Lastname("Last Name:", font, 18);
    Lastname.setFillColor(sf::Color::Black);
    Lastname.setPosition(230, 60);

    sf::Text Phoneno("Phone Number:", font, 18);
    Phoneno.setFillColor(sf::Color::Black);
    Phoneno.setPosition(35, 100);

    sf::Text AgeText("Age:", font, 18);
    AgeText.setFillColor(sf::Color::Black);
    AgeText.setPosition(35, 140);

    sf::Text Newusername("New UserName:", font, 18);
    Newusername.setFillColor(sf::Color::Black);
    Newusername.setPosition(35, 180);

    sf::Text Newpassword("New Password:", font, 18);
    Newpassword.setFillColor(sf::Color::Black);
    Newpassword.setPosition(35, 220);

    sf::Text TextCar("CAR", font, 18);
    TextCar.setFillColor(sf::Color::Black);
    TextCar.setPosition(75, 285);

    sf::Text TextBike("BIKE", font, 18);
    TextBike.setFillColor(sf::Color::Black);
    TextBike.setPosition(175, 285);

    sf::Text TextRickshaw("RICKSHAW", font, 18);
    TextRickshaw.setFillColor(sf::Color::Black);
    TextRickshaw.setPosition(255, 285);

    sf::Text Vehiclemodel("Vehicle Model:", font, 18);
    Vehiclemodel.setFillColor(sf::Color::Black);
    Vehiclemodel.setPosition(35, 325);

    sf::Text Registrationno("Vehicle Registration No:", font, 18);
    Registrationno.setFillColor(sf::Color::Black);
    Registrationno.setPosition(35, 370);

    sf::Text Enginepower("Engine Power in CC:", font, 18);
    Enginepower.setFillColor(sf::Color::Black);
    Enginepower.setPosition(35, 410);

    sf::Text SubmitForm("Submit", font, 18);
    SubmitForm.setFillColor(sf::Color::White);
    SubmitForm.setPosition(355, 420);

    sf::Text UserNameChange("Change Username", font1, 19);
    UserNameChange.setFillColor(sf::Color::White);
    UserNameChange.setPosition(177, 105);

    sf::Text PasswordChange("Change Password", font1, 19);
    PasswordChange.setFillColor(sf::Color::White);
    PasswordChange.setPosition(177, 174);

    sf::Text Logout("Log Out", font1, 19);
    Logout.setFillColor(sf::Color::White);
    Logout.setPosition(200, 247);

    sf::Text DeleteAccount("Delete Account", font1, 19);
    DeleteAccount.setFillColor(sf::Color::White);
    DeleteAccount.setPosition(190, 315);

    sf::Text changeusername("New Username:", font, 22);
    changeusername.setFillColor(sf::Color::Black);
    changeusername.setPosition(30, 200);

    sf::Text changepassword("New Password:", font, 22);
    changepassword.setFillColor(sf::Color::Black);
    changepassword.setPosition(35, 200);

    sf::Text SettingsOptionSubmit("Submit", font, 20);
    SettingsOptionSubmit.setFillColor(sf::Color::White);
    SettingsOptionSubmit.setPosition(200, 308);

    sf::Text SettingsBack("Back", font, 20);
    SettingsBack.setFillColor(sf::Color::White);
    SettingsBack.setPosition(208, 390);

//==========================RECTANGLE SHAPES=========================================

    sf::RectangleShape usernameBox(sf::Vector2f(200, 30));
    usernameBox.setPosition(170, 190);
    usernameBox.setFillColor(sf::Color::White);
    usernameBox.setOutlineColor(sf::Color::Black);
    usernameBox.setOutlineThickness(1.5);
  
    sf::RectangleShape passwordBox(sf::Vector2f(200, 30));
    passwordBox.setPosition(170, 250);
    passwordBox.setFillColor(sf::Color::White);
    passwordBox.setOutlineColor(sf::Color::Black);
    passwordBox.setOutlineThickness(1.5);

    sf::RectangleShape changeUsername(sf::Vector2f(200, 30));
    changeUsername.setPosition(185, 200);
    changeUsername.setFillColor(sf::Color::White);
    changeUsername.setOutlineColor(sf::Color::Black);
    changeUsername.setOutlineThickness(1.5);

    sf::RectangleShape changePassword(sf::Vector2f(200, 30));
    changePassword.setPosition(185, 200);
    changePassword.setFillColor(sf::Color::White);
    changePassword.setOutlineColor(sf::Color::Black);
    changePassword.setOutlineThickness(1.5);

    /////////NEW ACCOUNT CREATION//////////////

    sf::RectangleShape FirstName(sf::Vector2f(110, 25));
    FirstName.setPosition(110, 60);
    FirstName.setFillColor(sf::Color::White);
    FirstName.setOutlineColor(sf::Color::Black);
    FirstName.setOutlineThickness(1.5);

    sf::RectangleShape LastName(sf::Vector2f(100, 25));
    LastName.setPosition(320, 60);
    LastName.setFillColor(sf::Color::White);
    LastName.setOutlineColor(sf::Color::Black);
    LastName.setOutlineThickness(1.5);

    sf::RectangleShape PhoneNo(sf::Vector2f(200, 25));
    PhoneNo.setPosition(165, 100);
    PhoneNo.setFillColor(sf::Color::White);
    PhoneNo.setOutlineColor(sf::Color::Black);
    PhoneNo.setOutlineThickness(1.5);

    sf::RectangleShape Age(sf::Vector2f(100, 25));
    Age.setPosition(75, 140);
    Age.setFillColor(sf::Color::White);
    Age.setOutlineColor(sf::Color::Black);
    Age.setOutlineThickness(1.5);

    sf::RectangleShape NewUserName(sf::Vector2f(200, 25));
    NewUserName.setPosition(165, 180);
    NewUserName.setFillColor(sf::Color::White);
    NewUserName.setOutlineColor(sf::Color::Black);
    NewUserName.setOutlineThickness(1.5);

    sf::RectangleShape NewPassword(sf::Vector2f(200, 25));
    NewPassword.setPosition(165, 220);
    NewPassword.setFillColor(sf::Color::White);
    NewPassword.setOutlineColor(sf::Color::Black);
    NewPassword.setOutlineThickness(1.5);

    sf::RectangleShape CarOptionDisplay(sf::Vector2f(60, 25));
    CarOptionDisplay.setPosition(65, 285);
    CarOptionDisplay.setFillColor(sf::Color::Cyan);
    CarOptionDisplay.setOutlineColor(sf::Color::Black);
    CarOptionDisplay.setOutlineThickness(1.5);

    sf::RectangleShape BikeOptionDisplay(sf::Vector2f(60, 25));
    BikeOptionDisplay.setPosition(165, 285);
    BikeOptionDisplay.setFillColor(sf::Color::Cyan);
    BikeOptionDisplay.setOutlineColor(sf::Color::Black);
    BikeOptionDisplay.setOutlineThickness(1.5);

    sf::RectangleShape RickshawOptionDisplay(sf::Vector2f(90, 25));
    RickshawOptionDisplay.setPosition(250, 285);
    RickshawOptionDisplay.setFillColor(sf::Color::Cyan);
    RickshawOptionDisplay.setOutlineColor(sf::Color::Black);
    RickshawOptionDisplay.setOutlineThickness(1.5);

    sf::RectangleShape VehicleModel(sf::Vector2f(100, 25));
    VehicleModel.setPosition(160, 325);
    VehicleModel.setFillColor(sf::Color::White);
    VehicleModel.setOutlineColor(sf::Color::Black);
    VehicleModel.setOutlineThickness(1.5);

    sf::RectangleShape VehicleRegistrationNo(sf::Vector2f(140, 25));
    VehicleRegistrationNo.setPosition(220, 370);
    VehicleRegistrationNo.setFillColor(sf::Color::White);
    VehicleRegistrationNo.setOutlineColor(sf::Color::Black);
    VehicleRegistrationNo.setOutlineThickness(1.5);


    sf::RectangleShape EnginePower(sf::Vector2f(100, 25));
    EnginePower.setPosition(190, 410);
    EnginePower.setFillColor(sf::Color::White);
    EnginePower.setOutlineColor(sf::Color::Black);
    EnginePower.setOutlineThickness(1.5);
    
    /////////////////////////////////////////////

    sf::RectangleShape loginButton(sf::Vector2f(100, 40));
    loginButton.setPosition(195, 315);
    loginButton.setFillColor(sf::Color::Black);

    sf::RectangleShape FinishRide(sf::Vector2f(120, 40));
    FinishRide.setPosition(310, 13);
    FinishRide.setFillColor(sf::Color::Black);

    sf::RectangleShape Receiptclose(sf::Vector2f(100, 35));
    Receiptclose.setPosition(282, 399);
    Receiptclose.setFillColor(sf::Color::Black);

    sf::RectangleShape AccountDetailsclose(sf::Vector2f(100, 35));
    AccountDetailsclose.setPosition(179, 370);
    AccountDetailsclose.setFillColor(sf::Color::Black);

    sf::RectangleShape RideRequestNext(sf::Vector2f(100, 35));
    RideRequestNext.setPosition(179, 295);
    RideRequestNext.setFillColor(sf::Color::Black);

    sf::RectangleShape RideDecline(sf::Vector2f(100, 35));
    RideDecline.setPosition(70, 295);
    RideDecline.setFillColor(sf::Color::Red);

    sf::RectangleShape RideAccept(sf::Vector2f(100, 35));
    RideAccept.setPosition(250, 295);
    RideAccept.setFillColor(sf::Color::Green);


//=======================FONT COLOURS======================================
  
    sf::Color hoverColor(255,0, 0); // Green
    sf::Color hoverColor1(255, 30, 255); // Peach

//=========================VARIABLES=======================================

    string usernameInput="";
    string passwordInput="";
    string newusernameInput="";
    string passwordDisplay=""; // Display stars instead of letters

    string firstname = "";
    string lastname = "";
    string PhoneNumber = "";
    string age = "";
    string newUsername = "";
    string newPassword = "";
    string vehicleModel = "";
    string vehicleRegistrationNum = "";
    string enginePowerinCC = "";
    string changedUsername = "";
    string changedPassword = "";
    string Vehicle_Type = "";

    bool LoginPage = true;
    bool DrawMap = false;
    bool CreateAccountPage=false;
    bool usernameSelected = false;
    bool passwordSelected = false;
    bool createAccountSelected = false;
    bool FirstNameselected = false;
    bool LastNameselected = false;
    bool PhoneNoselected = false;
    bool ageselected = false;
    bool newUsernameselected = false;
    bool newPasswordselected = false;
    bool vehicleModelselected = false;
    bool vehicleRegistrationselected = false;
    bool enginePowerselected = false;
    bool EndRide = false;
    bool FareReceipt = false;
    bool RideReceipt = false;
    bool RideRequest = false;
    bool RideRequestName = false;
    bool MainMenu = false;
    bool AccountDetailsPage = false;
    bool TripsHistoryPage = false;
    bool SettingsOptionSelected = true;
    bool settingsPage = false;
    bool changeUsernameOptionSelected = false;
    bool changePasswordOptionSelected = false;
    bool changeUsernameBox = false;
    bool changePasswordBox = false;
    bool isPassengerPickedup = false;
    bool showPassenger = true;
    
//==============================MAP TRAFFIC SET===========================================

    int Traffic;
    // Randomly set initial position of the car
    float carPosX = 0.0;
    float carSpeed = 0.06f;
    bool carDirection = true; // true for moving right, false for moving left

//=========================================================================================


//=========================================================================================

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //=================MOUSE BUTTON PRESSED=================================================
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (LoginPage)
                {
                    if (usernameBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        usernameBox.setOutlineColor(sf::Color::Magenta);
                        passwordBox.setOutlineColor(sf::Color::Black);

                        usernameSelected = true;
                        passwordSelected = false;
                    }

                    else if (passwordBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        passwordBox.setOutlineColor(sf::Color::Magenta);
                        usernameBox.setOutlineColor(sf::Color::Black);

                        passwordSelected = true;
                        usernameSelected = false;

                    }

                    else if (loginButtonText.getGlobalBounds().contains(mousePos.x, mousePos.y)) //only for check
                    {
                        sound.play();

                        if (a1.userAuthenticationForLogin(usernameInput, passwordInput))
                        {
                            a1.setAccountDetails(Account_Details, &v1, usernameInput); //set account details of logged in account
                            f1.set_ChargesPerKm_And_FuelCharges(v1.getVehicleType());
                           
                            LoginPage = 0;
                            MainMenu = true;

                            WelcomeName.setString(a1.getFull_Name());

                            d1.readTripDetailsOfACertainUser(a1.getUsername());
                        }
                        else
                            ///if invalid credentials///
                        displayText.setString("Invalid Credentials");

                    }

                    else if (CreateAccount.getGlobalBounds().contains(mousePos.x, mousePos.y)) //only for check
                    {
                        sound.play();

                        LoginPage = 0;
                        CreateAccountPage = true;
                    }

                    else
                    {
                        usernameSelected = false;
                        passwordSelected = false;
                        passwordBox.setOutlineColor(sf::Color::Black);
                        usernameBox.setOutlineColor(sf::Color::Black);
                    }
                }

                else if (DrawMap)
                {

                    if (Endride.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        sound.play();

                        DrawMap = false;
                        FareReceipt = true;

                        f1.display(&r1); //virtual display
                        
                        FuelPrice.setString("Rs. " + (to_string(f1.getFuelPrice())));
                        ChargesPerKm.setString("Rs. " + (to_string(f1.getNormalCharges())));
                        TravelledDistance.setString(to_string(r1.getTotalDistanceTraveled()) + " km");
                        TotalCharges.setString("Rs. "+to_string(f1.calculateFare(&r1)));
                        TrafficSurcharge.setString("Rs. " + to_string(f1.getTrafficSurcharge(&r1)));
                        FuelPrice.setString("Rs. " + to_string(f1.getTotalFuelConsumed(&r1)));
                        Profit.setString("Rs. " + to_string(f1.calculateProfit(&r1)));

                        t1.saveTripDetails(a1.getUsername(), &r1, &l1, &f1);

                        d1.updateTripsRecord(a1.getUsername(), &r1, &f1);

                        d1.readTripDetailsOfACertainUser(a1.getUsername());

                        isPassengerPickedup = false;
                        value.setString("0.000 km");

                        showPassenger = true;

                        //r1.setTotalDistance(0.0);
                        //f1.setRates();
                        //d1.addNewTrip(t1);
                        //d1.readTripDetailsOfACertainUser(u1.getUsername());

                    }

                }

                else if (RideRequest)
                {
                    if (RideNext.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        RideRequest = 0;
                        RideRequestName = true;

                        MainMenuclick.play();
                    }
                }

                else if (RideRequestName)
                {
                    if (Rideaccept.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        RideRequestName = 0;
                        DrawMap = true;
                        carEngineStart.play();
                    }

                    if (Ridedecline.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        RideRequestName = 0;
                        MainMenu = true;
                    }
                }

                else if (FareReceipt)
                {
                    if (ReceiptClose.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        FareReceipt = false;
                        MainMenu = true;
                        cout << "no";

                        MainMenuclick.play();
                    }
                }

                else if (MainMenu)
                {
                    if (AccountDetails.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        MainMenu = 0;

                        a1.setAccountDetails(Account_Details, &v1,usernameInput);

                        AccountName.setString(a1.getFull_Name());
                        AccountUserName.setString(a1.getUsername());
                        AccountAge.setString(to_string(a1.get_age()));
                        AccountPhoneNo.setString(a1.get_phoneNumber());
                        AccountVehicleType.setString(v1.getVehicleType());
                        AccountVehicleRegNo.setString(v1.getVehicleRegNo());
                        
                        AccountDetailsPage = true;

                        MainMenuclick.play();
                    }
                    if (TripsHistory.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        MainMenu = 0;
                        TripsHistoryPage = true;
                        
                        t1.display(&r1); //overriden display

                        // Set the text to display the trips class object
                        Trips_History.setString(d1.toString()); // Use toString() function

                        d1.setTripDetails(a1.getUsername());
                        Totaltrips.setString(to_string(d1.getTotalTrips()));
                        totalProfitEarned.setString("Rs. " + to_string(d1.getTotalProfit()));
                        TotaldistanceTravelled.setString(to_string(d1.getTotalDistanceTravelled()) + " km");

                        MainMenuclick.play();

                    }
                    if (Settings.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        MainMenu = 0;
                        settingsPage = true;

                        MainMenuclick.play();

                    }
                    if (FindRideMain.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        RideRequest = true;
                        MainMenu = 0;

                        string names[] = { "Ahmed","Hassan","Ayesha","Ezaan","Abdur","Musa" }; //random one will be selected
                        int seed = time(0);
                        srand(seed);
                        string passengername = names[rand() % 6];

                        PassengerName.setString(passengername);
                        PassengerName_On_Receipt.setString(passengername);
                        t1.setPassengerName(passengername);
                       
                        l1.GenerateDestinationPoint(Dest_x, Dest_y, currentPosition);
                       
                        l1.assignDestination(Dest_y, Dest_x).setDestination(); //cascaded call

                        l1.Assign_Pickup_Location(Pick_x, Pick_y, currentPosition);

                        Destination.setString(l1.getDestination());
                        PickupLocation.setString(l1.getPickupLocation());

                        xcor = 0; ycor = 2;
                        l1.setLongitude(xcor);
                        l1.setLatitude(ycor);

                        // Random number generator setup
                        srand(time(nullptr));

                        // Randomly select a row for the car to move
                        int traffic;
                        while (1) { traffic = rand() % 15; if (traffic == 2 || traffic == 6 || traffic == 10 || traffic == 13) break; }
                        Traffic = traffic;

                        car.setPosition(xcor* SQUARE_SIZE, ycor* SQUARE_SIZE);
                        bike.setPosition(xcor* SQUARE_SIZE, (ycor* SQUARE_SIZE-3));
                        rickshaw.setPosition(xcor* SQUARE_SIZE, ycor* SQUARE_SIZE);
                        location.setPosition(Dest_x* SQUARE_SIZE, Dest_y* SQUARE_SIZE);

                        passengerr.setPosition(Pick_x* SQUARE_SIZE, Pick_y* SQUARE_SIZE-3);

                        int toll_x = 0, toll_y = 0;
                        do
                        {
                            toll_x = rand() % 14;
                            toll_y = rand() % 14;

                        } while (currentPosition[toll_x][toll_y] != 1);

                        Tollplaza.setPosition(toll_x * SQUARE_SIZE, toll_y * SQUARE_SIZE); /////////toll plaza ki position abhi random krni he

                        bike.setScale((SQUARE_SIZE+10) / bike.getLocalBounds().width, (SQUARE_SIZE + 17) / bike.getLocalBounds().height);
                        car.setScale(SQUARE_SIZE / car.getLocalBounds().width, SQUARE_SIZE / car.getLocalBounds().height);
                        rickshaw.setScale((SQUARE_SIZE + 7) / rickshaw.getLocalBounds().width, (SQUARE_SIZE + 7) / rickshaw.getLocalBounds().height);
                        cartraffic.setScale(SQUARE_SIZE / cartraffic.getLocalBounds().width, SQUARE_SIZE / cartraffic.getLocalBounds().height);
                        Tollplaza.setScale((SQUARE_SIZE + 20) / Tollplaza.getLocalBounds().width, (SQUARE_SIZE + 20) / Tollplaza.getLocalBounds().height);
                        passengerr.setScale((SQUARE_SIZE+20) / passengerr.getLocalBounds().width, (SQUARE_SIZE+36) / passengerr.getLocalBounds().height);

                        float locationScaleFactor = 2.3f; // Adjust the scale factor as needed
                        location.setScale((SQUARE_SIZE* locationScaleFactor+2) / car.getLocalBounds().width, (SQUARE_SIZE* locationScaleFactor+6) / car.getLocalBounds().height);

                        r1.setTotalDistance(0.0);
                        //f1.setRates();
                        //value.setString("0.00 km");

                        EndRide = 0;

                        MainMenuclick.play();

                    }
                }

                else if (TripsHistoryPage)
                {
                    if (Trips_History_close.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        MainMenu = true;
                        TripsHistoryPage = 0;
                    }
                }

                else if (AccountDetailsPage)
                {
                    if (AccountDetailsClose.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        MainMenu = true;
                        AccountDetailsPage = 0;
                    }
                }

                else if (CreateAccountPage)
                {
                    if (FirstName.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Magenta); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);

                        FirstNameselected = true;
                        LastNameselected = 0; ageselected = 0; PhoneNoselected = 0; newUsernameselected = 0; newPasswordselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;
                    }
                    else if (LastName.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Magenta); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);

                        LastNameselected = true;
                        FirstNameselected = 0; ageselected = 0; PhoneNoselected=0; newUsernameselected = 0; newPasswordselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;
                    }
                    else if (Age.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Magenta);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);

                        ageselected = true;
                        FirstNameselected = 0; LastNameselected = 0; PhoneNoselected = 0; newUsernameselected = 0; newPasswordselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;
                    }
                    else if (PhoneNo.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Magenta); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);

                        PhoneNoselected = true;
                        FirstNameselected = 0; LastNameselected = 0; ageselected = 0; newUsernameselected = 0; newPasswordselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;

                    }
                    else if (NewUserName.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Magenta); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);

                        newUsernameselected = true;
                        FirstNameselected = 0; LastNameselected = 0; ageselected = 0; PhoneNoselected = 0; newPasswordselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;
                    }
                    else if (NewPassword.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Magenta); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);

                        newPasswordselected = true;
                        FirstNameselected = 0; LastNameselected = 0; ageselected = 0; PhoneNoselected = 0; newUsernameselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;
                    }
                    else if (VehicleModel.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Magenta);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);

                        vehicleModelselected = true;
                        FirstNameselected = 0; LastNameselected = 0; ageselected = 0; PhoneNoselected = 0; newUsernameselected = 0; newPasswordselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;
                    }
                    else if (CarOptionDisplay.getGlobalBounds().contains(mousePos.x, mousePos.y)) 
                    {
                        Vehicle_Type = "car";
                        
                        CarOptionDisplay.setOutlineColor(sf::Color::Magenta);
                        BikeOptionDisplay.setOutlineColor(sf::Color::Black);
                        RickshawOptionDisplay.setOutlineColor(sf::Color::Black);
                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);
                    }
                    else if (BikeOptionDisplay.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        Vehicle_Type = "bike";
                        
                        CarOptionDisplay.setOutlineColor(sf::Color::Black);
                        BikeOptionDisplay.setOutlineColor(sf::Color::Magenta);
                        RickshawOptionDisplay.setOutlineColor(sf::Color::Black);
                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);
                    }
                    else if (RickshawOptionDisplay.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        Vehicle_Type = "rickshaw";
                        
                        CarOptionDisplay.setOutlineColor(sf::Color::Black);
                        BikeOptionDisplay.setOutlineColor(sf::Color::Black);
                        RickshawOptionDisplay.setOutlineColor(sf::Color::Magenta);
                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Black);
                    }
                    else if (VehicleRegistrationNo.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Magenta); EnginePower.setOutlineColor(sf::Color::Black);

                        vehicleRegistrationselected = true;
                        FirstNameselected = 0; LastNameselected = 0; ageselected = 0; PhoneNoselected = 0; newUsernameselected = 0; newPasswordselected = 0; vehicleModelselected = 0; enginePowerselected = 0;
                    }
                    else if (EnginePower.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        FirstName.setOutlineColor(sf::Color::Black); LastName.setOutlineColor(sf::Color::Black); PhoneNo.setOutlineColor(sf::Color::Black); Age.setOutlineColor(sf::Color::Black);
                        NewUserName.setOutlineColor(sf::Color::Black); NewPassword.setOutlineColor(sf::Color::Black); VehicleModel.setOutlineColor(sf::Color::Black);
                        VehicleRegistrationNo.setOutlineColor(sf::Color::Black); EnginePower.setOutlineColor(sf::Color::Magenta);

                        enginePowerselected = true;
                        FirstNameselected = 0; LastNameselected = 0; ageselected = 0; PhoneNoselected = 0; newUsernameselected = 0; newPasswordselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0;
                    }

                    else if (SubmitForm.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        bool checksPassed = true;

                        if(!isFirstName(firstname))
                        {
                            FirstName.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            FirstName.setOutlineColor(sf::Color::Green);
                        }
                        if(!isLastName(lastname))
                        {
                            LastName.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            LastName.setOutlineColor(sf::Color::Green);
                        }
                        if(!isDigits(PhoneNumber))
                        {
                            PhoneNo.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            PhoneNo.setOutlineColor(sf::Color::Green);
                        }
                        if(!isAge(age))
                        {
                            Age.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            Age.setOutlineColor(sf::Color::Green);
                        }
                        if(!isUserUnique(newUsername))
                        {
                            NewUserName.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            NewUserName.setOutlineColor(sf::Color::Green);
                        }
                        if(!isPassword(newPassword))
                        {
                            NewPassword.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            NewPassword.setOutlineColor(sf::Color::Green);
                        }
                        if(!isVehicleType(Vehicle_Type))
                        {
                            CarOptionDisplay.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            CarOptionDisplay.setOutlineColor(sf::Color::Black);
                        }
                        if(!isModel(vehicleModel))
                        {
                            VehicleModel.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            VehicleModel.setOutlineColor(sf::Color::Green);
                        }
                        if(!isRegistrationNo(vehicleRegistrationNum))
                        {
                            VehicleRegistrationNo.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            VehicleRegistrationNo.setOutlineColor(sf::Color::Green);
                        }
                        if(!isEngine(enginePowerinCC,Vehicle_Type))
                        {
                            EnginePower.setOutlineColor(sf::Color::Red); checksPassed = false;
                        }
                        else
                        {
                            EnginePower.setOutlineColor(sf::Color::Green);
                        }


                        if(checksPassed)
                        {
                            a1.set_firstName(firstname);
                            a1.set_lastName(lastname);
                            a1.set_phoneNumber(PhoneNumber);
                            a1.set_age(stoi(age));
                            a1.setUsername(newUsername);
                            a1.setPassword(newPassword);
                            v1.setVehicleType(Vehicle_Type);
                            v1.setVehicleModel(stoi(vehicleModel));
                            v1.setVehicleRegNo(vehicleRegistrationNum);
                            v1.setEnginePower(stoi(enginePowerinCC));

                            d1.create_TripsHistoryFile_Of_NewUser(a1.getUsername());

                            a1.saveAccount(Account_Details, User_Details, &v1);

                            CreateAccountPage = false;
                            LoginPage = true;

                            usernameInput = "";
                            passwordInput = "";
                            passwordDisplay = "";

                            Formsubmit.play();
                        }
                            
                    }

                    else
                    {
                        FirstNameselected = 0; LastNameselected = 0; ageselected = 0; PhoneNoselected = 0; newUsernameselected = 0; newPasswordselected = 0; vehicleModelselected = 0; vehicleRegistrationselected = 0; enginePowerselected = 0;
                    }

                }

                else if (settingsPage)
                {
                    if (UserNameChange.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        SettingsOptionSelected = 0;
                        changeUsernameOptionSelected = true;
                        changePasswordOptionSelected = 0;
                        newUsername = "";

                        MainMenuclick.play();
                        
                    }
                    if (PasswordChange.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        SettingsOptionSelected = 0;
                        changePasswordOptionSelected = true;
                        changeUsernameOptionSelected = 0;

                        newPassword = "";

                        MainMenuclick.play();
                    }
                    if (Logout.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        usernameInput = "";
                        passwordInput = "";
                        passwordDisplay = "";

                        displayText.setString("");

                        settingsPage = 0;
                        LoginPage = true;

                        MainMenuclick.play();
                    }
                    if (DeleteAccount.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        settingsPage = 0;
                        LoginPage = true;

                        usernameInput = "";
                        passwordInput = "";
                        passwordDisplay = "";

                        displayText.setString("");

                        a1.deleteAccount(a1.getUsername());

                    }
                    if (!SettingsOptionSelected)
                    {
                        if (changeUsernameOptionSelected)
                        {
                            if (changeUsername.getGlobalBounds().contains(mousePos.x, mousePos.y))
                                changeUsernameBox = true;

                            if (SettingsOptionSubmit.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            {

                                if (a1.changeUsername(a1.getUsername(), changedUsername))cout << "username changed" << endl;
                                else cout << "unable to change username" << endl;

                                a1.setAccountDetails(Account_Details, &v1, changedUsername);
                                SettingsOptionSelected = true;
                                LoginPage = true;
                                settingsPage = 0;
                                changeUsernameOptionSelected = 0;

                                usernameInput = "";
                                passwordInput = "";
                                passwordDisplay = "";
                            }
                        }

                        else if (changePasswordOptionSelected)
                        {
                            if (changePassword.getGlobalBounds().contains(mousePos.x, mousePos.y))
                                changePasswordBox = true;

                            if (SettingsOptionSubmit.getGlobalBounds().contains(mousePos.x, mousePos.y))
                            {
                                
                                if (a1.changePassword(a1.getUsername(), changedPassword))cout << "password changed" << endl;
                                else cout << "could not change password" << endl;
                                SettingsOptionSelected = true;
                                LoginPage = true;
                                settingsPage = 0;
                                changePasswordOptionSelected = 0;

                                usernameInput = "";
                                passwordInput = "";
                                passwordDisplay = "";
                            }
                        }
                    }
                    if (SettingsBack.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        settingsPage = 0;
                        MainMenu = true;

                        MainMenuclick.play();
                    }

                }

            }


 //========================================TEXT ENTERED=====================================================
            if (event.type == sf::Event::TextEntered)
            {
                if (usernameSelected)
                {
                    if (event.text.unicode == '\b' && !usernameInput.empty())
                    {
                        usernameInput.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        usernameInput += static_cast<char>(event.text.unicode);
                    }
                }

                if (passwordSelected)
                {
                    if (event.text.unicode == '\b' && !passwordInput.empty()) { // Corrected condition
                        passwordInput.pop_back(); // Use passwordInput instead of usernameInput
                        passwordDisplay.pop_back(); // Also remove from passwordDisplay
                    }
                    else if (event.text.unicode < 128) {
                        passwordInput += static_cast<char>(event.text.unicode);
                        passwordDisplay += '*';
                    }
                }

                if (FirstNameselected)
                {
                    if (event.text.unicode == '\b' && !firstname.empty())
                    {
                        firstname.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        firstname += static_cast<char>(event.text.unicode);
                    }
                }

                if (LastNameselected)
                {
                    if (event.text.unicode == '\b' && !lastname.empty())
                    {
                        lastname.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        lastname += static_cast<char>(event.text.unicode);
                    }
                }

                if (PhoneNoselected)
                {
                    if (event.text.unicode == '\b' && !PhoneNumber.empty())
                    {
                        PhoneNumber.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        PhoneNumber += static_cast<char>(event.text.unicode);
                    }
                }

                if (ageselected)
                {
                    if (event.text.unicode == '\b' && !age.empty())
                    {
                        age.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        age += static_cast<char>(event.text.unicode);
                    }
                }

                if (newUsernameselected)
                {
                    if (event.text.unicode == '\b' && !newUsername.empty())
                    {
                        newUsername.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        newUsername += static_cast<char>(event.text.unicode);
                    }
                }

                if (newPasswordselected)
                {
                    if (event.text.unicode == '\b' && !newPassword.empty())
                    {
                        newPassword.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        newPassword += static_cast<char>(event.text.unicode);
                    }
                }

                if (vehicleModelselected)
                {
                    if (event.text.unicode == '\b' && !vehicleModel.empty())
                    {
                        vehicleModel.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        vehicleModel += static_cast<char>(event.text.unicode);
                    }
                }

                if (vehicleRegistrationselected)
                {
                    if (event.text.unicode == '\b' && !vehicleRegistrationNum.empty())
                    {
                        vehicleRegistrationNum.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        vehicleRegistrationNum += static_cast<char>(event.text.unicode);
                    }
                }

                if (enginePowerselected)
                {
                    if (event.text.unicode == '\b' && !enginePowerinCC.empty())
                    {
                        enginePowerinCC.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        enginePowerinCC += static_cast<char>(event.text.unicode);
                    }
                }

                if (changeUsernameBox)
                {
                    
                    if (event.text.unicode == '\b' && !changedUsername.empty())
                    {
                        changedUsername.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        changedUsername += static_cast<char>(event.text.unicode);
                    }
                    
                }

                if (changePasswordBox)
                {
                    
                    if (event.text.unicode == '\b' && !changedPassword.empty())
                    {
                        changedPassword.pop_back();
                    }
                    else if (event.text.unicode < 128)
                    {
                        changedPassword += static_cast<char>(event.text.unicode);
                    }
                   
                }

            }

  //=======================================KEY PRESSED======================================================

            if (l1.IsDestinationReached(l1.getLongitude(), l1.getLatitude(), Dest_x, Dest_y, Pick_x, Pick_y) || showPassenger)
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
                {
                    if (l1.getLongitude() < MAP_SIZE - 1 && isColliding(l1.getLongitude() + 1, l1.getLatitude(), currentPosition))
                    {
                        l1.increaseLongitude();

                        if (!l1.IsPassengerPicked(l1.getLongitude(), l1.getLatitude(), Pick_x, Pick_y))
                        {
                            cout << "in condition" << endl;
                            isPassengerPickedup = true; showPassenger = false;
                        }

                        if (isPassengerPickedup)
                        {
                            cout << "in passenger pickedup" << endl;
                            r1.calculatePathTraveled(Traffic, &l1);
                            r1.calculate_Total_Distance_Traveled();
                            value.setString(to_string(r1.getTotalDistanceTraveled()));
                        }
                        
                        // Update car position
                        car.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        bike.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        rickshaw.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                    }
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
                {
                    if (l1.getLatitude() < MAP_SIZE - 1 && isColliding(l1.getLongitude(), l1.getLatitude() + 1, currentPosition))
                    {
                        l1.increaseLatitude();

                        if (!l1.IsPassengerPicked(l1.getLongitude(), l1.getLatitude(), Pick_x, Pick_y))
                        {
                            isPassengerPickedup = true; showPassenger = false;
                        }

                        if (isPassengerPickedup)
                        {
                            cout << "in passenger pickedup" << endl;

                            r1.calculatePathTraveled(Traffic, &l1);
                            r1.calculate_Total_Distance_Traveled();
                            value.setString(to_string(r1.getTotalDistanceTraveled()));
                        }
                        // Update car position
                        car.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        bike.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        rickshaw.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                    }
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
                {
                    if (l1.getLatitude() > 0 && isColliding(l1.getLongitude(), l1.getLatitude() - 1, currentPosition))
                    {
                        l1.decreaseLatitude();

                        if (!l1.IsPassengerPicked(l1.getLongitude(), l1.getLatitude(), Pick_x, Pick_y))
                        {
                            isPassengerPickedup = true; showPassenger = false;
                        }

                        if (isPassengerPickedup)
                        {
                            cout << "in passenger pickedup" << endl;

                            r1.calculatePathTraveled(Traffic, &l1);
                            r1.calculate_Total_Distance_Traveled();
                            value.setString(to_string(r1.getTotalDistanceTraveled()));
                        }
                        // Update car position
                        car.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        bike.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        rickshaw.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                    }
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
                {
                    if (l1.getLongitude() > 0 && isColliding(l1.getLongitude() - 1, l1.getLatitude(), currentPosition))
                    {
                        l1.decreaseLongitude();

                        if (!l1.IsPassengerPicked(l1.getLongitude(), l1.getLatitude(), Pick_x, Pick_y))
                        {
                            isPassengerPickedup = true; showPassenger = false;
                        }

                        if (isPassengerPickedup)
                        {
                            cout << "in passenger pickedup" << endl;

                            r1.calculatePathTraveled(Traffic, &l1);
                            r1.calculate_Total_Distance_Traveled();
                            value.setString(to_string(r1.getTotalDistanceTraveled()));
                        }
                        // Update car position
                        car.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        bike.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                        rickshaw.setPosition(l1.getLongitude()* SQUARE_SIZE, l1.getLatitude()* SQUARE_SIZE);
                    }
                }
            }
            else
            {
                EndRide = true;
                isPassengerPickedup = false;
            }

//=========================================MOUSE MOVED=======================================================

            if (event.type == sf::Event::MouseMoved) {
                // Get the mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check if the mouse is over the text
                if (LoginPage)
                {
                    if (loginButtonText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        loginButtonText.setFillColor(hoverColor); loginButtonText.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        loginButtonText.setFillColor(sf::Color::White); loginButtonText.setScale(originalScale);
                    }

                    if (CreateAccount.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        CreateAccount.setFillColor(hoverColor); CreateAccount.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        CreateAccount.setFillColor(sf::Color::Black); CreateAccount.setScale(originalScale);
                    }

                }

                if (CreateAccountPage)
                {
                    if (SubmitForm.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        SubmitForm.setFillColor(hoverColor); SubmitForm.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        SubmitForm.setFillColor(sf::Color::White); SubmitForm.setScale(originalScale);
                    }
                }

                if (DrawMap)
                {
                    if (Endride.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        Endride.setFillColor(hoverColor); Endride.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        Endride.setFillColor(sf::Color::White); Endride.setScale(originalScale);
                    }

                }

                if (RideRequest)
                {
                    if (RideNext.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        RideNext.setFillColor(hoverColor); RideNext.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        RideNext.setFillColor(sf::Color::White); RideNext.setScale(originalScale);
                    }
                }

                if (RideRequestName)
                {
                    if (Rideaccept.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        Rideaccept.setFillColor(hoverColor1); Rideaccept.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        Rideaccept.setFillColor(sf::Color::Black); Rideaccept.setScale(originalScale);
                    }

                    if (Ridedecline.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        Ridedecline.setFillColor(hoverColor1); Ridedecline.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        Ridedecline.setFillColor(sf::Color::Black); Ridedecline.setScale(originalScale);
                    }
                }

                if (FareReceipt)
                {
                    if (ReceiptClose.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        ReceiptClose.setFillColor(hoverColor); ReceiptClose.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        ReceiptClose.setFillColor(sf::Color::White); ReceiptClose.setScale(originalScale);
                    }
                }

                if (MainMenu)
                {
                    if (AccountDetails.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        AccountDetails.setFillColor(hoverColor); AccountDetails.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        AccountDetails.setFillColor(sf::Color::Black); AccountDetails.setScale(originalScale);
                    }

                    if (TripsHistory.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        TripsHistory.setFillColor(hoverColor); TripsHistory.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        TripsHistory.setFillColor(sf::Color::Black); TripsHistory.setScale(originalScale);
                    }

                    if (Settings.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        Settings.setFillColor(hoverColor); Settings.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        Settings.setFillColor(sf::Color::Black); Settings.setScale(originalScale);
                    }

                    if (FindRideMain.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        FindRideMain.setFillColor(hoverColor); FindRideMain.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        FindRideMain.setFillColor(sf::Color::White); FindRideMain.setScale(originalScale);
                    }
                }

                if (AccountDetailsPage)
                {
                    if (AccountDetailsClose.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        AccountDetailsClose.setFillColor(hoverColor); AccountDetailsClose.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        AccountDetailsClose.setFillColor(sf::Color::White); AccountDetailsClose.setScale(originalScale);
                    }
                }

                if (settingsPage)
                {
                    if (UserNameChange.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        UserNameChange.setFillColor(hoverColor); UserNameChange.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        UserNameChange.setFillColor(sf::Color::White); UserNameChange.setScale(originalScale);
                    }
                    if (PasswordChange.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        PasswordChange.setFillColor(hoverColor); PasswordChange.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        PasswordChange.setFillColor(sf::Color::White); PasswordChange.setScale(originalScale);
                    }
                    if (Logout.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        Logout.setFillColor(hoverColor); Logout.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        Logout.setFillColor(sf::Color::White); Logout.setScale(originalScale);
                    }
                    if (DeleteAccount.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        DeleteAccount.setFillColor(hoverColor); DeleteAccount.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        DeleteAccount.setFillColor(sf::Color::White); DeleteAccount.setScale(originalScale);
                    }
                    if (SettingsBack.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        SettingsBack.setFillColor(hoverColor); SettingsBack.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        SettingsBack.setFillColor(sf::Color::White); SettingsBack.setScale(originalScale);
                    }
                }

                if (TripsHistoryPage)
                {
                    if (Trips_History_close.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        Trips_History_close.setFillColor(hoverColor); Trips_History_close.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        Trips_History_close.setFillColor(sf::Color::White); Trips_History_close.setScale(originalScale);
                    }
                }

                if (!SettingsOptionSelected)
                {
                    if (SettingsOptionSubmit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        SettingsOptionSubmit.setFillColor(hoverColor); SettingsOptionSubmit.setScale(originalScale * scaleFactor);
                    }
                    else
                    {
                        SettingsOptionSubmit.setFillColor(sf::Color::White); SettingsOptionSubmit.setScale(originalScale);
                    }
                }

            }
        }
//===========================================================================================================
            
            window.clear();

            if (LoginPage)
            {
                window.draw(Loginform);
                window.draw(usernameLabel);
                window.draw(passwordLabel);
                window.draw(usernameBox);
                window.draw(passwordBox);
                window.draw(loginButton);
                window.draw(loginButtonText);
                window.draw(CreateAccount);

                sf::Text usernameText(usernameInput, font, 20);
                usernameText.setFillColor(sf::Color::Black);
                usernameText.setPosition(172, 190);
                window.draw(usernameText);

                sf::Text passwordText(passwordDisplay, font, 20); // Use passwordDisplay for rendering
                passwordText.setFillColor(sf::Color::Black);
                passwordText.setPosition(172, 250);
                window.draw(passwordText);

                window.draw(displayText);
            }

            if (MainMenu)
            {
                window.draw(MainMenupage);
                window.draw(WelcomeName);
                window.draw(AccountDetails);
                window.draw(TripsHistory);
                window.draw(Settings);
                window.draw(FindRideMain);
            }

            if (AccountDetailsPage)
            {
                window.draw(AccountDetailsdisplay);

                window.draw(AccountName);
                window.draw(AccountUserName);
                window.draw(AccountAge);
                window.draw(AccountPhoneNo);
                window.draw(AccountVehicleType);
                window.draw(AccountVehicleRegNo);

                window.draw(AccountDetailsclose);
                window.draw(AccountDetailsClose);
            }

            if (TripsHistoryPage)
            {
                window.draw(Trips_history);
                window.draw(Trips_History);
                window.draw(Totaltrips);
                window.draw(totalProfitEarned);
                window.draw(TotaldistanceTravelled);
                window.draw(Trips_History_close);

            }

            if (settingsPage)
            {
                if (SettingsOptionSelected)
                {
                    window.draw(Settingspage);
                    window.draw(UserNameChange);
                    window.draw(PasswordChange);
                    window.draw(Logout);
                    window.draw(DeleteAccount);
                    window.draw(SettingsBack);
                }

                else
                {
                    window.draw(SettingsPageempty);

                    if (changeUsernameOptionSelected)
                    {
                        window.draw(changeUsername);
                        window.draw(changeusername);
                        window.draw(SettingsOptionSubmit);

                        sf::Text usernamechanged(changedUsername, font, 20);
                        usernamechanged.setFillColor(sf::Color::Black);
                        usernamechanged.setPosition(188, 200);
                        window.draw(usernamechanged);

                    }
                    else if (changePasswordOptionSelected)
                    {
                        window.draw(changePassword);
                        window.draw(changepassword);
                        window.draw(SettingsOptionSubmit);

                        sf::Text passwordChanged(changedPassword, font, 20);
                        passwordChanged.setFillColor(sf::Color::Black);
                        passwordChanged.setPosition(188, 200);
                        window.draw(passwordChanged);
                    }
                }
            }

            if (RideRequest)
            {
                window.draw(FindRide);
                window.draw(RideRequestNext);
                window.draw(RideNext);
            }

            if (RideRequestName)
            {
                window.clear(sf::Color::White);
                window.draw(Ridename);
                window.draw(PassengerName);
                window.draw(Destination);
                window.draw(PickupLocation);
                window.draw(RideDecline);
                window.draw(RideAccept);
                window.draw(Rideaccept);
                window.draw(Ridedecline);
            }

            if (DrawMap)
            {
                window.clear();

                if (!isPassengerPickedup)
                {
                    window.draw(background);
                    //window.draw(passengerr);
                }
                else
                    window.draw(backgroundpassenger);

                if (v1.getVehicleType() == "car")
                    window.draw(car);

                else if (v1.getVehicleType() == "bike")
                    window.draw(bike);

                else
                    window.draw(rickshaw);

                window.draw(km);
                window.draw(value);
                window.draw(location);

                if (EndRide)
                {
                    window.draw(FinishRide);
                    window.draw(Endride);
                }

                // Draw the car on the selected row
                cartraffic.setPosition(carPosX, Traffic * 30);
                window.draw(cartraffic);

                if(showPassenger)
                window.draw(passengerr);

                // Move the car back and forth within the selected row
                if (carDirection) {
                    carPosX += carSpeed;
                    if (carPosX + 30 >= 450) {
                        carDirection = false;
                    }
                }
                else {
                    carPosX -= carSpeed;
                    if (carPosX <= 0) {
                        carDirection = true;
                    }
                }

                //window.draw(Tollplaza);
                
            }

            if (CreateAccountPage)
            {
                window.draw(CreateNewAccountform);
                window.draw(FirstName);
                window.draw(LastName);
                window.draw(PhoneNo);
                window.draw(Age);
                window.draw(NewUserName);
                window.draw(NewPassword);
                window.draw(CarOptionDisplay);
                window.draw(BikeOptionDisplay);
                window.draw(RickshawOptionDisplay);
                window.draw(VehicleModel);
                window.draw(VehicleRegistrationNo);
                window.draw(EnginePower);

                window.draw(Firstname);
                window.draw(Lastname);
                window.draw(Phoneno);
                window.draw(AgeText);
                window.draw(Newusername);
                window.draw(Newpassword);
                window.draw(TextCar);
                window.draw(TextBike);
                window.draw(TextRickshaw);
                window.draw(Vehiclemodel);
                window.draw(Registrationno);
                window.draw(Enginepower);

                window.draw(SubmitForm);

                /////////////////////

                sf::Text usernameText(firstname, font, 18);
                usernameText.setFillColor(sf::Color::Black);
                usernameText.setPosition(113, 60);
                window.draw(usernameText);

                sf::Text usernameText1(lastname, font, 18);
                usernameText1.setFillColor(sf::Color::Black);
                usernameText1.setPosition(323, 60);
                window.draw(usernameText1);

                sf::Text usernameText2(PhoneNumber, font, 18);
                usernameText2.setFillColor(sf::Color::Black);
                usernameText2.setPosition(168, 100);
                window.draw(usernameText2);

                sf::Text usernameText3(age, font, 18);
                usernameText3.setFillColor(sf::Color::Black);
                usernameText3.setPosition(78, 140);
                window.draw(usernameText3);

                sf::Text usernameText4(newUsername, font, 18);
                usernameText4.setFillColor(sf::Color::Black);
                usernameText4.setPosition(168, 180);
                window.draw(usernameText4);

                sf::Text usernameText5(newPassword, font, 18);
                usernameText5.setFillColor(sf::Color::Black);
                usernameText5.setPosition(168, 220);
                window.draw(usernameText5);

                sf::Text usernameText6(vehicleModel, font, 18);
                usernameText6.setFillColor(sf::Color::Black);
                usernameText6.setPosition(163, 325);
                window.draw(usernameText6);

                sf::Text usernameText7(vehicleRegistrationNum, font, 18);
                usernameText7.setFillColor(sf::Color::Black);
                usernameText7.setPosition(223, 370);
                window.draw(usernameText7);

                sf::Text usernameText8(enginePowerinCC, font, 18);
                usernameText8.setFillColor(sf::Color::Black);
                usernameText8.setPosition(193, 410);
                window.draw(usernameText8);
           
            }
             
            if (FareReceipt)
            {
                window.clear();
                window.draw(receipt);
                window.draw(PassengerName_On_Receipt);
                window.draw(TravelledDistance);
                window.draw(ChargesPerKm);
                window.draw(Toll_Tax_Charges);
                window.draw(TrafficSurcharge);
                window.draw(TotalCharges);
                window.draw(FuelPrice);
                window.draw(Profit);
                window.draw(Receiptclose);
                window.draw(ReceiptClose);     
            }

                window.display();
        
    }
    return 0;
}
