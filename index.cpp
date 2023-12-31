#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <iomanip> // dd
#include <string>
#include <unistd.h> // ;-) sleep();
#include <windows.h>
using namespace std;
//* test lg
//* test mdg tt


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
     NoneRole, // :-* NoneRole has been declared because enum starts from index 0. i need userAdmin to be index 1.
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
     Car,
     Bike,
     Motorbike
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
};

// <3 get current time from locallhost (pc)
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

// l need to add total staff
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

// <3 done completely
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

// l vehicle type need to change
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

// <3 remove student when they leave from university
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

// l in progress
void view_ses()
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

// l search by id
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
          cout << "\t======= Students' vehicles management system ===== " << endl;
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
               view_ses();
               cout << "\n\t";
               system("pause");
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

// :@ in progress function

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
     cout << "\n\t";
     system("pause");
     student_management();
}

void privacy_n_policy()
{
     cout << "\tPrivacy Policy for Rupp" << endl
          << endl;
     cout << "\tAt SVMS, accessible from https://github.com/LynaSovann/student_managment_system, one of our main priorities is the privacy of our visitors. This Privacy Policy document contains types of information that is collected and recorded by SVMS and how we use it." << endl;
     cout << "\n\tIf you have additional questions or require more information about our Privacy Policy, do not hesitate to contact us." << endl
          << endl;
     cout << "\tThis Privacy Policy applies only to our online activities and is valid for visitors to our website with regards to the information that they shared and/or collect in SVMS. This policy is not applicable to any information collected offline or via channels other than this website." << endl
          << endl
          << endl;
     cout << "\tConsent" << endl;
     cout << "\t\nBy using our system, you hereby consent to our Privacy Policy and agree to its terms." << endl
          << endl;
     cout << "\tInformation we collect" << endl
          << endl;
     cout << "\n\tThe personal information that you are asked to provide, and the reasons why you are asked to provide it, will be made clear to you at the point we ask you to provide your personal information." << endl
          << endl;
     cout << "\tIf you contact us directly, we may receive additional information about you such as your name, email address, phone number, the contents of the message and/or attachments you may send us, and any other information you may choose to provide." << endl
          << endl;
     cout << "\tWhen you register for an Account, we may ask for your contact information, including items such as name, company name, address, email address, and telephone number." << endl
          << endl;
     cout << "\n\tHow we use your information" << endl
          << endl;
     cout << "We use the information we collect in various ways, including to:" << endl
          << endl;
     cout << "\t-\tProvide, operate, and maintain our system" << endl;
     cout << "\t-\tImprove, personalize, and expand our system" << endl;
     cout << "\t-\tUnderstand and analyze how you use our system" << endl;
     cout << "\t-\tDevelop new services, features, and functionality" << endl;
     cout << "\t-\tCommunicate with you, either directly or through one of our partners, including for customer service, to provide you with updates and other information relating to the website, and for marketing and promotional purposes" << endl;
     cout << "\t-\tSend you emails" << endl;
     cout << "\t-\tFind and prevent fraud" << endl;
     cout << "\n\n\tLog files" << endl
          << endl;
     cout << "\tSVMS follows a standard procedure of using log files. These files log visitors when they visit websites. All hosting companies do this and a part of hosting services' analytics. The information collected by log files include internet protocol (IP) addresses, browser type, Internet Service Provider (ISP), date and time stamp, referring/exit pages, and possibly the number of clicks. These are not linked to any information that is personally identifiable. The purpose of the information is for analyzing trends, administering the site, tracking users' movement on the website, and gathering demographic information." << endl
          << endl;
     cout << "\tAdvertising Partners Privacy Policies" << endl
          << endl;
     cout << "\tYou may consult this list to find the Privacy Policy for each of the advertising partners of SVMS." << endl
          << endl;
     cout << "\tThird-party ad servers or ad networks uses technologies like cookies, JavaScript, or Web Beacons that are used in their respective advertisements and links that appear on SVMS, which are sent directly to users' browser. They automatically receive your IP address when this occurs. These technologies are used to measure the effectiveness of their advertising campaigns and/or to personalize the advertising content that you see on websites that you visit." << endl
          << endl;
     cout << "\tNote that SVMS has no access to or control over these cookies that are used by third-party advertisers." << endl
          << endl;
     cout << "\tThird Party Privacy Policies" << endl
          << endl;
     cout << "\tSVMS's Privacy Policy does not apply to other advertisers or websites. Thus, we are advising you to consult the respective Privacy Policies of these third-party ad servers for more detailed information. It may include their practices and instructions about how to opt-out of certain options." << endl
          << endl;
     cout << "\tYou can choose to disable cookies through your individual browser options. To know more detailed information about cookie management with specific web browsers, it can be found at the browsers' respective websites." << endl
          << endl;
     cout << "\tCCPA Privacy Rights (Do Not Sell My Personal Information)" << endl
          << endl;
     cout << "\tUnder the CCPA, among other rights, California consumers have the right to:" << endl
          << endl;
     cout << "\tRequest that a business that collects a consumer's personal data disclose the categories and specific pieces of personal data that a business has collected about consumers." << endl
          << endl;
     cout << "\tRequest that a business delete any personal data about the consumer that a business has collected." << endl
          << endl;
     cout << "\tRequest that a business that sells a consumer's personal data, not sell the consumer's personal data." << endl
          << endl;
     cout << "\tIf you make a request, we have one month to respond to you. If you would like to exercise any of these rights, please contact us." << endl
          << endl;
     cout << "\n\tGDPR Data Protection Rights" << endl
          << endl;
     cout << "\tWe would like to make sure you are fully aware of all of your data protection rights. Every user is entitled to the following:" << endl
          << endl;
     cout << "\tThe right to access – You have the right to request copies of your personal data. We may charge you a small fee for this service." << endl
          << endl;
     cout << "\tThe right to rectification – You have the right to request that we correct any information you believe is inaccurate. You also have the right to request that we complete the information you believe is incomplete." << endl
          << endl;
     cout << "\tThe right to erasure – You have the right to request that we erase your personal data, under certain conditions." << endl
          << endl;
     cout << "\tThe right to restrict processing – You have the right to request that we restrict the processing of your personal data, under certain conditions." << endl
          << endl;
     cout << "\tThe right to object to processing – You have the right to object to our processing of your personal data, under certain conditions." << endl
          << endl;
     cout << "\tThe right to data portability – You have the right to request that we transfer the data that we have collected to another organization, or directly to you, under certain conditions." << endl
          << endl;
     cout << "\tIf you make a request, we have one month to respond to you. If you would like to exercise any of these rights, please contact us." << endl
          << endl;
     cout << "\n\tChildren's Information" << endl
          << endl;
     cout << "\tAnother part of our priority is adding protection for children while using the internet. We encourage parents and guardians to observe, participate in, and/or monitor and guide their online activity." << endl
          << endl;
     cout << "\tSVMS does not knowingly collect any Personal Identifiable Information from children under the age of 13. If you think that your child provided this kind of information on our website, we strongly encourage you to contact us immediately and we will do our best efforts to promptly remove such information from our records." << endl
          << endl;
     cout << "\n\tChanges to This Privacy Policy" << endl
          << endl
          << endl;
     cout << "\tWe may update our Privacy Policy from time to time. Thus, we advise you to review this page periodically for any changes. We will notify you of any changes by posting the new Privacy Policy on this page. These changes are effective immediately, after they are posted on this page." << endl
          << endl;
     cout << "\tOur Privacy Policy was created with the help of the Privacy Policy Generator." << endl
          << endl
          << endl;
     cout << "\tContact Us" << endl
          << endl;
     cout << "\tIf you have any questions or suggestions about our Privacy Policy, do not hesitate to contact us." << endl;
}

