#include "db_connection.h"
#include <sstream>
#include <string>

using namespace std;

DBConnection::DBConnection()
{
    mysql = mysql_init(mysql);

    if (!mysql)
    {
        utils.log_app_action("db connection", "error", "-", "Connection with the database Failed");
    }
    else
    {
        mysql_options(mysql, MYSQL_READ_DEFAULT_FILE, (void *)"./my.cnf");
        if (!mysql_real_connect(mysql, DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME, 0, NULL, CLIENT_FOUND_ROWS))
        {
            utils.log_app_action("db connection", "error", "-", "Connection with the database Failed");
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
    else
    {
        string error = mysql_error(mysql);
        this->utils.log_app_action("db connection (add comment)", "error", "-", error);
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
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection (add product)", "error", "-", error);
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
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection (add user)", "error", "-", error);
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
                utils.log_app_action("db connection (get user salt)", "success", email);
            }
        }
        mysql_free_result(result);
    }
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection (get user salt)", "error", "-", error);
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

                cout << "Set-Cookie:Email=" + email + ";\r\n";
                cout << "Set-Cookie:Password=" + password_hash + ";\r\n";
                cout << "Set-Cookie:Domain=localhost;\r\n";
            }
            else
            {

                cout << "Set-Cookie:Email=-;\r\n";
                cout << "Set-Cookie:Password=-;\r\n";
                cout << "Set-Cookie:Domain=-;\r\n";
                string error = mysql_error(mysql);
                utils.log_app_action("db connection (verify login)", "error", "-", error);
            }
        }
        mysql_free_result(result);
    }
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }

    return response;
}

bool DBConnection::verify_session(string email, string password)
{
    Utils utils = Utils();
    bool response = false;
    string query = "call verify_login('" + email + "'," + "'" + password + "');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        MYSQL_RES *result = mysql_store_result(mysql);

        if (result) //Checks if we got results
        {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != 0)
            {
                response = true;
                utils.log_app_action("db connection (verify session)", "success", email);
            }
        }
        mysql_free_result(result);
    }
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }

    return response;
}

string DBConnection::exist_in_cart(string email, string code_product)
{
    string response = "false"; //  no existe
    string query = "call exists_product_in_cart('" + email + "'," + code_product + ");";
    if (mysql_query(mysql, query.c_str()))
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(mysql);

        if (!result)
        {
            string error = mysql_error(mysql);
            utils.log_app_action("db connection", "error", "-", error);
        }
        else
        {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row != 0)
            {
                response = "true";
                utils.log_app_action("db connection (exist in cart)", "success", email, "Product in cart");
            }
            mysql_free_result(result);
        }
    }
    return response;
}

vector<vector<string> > DBConnection::get_my_cart(string email)
{
    string query = "call get_my_cart('" + email + "');";
    vector<vector<string>   > product_list;
    if (mysql_query(mysql, query.c_str()))
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(mysql);

        if (!result)
        {
            string error = mysql_error(mysql);
            utils.log_app_action("db connection", "error", "-", error);
        }
        else
        {
            MYSQL_ROW row;
            int i;
            unsigned int num_fields = mysql_num_fields(result);
            while ((row = mysql_fetch_row(result)))
            {
                vector<string> prod;
                for (i = 0; i < num_fields; i++)
                {
                    prod.push_back(row[i]);
                }
                product_list.push_back(prod);
            }
            utils.log_app_action("db connection (get my cart) ", "success", email);
            mysql_free_result(result);
        }
    }
    return product_list;
}

bool DBConnection::add_to_cart(string email, string code_product)
{
    //int code_product_int = stoi(code_product);
    bool response = false; //no ha sido agregado
    string query = "call add_to_cart('" + email + "', '" + code_product + "');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //fue agregado al carrito
        utils.log_app_action("db connection (add to cart)", "success", email, "Product added to cart");
    }
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    return response;
}

bool DBConnection::delete_from_cart(string email, string code_product)
{
    bool response = false; //no ha sido boraado
    string query = "call remove_from_cart('" + email + "'," + code_product + ");";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //fue borrado
        utils.log_app_action("db connection (delete from cart)", "success", email, "Product deleted from cart");
    }
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    return response;

}bool DBConnection::buy_cart(string email)
{
    bool response = false; //no ha sido boraado
    string query = "call buy_cart('" + email + "');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //fue borrado
        utils.log_app_action("db connection (delete from cart)", "success", email, "Product deleted from cart");
    }
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    return response;
}

