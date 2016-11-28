#include<iostream>
#include<cstring>
using namespace std;

class Car
{public:
    char carName[20];
    double carPrice;
    int modelYear;
    char carColour[20];
    char fuelType[20];

    public:
        Car():carPrice(0),modelYear(0)
        {strcpy(carName,"NULL");strcpy(carColour,"NULL");strcpy(fuelType,"NULL");}
        void getCarInfo();
        void showCarInfo();
};

void Car::getCarInfo()
{
    cin.exceptions(std::ios_base::failbit);
    cout<<"Enter car name: ";
    cin>>carName;
    cout<<"Enter car price: ";
    cin>>carPrice;
    cout<<"Enter car Manufactured year: ";
   // cout.setf(ios::fixed);
    //cout.precision(2);
    cin>>modelYear;
    cout<<"Enter car colour: ";
    cin>>carColour;
    cout<<"Enter car fuel type: ";
    cin>>fuelType;
}

void Car::showCarInfo()
{
    cout<<"Car name            : "<<carName<<endl;
    cout<<"Year of manufacture : "<<modelYear<<endl;
    cout<<"Car Price           : "<<carPrice<<endl;
    cout<<"Colour              : "<<carColour<<endl;
    cout<<"Fuel type           : "<<fuelType<<endl;
}
