#include "connection.h"
#include "CheckInFile.h"
#include "auth.h"
#include "CheckOutFile.h"

string connection::connect()
{
	string connectionString = "host=localhost port=5432 dbname=parking user=postgres password =pranav";
	return connectionString;
}
