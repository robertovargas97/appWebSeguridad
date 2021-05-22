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
    char *navbar = "/templates/navbar.html";
    char *footer = "/templates/footer.html";
    char *header_content = utils.read_file(header, header_content);
    char *navbar_content = utils.read_file(navbar, navbar_content);
    char *footer_content = utils.read_file(footer, footer_content);

    cout << "Content-type:text/html\r\n\r\n";
    cout << header_content;
    DBConnection conn_1 = DBConnection();
    DBConnection conn_2 = DBConnection();
    map<string, string> form_data = utils.get_post_data();
    string user_salt = conn_1.get_user_salt(form_data["email"]);
    bool is_valid_login = conn_2.verify_login(form_data["email"], form_data["password"], user_salt);

    if (is_valid_login)
    {
        // string new_navbar = utils.replace_pattern(navbar_content, "REMOVE-->", "");
        // new_navbar = utils.replace_pattern(new_navbar, "<!--REMOVE", "");
        // cout << new_navbar << endl;verify_login
        // cout << "<script>" << endl;
        // cout << "alert(\" Login Successful \");" << endl;
        // // cout << "window.location.replace('http://" << serverIP << "/cgi-bin/Wall/Wall?id=" << id << "');" << endl;
        // cout << "</script>" << endl;
        cout << navbar_content;
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent mt-4 mb-4\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">Has iniciado sesión correctamente <i class=\"fas fa-check-square text-info\"></i></h1>";
        cout << "<hr>";
        cout << "<br>";
        cout << "<div class=\"mt-1 mb-3 col-12 text-center\">";
        cout << "<a href=\"/appWebSeguridad/home.cgi\" type=\"submit\" class=\"btn btn-info btn-login mt-4\" id=\"btn-spinner\" >Ir al inicio</a>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
    }
    else
    {
        cout << navbar_content;
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent mt-4 mb-4\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">Usuario y/o contraseña incorrectos. Intentalo de nuevo <i class=\"fas fa-info-circle text-info\"></i></h1>";
        cout << "<hr>";
        cout << "<br>";
        cout << "<div class=\"mt-1 mb-3 col-12 text-center\">";
        cout << "<a href=\"/appWebSeguridad/login.cgi\" type=\"submit\" class=\"btn btn-info btn-login mt-4\" id=\"btn-spinner\" >Volver al login</a>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
    }

    cout << footer_content;
    free(header_content);
    free(navbar_content);
    free(footer_content);
    return 0;
}