#include "../utils/utils.h"
#include "../utils/db_connection.h"
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
    char *header = "/templates/header.html";
    char *footer = "/templates/footer.html";
    char *header_content = utils.read_file(header, header_content);

    char *footer_content = utils.read_file(footer, footer_content);

    cout << "Set-Cookie:Email=null;\r\n";
    cout << "Set-Cookie:Password=null;\r\n";
    cout << "Set-Cookie:Domain=null;\r\n";
    cout << "Content-type:text/html\r\n\r\n";

    DBConnection conn = DBConnection();
    std::map<string, string> cookies = utils.get_cookies();
    bool is_signed = conn.verify_session(cookies["Email"], cookies["Password"]);
    
    printf(header_content);
    utils.get_navbar(is_signed);

    cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent mt-4 mb-4\">";
    cout << "<div class=\"container\">";
    cout << "<h1 class=\"display-4\">Sesión terminada correctamente.<i class=\"fas fa-check-square text-info\"></i></h1>";
    cout << "<hr>";
    cout << "<br>";
    cout << "<div class=\"mt-1 mb-3 col-12 text-center\">";
    cout << "<a href=\"/appWebSeguridad/home.cgi\" type=\"submit\" class=\"btn btn-info btn-login mt-4\" id=\"btn-spinner\" >Ir al inicio</a>";
    cout << "</div>";
    cout << "</div>";
    cout << "</div>";

    cout << footer_content;
    free(header_content);
    free(footer_content);
    return 0;
}