#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

struct Staff
{
    string username;
    string password;
    string phone_number;
    string create_at;
};

string get_current_time()
{
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;
    string am_pm = "AM";
    stringstream string_h, string_m, string_s;
    string_h << hour;
    string_m << minute;
    string_s << second;
    string h = string_h.str();
    string m = string_m.str();
    string s = string_s.str();

    string time;
    if (hour < 10)
    {
        h = "0" + h;
    }
    else
    {
        h = string_h.str();
    }
    if (minute < 10)
    {
        m = "0" + m;
    }
    else
    {
        m = string_m.str();
    }

    if (second < 10)
    {
        s = "0" + s;
    }
    else
    {
        s = s = string_s.str();
    }

    if (hour < 12)
    {
        am_pm = " AM";
    }
    else
    {
        am_pm = "PM";
    }
    time = h + ":" + m + ":" + s + am_pm;
    return time;
}

void read_staff_file()
{
    ifstream staffFile("staff.txt");
    if (!staffFile)
    {
        cout << "\tNo staff!!" << endl;
    }
    string data;
    cout << "\t=================\tStaff table\t================" << endl;
    cout << "\t" << left << setw(15) << "Name" << left << setw(15) << "Phone" << left << setw(15) << "Password"
         << "Create at" << endl;
    cout << "\t========================================================" << endl;
    while (getline(staffFile, data))
    {
        cout << data << "\n";
    }
    cout << "\t========================================================" << endl;
    staffFile.close();
}

bool staff_sign_in()
{
    string username, password, phone_number;
    cout << "\tEnter username: ";
    cin >> username;
    cin.seekg(0, ios::end);
    cin.clear();
    cout << "\tEnter phone number: ";
    cin >> phone_number;
    cin.seekg(0, ios::end);
    cin.clear();
    cout << "\tEnter password: ";
    cin >> password;
    cin.seekg(0, ios::end);
    cin.clear();
    ifstream staffFile("staff.txt");
    if (!staffFile)
    {
        cout << "\tNo staff yet!" << endl;
        return false;
    }

    string data;
    while (getline(staffFile, data))
    {
        stringstream ss(data);
        string username_stored, phone_number_stored, password_stored;
        ss >> username_stored >> phone_number_stored >> password_stored;
        if (username_stored == username && phone_number_stored == phone_number && password_stored == password)
        {
            staffFile.close();
            return true;
        }
    }
    staffFile.close();
    return false;
}

void add_student()
{
    string student_name, student_id, type_of_vehicle, create_at;
    cout << "\t==>> Note: there are there types of vehicle for students" << endl;
    cout << "\tBike" << endl;
    cout << "\tMotor" << endl;
    cout << "\tCar" << endl;
    cout << "\t==========" << endl;
    cout << "\tEnter studentname: ";
    cin >> student_name;
    cin.seekg(0, ios::end);
    cin.clear();
    cout << "\tEnter student id: ";
    cin >> student_id;
    cin.seekg(0, ios::end);
    cin.clear();
    cout << "\tEnter student's vehicle type: ";
    cin >> type_of_vehicle;
    cin.seekg(0, ios::end);
    cin.clear();
    create_at = get_current_time();
    ofstream studentFile("student.txt", ios::app);
    if (!studentFile)
    {
        cout << "\terror hz" << endl;
        return;
    }
    studentFile << "\t" << left << setw(10) << student_id << left << setw(10) << student_name << left << setw(10) << type_of_vehicle << left << setw(10) << create_at << endl;
    studentFile.close();
    cout << "\t\astudent has been created successfully!!" << endl;
}

void remove_student()
{
    string studentName;
    cout << "\t>> Note: Remove function is used to remove those who leave unversity" << endl;
    cout << "\tEnter Student name to remove from file: ";
    cin >> studentName;
    cin.seekg(0, ios::end);
    cin.clear();
    ifstream studentFile("student.txt");
    if (!studentFile)
    {
        cout << "\terror!!" << endl;
        return;
    }
    ofstream tempFile("temp.txt");
    if (!tempFile)
    {
        cout << "error to create temporary file@" << endl;
        return;
    }
    string data;
    bool student_found = false;
    while (getline(studentFile, data))
    {
        stringstream ss(data);
        string studentId_stored, student_name_stored, type_vehicle_stored, time_stored;
        ss >> studentId_stored >> student_name_stored >> type_vehicle_stored >> time_stored;
        if (student_name_stored != studentName)
        {
            tempFile << data << endl;
        }
        else
        {
            student_found = true;
        }
    }

    studentFile.close();
    tempFile.close();

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (student_found)
    {
        cout << "\tStudent has been removed successfully." << endl;
    }
    else
    {
        cout << "\tStudent not found." << endl;
    }
}

