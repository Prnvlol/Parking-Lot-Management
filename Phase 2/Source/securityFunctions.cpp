#include<iostream>
#include<string>
#include<pqxx/pqxx>

#include "securityFunctions.h"
#include "auth.h"
#include "connection.h"


using namespace std;

connection con; // Object to access members from connection class file
auth a; // Object to access members from connection class file



void securityFunctions::security()
{
	cout << "\n\n" << "-------------------------------------------------------------------------" << "\n\n" << endl;
	cout << "                     Security Management Page" << "\n\n" << endl;
	cout << "-------------------------------------------------------------------------" << "\n\n" << endl;
	cout << "\n\n";
	int floor = 1;
	while (floor!=0)
	{
		cout << "Please choose which floor you wish to VIEW or UPDATE\n" << endl;
		cout << "Press,\n1 for First floor\n2 for Second floor\n3 for Third floor\n4 for Fourth floor\n5 for Fifth floor\n" << endl;
		cin >> floor;

		if (floor == 1)
		{
			system("cls");
			floor1();
			break;
		}
		else if (floor == 2)
		{
			system("cls");
			floor2();
			break;
		}
		else if (floor == 3)
		{
			system("cls");
			floor3();
			break;
		}
		else if (floor == 4)
		{
			system("cls");
			floor4();
			break;
		}
		else if (floor == 5)
		{
			system("cls");
			floor5();
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter a valid floor number. There are only 5 floors available.\n" << endl;
		}
	}
}


void securityFunctions::floor1()
{
	pqxx::connection connectionObject(con.connect().c_str());
	pqxx::work work(connectionObject);
	pqxx::result response;

	response = work.exec("SELECT * FROM floor1 ORDER BY position ASC");
	cout << endl << "-------------------------Available lots in floor 1-------------------------" << endl;
	cout << endl;
	for (int i = 0; i < response.size(); i++) //For-Loop to print all the available lots 
	{
		std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
		cout << endl;
	}
	cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

	int choice = 1;
	while (choice != 0)
	{
		cout << "\n\nDo you want to update the capacity?\n" << endl;
		cout << "Press,\n1 to REMOVE a row (will remove 1 bike spot and 1 car spot from that position number)\n2 to ADD a new row (will add 1 bike spot and 1 car spot to that position number)\n3 for Security HOME page\n4 to LOGOUT" << endl;
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			string floor = "floor1";
			remove(floor);
			break;
		}
		else if (choice == 2)
		{
			system("cls");
			string floor = "floor1";
			add(floor);
			break;
		}
		else if (choice == 3)
		{
			system("cls");
			floor1();
			break;
		}
		else if (choice == 4)
		{
			system("cls");
			a.mainCopy();
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter a valid choice from the given choices" << endl;
		}
	}

}

void securityFunctions::floor2()
{
	pqxx::connection connectionObject(con.connect().c_str());
	pqxx::work work(connectionObject);
	pqxx::result response;

	response = work.exec("SELECT * FROM floor2 ORDER BY position ASC");
	cout << endl << "-------------------------Available lots in floor 2-------------------------" << endl;
	cout << endl;
	for (int i = 0; i < response.size(); i++) //For-Loop to print all the available lots 
	{
		std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
		cout << endl;
	}
	cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

	int choice = 1;
	while (choice != 0)
	{
		cout << "\n\nDo you want to update the capacity?\n" << endl;
		cout << "Press,\n1 to REMOVE a row (will remove 1 bike spot and 1 car spot from that position number)\n2 to ADD a new row (will add 1 bike spot and 1 car spot to that position number)\n3 for Security HOME page\n4 to LOGOUT" << endl;
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			string floor = "floor2";
			remove(floor);
			break;
		}
		else if (choice == 2)
		{
			system("cls");
			string floor = "floor2";
			add(floor);
			break;
		}
		else if (choice == 3)
		{
			system("cls");
			floor2();
			break;
		}
		else if (choice == 4)
		{
			system("cls");
			a.mainCopy();
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter a valid choice from the given choices" << endl;
		}
	}
}

void securityFunctions::floor3()
{
	pqxx::connection connectionObject(con.connect().c_str());
	pqxx::work work(connectionObject);
	pqxx::result response;

	response = work.exec("SELECT * FROM floor3 ORDER BY position ASC");
	cout << endl << "-------------------------Available lots in floor 3-------------------------" << endl;
	cout << endl;
	for (int i = 0; i < response.size(); i++) //For-Loop to print all the available lots 
	{
		std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
		cout << endl;
	}
	cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

	int choice = 1;
	while (choice != 0)
	{
		cout << "\n\nDo you want to update the capacity?\n" << endl;
		cout << "Press,\n1 to REMOVE a row (will remove 1 bike spot and 1 car spot from that position number)\n2 to ADD a new row (will add 1 bike spot and 1 car spot to that position number)\n3 for Security HOME page\n4 to LOGOUT" << endl;
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			string floor = "floor3";
			remove(floor);
			break;
		}
		else if (choice == 2)
		{
			system("cls");
			string floor = "floor3";
			add(floor);
			break;
		}
		else if (choice == 3)
		{
			system("cls");
			floor3();
			break;
		}
		else if (choice == 4)
		{
			system("cls");
			a.mainCopy();
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter a valid choice from the given choices" << endl;
		}
	}
}

