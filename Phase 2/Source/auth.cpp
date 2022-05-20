#include "auth.h"
#include "securityFunctions.h"
#include "customerFunctions.h"

using namespace std;

void auth::customer_login()
{
	int count = 0;
	string userId, password, id, pass;
	system("cls");
	cout << "\n\nPlease enter your username and password:" << endl;
	cout << "\n\nUser Name: ";
	cin >> userId;
	cout << "Password: ";
	cin >> password;

	ifstream input("customer_records.txt"); // customer_records.txt strores all user info in the format, "username"' '"password".
	while (input >> id >> pass)
	{
		if (id == userId && pass == password) // checking if the user entered info matches with the info in the txt file
		{
			count = 1;
			system("cls");
		}
	}
	input.close();
	if (count == 1)
	{
		customerFunctions cus; // Object to access member functions from customer_check_in class file
		system("cls");
		cout << userId << "\n-------------------------You have sucessfully logged in!-------------------------\n";
		cus.customer(userId);
	}
	else
	{
		int choice = 0;
		system("cls");
		cout << "\n Login ERROR - Please check your username and password again\n";
		while (choice<4)
		{
			cout << "\nPress,\n1 to TRY AGAIN\n2 to REGISTER (If you are a new user)\n3 for HOME page" << endl;
			cin >> choice;

			if (choice == 1)
			{
				system("cls");
				customer_login();
				break;
			}
			else if (choice == 2)
			{
				system("cls");
				customer_reg();
				break;
			}
			else if (choice == 3)
			{
				system("cls");
				mainCopy();
				break;
			}
			else
			{
				system("cls");
				cout << "Enter a Valid choice from the choices given\n" << endl;
			}
		}
	}
}


void auth::customer_reg()
{
	string ruserId, rpassword, rid, rpass;
	int count = 0;
	system("cls");
	cout << "\n\n";
	cout << "Please create new USERNAME and PASSWORD to register!" << "\n\n" << endl;
	cout << "Enter the Username: ";
	cin >> ruserId;
	cout << "Enter the Password: ";
	cin >> rpassword;

	ifstream input("customer_records.txt");
	while (input >> rid)
	{
		if (rid == ruserId) // checking if the user entered info matches with the info in the txt file to check for duplicates
		{
			count = 1;
			system("cls");
		}
	}
	input.close();
	//Checking for duplicate Username
	if (count == 1)
	{
		system("cls");
		cout << "\n\n" << "This User name already exists, please try a different username! \nOr if you already have an account, try logging in!\n" << endl;
		mainCopy();
	}
	else
	{
		ofstream write("customer_records.txt", ios::app); // 'app' here is an append function to add the newly registered info into the customer_records.txt file
		write << ruserId << ' ' << rpassword << endl;
		system("cls");

		cout << "\nRegistration is successfull!\n";
		mainCopy();
	}
	input.close();
}


void auth::security_login()
{
	securityFunctions sec; // Object to access members from the securityFunctions class file
	int count = 0;
	string suserId, spassword, sid, spass;
	system("cls");
	cout << "\n\nPlease enter your username and password:" << endl;
	cout << "\n\nUser Name: ";
	cin >> suserId;
	cout << "Password: ";
	cin >> spassword;

	ifstream input("security_records.txt"); // security_records.txt will contain all the security info in the format, "username"' '"password" which will be created by the developer.
	while (input >> sid >> spass)
	{
		if (sid == suserId && spass == spassword) // checking if the user entered info matches with the info in the txt file
		{
			count = 1;
			system("cls");
		}
	}
	input.close();
	if (count == 1)
	{
		system("cls");
		cout << suserId << "\n-------------------------You have sucessfully logged in!-------------------------\n";
		sec.security();
	}
	else
	{
		cout << "\n Login ERROR - Please check your username and password again\n";
		mainCopy(); // If the info does not match, it will re-direct the user to the main menu
	}
}


// Copy of the main Function incase other classes wanted access

void auth::mainCopy() {
	cout << "\n\n" << "--------------------------------------------------" << "\n\n" << endl;
	cout << "                      WELCOME" << "\n\n" << endl;
	cout << "--------------------------------------------------" << "\n\n" << endl;

	int login_choice = 1;

	while (login_choice!=0)
	{
		cout << "Press\n\n1 for Customer LOGIN\n2 for Customer Registration\n3 for Security LOGIN (ADMIN ACCESS ONLY)\n" << endl;
		cin >> login_choice;

		auth a; // Objects to access members from the auth class file
		if (login_choice == 1)
		{
			system("cls");
			a.customer_login();
			break;
		}
		else if (login_choice == 2)
		{
			system("cls");
			a.customer_reg();
			break;
		}
		else if (login_choice == 3)
		{
			system("cls");
			a.security_login();
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter a valid Choice from the given choices" << endl;
		}
	}
}