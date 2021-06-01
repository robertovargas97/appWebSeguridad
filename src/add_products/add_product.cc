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

int main(int argc, char const *argv[])
{

    Utils utils = Utils();

    char *footer = "/templates/footer.html";
    char *add_product = "/templates/add_product.html";
    char *header = "/templates/header.html";

    char *header_content = utils.read_file(header, header_content);
    char *add_product_content = utils.read_file(add_product, add_product_content);
    char *footer_content = utils.read_file(footer, footer_content);

    DBConnection conn = DBConnection();
    std::map<string, string> cookies = utils.get_cookies();
    bool is_signed = conn.verify_session(cookies["Email"], cookies["Password"]);

    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    utils.get_navbar(is_signed);

    if (is_signed)
    {

        printf(add_product_content);
    }
    else
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent mt-4 mb-4\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">Debes iniciar sesión para poder agregar un producto. <i class=\"fas fa-info-circle text-info\"></i></h1>";
        cout << "<hr>";
        cout << "<br>";
        cout << "<div class=\"mt-1 mb-3 col-12 text-center\">";
        cout << "<a href=\"/appWebSeguridad/login.cgi\" type=\"submit\" class=\"btn btn-info btn-login mt-4\" id=\"btn-spinner\" >Ir al login</a>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
    }

    printf(footer_content);

    free(header_content);
    free(footer_content);
    free(add_product_content);

    return 0;
}
