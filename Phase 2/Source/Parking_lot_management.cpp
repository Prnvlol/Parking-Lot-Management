
#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <exception>

#include "connection.h"
#include "auth.h"
#include "securityFunctions.h"

using namespace std;

int main() 
{
	cout << "\n\n" << "--------------------------------------------------" << "\n\n" << endl;
	cout << "                      WELCOME" << "\n\n" << endl;
	cout<< "--------------------------------------------------" << "\n\n" << endl;

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