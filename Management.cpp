#include<iostream>
#include <ctime>
#include<fstream>
#include "Car_showroom.cpp"
using namespace std;


class Manage:public Car
{
    char addedDate[15];

public:
            Manage()
            {strcpy(addedDate,"NULL");}
            void writeToFile();
            void readFromFile();
};
Manage cars;
int cnt=0;

void Manage::writeToFile()
{
    ofstream car("Car.txt",ios::binary|ios::app);
    cars.getCarInfo();
    cout<<"Enter Current date(dd-mm-yy):";
    cin>>cars.addedDate;
    cin.ignore();
    car.write(reinterpret_cast<char*>(&cars),sizeof(Manage));
    car.close();
    cnt++;
}

void Manage::readFromFile()
{
    int j=0;
    Manage m2;
    int slNo=0;
    ifstream car2("Car.txt",ios::binary);
    while(!car2.eof()){
        car2.read(reinterpret_cast<char*>(&m2),sizeof(Manage));
        slNo+=1;
            if(!car2.eof())
            {
                cout<<"Car Id              : "<<slNo<<endl;
                m2.showCarInfo();
                cout<<"Added date          : "<<m2.addedDate<<endl<<endl;
            }
    }car2.close();
}
int main()
{
    Manage m;
    int opt=0;
    do
    {
        cout<<"1->Add new car.\n";
        cout<<"2->Remove car.\n";
        cout<<"3->Update car.\n";
        cout<<"4->Display cars in showroom.\n";
        cout<<"5->Search for car.\n";
        cout<<"6->Exit.\n:";
        cin>>opt;
        switch(opt)
        {
            case 1: try
                    {
                        m.writeToFile();break;
                    }catch(std::ios_base::failure &failure)
                    {
                            cout<<"Invalid input";
                            return 0;
                    }
            //case 2:
           // case 3:
           case 4: m.readFromFile();
        }
    }while(opt!=6);
    return 0;
}
