#include<iostream>
#include<stdlib.h>
#include<fstream> // File Handling.
#include<string>
#include<pqxx/pqxx> // Official C++ client API for PostgreSQL.
using namespace std;

void login();
void registration();
void db(); // To access the database. Here db stands for DataBase.
void checkIn();
void TimeRecord(int, string, string, int); // To record the local time during check-in and check-out.
void reset(int, string); // To reset the databse when a customer checks-out.


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
		login();
	}
	else   if (c == 2)
	{
		registration();
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


void login()
{
	int count = 0; 
	string userId, password, id, pass;
	system("cls");
	cout << "\n\nPlease enter your username and password:" << endl;
	cout << "\n\nUser Name: ";
	cin >> userId;
	cout << "Password: ";
	cin >> password;

	ifstream input("records.txt"); // record.txt strores all user info in the format, "username' 'password".
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
		cout << userId << "\n-------------------------You have sucessfully logged in!-------------------------\n";
		system("cls");
		db(); 
	}
	else
	{
		cout << "\n Login ERROR - Please check your username and password again\n";
		main(); // If the info does not match, it will re-direct the user to the main menu
	}
}

void registration()
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
		if (rid == ruserId) // checking if the user entered info matches with the info in the txt file
		{
			count = 1;
			system("cls");
		}
	}

	//Checking for duplicate Username
	if (count == 1)
	{
		system("cls");
		cout << "\n\n" << "This User name already exists, please try a different username!\n\n" << endl;
		main();
	}
	else
	{
		ofstream write("records.txt", ios::app); // 'app' here is an append function to add the newly registered info into the records.txt file
		write << ruserId << ' ' << rpassword << endl;
		system("cls");

		cout << "\nRegistration is successfull!\n";
		main();
	}
}

//Accessing the DataBase

