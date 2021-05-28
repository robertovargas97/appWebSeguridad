#include "db_connection.h"
#include <sstream>
#include <string>

using namespace std;

DBConnection::DBConnection()
{
    mysql = mysql_init(mysql);

    if (!mysql)
    {
        cout << "<h3 class\"ml-4\">"
             << "Something went wrong while connection to the database"
             << "</h3>";
    }
    else
    {
        mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");
        if (!mysql_real_connect(mysql, DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME, 0, NULL, CLIENT_FOUND_ROWS))
        {
            cout << "<h3 class\"ml-4\">"
                 << "Connection with the database Failed"
                 << "</h3>";
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
    string query = "call add_product('" + name + "'," + "'" + price + "'," + "'" + description + "'," + "'" + category + "'" + ");";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true;
    }
    return response;
}

bool DBConnection::add_user(string name, string last_name, string email, string secret, string phone_number, string address, string salt)
{
    bool response = false;

    string query = "call add_user('" + name + "'," + "'" + last_name + "'," + "'" + email + "'," + "'" + secret + "'," + "'" + phone_number + "'," + "'" + address + "'," + "'" + salt + "'" + ");";

    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true;
    }
    return response;
}

string DBConnection::get_user_salt(string email)
{
    string salt = "";
    string query = "call get_user_salt('" + email + "');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        MYSQL_RES *result = mysql_store_result(mysql);

        if (result) //Checks if we got results
        {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != 0)
            {
                salt = row[0]; // salt from the db
            }
        }
        mysql_free_result(result);
    }

    return salt;
}

bool DBConnection::verify_login(string email, string password, string salt)
{
    Utils utils = Utils();
    bool response = false;
    string matching_email = "";
    string password_hash = utils.create_hash_sha2(password, salt);
    string query = "call verify_login('" + email + "'," + "'" + password_hash + "');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        MYSQL_RES *result = mysql_store_result(mysql);

        if (result) //Checks if we got results
        {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != 0)
            {
                matching_email = row[0]; // salt from the db
                response = true;
            }
        }
        mysql_free_result(result);
    }

    return response;
}


bool DBConnection::exist_in_cart(string email,string code_product)
{
    bool response = false; //  no existe
    string query = "call exit_in_cart('" + email + "'," + code_product +");";
    if (mysql_query(mysql, query.c_str())) {
      //printf("Query failed: %s\n", mysql_error(mysql));
    } else {
      MYSQL_RES *result = mysql_store_result(mysql);

      if (!result) {
        printf("Couldn't get results set: %s\n", mysql_error(mysql));
      } else {
        MYSQL_ROW row = mysql_fetch_row(result);
        if ( row != 0){
            response = true;
        }
        mysql_free_result(result);
      }
    }

    return response;
}

vector<vector<string>> DBConnection::get_my_cart(string email)
{
    string query = "call get_my_cart('" + email + "');";
    vector<vector<string>> product_list;          
    if (mysql_query(mysql, query.c_str())) {
      printf("Query failed: %s\n", mysql_error(mysql));
    } else {
      MYSQL_RES *result = mysql_store_result(mysql);

      if (!result) {
        printf("Couldn't get results set: %s\n", mysql_error(mysql));
      } else {
        MYSQL_ROW row;
        int i;
        unsigned int num_fields = mysql_num_fields(result);                                           
        while ((row = mysql_fetch_row(result))) {
            vector<string> prod;
          for (i = 0; i < num_fields; i++) {
                prod.push_back(row[i]);                             
            }
          product_list.push_back(prod);
        }
        mysql_free_result(result);
      }
    }
    return product_list;
 } 

bool DBConnection::add_to_cart(string email, string code_product)
{
    //int code_product_int = stoi(code_product);
    bool response = false;//no ha sido agregado 
    string query = "call add_to_cart('"+email+"', '"+ code_product+"');";
    cout<<query<<endl;
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //fue agregado al carrito
    }
    return response;
}

bool DBConnection::delete_from_cart(string email, string code_product)
{
    bool response = false; //no ha sido boraado
    string query = "call delete_from_cart('" + email + "'," + code_product +");";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //fue borrado 
    }
    return response;
}

bool DBConnection::empty_cart(string email, string code_product)
{
    bool response = false;  //aun no vaciado
    string query = "call empty_cart('" + email + "',"+  code_product +"');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //vacio el carryto correctamente
    }
    return response;
} 




/* bool DBConnection::add_product(string name, string price, string description, string category)
{
    bool response = false;
    //const int price_query = stoi(*price);
    string query = "call add_product('" + name + "'," + "'" + price + "'," + "'" + description + "'," + "'" + category + "'" + ");";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true;
    }
    return response;
} */

vector<vector<string> > DBConnection::get_all_products(){
    vector<vector<string>> product_list;  
    string query = "call get_all_products";           
    if (mysql_query(mysql, query.c_str())) {
      printf("Query failed: %s\n", mysql_error(mysql));
    } else {
      MYSQL_RES *result = mysql_store_result(mysql);

      if (!result) {
        printf("Couldn't get results set: %s\n", mysql_error(mysql));
      } else {
        MYSQL_ROW row;
        int i;
        unsigned int num_fields = mysql_num_fields(result);                                           
        while ((row = mysql_fetch_row(result))) {
            vector<string> prod;
          for (i = 0; i < num_fields; i++) {
                prod.push_back(row[i]);                             
            }
          product_list.push_back(prod);
        }
        mysql_free_result(result);
      }
    }
    return product_list;
}



// int main()
//  {
//     DBConnection conn = DBConnection();
//     bool exito = conn.add_to_cart("hellen@gmail.com", "4");
//     if(exito){
//         printf("Exito");
//     }
//     else{
//         printf("No sirvio");
//     }

    // }
    // /* bool result = conn.add_comment("Camila", "Viquez", "cv@mail.com", "Consulta", "Todo muy bonito");

    // cout << result;
    // vector<string> user_info = conn.get_user_info("hellen@gmail.com");
    // int user_info_size = user_info.size();
    // for (size_t i = 0; i < user_info_size; i++)
    // {
    //     if (i == (user_info_size - 1))
    //     {
    //         cout << user_info[i] << "\n";
    //     }
    //     else
    //     {
    //         cout << user_info[i] << ", ";
    //     }
    // } */

    //string query = "call login('dieg0cr98@gmail.com','8054EC4A85B659BCB31F22F5FC6756DC9F9AD51ED4B3E4EE09D38E1869C26627')";
    //mysql_query(c.mysql, query.c_str());
//     return 1;
//  }
