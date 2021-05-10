
#include "db_connection.h"

using namespace std;

DBConnection::DBConnection(string host, string user, string password, string databaseName)
{
    mysql = mysql_init(mysql);

    if (!mysql)
    {
        printf("Something went wrong while connection to the database\n");
    }
    else
    {
        mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");
        if (!mysql_real_connect(mysql, host.c_str(), user.c_str(), password.c_str(), databaseName.c_str(), 0, NULL, CLIENT_FOUND_ROWS))
        {
            printf("Connection with the database Failed\n");
        }
        else
        {
            printf("Connection stablished\n");
        }
    }
};

DBConnection::~DBConnection()
{
    mysql_close(mysql);
    mysql_library_end();
};

vector<string> DBConnection::get_user_info(string email)
{
    vector<string> info;
    string table = "Persona";
    string query = "SELECT * FROM " + table + " WHERE correo='" + email + "';";

    if (mysql_query(mysql, query.c_str()) != 0)
    {
        printf("Query failed: %s\n", mysql_error(mysql));
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(mysql);

        if (!result)
        {
            printf("Couldn't get results set: %s\n", mysql_error(mysql));
        }
        else
        {
            MYSQL_ROW row = mysql_fetch_row(result);
            info.push_back(row[0]); // email
            info.push_back(row[1]); // name
            info.push_back(row[2]); // last_name
            info.push_back(row[3]); // phone number
            info.push_back(row[4]); // address

            mysql_free_result(result);
        }
    }
    return info;
}

int main()
{

    DBConnection conn = DBConnection("localhost", "user", "user123", "testdb");
    vector<string> user_info = conn.get_user_info("hellen@gmail.com");
    int user_info_size = user_info.size();
    for (size_t i = 0; i < user_info_size; i++)
    {
        if (i == (user_info_size - 1))
        {
            cout << user_info[i] << "\n";
        }
        else
        {
            cout << user_info[i] << ", ";
        }
    }

    //string query = "call login('dieg0cr98@gmail.com','8054EC4A85B659BCB31F22F5FC6756DC9F9AD51ED4B3E4EE09D38E1869C26627')";
    //mysql_query(c.mysql, query.c_str());
    return 1;
}
