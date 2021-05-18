#include "db_connection.h"

using namespace std;

DBConnection::DBConnection()
{
    mysql = mysql_init(mysql);

    if (!mysql)
    {
        cout << "<h3 class\"ml-4\">" << "Something went wrong while connection to the database" << "</h3>";
    }
    else
    {
        mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");
        if (!mysql_real_connect(mysql, DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME, 0, NULL, CLIENT_FOUND_ROWS))
        {
            cout << "<h3 class\"ml-4\">" << "Connection with the database Failed" << "</h3>";
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

bool DBConnection::add_comment(string name, string last_name, string email, string comment_type, string comment)
{
    bool response = false;
    string u_name = name;
    string u_last_name = last_name;
    string full_name = u_name + " " + u_last_name;
    string query = "call add_comment('" + full_name + "'," + "'" + email + "'," + "'" + comment_type + "'," + "'" + comment + "'" + ");";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true;
    }
    return response;
}

bool DBConnection::add_product(string name, string price, string description, string category)
{
    bool response = false;
    //const int price_query = stoi(*price);
    string query = "call add_product('" + name + "'," + "'"  + price + "'," + "'" +description + "'," + "'" + category + "'" + ");";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true;
    }
    return response;
}


