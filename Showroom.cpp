#include<iostream>
#include<stdlib.h>
#include<fstream>
#include "Car_showroom.cpp"
#include<limits>
#include<windows.h>
using namespace std;


class ShowRoom:public Car
{
    char addedDate[15];

public:
    ShowRoom()
    {
        strcpy(addedDate,"NULL");
    }
    void writeToFile();
    void readFromFile();
    void deleteCar();
    char* getName();
    char* getColour();
    double getPrice();
    void updateCar();
    void searchCar();
    friend void SetColor(int ForgC);
};
ShowRoom cars;
int cnt=0;

char* ShowRoom::getName()
{
    return carName;
}
char* ShowRoom::getColour()
{
    return carColour;
}
double ShowRoom::getPrice()
{
    return carPrice;
}
void SetColor(int ForgC)
 {
        WORD wColor;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
        return;
 }
void ShowRoom::writeToFile()
{
    ofstream car("Car.txt",ios::binary|ios::app);
    cars.getCarInfo();
    cout<<"Enter Current date(dd-mm-yy):";
    cin>>cars.addedDate;
    cin.ignore();
    car.write(reinterpret_cast<char*>(&cars),sizeof(ShowRoom));
    system("cls");
    cout<<"\n\n*** Car added ***\n\n";
    car.close();
    cnt++;
}

void ShowRoom::readFromFile()
{
    int j=0;
    ShowRoom m2;
    int slNo=0;
    ifstream car2("Car.txt",ios::binary);
    if(car2.eof())
    {
            cout<<"*** No cars in Showroom. ***\n\n";
            return;
    }
    while(!car2.eof())
    {
        car2.read(reinterpret_cast<char*>(&m2),sizeof(ShowRoom));
        slNo+=1;
        if(!car2.eof())
        {
            cout<<"Car Id              : "<<slNo<<endl;
            m2.showCarInfo();
            cout<<"Added date          : "<<m2.addedDate<<endl<<endl;
        }
    }
    car2.close();
}
void ShowRoom::updateCar()
{
	char n[100];
	fstream fp;
	int flag=0;
	ShowRoom m1;
	cin.ignore();
	cout<<"Enter car name to update: ";
	gets(n);
	fp.open("Car.txt",ios::in| ios::out|ios::binary);
	if(!fp)
	{
		cout<<"*** File not Found ***";
		return;
	}
	else
	{

		while(!fp.eof())
		{
		    fp.read(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
			if(strcmp(n,m1.getName())==0)
			{
				fp.seekg(0,ios::cur);
				cout<<"Enter new details\n"<<endl;
				m1.getCarInfo();
				fp.seekp(fp.tellg()-sizeof(m1));
				fp.write(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
				flag=1;
				cout<<"\n*** Details Updated ***\n\n";
				return;
			}
		}
	}
	if(flag==0)
        cout<<"\n\n*** Car Not Found ***\n\n";
	fp.close();
}
void ShowRoom::deleteCar()
{
	char n[100];
	ShowRoom m1;
	int flag=0;
	cin.ignore();
	cout<<"Enter car name that should be deleted :";
	gets(n);
	ofstream fp("new.txt",ios::binary);
	ifstream fp1("Car.txt",ios::binary);
	if(!fp1)
	{
		cout<<"File not Found";
		return;
	}
	else
	{
		fp1.read(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
		while(!fp1.eof())
		{
			if(strcmp(n,m1.getName())!=0)
			{
				fp.write(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
			}
			else
			{
				 cout<<"*** Car Removed from showroom ***\n "<<endl;
				 flag=1;
			}
			fp1.read(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
		}
	}
	if(flag==0)
        cout<<"\n\n*** Car Not Found ***\n\n";
	fp.close();
	fp1.close();
	remove("Car.txt");
	rename("new.txt", "Car.txt");
}

void ShowRoom::searchCar()
{
    int opt;
    char n[100];
    double cost;
	fstream fp;
	int flag=0;
	ShowRoom m1;
	cin.ignore();
	cout<<"Search car by \n1->Name \t 2->Colour \t 3->Price \t 4->Go Back\n: ";
	cin>>opt;
	fp.open("Car.txt",ios::in| ios::out|ios::binary);
	if(!fp)
	{
		cout<<"*** File not Found ***";
		return;
	}
	else
	{
		    switch(opt)
            {
                    case 1: cout<<"Enter Car name: "; cin>>n;
                            while(!fp.eof())
                            {
                                fp.read(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
                                if(!fp.eof())
                                    if(strcmp(n,m1.getName())==0)
                                        {m1.showCarInfo();cout<<"\n\n";flag=1;}
                            }break;
                    case 2: cout<<"Enter car colour: "; cin>>n;
                            while(!fp.eof())
                            {
                                fp.read(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
                                if(!fp.eof())
                                    if(strcmp(n,m1.getColour())==0)
                                        {m1.showCarInfo();cout<<"\n\n";flag=1;}
                            };break;
                    case 3: cout<<"Enter car price: "; cin>>cost;
                            while(!fp.eof())
                            {
                                fp.read(reinterpret_cast<char*>(&m1),sizeof(ShowRoom));
                                if(!fp.eof())
                                    if(cost>=m1.getPrice())
                                         {m1.showCarInfo();cout<<"\n\n";flag=1;}
                            }break;
                    case 4: return;
                        default: cout<<"\n\n*** Invalid option ***\n\n";
                                return;
			}
		}
    if(flag==0)
        cout<<"\n\n*** No cars found for your search :-( ***\n\n";
	fp.close();
}
int main()
{
    ShowRoom m;
    int opt=0;
    cout.setf(ios::fixed);
    cout.precision(2);
    SetColor(11);
    cout<<"PCP PROJECT BY AJIT HEGDE(16BM1IS400) AND PRAJWAL B.S.(1BM15IS015)\n\n";
    SetColor(15);
    while(1)
    {
        cout<<"1->Add new car.\n";
        cout<<"2->Remove car.\n";
        cout<<"3->Update car.\n";
        cout<<"4->Display cars in showroom.\n";
        cout<<"5->Search for car.\n";
        cout<<"6->Exit.\n:";
        while(!(cin>>opt)) {
            cout << "Incorrect input. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch(opt)
        {
        case 1:
            try
            {
                m.writeToFile();
                break;
            }
            catch(std::ios_base::failure &failure)
            {
                cout<<"Invalid input";
                return 0;
            }
        case 2: m.deleteCar(); break;
        case 3: m.updateCar(); break;
        case 4: m.readFromFile(); break;
        case 5: m.searchCar(); break;
        case 6: return 0;
        default:
                cout<<"\n\n**** Invalid option ****\n\n";
                break;
        }
    }
    return 0;
}


