#include "connection.h"

using namespace std;

string connection::connect()
{
	string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
	return connectionString;
}
