#include<iostream>
#include<string>
#include<pqxx/pqxx>

#include "customerFunctions.h"
#include "securityFunctions.h"
#include "auth.h"
#include "connection.h"

using namespace std;



void customerFunctions::customer(string userId)
{
	cout << "\n\n" << "-------------------------------------------------------------------------" << "\n\n" << endl;
	cout << "                     Welcome " << userId << "!!\n\n" << endl;
	cout << "-------------------------------------------------------------------------" << "\n\n" << endl;
	cout << "\n\n";

	int choice = 1;
	while (choice != 0)
	{
		cout << "Press,\n1 to CHECK-IN\n2 to CHECK-OUT\n3 to LOG-OUT\n" << endl;
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			check_in(userId);
			break;
		}
		else if (choice == 2)
		{
			system("cls");
			
			// confirming if the user's vehicle is already parked or not
			int j = 0;
			while(j<6)
			{
				j++;
				string floorNo = "floor"+to_string(j);

				try
				{
					connection con;
					pqxx::connection connectionObject(con.connect().c_str());
					pqxx::work work(connectionObject);
					pqxx::result response = work.exec("SELECT username_bike FROM " + pqxx::to_string(floorNo) + pqxx::to_string(" ORDER BY position ASC"));
					int check = 0, i;
					for (i = 0; i < response.size(); i++)
					{
						string a = response[i][0].c_str(); // Here we are converting the C++ string format into C string format in order to use the compare() function
						if (a.compare(userId) == 0)
						{
							check++;
							break;
						}
					}
					int po = i + 1;
					//Checking if the User's vehicle is already parked
					if (check > 0)
					{
						string vtype = "bike";
						check_out(po, vtype, userId, floorNo);
						break;
					}
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}

				try
				{
					connection con;
					pqxx::connection connectionObject(con.connect().c_str());
					pqxx::work work(connectionObject);
					pqxx::result response = work.exec("SELECT username_car FROM " + pqxx::to_string(floorNo) + pqxx::to_string(" ORDER BY position ASC")); //Query to access only bike column and to check if there is free lot available

					int check = 0;
					int i = 0;
					for (i = 0; i < response.size(); i++)
					{
						string a = response[i][0].c_str(); // Here we are converting the C++ string format into C string format in order to use the compare() function
						if (a.compare(userId) == 0)
						{
							check++;
							break;
						}
					}
					int po = i + 1;
					if (check > 0)
					{
						string vtype = "car";
						check_out(po, vtype, userId, floorNo);
				        break;
					}
				}
				catch (const std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			system("cls");
			cout << "\n"<<userId<<", Your Vehicle is not parked yet.\n" << endl;
			customer(userId);
			break;
		}
		else if (choice == 3)
		{
			auth a;
			system("cls");
			a.mainCopy();
			break;
		}
		else
		{
			system("cls");
			cout << "\nPlease enter a valid choice from the given choices\n" << endl;
		}
	}
}


void customerFunctions::check_in(string userId)
{
	cout << "\n\n" << "-------------------------------------------------------------------------" << "\n\n" << endl;
	cout << "                     Welcome to CHECK-IN PAGE "<< userId << "!!\n\n" << endl;
	cout << "-------------------------------------------------------------------------" << "\n\n" << endl;
	cout << "\n\n";

	string vehicle_type;
	int position_number = 0;
	int floor_number = 0;
	cout << "\tPlease reach out to the security and ask for available parking slots for your vehicle and enter the details below to CHECK-IN\n\n" << endl;
	
	cout << "VEHICLE TYPE: (case sensitive) \n" << endl;
	cout << "Type,\n'bike' for 2-wheeler\n'car' for 4-wheeler\n" << endl;
	cin >> vehicle_type;

	do
	{
		cout << "\nFLOOR NUMBER: \n" << endl;
		cout << "Type,\n1 for first floor\n2 for second floor\n3 for third floor\n4 for fourth floor\n5 for fifth floor\n" << endl;
		cin >> floor_number;
	} while (floor_number <= 0 || floor_number > 5);


	cout << "\nPOSITION NUMBER: \n" << endl;
	cout << "Type the POSITION NUMBER: " << endl;
	cin >> position_number;

	int ch = 1;
	while (ch != 0)
	{
		cout << "\nCONFIRM CHECK-IN\n" << endl;
		cout << "Press,\n1 to CONFIRM CHECK-IN\n2 to re-enter CHECK-IN details\n" << endl;
		cin >> ch;
		if (ch == 1)
		{
			system("cls");

			cout << "\n\n" << "-------------------------------------------------------------------------" << "\n\n" << endl;
			cout << "                     You have successfully checked in " << userId << "!!\n\n" << endl;
			cout << "-------------------------------------------------------------------------" << "\n\n" << endl;
			cout << "\n\n";
			string floor;
			if (floor_number == 1)
			{
				floor = "floor1";
			}
			else if (floor_number == 2)
			{
				floor = "floor2";
			}
			else if (floor_number == 3)
			{
				floor = "floor3";
			}
			else if (floor_number == 4)
			{
				floor = "floor4";
			}
			else if (floor_number == 5)
			{
				floor = "floor5";
			}

			string time;
			string user;
			string vtype = vehicle_type.c_str();
			if (vtype.compare("bike")==0)
			{
				time = "check_in";
				user = "username_bike";
			}
			else if (vtype.compare("car") == 0)
			{
				time = "check_in_car";
				user = "username_car";
			}
			try
			{
				connection con;
				pqxx::connection connectionObject(con.connect().c_str());
				pqxx::work work(connectionObject);
				pqxx::result response;

				response = work.exec("UPDATE " + pqxx::to_string(floor) + pqxx::to_string(" SET ") + pqxx::to_string(vehicle_type) + pqxx::to_string(" = '+', ") + pqxx::to_string(time)
					+ pqxx::to_string(" = LOCALTIME(0), ") + pqxx::to_string(user) + pqxx::to_string(" = ") + pqxx::to_string("'") + pqxx::to_string(userId) + pqxx::to_string("'") + pqxx::to_string(" WHERE position = ")
					+ pqxx::to_string(position_number) + pqxx::to_string("; ") + pqxx::to_string(" SELECT ") + pqxx::to_string(time) + pqxx::to_string(" FROM ") + pqxx::to_string(floor)
					+ pqxx::to_string(" WHERE position = ") + pqxx::to_string(position_number));
				work.commit();

				string check_in_time = pqxx::to_string(response[0][0]); // here, we are storing the check in time in the form of a string
				string convert_hour = check_in_time.substr(0, 2); // Here, we are specifically selecting the 'Hour' part from the time using the substr() function
				stringstream convert(convert_hour); //Here, we are Converting the Hour part which is in string format to integer format to perform calculations
				int check_in_hour = 0;
				convert >> check_in_hour; // check_in_hour is the hour part in integer format

				cout << "\nYour CHECK-IN time is - " << check_in_time << endl;

				int c = 1;
				while (c != 0)
				{
					cout << "\n\nPress,\n1 for HOME page\n2 to LOG-OUT\n" << endl;
					cin >> c;
					
					if (c == 1)
					{
						system("cls");
						customer(userId);
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
						cout << "\nEnter a valid choice from the choices given" << endl;
					}
				}

			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}

		}
		else if (ch == 2)
		{
			system("cls");
			check_in(userId);
			break;
		}
		else
		{
			system("cls");
			cout << "\nEnter a valid choice from the choices given\n" << endl;
		}
	}
}


void customerFunctions::check_out(int po, string vtype, string userId, string floorNo)
{
	system("cls");
	string vehicle_type = vtype.c_str();
	string timein;
	string timeout;
	string user;
	int money;
	if (vehicle_type.compare("bike") == 0)
	{
		timein = "check_in";
		timeout = "check_out";
		user = "username_bike";
		money = 10;
	}
	else if (vehicle_type.compare("car") == 0)
	{
		timein = "check_in_car";
		timeout = "check_out_car";
		user = "username_car";
		money = 50;
	}

	connection con;
	try
	{
		pqxx::connection connectionObject(con.connect().c_str());
		pqxx::work work(connectionObject);
		pqxx::result response;

		// For CHECK-IN time
		response = work.exec("SELECT " + pqxx::to_string(timein) + pqxx::to_string(" FROM ") + pqxx::to_string(floorNo) + pqxx::to_string(" WHERE position = ") + pqxx::to_string(po));
		work.commit();

		string check_in_time = pqxx::to_string(response[0][0]); // here, we are storing the check in time in the form of a string
		string convert_hour = check_in_time.substr(0, 2); // Here, we are specifically selecting the 'Hour' part from the time using the substr() function
		stringstream convert(convert_hour); //Here, we are Converting the Hour part which is in string format to integer format to perform calculations
		int check_in_hour = 0;
		convert >> check_in_hour; // check_in_hour is the hour part in integer format

		int ch = 0;
		cout << "\nPress 1 to confirm CHECK-OUT\nPress 2 to go back to HOME Page\n\n" << endl;
		cin >> ch;
		if (ch == 1)
		{
			pqxx::connection connectionObject(con.connect().c_str());
			pqxx::work work(connectionObject);
			pqxx::result response;

			response = work.exec("UPDATE " + pqxx::to_string(floorNo) + pqxx::to_string(" SET ") + pqxx::to_string(timeout) + pqxx::to_string(" = LOCALTIME(0) WHERE position = ") + pqxx::to_string(po)
				+ pqxx::to_string("; ") + pqxx::to_string("SELECT ") + pqxx::to_string(timeout) + pqxx::to_string(" FROM ") + pqxx::to_string(floorNo) + pqxx::to_string(" WHERE position = ") + pqxx::to_string(po));
			work.commit();

			string check_out_time = pqxx::to_string(response[0][0]);
			string convert_hour1 = check_out_time.substr(0, 2);
			stringstream convert1(convert_hour1);
			int check_out_hour = 0;
			convert1 >> check_out_hour;


			cout << "\n\n" << userId<<", \n\nYour CHECK-IN time is - " << check_in_time << endl;
			cout << "\n\n" << "Your CHECK-OUT time is - " << check_out_time << "\n\n" << endl;

			int time_diff = check_out_hour - check_in_hour; // To calculate the amount due 
			customerFunctions cf;
			if (time_diff <= 1)
			{
				cout << endl << "******************************************************************************" << endl;
				cout << endl << "\n\nThank you for visiting!! Visit again!!" << endl;
				cout << endl << "\n\nYou are charged Rs." << money << " for making use of the parking lot, Kindly pay it to the counter while leaving!\n\n" << endl;
				cout << endl << "******************************************************************************" << endl;
				cf.reset(po, vtype, floorNo);
			}
			else
			{
				int charge = time_diff * money;
				cout << endl << "******************************************************************************" << endl;
				cout << endl << "\n\nThank you for visiting!! Visit again!!" << endl;
				cout << endl << "\n\nYou are charged Rs." << charge << " for making use of the parking lot, Kindly pay it to the counter while leaving!\n\n" << endl;
				cout << endl << "******************************************************************************" << endl;
				cf.reset(po, vtype, floorNo);
			}
		}
		else if (ch == 2)
		{
			system("cls");
			customer(userId);
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void customerFunctions::reset(int po, string vtype, string floorNo)
{
	string vehicle_type = vtype.c_str();
	string timeout;
	string timein;
	string user;
	if (vehicle_type.compare("bike") == 0)
	{
		timein = "check_in";
		timeout = "check_out";
		user = "username_bike";
	}
	else if (vehicle_type.compare("car") == 0)
	{
		timein = "check_in_car";
		timeout = "check_out_car";
		user = "username_car";
	}

	try
	{
		connection con;
		pqxx::connection connectionObject(con.connect().c_str());
		pqxx::work work(connectionObject);
		pqxx::result response;

		response = work.exec("UPDATE " + pqxx::to_string(floorNo) + pqxx::to_string(" SET ") + pqxx::to_string(vtype) + pqxx::to_string(" = '-', ") + pqxx::to_string(timein)
			+ pqxx::to_string(" = '00:00:00', ") + pqxx::to_string(timeout) + pqxx::to_string(" = '00:00:00', ") + pqxx::to_string(user) + pqxx::to_string(" = '-' ")
			+ pqxx::to_string("WHERE position = ") + pqxx::to_string(po));
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
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}