void view_student()
{
    ifstream studentFile("student.txt");
    if (!studentFile)
    {
        cout << "\terror to open file" << endl;
        return;
    }
    string data;
    cout << "\t========="
         << "\t"
         << "Student table"
         << "\t"
         << "==========" << endl;
    cout << "\t" << left << setw(10) << "ID" << left << setw(10) << "Name" << left << setw(10) << "Type" << left << setw(10) << "Enter at" << endl;
    cout << "\t==========================================" << endl;
    while (getline(studentFile, data))
    {
        stringstream ss(data);
        cout << data << endl;
    }
    cout << "\t==========================================" << endl;
    studentFile.close();
}

void search_student()
{
    string search_id;
    cout << "\tEnter student id to search: ";
    cin >> search_id;
    cin.seekg(0, ios::end);
    cin.clear();
    ifstream studentFile("student.txt");
    if (!studentFile)
    {
        cout << "\tError..." << endl;
        return;
    }
    string data;
    bool student_found = false;
    while (getline(studentFile, data))
    {
        stringstream ss(data);
        string stored_id, student_name, type, create_at;
        ss >> stored_id >> student_name >> type >> create_at;
        if (stored_id == search_id)
        {
            cout << "\tStudent found!" << endl;
            cout << "\tId: " << stored_id << endl;
            cout << "\tName: " << student_name << endl;
            cout << "\tVehicle type: " << type << endl;
            cout << "\tGet in at: " << create_at << endl;
            student_found = true;
            break;
        }
    }
    if (student_found == false)
    {
        cout << "\tStudent not found" << endl;
    }
    studentFile.close();
}

void student_management()
{
    int option;
    while (1)
    {
        cout << endl;
        cout << "\t======= Student management ===== " << endl;
        cout << "\t1. Add student" << endl;
        cout << "\t2. Remove student" << endl;
        cout << "\t3. View all students " << endl;
        cout << "\t4. Search for student" << endl;
        cout << "\t5. Back" << endl;
        cout << "\tEnter your option: ";
        cin >> option;
        system("cls");
        switch (option)
        {
        case 1:
            add_student();
            cout << "\tPress any key to conticue..." << endl;
            cin.ignore();
            break;
        case 2:
            remove_student();
            cout << "\tPress any key to conticue..." << endl;
            cin.ignore();
            break;
        case 3:
            view_student();
            break;
        case 4:
            search_student();
            cout << "\tPress any key to conticue..." << endl;
            cin.ignore();
            break;
        case 5:
            return;
        default:
            cout << "\tInvalid option!! Please try again" << endl;
            break;
        }
    }
}

//* in progress function

void staff_sign_up()
{
    string username, password, phone_number;
    cout << "\tEnter username: ";
    cin >> username;
    cin.seekg(0, ios::end);
    cin.clear();
    cout << "\tEnter phone number: ";
    cin >> phone_number;
    cin.seekg(0, ios::end);
    cin.clear();
    cout << "\tEnter password: ";
    cin >> password;
    cin.seekg(0, ios::end);
    cin.clear();

    Staff staff;
    staff.username = username;
    staff.phone_number = phone_number;
    staff.password = password;
    ofstream staffFile("staff.txt", ios::app);
    string create_at = get_current_time();
    if (!staffFile)
    {
        cout << "\terror to open staff file" << endl;
        return;
    }
    staffFile << "\t" << left << setw(15) << staff.username << left << setw(15) << staff.phone_number << left << setw(15) << staff.password << create_at << endl;
    staffFile.close();
    cout << "\tYou created new accound successfully!!" << endl;
    cout << "Continue....?" << endl;
    system("pause");
    student_management();
}

int main()
{
    int option, view_staff;
    bool loggedIn = false, valid_input = false;
    //* When user input wrong format then this function will run
    while (!valid_input)
    {
        cout << "\n\tEnter [1] to see staff: ";
        cin >> view_staff;
        cout << endl;
        if (cin.fail())
        {
            cin.clear();
            //* stop characters when you press enter(\n) , this will clear buffer after inputting string
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\tInvalid format. Please enter number" << endl;
        }
        else
        {
            //* Get out from the loop if user input the right format. For example they input any number not string
            valid_input = true;
        }
    }

    if (view_staff == 1)
    {
        read_staff_file();
    }
    else
    {
        cout << "\tInvalid number! Feel free to input again" << endl;
    }
    cout << endl;
    system("pause");
    cout << endl;
    while (true)
    {
        cout << "\t=== Welcome to our system ===" << endl;
        cout << "\t1. Sign in" << endl;
        cout << "\t2. Sign up" << endl;
        cout << "\t3. Exite" << endl;
        cout << "\tEnter your option: ";
        cin >> option;
        switch (option)
        {
        case 1:
            loggedIn = staff_sign_in();
            if (loggedIn)
            {
                system("cls");
                cout << "\tSigned in successfully!!" << endl;
                student_management();
            }
            else
            {
                cout << "Invalid ey muy hz!!" << endl;
            }
            break;
        case 2:
            staff_sign_up();
            student_management();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "\tinvalid option" << endl;
            break;
        }
    }

    cout << "Test branch has been added by lyna cute girl" << endl;

    return 0;
}