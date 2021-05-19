#include "../utils/utils.h"
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
    "SERVER_SIGNATURE", "SERV ER_SOFTWARE", "CONTENT_LENGTH", "HTTP_COOKIE"};

int main(int argc, char const *argv[])
{

    Utils file_reader = Utils();
    char *header = "/templates/header.html";
    char *navbar = "/templates/navbar.html";
    char *list_products = "/templates/list_products.html";
    char *footer = "/templates/footer.html";
    char *header_content = file_reader.read_file(header, header_content);
    char *navbar_content = file_reader.read_file(navbar, navbar_content);
    char *list_products_content = file_reader.read_file(list_products, list_products_content);
    char *footer_content = file_reader.read_file(footer, footer_content);

    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    printf(navbar_content);
    printf(list_products_content);
    cout << "	<body>";
    cout << "<div class=\"container\">";
    //DBConnection conn = DBConnection();
    //map<string, string> form_data = utils.get_post_data();
    char *categoria="" ;
    char *nombre="";
    char *precio = "";
    char *descripcion = "";
    
    	categoria="bi bi-controller" ;
    	nombre="Grogu";
    	precio = "4500";
    	descripcion = "Cute grogu, The Mandalorian Star Wars";
    
	
	cout << "<div class=\"card mb-3\" style=\"max-width: 540px;\"> ";
	cout << "  <div class=\"row g-0\">";
	cout << "    <div class=\"col-md-4\">";
	cout << "	<i class=\""<< categoria << "\" style=\"font-size: 10rem; margin: 20px; align-self: center; height:160;\"></i>";
	cout << "    </div>";
	cout << "    <div class=\"col-md-8\">";
	cout << "	  <div class=\"card-body\">";
	cout << "	    <h5 class=\"card-title\">" << nombre << "</h5>";
	cout << "	    <h7 lass=\"card-sub title\" style=\"color:blue\"> Precio=₡"<< precio  <<"</h7>";
	cout << "	    <p class=\"card-text\"> "<< descripcion <<"</p>";
	cout << "		    <button class=\"btn btn-secondary\">Quitar del carrito</button>";
	cout << "	  </div>";
	cout << "	 </div>";
	cout << "   </div>";
	cout << " </div>";

    cout <<"</div>";
    cout << "</body>";
    cout << "</html>";
    printf(footer_content);

    free(header_content);
    free(navbar_content);
    free(list_products_content);
    free(footer_content);
    return 0;
}