void db()
{
	try
	{
		string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
		pqxx::connection connectionObject(connectionString.c_str());
		pqxx::work work(connectionObject);
		pqxx::result response = work.exec("SELECT * FROM parkinglot ORDER BY position ASC"); // Executing Query to display all the available lots in ascending order

		cout << endl << "-------------------------Available lots-------------------------" << endl;
		cout << endl;

		for (int i = 0; i < response.size(); i++)
		{
			std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
			cout << endl;
		}

		cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

		int ch = 1; // Here, 'ch' means Choice

		while (ch != 0) //Loop to repeat the program till the user enters a valid choice
		{
			cout << endl << "-------------------------Do you want to check in now?-------------------------" << endl;
			cout << endl << "Enter,\n1 For Check in\n2 For Main Menu\n\n" << endl;
			cout << endl << "Enter your choice: " << endl;
			cin >> ch;

			if (ch == 1)
			{
				checkIn();
				break;

			}
			else if (ch == 2)
			{
				//cout << endl << "Thank you!" << endl;
				system("cls");
				main();
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

// Function to modify the Data Base if the user decides to check in and to record the local time

void checkIn()
{
	system("cls");
	string vehicleType;
	int checkInTime = 0, check = 0;
	cout << endl << "-------------------------Welcome to the Check-in page!-------------------------" << endl;
	cout << endl << "Choose your vehicle type (2-Wheeler or 4-Wheeler)" << endl;
	cout << endl << "Type (Case sensitive),\n'bike' or\n'car' \n" << endl;
	cin >> vehicleType;
	
	if (vehicleType == "bike")
	{
		try
		{
			string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
			pqxx::connection connectionObject(connectionString.c_str());
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
						response = work.exec("UPDATE parkinglot SET bike = '+' WHERE position = "+ pqxx::to_string(i+1)); // Updating the Data Base by replacing the '-' into '+' to represent that it is taken
						work.commit(); // Postgres function used to save the changes made to the Data Base
						cout << endl << "\n\nYou can park your vehicle at position " << i + 1 << endl;
						string time = "check_in";
						int money = 10;
						TimeRecord(i+1, vehicleType, time, money); // Calling the Check out function, passing the position number and the Vehicle Type
						break;
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
			string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
			pqxx::connection connectionObject(connectionString.c_str());
			pqxx::work work(connectionObject);
			pqxx::result response = work.exec("SELECT car FROM parkinglot ORDER BY position ASC");

			for (int i = 0; i < response.size(); i++)
			{
				string a = response[i][0].c_str();
				if (a.compare("-") == 0)
				{
					check++;
				}
			}
			//cout << check;
			if (check > 0)
			{
				system("cls");
				cout << endl << "Parking slot available!!" << endl;
				for (int i = 0; i < response.size(); i++)
				{
					string a = response[i][0].c_str();
					if (a.compare("-") == 0)
					{
						response = work.exec("UPDATE parkinglot SET car = '+' WHERE position = " + pqxx::to_string(i + 1));
						work.commit();
						cout << endl << "\n\nYou can park your vehicle at position " << i + 1 << endl;
						string time = "check_in_car";
						int money = 50;
						TimeRecord(i+1, vehicleType, time, money);
						break;
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

// TimeRecord() function will record the Check In time and will wait for the users command for recording the Check Out time

void TimeRecord(int po, string vehicleType, string time, int money)
{
	try
	{
		string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
		pqxx::connection connectionObject(connectionString.c_str());
		pqxx::work work(connectionObject);
		pqxx::result response = work.exec("SELECT * FROM parkinglot ORDER BY position ASC");

		cout << endl << "-------------------------Available lots-------------------------" << endl;
		cout << endl;

		for (int i = 0; i < response.size(); i++)
		{
			std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
			cout << endl;
		}

		cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

		//check_in is the column in the Data Base to record the check in time for Bikes alone to avoid overlapping when a car is parked in the same row.
		response = work.exec("UPDATE parkinglot SET " + pqxx::to_string(time) + pqxx::to_string(" = LOCALTIME(0) WHERE position = ") + pqxx::to_string(po) + pqxx::to_string("; ") 
			+ pqxx::to_string(" \ SELECT " + pqxx::to_string(time) + pqxx::to_string(" from parkinglot where position = ") + pqxx::to_string(po)));
		work.commit();

		string check_in_time = pqxx::to_string(response[0][0]); // here, we are storing the check in time in the form of a string

		string convert_hour = check_in_time.substr(0, 2); // Here, we are specifically selecting the 'Hour' part from the time using the substr() function

		stringstream convert(convert_hour); //Here, we are Converting the Hour part which is in string format to integer format to perform calculations
		int check_in_hour = 0;
		convert >> check_in_hour; // check_in_hour is the hour part in integer format

		int button = 0; // This button will wait for the user's Command in order to record the check out time

		cout << endl << "================================================" << endl;
		cout << "\n\n" << endl;
		cout << "\t\tHappy Shopping!!" << endl;
		cout << "\n\n\n" << endl;
		cout << endl << "================================================" << endl;
		cout << "\n\n" << endl;			
		cout << endl << "Please press '1' when you Check-Out to calculate the parking charges" << endl;
		cout << endl << "\n\n" << "Waiting for your response...\n\n" << endl;

		cin >> button;

		if (button == 1)
		{
			system("cls");

			string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
			pqxx::connection connectionObject(connectionString.c_str());
			pqxx::work work(connectionObject);

			//The data base will record the check out time when the user clicks the button
			response = work.exec("UPDATE parkinglot SET " + pqxx::to_string(time) + pqxx::to_string(" = LOCALTIME(0) WHERE position = ") + pqxx::to_string(po) + pqxx::to_string("; ")
				+ pqxx::to_string(" \ SELECT " + pqxx::to_string(time) + pqxx::to_string(" from parkinglot where position = ") + pqxx::to_string(po)));
			work.commit();

			//getting the time and converting the hour part alone into integer like we did earlier
			string check_out_time = pqxx::to_string(response[0][0]);
			cout << endl << "Your Check-In time is:" << check_in_time << endl;
			cout << endl << "Your Check-Out time is:" << check_out_time << endl;
			string convert_hour1 = check_out_time.substr(0, 2);
			stringstream convert1(convert_hour1);
			int check_out_hour = 0;
			convert1 >> check_out_hour;

			int time_diff = check_out_hour - check_in_hour; // To calculate the amount due 
			if (time_diff <= 1)
			{
				cout << endl << "******************************************************************************" << endl;
				cout << endl << "\n\nThank you for visiting!! Visit again!!" << endl;
				cout << endl << "\n\nYou are charged Rs." << money << " for making use of the parking lot, Kindly pay it to the counter while leaving!\n\n" << endl;
				cout << endl << "******************************************************************************" << endl;
				reset(po, vehicleType);
			}
			else
			{
				int charge = time_diff * money;
				cout << endl << "******************************************************************************" << endl;
				cout << endl << "\n\nThank you for visiting!! Visit again!!" << endl;
				cout << endl << "\n\nYou are charged Rs." << charge << " for making use of the parking lot, Kindly pay it to the counter while leaving!\n\n" << endl;
				cout << endl << "******************************************************************************" << endl;
				reset(po, vehicleType);
			}

		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

//leave() function is used to reset the data base to original format after the customer checks-out so that other users can use that spot

void reset(int po, string vehicleType)
{
	if (vehicleType == "bike")
	{
		string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
		pqxx::connection connectionObject(connectionString.c_str());
		pqxx::work work(connectionObject);
		//Excecuting the query to reset the database
		pqxx::result response = work.exec("update parkinglot set " + pqxx::to_string(vehicleType) + pqxx::to_string("= '-' where position = ") + pqxx::to_string(po)
			+ pqxx::to_string(";") + pqxx::to_string(" \ UPDATE parkinglot SET check_in = '00:00' WHERE position = ") + pqxx::to_string(po) + pqxx::to_string(";") + pqxx::to_string(" \ UPDATE parkinglot SET check_out = '00:00' WHERE position = ") + pqxx::to_string(po));
		work.commit();

		int console_exit = 1;
		cout << endl << "\n\nPress 0 to EXIT the console" << endl;
		cin >> console_exit;

		if (console_exit == 0)
		{
			system("cls");
			cout << endl << "================================================" << endl;
			cout << "\n\n\n" << endl;
			cout << "\t\tThank You" << endl;
			cout << "\n\n\n" << endl;
			cout << endl << "================================================" << endl;
			cout << "\n\n\n" << endl;

			system("pause");
		}
	}

	else if (vehicleType == "car")
	{
		string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
		pqxx::connection connectionObject(connectionString.c_str());
		pqxx::work work(connectionObject);
		pqxx::result response = work.exec("update parkinglot set " + pqxx::to_string(vehicleType) + pqxx::to_string("= '-' where position = ") + pqxx::to_string(po)
			+ pqxx::to_string(";") + pqxx::to_string(" \ UPDATE parkinglot SET check_in_car = '00:00' WHERE position = ") + pqxx::to_string(po) + pqxx::to_string(";") + pqxx::to_string(" \ UPDATE parkinglot SET check_out_car = '00:00' WHERE position = ") + pqxx::to_string(po));
		work.commit();

		int console_exit = 1;
		cout << endl << "\n\nPress 0 to EXIT the console" << endl;
		cin >> console_exit;

		if (console_exit == 0)
		{
			system("cls");
			cout << endl << "================================================" << endl;
			cout << "\n\n\n" << endl;
			cout << "\t\tThank You" << endl;
			cout << "\n\n\n" << endl;
			cout << endl << "================================================" << endl;
			cout << "\n\n\n" << endl;
			system("pause");
		}
	}
}