#include "auth.h" 
#include "CheckInFile.h"
#include "CheckOutFile.h"
#include "connection.h"
using namespace std;

// Login Function
void auth::login()
{
	int count = 0;
	string userId, password, id, pass;
	system("cls");
	cout << "\n\nPlease enter your username and password:" << endl;
	cout << "\n\nUser Name: ";
	cin >> userId;
	cout << "Password: ";
	cin >> password;

	ifstream input("records.txt"); // record.txt strores all user info in the format, "username"' '"password".
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
		system("cls");
		cout << userId << "\n-------------------------You have sucessfully logged in!-------------------------\n";
		db(userId);
	}
	else
	{
		cout << "\n Login ERROR - Please check your username and password again\n";
		mainCopy(); // If the info does not match, it will re-direct the user to the main menu
	}
}

// Registration Function
void auth::registration()
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

	ifstream input("records.txt");
	while (input >> rid)
	{
		if (rid == ruserId) // checking if the user entered info matches with the info in the txt file to check for duplicates
		{
			count = 1;
			system("cls");
		}
	}

	//Checking for duplicate Username
	if (count == 1)
	{
		system("cls");
		cout << "\n\n" << "This User name already exists, please try a different username! \nOr if you already have an account, try logging in!\n" << endl;
		mainCopy();
	}
	else
	{
		ofstream write("records.txt", ios::app); // 'app' here is an append function to add the newly registered info into the records.txt file
		write << ruserId << ' ' << rpassword << endl;
		system("cls");

		cout << "\nRegistration is successfull!\n";
		mainCopy();
	}
}

// Function to access the Data Base
void auth::db(string UserId)
{
	CheckInFile c; // c is an object to access members from CheckInFile 
	CheckOutFile cho; // cho is an object to access members from CheckOutFile 
	connection con; // con is an object to access members from connection file 
	try
	{
		pqxx::connection connectionObject(con.connect().c_str());
		pqxx::work work(connectionObject); // Transactional Object

		pqxx::result response = work.exec("SELECT * FROM parkinglot ORDER BY position ASC"); // Executing Query to display all the available lots in ascending order
		cout << endl << "-------------------------Available lots-------------------------" << endl;
		cout << endl;

		for (int i = 0; i < response.size(); i++) //For-Loop to print all the available lots 
		{
			std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
			cout << endl;
		}

		cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

		int ch = 1; // Here, 'ch' means Choice
		while (ch != 0) //Loop to repeat the program till the user enters a valid choice
		{
			cout << endl << "-------------------------Do you want to CHECK-IN or CHECK-OUT?-------------------------" << endl;
			cout << endl << "Enter,\n1 For Check-in\n2 for Check-Out\n3 For Main Menu\n\n" << endl;
			cout << endl << "Enter your choice: " << endl;
			cin >> ch;

			if (ch == 1)
			{
				c.checkIn(UserId);
				break;

			}
			else if (ch == 2)
			{
				try
				{
					// Checking if the User has their Vehicle already parked
					pqxx::connection connectionObject(con.connect().c_str());
					pqxx::work work(connectionObject);
					pqxx::result response = work.exec("SELECT username_bike FROM parkinglot ORDER BY position ASC");

					int check = 0, i;
					for (i = 0; i < response.size(); i++)
					{
						string a = response[i][0].c_str(); // Here we are converting the C++ string format into C string format in order to use the compare() function
						if (a.compare(UserId) == 0)
						{
							check++;
							break;
						}
					}
					int po = i + 1;
					
					if (check > 0) // If the User's vehicle is already parked
					{
						string vtype = "bike";
						cho.checkOut(po, vtype, UserId);
					}
					else // If the user has no vehicle parked 
					{
						system("cls");
						int ch = 0;
						cout << "\n" << "You don't have any vehicles parked to CHECK-OUT\n" << endl;
						cout << "\n" << "Press,\n1 to CHECK-IN\n2 to LOGOUT\n" << endl;
						cin >> ch;

						while (ch)
						{
							if (ch == 1)
							{
								system("cls");
								c.checkIn(UserId);
								break;
							}
							else if (ch == 2)
							{
								system("cls");
								mainCopy();
								break;
							}
						}
					}
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
				try //Checking for the same conditions under car column in database
				{
					pqxx::connection connectionObject(con.connect().c_str());
					pqxx::work work(connectionObject);

					pqxx::result response = work.exec("SELECT username_car FROM parkinglot ORDER BY position ASC"); //Query to access only bike column and to check if there is free lot available

					int check = 0;
					int i = 0;
					for (i = 0; i < response.size(); i++)
					{
						string a = response[i][0].c_str(); // Here we are converting the C++ string format into C string format in order to use the compare() function
						if (a.compare(UserId) == 0)
						{
							check++;
							break;
						}
					}
					int po = i + 1;
					if (check > 0) // if the User's vehicle is already parked
					{
						string vtype = "car";
						cho.checkOut(po, vtype, UserId);
					}
					else // If the user has no vehicle parked 
					{
						system("cls");
						int ch = 0;
						cout << "\n" << "You don't have any vehicles parked to CHECK-OUT\n" << endl;
						cout << "\n" << "Press,\n1 to CHECK-IN\n2 to LOGOUT\n" << endl;
						cin >> ch;

						while (ch)
						{
							if (ch == 1)
							{
								system("cls");
								c.checkIn(UserId);
								break;
							}
							else if (ch == 2)
							{
								system("cls");
								mainCopy();
								break;
							}
						}
					}
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else if (ch == 3) // Back to Main Menu
			{
				auth a;
				system("cls");
				a.mainCopy();
			}
			else 
			{
				system("cls");
				cout << endl << "Enter a valid number from the given options" << endl;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

// A copy of the main function in case other member function needs access (To come back to Main Menu)
void auth::mainCopy()
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
		auth p;
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
		mainCopy();
	}
}


