#include "CheckInFile.h"
#include "auth.h"
#include "CheckOutFile.h"
#include "connection.h"

using namespace std;

// Function to Check-In
void CheckInFile::checkIn(string UserId)
{
	CheckOutFile co; // Object to access members from CheckOutFile
	auth a; // Object to access members from CheckInFile
	connection con; // Object declaration to access members from connection file
	try
	{
		//Checking if the User's bike is already parked
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
		if (check > 0) // If the user's bike is already parked
		{
			string vtype = "bike";
			int ch = 0; // ch = choice
			system("cls");
			cout << endl << "\n\n" << UserId << ", Your Bike is already Parked, would you like to check out?\n" << endl;
			cout << endl << "\n\n" << "Press\n1 If you would like to CHECK-OUT now\n2 If you would like to go back to the Main Menu" << "\n" << endl;
			cin >> ch;

			if (ch == 1)
			{
				CheckOutFile co;
				co.checkOut(po, vtype, UserId);
			}
			else if (ch == 2)
			{
				system("cls");
				a.db(UserId);
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		//Checking if the User's Car is already parked
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
		if (check > 0) // If the user's Car is already parked
		{
			string vtype = "car";
			int ch = 0; // ch = choice
			system("cls");
			cout << endl << "\n\n" << UserId << ", Your Car is already Parked, would you like to check out?\n" << endl;
			cout << endl << "\n\n" << "Press\n1 If you would like to CHECK-OUT now\n2 If you would like to go back to the Main Menu" << "\n" << endl;
			cin >> ch;

			if (ch == 1)
			{
				CheckOutFile co;
				co.checkOut(po, vtype, UserId);
			}
			else if (ch == 2)
			{
				system("cls");
				a.db(UserId);
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	// If the User has no vehicle Parked, the following code will execute
	system("cls");
	string vehicleType;
	int checkInTime = 0;
	int check = 0;
	cout << endl << "-------------------------Welcome to the Check-in page!-------------------------" << endl;
	cout << endl << "Choose your vehicle type (2-Wheeler or 4-Wheeler)" << endl;
	cout << endl << "Type (Case sensitive),\n'bike' or\n'car' \n" << endl;
	cin >> vehicleType;

	if (vehicleType == "bike") // If the user has a Bike
	{
		try
		{
			pqxx::connection connectionObject(con.connect().c_str());
			pqxx::work work(connectionObject);
			pqxx::result response = work.exec("SELECT bike FROM parkinglot ORDER BY position ASC"); //Query to access only bike column and to check if there is free lot available

			for (int i = 0; i < response.size(); i++)
			{
				string a = response[i][0].c_str(); // Here we are converting the C++ string format into C string format in order to use the compare() function
				if (a.compare("-") == 0)
				{
					check++;
				}
			}
			if (check > 0)
			{
				system("cls");
				cout << endl << "Parking slot available!!" << endl;
				for (int i = 0; i < response.size(); i++)
				{
					string a = response[i][0].c_str();
					if (a.compare("-") == 0)
					{
						// Updating the Data Base by replacing the '-' into '+' to represent that it is taken
						response = work.exec("UPDATE parkinglot SET bike = '+' WHERE position = " + pqxx::to_string(i + 1) + pqxx::to_string("; ")
							+ pqxx::to_string("UPDATE parkinglot SET check_in = LOCALTIME(0) WHERE position = ") + pqxx::to_string(i + 1) + pqxx::to_string("; ")
							+ pqxx::to_string("UPDATE parkinglot SET username_bike = " + pqxx::to_string("'") + pqxx::to_string(UserId) + pqxx::to_string("'") + pqxx::to_string(" WHERE position = ") + pqxx::to_string(i + 1) + pqxx::to_string("; ")
								+ pqxx::to_string(" SELECT check_in" + pqxx::to_string(" from parkinglot where position = ") + pqxx::to_string(i + 1))));
						work.commit(); // Postgres function used to save the changes made to the Data Base

						string check_in_time = pqxx::to_string(response[0][0]); // here, we are storing the check in time in the form of a string
						string convert_hour = check_in_time.substr(0, 2); // Here, we are specifically selecting the 'Hour' part from the time using the substr() function
						stringstream convert(convert_hour); //Here, we are Converting the Hour part which is in string format to integer format to perform calculations
						int check_in_hour = 0;
						convert >> check_in_hour; // check_in_hour is the hour part in integer format

						cout << endl << "\n\nYou can park your Bike at position " << i + 1 << endl;
						cout << endl << "\nYour CHECK-IN time is - " << check_in_time << endl;
						cout << endl << "================================================" << endl;
						cout << "\n\n" << endl;
						cout << "\t\tHappy Shopping!!" << endl;
						cout << "\n\n\n" << endl;
						cout << endl << "================================================" << endl;
						cout << "\n\n" << endl;

						int c = 0;
						while (c != 1)
						{
							cout << "\n\n" << "Press\n1 for Main Menu\n2 to LOGOUT" << "\n";
							cin >> c;

							if (c == 1)
							{
								auth a;
								system("cls");
								a.db(UserId);
								break;
							}
							else if (c == 2)
							{
								auth a;
								system("cls");
								a.mainCopy();
								break;
							}
							else
							{
								system("cls");
								cout << endl << "Invalid Option, please select from the options given\n" << endl;
							}
						}
					}
				}
			}
			else
			{
				cout << endl << "Sorry, no parking lot available" << endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}


	// Same as above but for 'Car' column in the Data Base
	else if (vehicleType == "car")
	{
		try
		{
			pqxx::connection connectionObject(con.connect().c_str());
			pqxx::work work(connectionObject);
			pqxx::result response = work.exec("SELECT car FROM parkinglot ORDER BY position ASC"); //Query to access only bike column and to check if there is free lot available

			for (int i = 0; i < response.size(); i++)
			{
				string a = response[i][0].c_str(); // Here we are converting the C++ string format into C string format in order to use the compare() function
				if (a.compare("-") == 0)
				{
					check++;
				}
			}
			if (check > 0)
			{
				system("cls");
				cout << endl << "Parking slot available!!" << endl;
				for (int i = 0; i < response.size(); i++)
				{
					string a = response[i][0].c_str();
					if (a.compare("-") == 0)
					{
						// Updating the Data Base by replacing the '-' into '+' to represent that it is taken
						response = work.exec("UPDATE parkinglot SET car = '+' WHERE position = " + pqxx::to_string(i + 1) + pqxx::to_string("; ")
							+ pqxx::to_string("UPDATE parkinglot SET check_in_car = LOCALTIME(0) WHERE position = ") + pqxx::to_string(i + 1) + pqxx::to_string("; ")
							+ pqxx::to_string("UPDATE parkinglot SET username_car = " + pqxx::to_string("'") + pqxx::to_string(UserId) + pqxx::to_string("'") + pqxx::to_string(" WHERE position = ") + pqxx::to_string(i + 1) + pqxx::to_string("; ")
								+ pqxx::to_string(" SELECT check_in_car" + pqxx::to_string(" from parkinglot where position = ") + pqxx::to_string(i + 1))));
						work.commit(); // Postgres function used to save the changes made to the Data Base

						string check_in_time = pqxx::to_string(response[0][0]); // here, we are storing the check in time in the form of a string
						string convert_hour = check_in_time.substr(0, 2); // Here, we are specifically selecting the 'Hour' part from the time using the substr() function
						stringstream convert(convert_hour); //Here, we are Converting the Hour part which is in string format to integer format to perform calculations
						int check_in_hour = 0;
						convert >> check_in_hour; // check_in_hour is the hour part in integer format

						cout << endl << "\n\nYou can park your Car at Position " << i + 1 << endl;
						cout << endl << "\nYour CHECK-IN time is - " << check_in_time << endl;
						cout << endl << "================================================" << endl;
						cout << "\n\n" << endl;
						cout << "\t\tHappy Shopping!!" << endl;
						cout << "\n\n\n" << endl;
						cout << endl << "================================================" << endl;
						cout << "\n\n" << endl;

						int c = 0;
						while (c != 1)
						{
							cout << "\n\n" << "Press\n1 for Main Menu\n2 to LOGOUT" << "\n";
							cin >> c;

							if (c == 1)
							{
								auth a;
								system("cls");
								a.db(UserId);
								break;
							}
							else if (c == 2)
							{
								auth a;
								system("cls");
								a.mainCopy();
							}
							else
							{
								system("cls");
								cout << endl << "Invalid Option, please select from the options given\n" << endl;
							}
						}
					}
				}
			}
			else
			{
				cout << endl << "Sorry, no parking lot available" << endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
