
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

    DBConnection conn = DBConnection();
    DBConnection conn_2 = DBConnection();
    std::map<string, string> cookies = utils.get_cookies();
    std::map<string, string> form_data = utils.get_post_data();
    bool is_signed = conn_2.verify_session(cookies["Email"], cookies["Password"]);
    bool new_product_result = conn.add_product(form_data["name"], form_data["price"], form_data["description"], form_data["category"]);
    utils.get_navbar(is_signed);

    if (new_product_result)
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">Tu producto fue agregado correctamente <i class=\"fas fa-check-square text-info\"></i></h1>";
        cout << "<hr>";
        cout << "</div>";
        cout << "</div>";
        utils.log_app_action("add product", "success", cookies["email"]);
    }
    else
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">Algo ha salido mal , por favor vuelve a intentarlo <i class=\"fas fa-info-circle text-info\"></i></h1>";
        cout << "<hr>";
        cout << "</div>";
        cout << "</div>";
        utils.log_app_action("add product", "error", cookies["email"], "The product could not be added");
    }

    printf(footer_content);
    free(header_content);
    free(footer_content);

    return new_product_result;
}
