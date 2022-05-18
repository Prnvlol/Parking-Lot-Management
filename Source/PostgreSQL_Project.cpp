#include<iostream>
#include<stdlib.h>
#include<fstream> // File Handling
#include<string> 
#include<pqxx/pqxx> // Official C++ client API for PostgreSQL

#include "auth.h" // Authentication class file
#include "CheckInFile.h" // Check-In class file
#include "CheckOutFile.h" // Check-Out class file

using namespace std;

int main()
{
	cout << "\n\n\n-------------------------Parking lot management-------------------------" << endl;

	int c = 0; // Here, c stands for choice
	cout << "\n\n\n\n\n";
	cout << "Login or Register to continue\n\n" << endl;
	cout << "1. Login\n2. Register\n3. Exit\n" << endl;
	cout << "Enter your choice: " << endl;
	cin >> c;
	cout << endl;

	if (c == 1)
	{
		auth p; // p is an object here to access members from the class file
		p.login();
	}
	else   if (c == 2)
	{
		auth p;
		p.registration();
	}
	else if (c == 3)
	{
		cout << endl << "Thank you!" << endl;
		system("pause");
	}
	else
	{
		system("cls");
		cout << "\nEnter a valid option from the options given\n" << endl;
		main();
	}
}