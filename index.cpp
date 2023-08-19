#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <conio.h>
using namespace std;

// :-D Global Scope declaration
const string UNIVERSITY_NAME = "1";
const string FIRST_NAME = "1";
const string LAST_NAME = "1";
const int AGE = 1;
const string GENDER = "Male";
const string PHONE_NUMBER = "1";
const string PASSWORD = "1";

// :-D Enum
enum Role
{
     NoneRole,
     UserAdmin,
     UserStaff
};

enum Gender
{
     NoGender,
     Male,
     Felmale
};

enum VehicleType
{
     NoType,
     Bike,
     Motorbike,
     Car
};

// :-D Structure
struct Admin
{
     string university_name;
     string firstname, lastname;
     int age;
     string gender;
     string phone_num;
     string password;
};

struct Staff
{
     string username;
     string password;
     string phone_number;
     string create_at;
     int price;
};

struct Student
{
     string student_id;
     string student_name;
     string vehicle_type;
     string create_at;
     int price;
};

void invalid_option_message()
{
     cout << "\tInvalid option!" << endl;
     cout << "\tInput option again" << endl;
}

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
          am_pm = " PM";
     }
     time = h + ":" + m + ":" + s + am_pm;
     return time;
}

string asterisk_display(char ch, string pw)
{
     while ((ch = _getch()) != 13)
     {
          if (ch == '\b')
          {
               if (!pw.empty())
               {
                    pw.erase(pw.size() - 1);
                    cout << "\b \b";
               }
          }
          else
          {
               pw += ch;
               cout << '*';
          }
     }
     return pw;
}

void read_staff_file()
{
     ifstream staffFile("staff.txt");
     if (!staffFile)
     {
          cout << "\tNo staff!!" << endl;
     }
     string data;
     int total_staff = 0;
     cout << "\t======================\t Staff table\t======================" << endl;
     cout << "\t" << left << setw(21) << "Name" << left << setw(15) << "Phone" << left << setw(15) << "Password"
          << "Create at" << endl;
     cout << "\t==============================================================" << endl
          << endl;
     while (getline(staffFile, data))
     {
          cout << data << "\n";
          total_staff++;
     }
     cout << "\n\t==============================================================" << endl;
     cout << "\tTotal: " << total_staff << " staff" << endl;
     staffFile.close();
}

bool staff_sign_in()
{
     string username, password, phone_number;
     char ch1;
     system("cls");
     cout << "\n\t\t >> You chose sign as a staff." << endl
          << endl;

     cout << "\tEnter username: ";
     cin.ignore();
     getline(cin, username);
     cout << "\tEnter phone number: ";
     cin >> phone_number;
     cout << "\tEnter password: ";
     password = asterisk_display(ch1, password);
     ifstream staffFile("staff.txt");
     if (!staffFile)
     {
          cout << "\tNo staff yet!" << endl;
          return false;
     }

     cout << username << "\t" << phone_number << "\t" << password << endl;

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
     string student_id, student_name, vehicle_type, time;
     int price;
     int opt_ve;
     cout << "\n\t\t >> You chose option \"[1]. add student\". " << endl
          << endl;
     cout << "\t\tEnter student ID: ";
     cin.ignore();
     getline(cin, student_id);
     cout << "\t\tEnter student name: ";
     getline(cin, student_name);
     cout << "\t\tThere are 3 types of vehicles for students" << endl;
     cout << "\t\t\t[1]. Bike" << endl;
     cout << "\t\t\t[2]. Motorbike" << endl;
     cout << "\t\t\t[3]. Car" << endl;
     cout << "\t\tEnter student's vehicle type: ";
     cin >> opt_ve;

     switch (opt_ve)
     {
     case 1:
          vehicle_type = "Bike";
          price = 100;
          break;
     case 2:
          vehicle_type = "Motorbike";
          price = 300;
          break;
     case 3:
          vehicle_type = "Car";
          price = 1000;
          break;
     default:
          cout << "\t\tInvalid option!" << endl;
          return;
     }

     time = get_current_time();

     Student student;
     student.student_id = student_id;
     student.student_name = student_name;
     student.vehicle_type = vehicle_type;
     student.price = price;
     student.create_at = time;

     ifstream studentFile("student.txt");
     ofstream tempFile("temp.txt", ios::app);

     if (!studentFile || !tempFile)
     {
          cout << "\tError opening the file" << endl;
          return;
     }

     string data;
     bool found = false;

     while (getline(studentFile, data))
     {
          stringstream ss(data);
          ss >> student.student_id >> student.student_name >> student.vehicle_type >> student.create_at >> student.price;
          if (student.student_id == student_id)
          {
               found = true;
               break;
          }
          tempFile << "\t" << left << setw(10) << student.student_id << left << setw(20) << student.student_name << left << setw(15) << student.vehicle_type << left << setw(20) << student.create_at << student.price << " riel" << endl;
     }

     studentFile.close();
     tempFile.close();

     if (found)
     {
          cout << "\n\tInvalid! This ID already exists." << endl;
          remove("temp.txt");
     }
     else
     {
          ofstream studentFile("student.txt", ios::app);
          studentFile << "\t" << left << setw(10) << student_id << left << setw(20) << student_name << left << setw(15) << vehicle_type << left << setw(20) << time << price << " riel" << endl;
          studentFile.close();
          cout << "\n\t\t\tStudent: " << student_name << " has to pay " << price << " riel."
               << "\n\t\n";
          cout << "\n\t\tPress any key after the student pays the price\n";
          getch();
          cout << "\n\t\tAdded successfully!!" << endl;
     }
}

