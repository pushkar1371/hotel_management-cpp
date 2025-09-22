/*
    Title        : Hotel Management System
    Language     : Modern C++ (g++)
    Author       : Pushkar Bopanwar
    Updated By   : Pushkar
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

// MARK:- Interface Functions

void intro()
{
    cout << "\n\n\t   C++ Project On Hotel Management System";
    cout << "\n\n\t\t\t     MADE BY";
    cout << "\n----------------------------------------------";
    cout << "\n\t\t\t   Pushkar Deepak Bopanwar";
    cout << "\n----------------------------------------------\n";
}

void head()
{
    cout << "\n----------------------------------------------";
    cout << "\n\t\t  FCMR Group of Hotels";
    cout << "\n----------------------------------------------\n";
}

void waitForEnter()
{
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}

// MARK:- Hotel Class

class hotel
{
private:
    int room_no;
    string name;
    string address;
    string phone;
    int days;
    float fare;

public:
    void main_menu();     // main menu
    void add();           // book a room
    void display();       // display a customer record
    void rooms();         // display all rooms
    void edit();          // edit a record
    int check(int);       // check if room is booked
    void modify(int);     // modify a record
    void delete_rec(int); // delete a record
};

void hotel::main_menu()
{
    int choice = 0;
    while (choice != 5)
    {
        system("clear"); // use "cls" for Windows
        head();
        cout << "\n\t*************";
        cout << "\n\t* MAIN MENU *";
        cout << "\n\t*************";
        cout << "\n\n1. Book A Room";
        cout << "\n2. Customer Record";
        cout << "\n3. Rooms Allotted";
        cout << "\n4. Edit Record";
        cout << "\n5. Exit";
        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            display();
            break;
        case 3:
            rooms();
            break;
        case 4:
            edit();
            break;
        case 5:
            break;
        default:
            cout << "\nWrong choice!";
            waitForEnter();
        }
    }
}

void hotel::add()
{
    system("clear");
    head();
    int r, flag;
    ofstream fout("Record.dat", ios::app | ios::binary);
    cout << "\nEnter Customer Details";
    cout << "\n----------------------";
    cout << "\nRoom no: ";
    cin >> r;
    flag = check(r);
    if (flag)
        cout << "\nSorry..!!! Room is already booked";
    else
    {
        room_no = r;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Address: ";
        getline(cin, address);
        cout << "Phone No: ";
        getline(cin, phone);
        cout << "No of Days to Checkout: ";
        cin >> days;
        fare = days * 900; // default price per day
        fout.write((char *)this, sizeof(hotel));
        cout << "\nRoom is booked...!!!";
    }
    fout.close();
    waitForEnter();
}

void hotel::display()
{
    system("clear");
    head();
    ifstream fin("Record.dat", ios::in | ios::binary);
    int r, flag = 0;
    cout << "\nEnter room no: ";
    cin >> r;
    while (fin.read((char *)this, sizeof(hotel)))
    {
        if (room_no == r)
        {
            system("clear");
            head();
            cout << "\nCustomer Details";
            cout << "\n----------------";
            cout << "\nRoom no: " << room_no;
            cout << "\nName: " << name;
            cout << "\nAddress: " << address;
            cout << "\nPhone no: " << phone;
            cout << "\nDays: " << days;
            cout << "\nTotal Fare: " << fare;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\nSorry Room no. not found or vacant....!!";
    fin.close();
    waitForEnter();
}

void hotel::rooms()
{
    system("clear");
    head();
    ifstream fin("Record.dat", ios::in | ios::binary);
    cout << "\nList Of Rooms Allotted";
    cout << "\n----------------------";
    while (fin.read((char *)this, sizeof(hotel)))
    {
        cout << "\nRoom no: " << room_no << "\nName: " << name;
        cout << "\nAddress: " << address << "\nPhone: " << phone;
        cout << "\nDays: " << days << "\nTotal: " << fare;
        cout << "\n**********************************";
    }
    fin.close();
    waitForEnter();
}

void hotel::edit()
{
    system("clear");
    head();
    int choice, r;
    cout << "\nEDIT MENU";
    cout << "\n---------";
    cout << "\n1. Modify Customer Record";
    cout << "\n2. Delete Customer Record";
    cout << "\nEnter your choice: ";
    cin >> choice;

    cout << "\nEnter room no: ";
    cin >> r;
    switch (choice)
    {
    case 1:
        modify(r);
        break;
    case 2:
        delete_rec(r);
        break;
    default:
        cout << "\nWrong Choice.....!!";
    }
    waitForEnter();
}

int hotel::check(int r)
{
    int flag = 0;
    ifstream fin("Record.dat", ios::in | ios::binary);
    while (fin.read((char *)this, sizeof(hotel)))
    {
        if (room_no == r)
        {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

void hotel::modify(int r)
{
    system("clear");
    head();
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read((char *)this, sizeof(hotel)))
    {
        pos = file.tellg();
        if (room_no == r)
        {
            cout << "\nEnter New Details";
            cout << "\n-----------------";
            cin.ignore();
            cout << "Name: ";
            getline(cin, name);
            cout << "Address: ";
            getline(cin, address);
            cout << "Phone no: ";
            getline(cin, phone);
            cout << "Days: ";
            cin >> days;
            fare = days * 900;
            file.seekp(pos - sizeof(hotel));
            file.write((char *)this, sizeof(hotel));
            cout << "\nRecord is modified....!!";
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\nSorry Room no. not found or vacant...!!";
    file.close();
}

void hotel::delete_rec(int r)
{
    system("clear");
    head();
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in | ios::binary);
    ofstream fout("temp.dat", ios::out | ios::binary);
    while (fin.read((char *)this, sizeof(hotel)))
    {
        if (room_no == r)
        {
            cout << "\nName: " << name;
            cout << "\nAddress: " << address;
            cout << "\nPhone No: " << phone;
            cout << "\nDays: " << days;
            cout << "\nTotal Fare: " << fare;
            cout << "\n\nDo you want to delete this record (y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write((char *)this, sizeof(hotel));
            flag = 1;
        }
        else
        {
            fout.write((char *)this, sizeof(hotel));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\nSorry room no. not found or vacant...!!";
    else
    {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
        cout << "\nRecord deleted successfully!";
    }
}

// MARK:- Main Function

int main()
{
    hotel h;
    system("clear");
    intro();
    waitForEnter();

    system("clear");
    head();
    string id, pass;
    cout << "\nUsername => ";
    cin >> id;
    cout << "Password => ";
    cin >> pass;
    if (id == "admin" && pass == "123456")
        cout << "\nLogin Successful!";
    else
    {
        cout << "\nINVALID CREDENTIALS!";
        return 0;
    }
    waitForEnter();
    h.main_menu();
    return 0;
}