void securityFunctions::floor4()
{
	pqxx::connection connectionObject(con.connect().c_str());
	pqxx::work work(connectionObject);
	pqxx::result response;

	response = work.exec("SELECT * FROM floor4 ORDER BY position ASC");
	cout << endl << "-------------------------Available lots in floor 4-------------------------" << endl;
	cout << endl;
	for (int i = 0; i < response.size(); i++) //For-Loop to print all the available lots 
	{
		std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
		cout << endl;
	}
	cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

	int choice = 1;
	while (choice != 0)
	{
		cout << "\n\nDo you want to update the capacity?\n" << endl;
		cout << "Press,\n1 to REMOVE a row (will remove 1 bike spot and 1 car spot from that position number)\n2 to ADD a new row (will add 1 bike spot and 1 car spot to that position number)\n3 for Security HOME page\n4 to LOGOUT" << endl;
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			string floor = "floor4";
			remove(floor);
			break;
		}
		else if (choice == 2)
		{
			system("cls");
			string floor = "floor4";
			add(floor);
			break;
		}
		else if (choice == 3)
		{
			system("cls");
			floor4();
			break;
		}
		else if (choice == 4)
		{
			system("cls");
			a.mainCopy();
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter a valid choice from the given choices" << endl;
		}
	}
}

void securityFunctions::floor5()
{
	pqxx::connection connectionObject(con.connect().c_str());
	pqxx::work work(connectionObject);
	pqxx::result response;

	response = work.exec("SELECT * FROM floor5 ORDER BY position ASC");
	cout << endl << "-------------------------Available lots in floor 5-------------------------" << endl;
	cout << endl;
	for (int i = 0; i < response.size(); i++) //For-Loop to print all the available lots 
	{
		std::cout << "Position: " << response[i][0] << "\t" << " Bike: " << response[i][1] << "\t" << " Car: " << response[i][2] << std::endl;
		cout << endl;
	}
	cout << endl << "\nHere,\n\n'-' means Available\n'+' means Reserved" << endl;

	int choice = 1;
	while (choice != 0)
	{
		cout << "\n\nDo you want to update the capacity?\n" << endl;
		cout << "Press,\n1 to REMOVE a row (will remove 1 bike spot and 1 car spot from that position number)\n2 to ADD a new row (will add 1 bike spot and 1 car spot to that position number)\n3 for Security HOME page\n4 to LOGOUT" << endl;
		cin >> choice;

		if (choice == 1)
		{
			system("cls");
			string floor = "floor5";
			remove(floor);
			break;
		}
		else if (choice == 2)
		{
			system("cls");
			string floor = "floor5";
			add(floor);
			break;
		}
		else if (choice == 3)
		{
			system("cls");
			floor5();
			break;
		}
		else if (choice == 4)
		{
			system("cls");
			a.mainCopy();
			break;
		}
		else
		{
			system("cls");
			cout << "Please enter a valid choice from the given choices" << endl;
		}
	}
}



void securityFunctions::remove(string floor)
{
	try
	{
		pqxx::connection connectionObject(con.connect().c_str());
		pqxx::work work(connectionObject);
		int position = 0;
		std::cout << "Enter the POSITION number that you want to remove: " << std::endl;
		std::cin >> position;

		pqxx::result response = work.exec("DELETE FROM " + pqxx::to_string(floor) + pqxx::to_string(" WHERE position = ") + pqxx::to_string(position));
		work.commit();

		system("cls");
		std::cout << std::endl << "\nSuccessfully Deleted " << position << "th row from " << floor << std::endl;
		string f = floor.c_str();
		if (f.compare("floor1") == 0)
		{
			floor1();
		}
		else if (f.compare("floor2") == 0)
		{
			floor2();
		}
		else if (f.compare("floor3") == 0)
		{
			floor3();
		}
		else if (f.compare("floor4") == 0)
		{
			floor4();
		}
		else if (f.compare("floor5") == 0)
		{
			floor5();
		}
	}
	catch (const std::exception& e)
	{
		system("cls");
		std::cout << e.what() << std::endl;
		remove(floor);
	}
}

void securityFunctions::add(string floor)
{
	try
	{
		pqxx::connection connectionObject(con.connect().c_str());
		pqxx::work work(connectionObject);
		int position = 0;
		std::cout << "Enter Position number that you want to add: " << std::endl;
		std::cin >> position;

		pqxx::result response = work.exec("INSERT INTO " + pqxx::to_string(floor) + pqxx::to_string("(position, bike, car, check_in, check_out, check_in_car, check_out_car, username_bike, username_car)"
			"VALUES (" + pqxx::to_string(position) + pqxx::to_string(", '-', '-', '00:00:00', '00:00:00', '00:00:00', '00:00:00', '-', '-')")));
		work.commit();

		system("cls");
		std::cout << std::endl << "Added position number " << position << " to " << floor << std::endl;

		string f = floor.c_str();
		if (f.compare("floor1") == 0)
		{
			floor1();
		}
		else if (f.compare("floor2") == 0)
		{
			floor2();
		}
		else if (f.compare("floor3") == 0)
		{
			floor3();
		}
		else if (f.compare("floor4") == 0)
		{
			floor4();
		}
		else if (f.compare("floor5") == 0)
		{
			floor5();
		}
	}
	catch (const std::exception& e)
	{
		system("cls");
		std::cout << e.what() << std::endl;
		add(floor);
	}
}