void remove_student()
{
     string student_id;
     cout << "\n\t>> You chose removing student from the file. " << endl
          << endl;
     cout << "\tEnter Student ID to remove from the file: ";
     cin >> student_id;
     cin.seekg(0, ios::end);
     cin.clear();

     ifstream studentFile("student.txt");
     if (!studentFile)
     {
          cout << "\tError opening the file." << endl;
          return;
     }

     ofstream tempFile("temp.txt");
     if (!tempFile)
     {
          cout << "\tError creating temporary file." << endl;
          return;
     }

     string data;
     bool student_found = false;
     bool removed = false;
     while (getline(studentFile, data))
     {
          stringstream ss(data);
          string studentId_stored, student_name_stored, type_vehicle_stored, time_stored, price_stored;
          ss >> studentId_stored >> student_name_stored >> type_vehicle_stored >> time_stored >> price_stored;
          if (studentId_stored != student_id)
          {
               tempFile << data << endl;
          }
          else
          {
               student_found = true;
               cout << "\n\tAre you sure you want to delete the student with ID '" << student_id << "'? (Y/N): ";
               char confirmation;
               cin >> confirmation;
               if (confirmation == 'N' || confirmation == 'n')
               {
                    tempFile << data << endl;
               }
               else
               {
                    removed = true;
               }
          }
     }

     studentFile.close();
     tempFile.close();

     remove("student.txt");
     rename("temp.txt", "student.txt");

     if (student_found && removed)
     {
          cout << "\tRemoved successfully!" << endl;
     }
     else if (student_found)
     {
          cout << "\tDeletion canceled." << endl;
     }
     else
     {
          cout << "\tStudent not found." << endl;
     }
}
void view_ses()
{
     ifstream studentFile("student.txt");
     if (!studentFile)
     {
          cout << "\terror to open file" << endl;
          return;
     }
     string data;
     int total_student = 0;
     cout << "\t=========================="
          << "\t"
          << "Student table"
          << "\t"
          << "==========================" << endl;
     cout << "\t" << left << setw(10) << "ID" << left << setw(20) << "Name" << left << setw(15) << "Type" << left << setw(20) << "Enter at"
          << "Price" << endl;
     cout << "\t==========================================================================" << endl
          << endl;
     while (getline(studentFile, data))
     {
          stringstream ss(data);
          cout << data << endl;
          total_student++;
     }
     cout << "\n\t==========================================================================" << endl;
     cout << "\n\tTotal students: " << total_student << endl
          << endl;
     ;
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

void update_student()
{
}

void student_management()
{
     int option;
     while (1)
     {
          system("cls");
          cout << endl;
          cout << "\t================= Students' vehicles management =============== " << endl
               << endl;
          cout << "\t\t1. Add student" << endl;
          cout << "\t\t2. Remove student" << endl;
          cout << "\t\t3. View all students " << endl;
          cout << "\t\t4. Search for student" << endl;
          cout << "\t\t5. Update student" << endl;
          cout << "\t\t6. sign out" << endl
               << endl;
          ;
          cout << "\t>> Enter your option: ";
          cin >> option;
          system("cls");
          switch (option)
          {
          case 1:
               add_student();
               cout << "\t";
               system("pause");
               break;
          case 2:
               remove_student();
               cout << "\t";
               system("pause");
               break;
          case 3:
               view_ses();
               cout << "\n\t";
               system("pause");
               system("cls");
               break;
          case 4:
               search_student();
               cout << "\t";
               system("pause");
               break;
          case 5:
               update_student();
               cout << "\t";
               system("pause");
          case 6:
               cin.ignore();
               system("cls");
               return;
               break;
          default:
               cout << "\tInvalid option!! Please try again" << endl;
               break;
          }
     }
}

void staff_sign_up()
{
     string username, password, phone_number, pass, time;
     char ch1, ch2;
     cout << "\n\tEnter username: ";
     cin.ignore();
     getline(cin, username);
     cout << "\tEnter phone number: ";
     cin >> phone_number;

inputPassword:
     cout << "\tEnter password: ";
     pass = asterisk_display(ch1, pass);
     cout << "\n\tEnter confirm password: ";
     password = asterisk_display(ch2, password);

     if (pass != password)
     {
          cout << "\n\t!Confirm password doesn't match with the previous password";
          cout << "\n\tEnter again\n";
          pass = "";
          password = "";
          goto inputPassword;
     }
     else
     {
          time = get_current_time();
          Staff staff;
          staff.username = username;
          staff.phone_number = phone_number;
          staff.password = password;
          staff.create_at = time;

          ifstream staffFile("staff.txt");
          ofstream tempFile("temp.txt", ios::app);

          if (!staffFile || !tempFile)
          {
               cout << "\tError opening the file" << endl;
               return;
          }

          string data;
          bool found = false;

          while (getline(staffFile, data))
          {
               stringstream ss(data);
               ss >> staff.username >> staff.phone_number >> staff.password >> staff.create_at;
               if (staff.phone_number == phone_number)
               {
                    found = true;
                    break;
               }
               tempFile << "\t" << left << setw(21) << staff.username << left << setw(15) << staff.phone_number << left << setw(15) << staff.password << staff.create_at << endl;
          }

          staffFile.close();
          tempFile.close();

          if (found)
          {
               cout << "\n\tInvalid! This phone number already exists!" << endl;
               remove("temp.txt");
               sleep(1);
          }
          else
          {
               ofstream staffFile("staff.txt", ios::app);
               staffFile << "\t" << left << setw(21) << username << left << setw(15) << phone_number << left << setw(15) << password << time << endl;
               staffFile.close();
               system("pause");
               cout << "\n\tSuccessfully created account\n";
               remove("temp.txt");
               student_management();
          }
     }
}

void privacy_n_policy()
{
     cout << "\t\t...We need to discuss with our client about this part\n\n";
}

void remove_staff_by_phone_number(const string &phone)
{
     ifstream inputFile("staff.txt");
     ofstream tempFile("temp.txt");
     if (!inputFile || !tempFile)
     {
          cout << "\tError opening the file" << endl;
          return;
     }
     string data;
     bool found = false;
     bool removed = false;
     while (getline(inputFile, data))
     {
          stringstream ss(data);
          Staff staff;
          ss >> staff.username >> staff.phone_number >> staff.password >> staff.create_at;
          if (staff.phone_number == phone)
          {
               found = true;
               cout << "\n\tAre you sure you want to delete the staff with phone number '" << phone << "'? (Y/N): ";
               char confirmation;
               cin >> confirmation;
               if (confirmation == 'N' || confirmation == 'n')
               {
                    tempFile << "\t" << left << setw(21) << staff.username << left << setw(15) << staff.phone_number << left << setw(15) << staff.password << staff.create_at << endl;
               }
               else
               {
                    removed = true;
               }
               continue;
          }
          tempFile << "\t" << left << setw(21) << staff.username << left << setw(15) << staff.phone_number << left << setw(15) << staff.password << staff.create_at << endl;
     }
     inputFile.close();
     tempFile.close();
     remove("staff.txt");
     rename("temp.txt", "staff.txt");

     if (!found)
     {
          cout << "\tPhone number: " << phone << " not found." << endl;
     }
     else if (removed)
     {
          cout << "\tRemoved successfully!" << endl;
          system("pause");
          system("cls");
     }
}

void update_staff()
{
     string phone, opt;
     char ch;

     cout << "\n\t\tDo you want to update username, phone number, or password (1-3)?\n\n";
     cout << "\t\t\t1. Update username" << endl;
     cout << "\t\t\t2. Update phone number" << endl;
     cout << "\t\t\t3. Update password" << endl;
     cout << "\n\t\t>> Enter your option: ";
     cin >> opt;

     cout << "\n\tEnter the staff phone number: ";
     cin.ignore();
     getline(cin, phone);

     ifstream staffFile("staff.txt");
     ofstream tempFile("temp.txt");

     if (!staffFile || !tempFile)
     {
          cout << "\tError opening the file" << endl;
          return;
     }

     string data;
     bool found = false;

     while (getline(staffFile, data))
     {
          stringstream ss(data);
          Staff staff;
          ss >> staff.username >> staff.phone_number >> staff.password >> staff.create_at;
          if (staff.phone_number == phone)
          {
               found = true;

               if (opt == "1")
               {
                    cout << "\n\tEnter updated name: ";
                    getline(cin, staff.username);
               }
               else if (opt == "2")
               {
                    string newPhoneNumber;
                    cout << "\n\tEnter updated phone number: ";
                    getline(cin, newPhoneNumber);

                    bool duplicateNumber = false;
                    ifstream duplicateCheckFile("staff.txt");
                    if (duplicateCheckFile)
                    {
                         string data;
                         while (getline(duplicateCheckFile, data))
                         {
                              stringstream ss(data);
                              string username, phoneNum, password, createdAt;
                              ss >> username >> phoneNum >> password >> createdAt;
                              if (phoneNum == newPhoneNumber && phoneNum != phone)
                              {
                                   duplicateNumber = true;
                                   break;
                              }
                         }
                         duplicateCheckFile.close();
                    }

                    if (duplicateNumber)
                    {
                         cout << "\n\tPhone number '" << newPhoneNumber << "' already exists. Cannot update." << endl;
                         remove("temp.txt");
                         return;
                    }
                    else
                    {
                         staff.phone_number = newPhoneNumber;
                    }
               }
               else if (opt == "3")
               {
                    string current_password, new_password, confirm_password;
                    cout << "\n\tEnter current password: ";
                    current_password = asterisk_display(ch, current_password);
                    if (current_password == staff.password)
                    {
                         cout << "\n\tEnter new password: ";
                         new_password = asterisk_display(ch, new_password);
                         cout << "\n\tConfirm new password: ";
                         confirm_password = asterisk_display(ch, confirm_password);
                         if (new_password == confirm_password)
                         {
                              staff.password = new_password;
                         }
                         else
                         {
                              cout << "\n\tPasswords do not match. Password not updated." << endl;
                         }
                    }
                    else
                    {
                         cout << "\n\tIncorrect password. Password not updated." << endl;
                    }
               }
          }
          tempFile << "\t" << left << setw(21) << staff.username << left << setw(15) << staff.phone_number << left << setw(15) << staff.password << staff.create_at << endl;
     }

     staffFile.close();
     tempFile.close();

     if (!found)
     {
          cout << "\n\tStaff with phone number '" << phone << "' not found!" << endl;
          remove("temp.txt");
          return;
     }

     remove("staff.txt");
     rename("temp.txt", "staff.txt");

     cout << "\n\tStaff information updated successfully!" << endl;
}

void adminnn(int admin_option)
{
     Admin admin;
     int opt_gender;
     system("cls");
     cout << "\n\n\n\t\t\tWait a moment..." << endl;
     sleep(1);
     system("cls");
     cout << "\n\n\t!We ask you questions to make your system more secure." << endl;
     cout << "\n\t\tEnter your university name: ";
     getline(cin >> ws, admin.university_name);
     cout << "\t\tEnter your first name: ";
     getline(cin >> ws, admin.firstname);
     cout << "\t\tEnter your last name: ";
     getline(cin >> ws, admin.lastname);
     cout << "\t\tEnter your age: ";
     cin >> admin.age;
inputGender:
     cout << "\t\t\t[1]. Male" << endl;
     cout << "\t\t\t[2]. Female" << endl;
     cout << "\t\tChoose your gender: ";
     cin >> opt_gender;
     switch (opt_gender)
     {
     case Male:
          admin.gender = "Male";
          break;
     case Felmale:
          admin.gender = "Female";
          break;
     default:
          cout << "\t\tInvalid option!" << endl;
          goto inputGender;
          break;
     }
     cout << "\t\tEnter your phone number: ";
     getline(cin >> ws, admin.phone_num);
     cout << "\t\tEnter your password: ";
     getline(cin >> ws, admin.password);
     cout << "\n\t\tLoading data. Please wait..." << endl;
     sleep(1.5);
     system("cls");
     if ((admin.university_name == UNIVERSITY_NAME) && (admin.firstname == FIRST_NAME) && (admin.lastname == LAST_NAME) && (admin.age == AGE) && (admin.gender == GENDER) && (admin.phone_num == PHONE_NUMBER) && (admin.password == PASSWORD))
     {
          cout << "\n\t\t\tYou have logged in as admin" << endl;
          while (1)
          {
               cout << "\n\t\t1. Remove staff" << endl;
               cout << "\t\t2. View staff " << endl;
               cout << "\t\t3. View students" << endl;
               cout << "\t\t4. Update staff" << endl;
               cout << "\t\t5. Sign out" << endl
                    << endl;
               ;
               cout << "\t>> Enter your option: ";
               cin >> admin_option;
               cout << endl;
               if (admin_option == 1)
               {
                    string phone_remove;
                    cout << "\tPlease enter staff's phone number to remove." << endl;
                    cout << "\tEnter phone number: ";
                    cin >> phone_remove;
                    remove_staff_by_phone_number(phone_remove);
               }
               else if (admin_option == 2)
               {
                    read_staff_file();
                    cout << "\n\t";
                    system("pause");
                    system("cls");
               }
               else if (admin_option == 3)
               {
                    view_ses();
                    cout << "\n\t";
                    system("pause");
                    system("cls");
               }
               else if (admin_option == 4)
               {
                    cout << "\n\t>> You chose 4.\"update staff \" " << endl;
                    update_staff();
               }
               else if (admin_option == 5)
                    break;
               else
               {
                    invalid_option_message();
                    system("pause");
               }
          }
          cout << endl;
          system("cls");
          cout << endl;
     }

     else
     {
          cout << "\t\tWrong input!!";
          system("pause");
     }
}

void stafff(int option, bool loggedIn = false)
{
     while (true)
     {
          cout << endl;
          cout << "\t========== Staff Options ==========" << endl;
          cout << "\n";
          cout << "\t\t1. Sign in" << endl;
          cout << "\t\t2. Sign up" << endl;
          cout << "\t\t3. Exit" << endl
               << endl;
          cout << "\t>> Enter your option: ";
          cin >> option;
          switch (option)
          {
          case 1:
               loggedIn = staff_sign_in();
               if (loggedIn)
               {
                    system("cls");
                    cout << "\tSigned in successfully!!" << endl;
                    cout << "\t";
                    system("pause");
                    student_management();
               }
               else
               {
                    cout << "khos!!" << endl;
               }
               break;
          case 2:
               staff_sign_up();
               break;
          case 3:
               return;
               break;
          default:
               cout << "\tinvalid option" << endl;
               break;
          }
     }
}

void instruction()
{
     cout << "\n\t\t >>> Sech kdey nae nom <<<\n\n";
     cout << "\tThere are two roles in the program which are admin and staff. \n\t+ Admin is the one who take control all over staff and be able to delete staff's account as well. The admin can also view staff information and password. So when the staff forget the passsowrd they better contact direactly to admin to get they password or change their information.\n\t+ Staff is the postion which works on students. They can create student, delete student, view student, and take control or the entering of student and leaving of student. So their task is to take responsibility of student. For example, the student lost the vehicle, the staff would  take responsibel for it.\nIf you are admin you need to login first before getting into the program and do stuff.\n\n\tHow to login as admin.\n\t You must enter university name, first name, last name, gender, phone number ,and password correctly. Those are provided by the developer. So if you feel like changing those stuff, all you have to do if inform to the developer.\n\tAfter logging into the program you are authorized as an admin. You can view staff, student and delete staff.\n\t.... \n\n\tHow to use our system as staff. \n\tYou have two choices . You can sign in or sign up. \n\tSign up means create account(Note: Staff's name never have space). And sign in is to log in to your account.  \n\tIn case, you forget yourr password , you can contact the admin to get your password back or tell admin to delete your account. \n\n\t *** Dont be serious, if you have any problem of using our system feel free to contact the developer direactly to the email (unknown.kid@gmail.com)\n\n\t";
     system("pause");
}

bool continue_or_not(int option)
{
     system("cls");
     cout << "\n\t\tDo you want to read more or go to the next page?\n\n"
          << endl;
inputAgain:
     cout << "\t1. Read more" << endl;
     cout << "\t2. Go to the next page" << endl;
     cout << "\t>> Enter your option: ";
     cin >> option;
     if (option == 1)
     {
          cout << "\n\t";
          system("cls");
          return true;
     }
     else if (option == 2)
     {
          return false; // -.- to exit the loop
     }
     else
     {
          invalid_option_message();
          goto inputAgain;
     }
}

int main()
{
     int option_one, admin_option, option;
     bool loggedIn = false, valid_input = false;
     system("cls");
     cout << "\n========================== Welcome to our system ==========================\n";
     cout << "\n\n\tPlease read the instruction carefully before using our system" << endl;
     while (1)
     {
          int opt, n;
          cout << "\n\t\t1. How to use it" << endl;
          cout << "\t\t2. Policy and privacy" << endl;
          cout << "\t\t3. About developer" << endl;
          cout << "\t\t4. Skip" << endl;
          cout << "\n\t>> Enter your option: ";
          cin >> opt;
          if (opt == 1)
          {
               instruction();
               if (!continue_or_not(n))
                    break;
          }
          else if (opt == 2)
          {
               privacy_n_policy();
               if (!continue_or_not(n))
                    break;
          }
          else if (opt == 3)
          {
               system("cls");
               cout << "\n\tThere are 5 members in our team.\n";
               cout << "\t\tLyna\n";
               cout << "\tSomnang\n";
               cout << "\tSehya\n";
               cout << "\tSela\n";
               cout << "\tSim\n";
               cout << "\tThean\n";
               cout << "\tSros\n";
          }
          else if (opt == 4)
               break;
          else
          {
               invalid_option_message();
          }
     }
     cout << "\t";
     while (1)
     {
     inputOption:
          system("cls");
          cout << "\n\n\tAre you Staff or Admin?" << endl
               << endl;
          cout << "\t\t1. Admin" << endl;
          cout << "\t\t2. Staff" << endl;
          cout << "\t\t3. Leave the program" << endl
               << endl;
          cout << "\t>> Enter your option: ";
          cin >> option_one;
          if (option_one == UserAdmin)
          {
               adminnn(option);
          }
          else if (option_one == UserStaff)
          {
               stafff(option, loggedIn);
          }
          else if (option_one == 3)
          {
               cout << "\n\t\tThanks for using our system" << endl;
               cout << "\tThis program will be closed in 2 s." << endl;
               sleep(2);
               return 0;
          }
          else
          {
               cout << "\tInvalid option!!" << endl;
               cout << "\tInput again!!" << endl;
               goto inputOption;
          }
     }

     return 0;
}