bool DBConnection::empty_cart(string email, string code_product)
{
    bool response = false; //aun no vaciado
    string query = "call empty_cart('" + email + "'," + code_product + "');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //vacio el carryto correctamente
        utils.log_app_action("db connection (empty cart)", "success", email, "The cart is empty now");
    }
    else
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    return response;
}

bool DBConnection::erase_product(string codigoProducto){
    bool response = false; //aun no vaciado
    string query = "call erase_product('"+codigoProducto+ "');";
    if (mysql_query(mysql, query.c_str()) == 0)
    {
        response = true; //vacio el carryto correctamente
        utils.log_app_action("db connection (erase_product)", "success", codigoProducto, "Erased product");
    }
    else
    {
        string error = mysql_error(mysql);
        //utils.log_app_action("db connection", "error", "-", error);
        utils.log_app_action("db connection (erase_product)", "error", codigoProducto, "Failure erasing product");
    }
    return response;
}

bool DBConnection::erase_products(string correo, vector<vector<string> > cart_list){
    bool erased_product = false;
    string codigo_producto = "";  
    
     if (cart_list.size() != 0)
    {       
        for (int i = 0; i < cart_list.size(); i++)
        {           
            codigo_producto = cart_list[i][3];
            erased_product = erase_product(codigo_producto);   
        }
    }     else{
            utils.log_app_action("db connection (erase_product)", "error", correo, "Failure erasing product is empty"); 
    }    
    if(erased_product){
        utils.log_app_action("db connection (erase_product)", "success", correo, "Products deleted from the lists of products");
    } 
    return erased_product;
}

vector<vector<string>> DBConnection::get_all_products()
{
    vector<vector<string>> product_list;
    string query = "call get_all_products";
    if (mysql_query(mysql, query.c_str()))
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    else
    {

        MYSQL_RES *result = mysql_store_result(mysql);

        if (!result)
        {
            string error = mysql_error(mysql);
            utils.log_app_action("db connection", "error", "-", error);
        }
        else
        {
            MYSQL_ROW row;
            int i;
            unsigned int num_fields = mysql_num_fields(result);

            while ((row = mysql_fetch_row(result)))
            {
                vector<string> prod;
                for (i = 0; i < num_fields; i++)
                {
                    if (row[i] != nullptr)
                    {
                        prod.push_back(row[i]);
                    }
                    else
                    {
                        prod.push_back("");
                    }
                }

                product_list.push_back(prod);
            }
            utils.log_app_action("db connection (get all products)", "success", "");
            mysql_free_result(result);
        }
    }
    return product_list;
}

vector<vector<string>> DBConnection::search_product(string product)
{
    vector<vector<string>> product_list;
    string query = "call search_product('" + product + "')";
    if (mysql_query(mysql, query.c_str()))
    {
        string error = mysql_error(mysql);
        utils.log_app_action("db connection", "error", "-", error);
    }
    else
    {
        MYSQL_RES *result = mysql_store_result(mysql);

        if (!result)
        {
            string error = mysql_error(mysql);
            utils.log_app_action("db connection", "error", "-", error);
        }
        else
        {
            MYSQL_ROW row;
            int i;
            unsigned int num_fields = mysql_num_fields(result);
            while ((row = mysql_fetch_row(result)))
            {
                vector<string> prod;
                for (i = 0; i < num_fields; i++)
                    if (row[i] != nullptr)
                    {
                        prod.push_back(row[i]);
                    }
                    else
                    {
                        prod.push_back("");
                    }
                product_list.push_back(prod);
            }
            utils.log_app_action("db connection (get search products)", "success", "");
            mysql_free_result(result);
        }
    }
    return product_list;
}

/*
  int main()
   {

      DBConnection conn = DBConnection();
      DBConnection conn2 = DBConnection();
      vector<vector<string> > cart_list = conn2.get_my_cart("maggie@gmail.com");
      bool exito = conn.erase_products("maggie@gmail.com", cart_list);
      //bool exito = conn.erase_product("7");
      if(exito){
          printf("Exito");
      }
      else{
          printf("No sirvio");
      }
      return 1;
   }
*/