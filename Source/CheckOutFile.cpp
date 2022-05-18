#include "CheckOutFile.h"
#include "auth.h"
#include "CheckInFile.h"

using namespace std;

// checkOut() is used to record the check-out time and to calculate the parking charges 

void CheckOutFile::checkOut(int po, string vehicleType, string userId)
{
	system("cls");
	if (vehicleType == "bike") // If the user has a Bike
	{
		try
		{
			string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
			pqxx::connection connectionObject(connectionString.c_str());
			pqxx::work work(connectionObject);
			pqxx::result response;

			//check_in is the column in the Data Base to record the check in time for Bikes alone to avoid overlapping when a car is parked in the same row.
			response = work.exec("SELECT check_in from parkinglot where position = " + pqxx::to_string(po));
			work.commit();

			string check_in_time = pqxx::to_string(response[0][0]); // here, we are storing the check in time in the form of a string
			string convert_hour = check_in_time.substr(0, 2); // Here, we are specifically selecting the 'Hour' part from the time using the substr() function
			stringstream convert(convert_hour); //Here, we are Converting the Hour part which is in string format to integer format to perform calculations
			int check_in_hour = 0;
			convert >> check_in_hour; // check_in_hour is the hour part in integer format

			int ch = 0;
			cout << "\nPress 1 to confirm CHECK-OUT:\n" << endl;
			cin >> ch;
			if (ch == 1)
			{
				string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
				pqxx::connection connectionObject(connectionString.c_str());
				pqxx::work work(connectionObject);

				//The data base will record the check out time when the user clicks the button
				response = work.exec("UPDATE parkinglot SET check_out = LOCALTIME(0) WHERE position = " + pqxx::to_string(po) + pqxx::to_string("; ")
					+ pqxx::to_string(" SELECT check_out " + pqxx::to_string(" from parkinglot where position = ") + pqxx::to_string(po)));
				work.commit();

				//getting the time and converting the hour part alone into integer like we did earlier
				string check_out_time = pqxx::to_string(response[0][0]);
				string convert_hour1 = check_out_time.substr(0, 2);
				stringstream convert1(convert_hour1);
				int check_out_hour = 0;
				convert1 >> check_out_hour;

				cout << "\n\n" << "Your CHECK-IN time is - " << check_in_time << endl;
				cout << "\n\n" << "Your CHECK-OUT time is - " << check_out_time << "\n\n" << endl;

				int time_diff = check_out_hour - check_in_hour; // To calculate the amount due 
				if (time_diff <= 1)
				{
					cout << endl << "******************************************************************************" << endl;
					cout << endl << "\n\nThank you for visiting!! Visit again!!" << endl;
					cout << endl << "\n\nYou are charged Rs.10 for making use of the parking lot, Kindly pay it to the counter while leaving!\n\n" << endl;
					cout << endl << "******************************************************************************" << endl;
					reset(po, vehicleType);
				}
				else
				{
					int charge = time_diff * 10;
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

	else if (vehicleType == "car") // If the user has a car
	{
		try
		{
			string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
			pqxx::connection connectionObject(connectionString.c_str());
			pqxx::work work(connectionObject);
			pqxx::result response;

			//check_in is the column in the Data Base to record the check in time for Bikes alone to avoid overlapping when a car is parked in the same row.
			response = work.exec("SELECT check_in_car from parkinglot where position = " + pqxx::to_string(po));
			work.commit();

			string check_in_time = pqxx::to_string(response[0][0]); // here, we are storing the check in time in the form of a string
			string convert_hour = check_in_time.substr(0, 2); // Here, we are specifically selecting the 'Hour' part from the time using the substr() function
			stringstream convert(convert_hour); //Here, we are Converting the Hour part which is in string format to integer format to perform calculations
			int check_in_hour = 0;
			convert >> check_in_hour; // check_in_hour is the hour part in integer format

			int ch = 0;
			cout << "\nPress 1 to confirm CHECK-OUT:\n" << endl;
			cin >> ch;
			if (ch == 1)
			{
				string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
				pqxx::connection connectionObject(connectionString.c_str());
				pqxx::work work(connectionObject);

				//The data base will record the check out time when the user clicks the button
				response = work.exec("UPDATE parkinglot SET check_out_car = LOCALTIME(0) WHERE position = " + pqxx::to_string(po) + pqxx::to_string("; ")
					+ pqxx::to_string(" SELECT check_out_car " + pqxx::to_string(" from parkinglot where position = ") + pqxx::to_string(po)));
				work.commit();

				//getting the time and converting the hour part alone into integer like we did earlier
				string check_out_time = pqxx::to_string(response[0][0]);
				string convert_hour1 = check_out_time.substr(0, 2);
				stringstream convert1(convert_hour1);
				int check_out_hour = 0;
				convert1 >> check_out_hour;

				cout << "\n\n" << "Your CHECK-IN time is - " << check_in_time << endl;
				cout << "\n\n" << "Your CHECK-OUT time is - " << check_out_time << "\n\n" << endl;

				int time_diff = check_out_hour - check_in_hour; // To calculate the amount due 
				if (time_diff <= 1)
				{
					cout << endl << "******************************************************************************" << endl;
					cout << endl << "\n\nThank you for visiting!! Visit again!!" << endl;
					cout << endl << "\n\nYou are charged Rs.50 for making use of the parking lot, Kindly pay it to the counter while leaving!\n\n" << endl;
					cout << endl << "******************************************************************************" << endl;
					reset(po, vehicleType);
				}
				else
				{
					int charge = time_diff * 50;
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
}


// reset() function here is used to reset all the datas of a customer back to originals so that others can use the space

void CheckOutFile::reset(int po, string vehicleType)
{
	if (vehicleType == "bike")
	{
		string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
		pqxx::connection connectionObject(connectionString.c_str());
		pqxx::work work(connectionObject);
		//Excecuting the query to reset the database
		pqxx::result response = work.exec("update parkinglot set " + pqxx::to_string(vehicleType) + pqxx::to_string("= '-' where position = ") + pqxx::to_string(po)
			+ pqxx::to_string(";") + pqxx::to_string(" UPDATE parkinglot SET check_in = '00:00' WHERE position = ") + pqxx::to_string(po) + pqxx::to_string(";")
			+ pqxx::to_string("UPDATE parkinglot SET username_bike = '-' WHERE position = " + pqxx::to_string(po) + pqxx::to_string(";")
				+ pqxx::to_string(" UPDATE parkinglot SET check_out = '00:00' WHERE position = ") + pqxx::to_string(po)));
		work.commit();

		int console_exit = 1;
		cout << endl << "\n\PRESS 0 to EXIT the console or PRESS 1 to LOGOUT" << endl;
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
			exit(0);
		}
		else if (console_exit == 1)
		{
			auth a;
			system("cls");
			a.mainCopy();
		}
	}

	else if (vehicleType == "car")
	{
		string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
		pqxx::connection connectionObject(connectionString.c_str());
		pqxx::work work(connectionObject);
		pqxx::result response = work.exec("update parkinglot set " + pqxx::to_string(vehicleType) + pqxx::to_string("= '-' where position = ") + pqxx::to_string(po)
			+ pqxx::to_string(";") + pqxx::to_string(" UPDATE parkinglot SET check_in_car = '00:00' WHERE position = ") + pqxx::to_string(po) + pqxx::to_string(";")
			+ pqxx::to_string("UPDATE parkinglot SET username_car = '-' WHERE position = " + pqxx::to_string(po) + pqxx::to_string(";")
				+ pqxx::to_string(" UPDATE parkinglot SET check_out_car = '00:00' WHERE position = ") + pqxx::to_string(po)));
		work.commit();

		int console_exit = 1;
		cout << endl << "\n\PRESS 0 to EXIT the console or PRESS 1 to LOGOUT" << endl;
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
			exit(0);
		}
		else if (console_exit == 1)
		{
			auth a;
			system("cls");
			a.mainCopy();
		}
	}
}