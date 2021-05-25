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

int main(int argc, const char *argv[], const char *env[])
{

    Utils utils = Utils();
    char *header = "/templates/header.html";
    char *navbar = "/templates/navbar.html";
    char *footer = "/templates/footer.html";
    char *header_content = utils.read_file(header, header_content);
    char *navbar_content = utils.read_file(navbar, navbar_content);
    char *footer_content = utils.read_file(footer, footer_content);
    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    printf(navbar_content);

    DBConnection conn = DBConnection();
    map<string, string> form_data = utils.get_post_data();
    
    //Generate salt here
    std::string u_salt = utils.create_salt();

    //Encrypt password
    std::string u_secret = utils.create_hash_sha2( form_data["password"], u_salt );

    bool new_comment_result = conn.add_user( form_data["name"], form_data["last_name"], form_data["email"], u_secret, form_data["phone_number"], form_data["address"], u_salt );

    if (new_comment_result)
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">Tu usuario ha sido registrado. <i class=\"fas fa-check-square text-info\"></i></h1>";
        cout << "<hr>";
        cout << "<a class=\"btn btn-info btn-login mt-4\" href=\"/login.cgi\">Ir a Login</a>";
        cout << "</div>";
        cout << "</div>";
    }
    else
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">Algo ha salido mal , por favor vuelve a intentarlo <i class=\"fas fa-time-circle text-info\"></i></h1>";
        cout << "<hr>";
        cout << "</div>";
        cout << "</div>";
    }

    printf(footer_content);
    free(header_content);
    free(navbar_content);
    free(footer_content);

    return new_comment_result;
}
