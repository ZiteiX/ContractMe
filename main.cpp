#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define N 30  // max char for username

const int HR_TYPE = 1;
const int EMPLOYEER_TYPE = 2;
const int CONSTARCTOR_TYPE = 3;

int ContractorCount = 0; // Contractor user count.
int EmployerCount = 0;  // Employer user count.
typedef enum {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec} Month;

typedef struct {
	char *name;  // name +last name 
	char *username;  // username
	char *password;
	int UserType=0;  //  1 = HR  ,  2 = Employeer  ,  3 = Contractor
} User;

typedef struct {
	User details;
	int salary;
	//WorkDay *workDay;
}Contractor;
 
typedef struct {
	int day;
	Month month;
	int startTime;
	int endTime;
}WorkDay;



void mainmenu();
void login();
void signUp();
void writeUserToFile(User);
void tech();
void hrMenu();
void employeerMenu();
void contractorMenu();
void ChooseMenu(int type);
bool checkUserExists(ifstream&, char*);
void lowercase(char*);



int main()
{
	cout << "\nCCCCCC                                                       MMM    MMM " << endl;
	cout << "CC       ooo   n       t                           t        M   M  M   M" << endl;
	cout << "C       o   o  nnnn   ttt   r rrrr  aaaa    cccc  ttt      M     MM     M    eeee" << endl;
	cout << "CC      o   o  n   n   t     r      a  a    c      t      M              M   e--- " << endl;
	cout << "CCCCCC   ooo   n   n   tttt  r      aaaaaa  cccc   tttt  M                M  eeee " << endl;

	cout << "\n\n\n+++++++++++++++++++++++++++++++++++++++++++\n+++  HELLO! :), welcome to ContractMe!  +++  (for technical support press '0' at anytime)\n+++++++++++++++++++++++++++++++++++++++++++\n" << endl;

	mainmenu();

	// Good Bye message with hand gesture :DD
	return 0;
}

void mainmenu()
{
	int choice;
	
	do {
		cout << "\n\tLOGIN & Sign up page\n\tEnter your choice:\n\n1. Login \n2. Sign up \n3. Exit\n" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: // technical support
			tech();
			break;
		case 1: // login
			login();
			break;
		case 2: // sign up
			signUp();
			break;
		case 3: // exit
			break;
		default:
			cout << "\nError, please try again:\n" << endl;
		} 
	} while (choice != 3);
}

void login()
{
	char userInput[N];
	int pass;
	cout << "please enter your username:\n" << endl;
	cin >> userInput;
	cout << "please enter your password:\n" << endl;
	cin >> pass;

	lowercase(userInput); //Change to lowercase before checking if exists.
	
	ifstream inFile;
	inFile.open("database.txt");
	if (inFile.fail()) {
		cerr << "error opening file" << endl;
		exit(1);
	}
	//char* checkuser = new char[strlen(user) + 1];
	int checkpass;
	int checktype;
	if( checkUserExists(inFile, userInput) ) {
		inFile >> checkpass;
		if (checkpass == pass) 
		{
			cout << "Welcome\n";
			inFile >> checktype;
			inFile.close();
			ChooseMenu(checktype);
			return;
		}
		else cout << "Wrong pass.\n";
		return;
	}
	cout << "user does not exsist in the database, try again";
	inFile.close();
	return;
}

void signUp() // only Employer can signup
{
	User u1;
	char name[N], username[N], password[N];

	cout << ("\nHello, enter your name, user and password:\n");
	cin >> name >> username >> password;
	
	lowercase(username); //Account usernames will be stored in lowercase on the DataBase.
	
	// Username in database must be unique.
	ifstream inFile;
	inFile.open("database.txt");
	if (inFile.fail()) {
		cerr << "error opening file" << endl;
		exit(1);
	}
	while(checkUserExists(inFile, username)) {
		cout << "Username taken."
			 << "Enter another username " << endl;
		cin >> username;
	}
	u1.name = name;
	u1.username = username;
	u1.password = password;
	u1.UserType = EMPLOYEER_TYPE;  // employer 
	writeUserToFile(u1);

	EmployerCount++; // Counting the number of employers in the system - for "Statistic Analysis"
	employeerMenu();
}

void writeUserToFile(User newUser)
{
	ofstream inFile;
	inFile.open("database.txt",ios::app);
	if (inFile.fail()) {
		cout << "error opening file" << endl;
		exit(1);
	}
	inFile << "\n";
	inFile << newUser.name << " ";
	inFile << newUser.username << " ";
	inFile << newUser.password << " ";
	inFile << newUser.UserType << " ";
	//if (newUser.UserType == 3) // if its contractor
	//	inFile << newUser.salary;
	inFile.close();
}

void ChooseMenu(int type)
{
	if (type == 1)
		hrMenu();
	else if (type == 2)
		employeerMenu();
	else
		contractorMenu();
}

void tech()
{

}

void hrMenu()
{
	int choice = 0;
	while (choice != 5) {
		cout << "Hello, welcome to the HR Menu, what do you want to do next? " << endl
			<< "1.Statistic Analysis" << endl
			<< "2.Monitor Hiring" << endl 
			<< "3.Add New Worker" << endl
			<< "4.Workers Feed" << endl
			<< "5.Sign out" << endl;
		cin >> choice;
		switch (choice) {
			case 1: 
				//statisticAnalysis();
				break;
			case 2:
				//monitorHiring();
				break;
			case 3:
				//addNewWorker();
				break;
			case 4:
				//workersFeed();
				break;
			case 5:
				cout << "Signed out of the system." << endl;
				break;
			default: 
				cout << "Please enter choce between 1-5 only, 5 to sign out." << endl;
		}
	}
}

void employeerMenu()
{
	int choice = 0;
	while (choice != 3) {
		cout << "Hello, welcome to the Employeer Menu, what do you want to do next? " << endl
			<< "1.Hiring History" << endl
			<< "2.Search Contractor" << endl 
			<< "3.Sign out" << endl;
		cin >> choice;
		switch (choice) {
			case 1: 
				//hiringHistory();
				break;
			case 2:
				//searchContractor();
				break;
			case 3:
				cout << "Signed out of the system." << endl;
				break;
			default: 
				cout << "Please enter choce between 1-3 only, 3 to sign out." << endl;
		}
	}
}

void contractorMenu()
{
	//Show monthly work hors and salary.
	//Only one choice - report work hours or vacation.
}

//  
// HELPERS FUNCTIONS
// 

void lowercase(char* lower)
{
	for (unsigned int i = 0; i < strlen(lower); i++) // to lowercase the chars
	{
		lower[i] = tolower(lower[i]);
	}
}

bool checkUserExists(ifstream& inFile, char* userInput)
{
	char* checkInput = new char[strlen(userInput)+1];
	string skipLine;
	while (!inFile.eof()) {
		inFile >> checkInput; // Ignoring first word.
		inFile >> checkInput; // Getting the UserName field from the file.
		if(strcmp(checkInput,userInput) == 0) {
			return true;
		}
		getline(inFile, skipLine); // Skiping line
	}
	return false; // If no matching user was found.
}