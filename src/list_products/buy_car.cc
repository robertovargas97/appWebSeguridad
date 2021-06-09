#include "../../utils/utils.h"
#include "../../utils/db_connection.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const string ENV[26] = {
    "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",
    "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",
    "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",
    "HTTP_HOST", "HTTP_USER_AGENT", "PATH",
    "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",
    "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
    "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",
    "SERVER_NAME", "SERVER_PORT", "SERVER_PROTOCOL",
    "SERVER_SIGNATURE", "SERVER_SOFTWARE", "CONTENT_LENGTH", "HTTP_COOKIE"};

int main(int argc, const char *argv[], const char *env[])
{

    Utils utils = Utils();
    char *header = "/templates/header.html";

    char *footer = "/templates/footer.html";
    char *header_content = utils.read_file(header, header_content);

    char *footer_content = utils.read_file(footer, footer_content);
    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    DBConnection conn_2 = DBConnection();
    std::map<string, string> cookies = utils.get_cookies();
    bool is_signed = conn_2.verify_session(cookies["Email"], cookies["Password"]);
    utils.get_navbar(is_signed);

    DBConnection conn = DBConnection();
    std::map<string, string> form_data = utils.get_post_data();
    bool buy_car_result = false;//conn.erase_products(form_data["correo"]);

    
    DBConnection conn4 = DBConnection();
    vector<vector<string> > cart_list = conn4.get_my_cart(cookies["Email"]);

    DBConnection conn3 = DBConnection();
    buy_car_result = conn3.erase_products(cookies["Email"], cart_list);


    if(is_signed){
            if (buy_car_result)
            {
                cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
                cout << "<div class=\"container\">";
                cout << "<h1 class=\"display-4\">Se realizó la compra correctamente <i class=\"fas fa-check-square text-info\"></i></h1>";
                cout << "<hr>";
                cout << "</div>";
                cout << "</div>";
                utils.log_app_action("buy products", "success", cookies["email"]);
            }
            else
            {
                cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
                cout << "<div class=\"container\">";
                cout << "<h1 class=\"display-4\">Algo ha salido mal , por favor vuelve a intentarlo <i class=\"fas fa-time-circle text-info\"></i></h1>";
                cout << "<hr>";
                cout << "</div>";
                cout << "</div>";
                utils.log_app_action("buy products", "error", cookies["email"], "There was a problem while processing the order");
            }
    } else{
                cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
                cout << "<div class=\"container\">";
                cout << "<h1 class=\"display-4\">No hay sesión iniciada <i class=\"fas fa-time-circle text-info\"></i></h1>";
                cout << "<hr>";
                cout << "</div>";
                cout << "</div>";
    }
    printf(footer_content);
    free(header_content);
    free(footer_content);
   /* Utils utils = Utils();
    char *header = "/templates/header.html";
    char *header_content = utils.read_file(header, header_content);
    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    DBConnection conn = DBConnection();
    std::map<string, string> form_data = utils.get_post_data();
    bool buy_car_result = conn.erase_products(form_data["correo"]);
    free(header_content);*/

    return 1;
}