void term_n_condition()
{
     cout << "\tTerms and Conditions" << endl
          << endl;
     cout << "\tWelcome to SVMS!" << endl
          << endl;
     cout << "\tThese terms and conditions outline the rules and regulations for the use of rupp's System, located at https://github.com/LynaSovann/student_managment_system." << endl
          << endl;
     cout << "\tBy accessing this website we assume you accept these terms and conditions. Do not continue to use SVMS if you do not agree to take all of the terms and conditions stated on this page" << endl
          << endl;
     cout << "\tThe following terminology applies to these Terms and Conditions, Privacy Statement and Disclaimer Notice and all Agreements: \"Client\", \"You\" and \"Your\" refers to you, the person log on this website and compliant to the Company's terms and conditions. \"The Company\", \"Ourselves\", \"We\", \"Our\" and \"Us\", refers to our Company. \"Party\", \"Parties\", or \"Us\", refers to both the Client and ourselves. All terms refer to the offer, acceptance and consideration of payment necessary to undertake the process of our assistance to the Client in the most appropriate manner for the express purpose of meeting the Client's needs in respect of provision of the Company's stated services, in accordance with and subject to, prevailing law of kh. Any use of the above terminology or other words in the singular, plural, capitalization and/or he/she or they, are taken as interchangeable and therefore as referring to same." << endl
          << endl;
     cout << "\n\tCookies" << endl
          << endl;
     cout << "\tWe employ the use of cookies. By accessing SVMS, you agreed to use cookies in agreement with the rupp's Privacy Policy." << endl
          << endl;
     cout << "\tMost interactive websites use cookies to let us retrieve the user's details for each visit. Cookies are used by our website to enable the functionality of certain areas to make it easier for people visiting our website. Some of our affiliate/advertising partners may also use cookies." << endl
          << endl;
     cout << "\n\tLicense" << endl
          << endl;
     cout << "\tUnless otherwise stated, rupp and/or its licensors own the intellectual property rights for all material on SVMS. All intellectual property rights are reserved. You may access this from SVMS for your own personal use subjected to restrictions set in these terms and conditions." << endl
          << endl;
     cout << "\tYou must not:" << endl
          << endl;
     cout << "\t-\tRepublish material from SVMS" << endl;
     cout << "\t-\tSell, rent or sub-license material from SVMS" << endl;
     cout << "\t-\tReproduce, duplicate or copy material from SVMS" << endl;
     cout << "\t-\tRedistribute content from SVMS" << endl
          << endl;
     cout << "\tThis Agreement shall begin on the date hereof. Our Terms and Conditions were created with the help of the Free Terms and Conditions Generator." << endl
          << endl;
     cout << "\tParts of this system offer an opportunity for users to post and exchange opinions and information in certain areas of the website. Rupp does not filter, edit, publish or review Comments prior to their presence on the system. Comments do not reflect the views and opinions of rupp,its agents and/or affiliates. Comments reflect the views and opinions of the person who post their views and opinions. To the extent permitted by applicable laws, rupp shall not be liable for the Comments or for any liability, damages or expenses caused and/or suffered as a result of any use of and/or posting of and/or appearance of the Comments on this website." << endl
          << endl;
     cout << "\trupp reserves the right to monitor all Comments and to remove any Comments which can be considered inappropriate, offensive or causes breach of these Terms and Conditions." << endl
          << endl;
     cout << "\tyou warrant and represent that:" << endl
          << endl;
     cout << "\t-\tYou are entitled to post the Comments on our website and have all necessary licenses and consents to do so;" << endl;
     cout << "\t-\tThe Comments do not invade any intellectual property right, including without limitation copyright, patent or trademark of any third party;" << endl;
     cout << "\t-\tThe Comments do not contain any defamatory, libelous, offensive, indecent or otherwise unlawful material which is an invasion of privacy" << endl;
     cout << "\t-\tThe Comments will not be used to solicit or promote business or custom or present commercial activities or unlawful activity." << endl
          << endl;
     cout << "\tYou hereby grant rupp a non-exclusive license to use, reproduce, edit and authorize others to use, reproduce and edit any of your Comments in any and all forms, formats or media." << endl
          << endl
          << endl;
     cout << "\tHyperlinking to our Content" << endl;
     cout << "\n\tThe following organizations may link to our Website without prior written approval:" << endl
          << endl;
     cout << "\t-\tGovernment agencies;" << endl;
     cout << "\t-\tSearch engines;" << endl;
     cout << "\t-\tNews organizations;" << endl;
     cout << "\t-\tOnline directory distributors may link to our Website in the same manner as they hyperlink to the Websites of other listed businesses; and" << endl;
     cout << "\t-\tSystem wide Accredited Businesses except soliciting non-profit organizations, charity shopping malls, and charity fundraising groups which may not hyperlink to our Web site." << endl;
     cout << "\n\tThese organizations may link to our home page, to publications or to other Website information so long as the link: (a) is not in any way deceptive; (b) does not falsely imply sponsorship, endorsement or approval of the linking party and its products and/or services; and (c) fits within the context of the linking party's site." << endl
          << endl;
     cout << "\tWe may consider and approve other link requests from the following types of organizations:" << endl
          << endl;
     cout << "\t-\tcommonly-known consumer and/or business information sources;" << endl;
     cout << "\t-\tdot.com community sites;" << endl;
     cout << "\t-\tassociations or other groups representing charities;" << endl;
     cout << "\t-\tonline directory distributors;" << endl;
     cout << "\t-\tinternet portals;" << endl;
     cout << "\t-\taccounting, law and consulting firms; and" << endl;
     cout << "\t-\teducational institutions and trade associations." << endl
          << endl;
     cout << "\tWe will approve link requests from these organizations if we decide that: (a) the link would not make us look unfavorably to ourselves or to our accredited businesses; (b) the organization does not have any negative records with us; (c) the benefit to us from the visibility of the hyperlink compensates the absence of rupp; and (d) the link is in the context of general resource information." << endl
          << endl;
     cout << "\tThese organizations may link to our home page so long as the link: (a) is not in any way deceptive; (b) does not falsely imply sponsorship, endorsement or approval of the linking party and its products or services; and (c) fits within the context of the linking party's site." << endl
          << endl;
     cout << "\tIf you are one of the organizations listed in paragraph 2 above and are interested in linking to our website, you must inform us by sending an e-mail to rupp. Please include your name, your organization name, contact information as well as the URL of your site, a list of any URLs from which you intend to link to our Website, and a list of the URLs on our site to which you would like to link. Wait 2-3 weeks for a response." << endl
          << endl;
     cout << "\n\tApproved organizations may hyperlink to our Website as follows:" << endl
          << endl;
     cout << "\t-\tBy use of our corporate name; or" << endl;
     cout << "\t-\tBy use of the uniform resource locator being linked to; or" << endl;
     cout << "\t-\tBy use of any other description of our Website being linked to that makes sense within the context and format of content on the linking party's site." << endl;
     cout << "\n\n\tNo use of rupp's logo or other artwork will be allowed for linking absent a trademark license agreement." << endl
          << endl
          << endl;
     cout << "\tiFrames" << endl
          << endl;
     cout << "\tWithout prior approval and written permission, you may not create frames around our Webpages that alter in any way the visual presentation or appearance of our Website." << endl
          << endl
          << endl;
     cout << "\tContent Liability" << endl
          << endl;
     cout << "\tWe shall not be hold responsible for any content that appears on your Website. You agree to protect and defend us against all claims that is rising on your Website. No link(s) should appear on any Website that may be interpreted as libelous, obscene or criminal, or which infringes, otherwise violates, or advocates the infringement or other violation of, any third party rights." << endl
          << endl
          << endl;
     cout << "\tReservation of Rights" << endl
          << endl
          << endl;
     cout << "\tWe reserve the right to request that you remove all links or any particular link to our Website. You approve to immediately remove all links to our Website upon request. We also reserve the right to amen these terms and conditions and it's linking policy at any time. By continuously linking to our Website, you agree to be bound to and follow these linking terms and conditions." << endl
          << endl
          << endl;
     cout << "\tRemoval of links from our website" << endl
          << endl;
     cout << "\tIf you find any link on our Website that is offensive for any reason, you are free to contact and inform us any moment. We will consider requests to remove links but we are not obligated to or so or to respond to you directly." << endl
          << endl
          << endl;
     cout << "\tWe do not ensure that the information on this website is correct, we do not warrant its completeness or accuracy; nor do we promise to ensure that the website remains available or that the material on the website is kept up to date." << endl
          << endl
          << endl;
     cout << "\tDisclaimer" << endl;
     cout << "\n\tTo the maximum extent permitted by applicable law, we exclude all representations, warranties and conditions relating to our website and the use of this website. Nothing in this disclaimer will:" << endl
          << endl;
     cout << "\t-\tlimit or exclude our or your liability for death or personal injury;" << endl;
     cout << "\t-\tlimit or exclude our or your liability for fraud or fraudulent misrepresentation;" << endl;
     cout << "\t-\tlimit any of our or your liabilities in any way that is not permitted under applicable law; or" << endl;
     cout << "\t-\texclude any of our or your liabilities that may not be excluded under applicable law." << endl;
     cout
         << "\n\tThe limitations and prohibitions of liability set in this Section and elsewhere in this disclaimer: (a) are subject to the preceding paragraph; and (b) govern all liabilities arising under the disclaimer, including liabilities arising in contract, in tort and for breach of statutory duty." << endl
         << endl;
     cout << "\tAs long as the website and the information and services on the website are provided free of charge, we will not be liable for any loss or damage of any nature." << endl
          << endl;
}

