#include<iostream>
#include<fstream>
#include "Car_showroom.cpp"
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
    void updateCar();
};
ShowRoom cars;
int cnt=0;

char* ShowRoom::getName()
{
    return carName;
}
void ShowRoom::writeToFile()
{
    ofstream car("Car.txt",ios::binary|ios::app);
    cars.getCarInfo();
    cout<<"Enter Current date(dd-mm-yy):";
    cin>>cars.addedDate;
    cin.ignore();
    car.write(reinterpret_cast<char*>(&cars),sizeof(ShowRoom));
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

int main()
{
    ShowRoom m;
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
        //  case 5:
        }
    }
    while(opt!=6);
    return 0;
}
