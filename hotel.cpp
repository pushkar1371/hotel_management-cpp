#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

// MARK:- Interface Functions

void intro()
{
    cout << "\n\n\t====================================================";
    cout << "\n\t           HOTEL MANAGEMENT SYSTEM";
    cout << "\n\t====================================================";
    cout << "\n\t\t\t   MADE BY Pushkar Deepak Bopanwar";
    cout << "\n\t====================================================\n";
}

void head()
{
    cout << "\n\t----------------------------------------------------";
    cout << "\n\t\t      FCMR GROUP OF HOTELS";
    cout << "\n\t----------------------------------------------------\n";
}

void waitForEnter()
{
    cout << "\n\tPress ENTER to continue...";
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
    // Getters
    int getRoomNo() const { return room_no; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    int getDays() const { return days; }
    float getFare() const { return fare; }

    // Setters
    void setRoomNo(int r) { room_no = r; }
    void setName(const string &n) { name = n; }
    void setAddress(const string &a) { address = a; }
    void setPhone(const string &p) { phone = p; }
    void setDays(int d)
    {
        days = d;
        fare = days * 900;
    }

    // Member functions
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);

    // Helper functions to read/write text
    void writeRecord(ofstream &fout) const;
    bool readRecord(ifstream &fin);
};

// MARK:- Text File Helpers

void hotel::writeRecord(ofstream &fout) const
{
    fout << room_no << '\n'
         << name << '\n'
         << address << '\n'
         << phone << '\n'
         << days << '\n'
         << fare << '\n';
}

bool hotel::readRecord(ifstream &fin)
{
    if (!(fin >> room_no))
        return false;
    fin.ignore();
    getline(fin, name);
    getline(fin, address);
    getline(fin, phone);
    fin >> days;
    fin >> fare;
    fin.ignore();
    return true;
}

// MARK:- Main Menu Functions

void hotel::main_menu()
{
    int choice = 0;
    while (choice != 5)
    {
        system("clear");
        head();
        cout << "\n\t******************** MAIN MENU ********************";
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
            cout << "\n\tThank you for using the system!\n";
            break;
        default:
            cout << "\n\tInvalid choice! Try again.";
            waitForEnter();
        }
    }
}

void hotel::add()
{
    system("clear");
    head();
    int r;
    cout << "\n\t****************** BOOK A ROOM ******************\n";
    cout << "\nEnter Room No: ";
    cin >> r;

    if (check(r))
    {
        cout << "\n\tSorry! Room " << r << " is already booked.";
    }
    else
    {
        setRoomNo(r);
        cin.ignore();
        string temp;
        cout << "Name: ";
        getline(cin, temp);
        setName(temp);
        cout << "Address: ";
        getline(cin, temp);
        setAddress(temp);
        cout << "Phone No: ";
        getline(cin, temp);
        setPhone(temp);
        int d;
        cout << "No of Days to Checkout: ";
        cin >> d;
        setDays(d);

        ofstream fout("Record.txt", ios::app);
        writeRecord(fout);
        fout.close();

        cout << "\n\tRoom " << r << " booked successfully!";
    }
    waitForEnter();
}

void hotel::display()
{
    system("clear");
    head();
    ifstream fin("Record.txt");
    int r;
    bool flag = false;
    cout << "\n\t*************** CUSTOMER RECORD ****************\n";
    cout << "\nEnter Room No: ";
    cin >> r;

    hotel temp;
    while (temp.readRecord(fin))
    {
        if (temp.getRoomNo() == r)
        {
            system("clear");
            head();
            cout << "\n\t********** CUSTOMER DETAILS **********\n";
            cout << "Room No      : " << temp.getRoomNo() << "\n";
            cout << "Name         : " << temp.getName() << "\n";
            cout << "Address      : " << temp.getAddress() << "\n";
            cout << "Phone No     : " << temp.getPhone() << "\n";
            cout << "Days         : " << temp.getDays() << "\n";
            cout << "Total Fare   : " << temp.getFare() << "\n";
            flag = true;
            break;
        }
    }
    if (!flag)
        cout << "\n\tSorry! Room not found or vacant.";
    fin.close();
    waitForEnter();
}

void hotel::rooms()
{
    system("clear");
    head();
    ifstream fin("Record.txt");
    hotel temp;
    cout << "\n\t************* ROOMS ALLOTTED *************\n";
    while (temp.readRecord(fin))
    {
        cout << "\nRoom No      : " << temp.getRoomNo();
        cout << "\nName         : " << temp.getName();
        cout << "\nAddress      : " << temp.getAddress();
        cout << "\nPhone No     : " << temp.getPhone();
        cout << "\nDays         : " << temp.getDays();
        cout << "\nTotal Fare   : " << temp.getFare();
        cout << "\n--------------------------------------------";
    }
    fin.close();
    waitForEnter();
}

int hotel::check(int r)
{
    ifstream fin("Record.txt");
    hotel temp;
    while (temp.readRecord(fin))
    {
        if (temp.getRoomNo() == r)
        {
            fin.close();
            return 1;
        }
    }
    fin.close();
    return 0;
}

void hotel::edit()
{
    system("clear");
    head();
    int choice, r;
    cout << "\n\t**************** EDIT MENU ****************\n";
    cout << "1. Modify Customer Record\n2. Delete Customer Record\n";
    cout << "\nEnter your choice: ";
    cin >> choice;
    cout << "Enter Room No: ";
    cin >> r;

    ifstream fin("Record.txt");
    ofstream fout("Temp.txt");
    hotel temp;
    bool found = false;

    while (temp.readRecord(fin))
    {
        if (temp.getRoomNo() == r)
        {
            found = true;
            if (choice == 1)
            {
                cin.ignore();
                string t;
                cout << "New Name: ";
                getline(cin, t);
                temp.setName(t);
                cout << "New Address: ";
                getline(cin, t);
                temp.setAddress(t);
                cout << "New Phone: ";
                getline(cin, t);
                temp.setPhone(t);
                int d;
                cout << "New Days: ";
                cin >> d;
                temp.setDays(d);
                cout << "\n\tRecord modified!";
                temp.writeRecord(fout);
            }
            else if (choice == 2)
            {
                char ch;
                cout << "\nDo you want to delete this record (y/n): ";
                cin >> ch;
                if (ch == 'n')
                    temp.writeRecord(fout); // keep record
                continue;                   // skip writing to delete
            }
        }
        else
        {
            temp.writeRecord(fout); // write unmodified records
        }
    }

    fin.close();
    fout.close();
    remove("Record.txt");
    rename("Temp.txt", "Record.txt");

    if (!found)
        cout << "\n\tRoom not found!";
    waitForEnter();
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