int main()
{
     int option, admin_option, option_one;
     bool loggedIn = false, valid_input = false;

     // loading
     system("COLOR 2");
     system("cls");
     printf("\e[?251");

     // set ASCII to priint special charecter
     //  code page 437

     SetConsoleCP(437);
     SetConsoleOutputCP(437);
     cout << "\t\t\t-------------------------------" << endl;
     // cout << "\n\n\n\n\t\t\t==============================" << endl;
     cout << "\t\t\t|||  Vihecal Parking System  || " << endl;
     cout << "\t\t\t==============================" << endl;
     cout << "\n\n\n\n\t\t\t\t  LODING...";
     cout << "\n\n\t\t\t";

     char bar1 = 177, bar2 = 219;
     for (int i = 0; i < 30; i++)
     {
          cout << bar1;
     }
     cout << "\r";
     cout << "\t\t\t";
     for (int i = 0; i < 30; i++)
     {
          cout << bar2;
          Sleep(150);
     }

     cout << "\n\n\t\t\t" << (char)1 << "!";
     system("Pause");

     // :@ When user input wrong format then this function will run
     while (1)
     {

     inputOption:
          system("cls");
          cout << endl
               << endl;
          cout << "\tAre you Staff or Admin?" << endl
               << endl;
          cout << "\t\t1. Admin" << endl;
          cout << "\t\t2. Staff" << endl;
          cout << "\t\t3. Leave the program" << endl
               << endl;
          cout << "\t>> Enter your option: ";
          cin >> option_one;
          if (option_one == UserAdmin)
          {
               Admin admin;
               int opt_gender;
               system("cls");
               cout << "\n\n\n\t\t\tWait a moment..." << endl;
               sleep(1); // l dalay 5 seconds
               system("cls");
               cout << "\n\n\t!We ask you questions to make your system more secure." << endl;
               cout << "\n\t\tEnter your university name: ";
               getline(cin >> ws, admin.university_name); // ;-) ws is used to remove whitespace
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
                    cout << "\n\t\tYou have logged in as admin" << endl;
                    while (1)
                    {
                         cout << "\n\t1. View staff " << endl;
                         cout << "\t2. View students" << endl;
                         cout << "\t3. Terms and Conditions" << endl;
                         cout << "\t4. Privacy and policy" << endl;
                         cout << "\t5. Clear Screen" << endl;
                         cout << "\t6. Back" << endl;
                         cout << "\t>> Enter your option: ";
                         cin >> admin_option;
                         cout << endl;
                         if (admin_option == 1)
                         {
                              read_staff_file();
                              cout << "\n\t";
                              system("pause");
                         }
                         else if (admin_option == 2)
                         {
                              view_ses();
                              cout << "\n\t";
                              system("pause");
                         }
                         else if (admin_option == 3)
                         {
                              term_n_condition();
                              cout << "\n\t";
                              system("pause");
                         }
                         else if (admin_option == 4)
                         {
                              privacy_n_policy();
                              cout << "\n\t";
                              system("pause");
                         }
                         else if (admin_option == 5)
                         {
                              system("cls");
                         }
                         else if (admin_option == 6)
                              break;

                         else
                         {
                              cout << "\tInvalid number! Feel free to input again" << endl;
                              cout << "\n\t";
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
               }
          }
          else if (option_one == UserStaff)
          {
               while (true)
               {
                    cout << endl;
                    cout << "\t========== Welcome to our system ==========" << endl;
                    cout << "\n";
                    cout << "\t\t1. Sign in" << endl;
                    cout << "\t\t2. Sign up" << endl;
                    cout << "\t\t3. Exite" << endl;
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
                              student_management();
                         }
                         else
                         {
                              cout << "khos!!" << endl;
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
          }
          else if (option_one == 3)
          {
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