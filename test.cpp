/*Write a program that uses a structure to store the following inventory data in a file: Item
Description, Quantity, WholeSaleCost, RetailCost, DateaddedtoInventory. The program should
allow the user to perform the addition of records to file and display of the records from file.
*/
#include<iostream>
#include<fstream>
using namespace std;

struct product
{
    char des[40];
    int qua;
    float whole, ret;
    char date[11];
};

int main()
{
    product p,p1;
    char ch;
    int i = 0;
    cout<<"\t\t\tINVENTORY\n\n";
    ofstream f1("Inventory.txt",ios::binary);
    do{
        cout<<"\nITEM "<<i+1<<endl;
        i++;
        cout<<"Enter the item description\n";
        cin.getline(p.des,40);
        cout<<"Enter the quantity of item\n";
        cin>>p.qua;
        cout<<"Enter the wholesale price and retail price\n";
        cin>>p.whole>>p.ret;
        cout<<"Enter the date when item was added to inventory (in dd-mm-yyyy format)\n";
        cin>>p.date;
        f1.write(reinterpret_cast<char*>(&p), sizeof(product));
        cout<<"Do you wish to add another item to the inventory(y/n)\n";
        cin>>ch;
        cin.ignore();
    }while(ch == 'y'||ch == 'Y');
    f1.close();
    ifstream f2("Inventory.txt",ios::binary);
    while(!f2.eof())
    {
        f2.read(reinterpret_cast<char*>(&p1), sizeof(product));
        if(!f2.eof())
        {

            cout<<"\nITEM\n";
            cout<<"Item Description : "<<p1.des<<endl;
            cout<<"Quantity : "<<p1.qua<<endl;
            cout<<"Wholesale Price : "<<p1.whole<<"\nRetail Price : "<<p.ret<<endl;
            cout<<"Date : "<<p1.date<<endl;
        }
    }


}
