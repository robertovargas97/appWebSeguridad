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
    "SERVER_SIGNATURE", "SERV ER_SOFTWARE", "CONTENT_LENGTH", "HTTP_COOKIE"};

int main(int argc, char const *argv[])
{

    Utils file_reader = Utils();
    char *header = "/templates/header.html";
    char *list_products = "/templates/list_products.html";
    char *footer = "/templates/footer.html";
    char *header_content = file_reader.read_file(header, header_content);
    char *list_products_content = file_reader.read_file(list_products, list_products_content);
    char *footer_content = file_reader.read_file(footer, footer_content);
    char *view_carrito="/appWebSeguridad/view_car.cgi";
    
    DBConnection conn = DBConnection();
    std::map<string, string> cookies = file_reader.get_cookies();
    bool is_signed = conn.verify_session(cookies["Email"], cookies["Password"]);
    
    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    file_reader.get_navbar(is_signed);
    printf(list_products_content);
    cout << "	<body>";
    cout << "<div class=\"container register\">";
    cout << "<p align=\"right\"> <a href= "<< view_carrito <<" class=\"btn btn-primary\" align=\"right\" id=\"/\">Ver carrito<span class=\"sr-only\"></span></a></p>";
    cout << "<div class=\"row\">";
    
    
    char *categoria="" ;
    char *nombre="";
    char *precio = "";
    char *descripcion = "";
    bool en_carrito = false;
    bool lista_productos = false;
    //DBConnection conn = DBConnection();
    lista_productos = true;//lista_productos = conn.get_allProducts(correoUser,product);
    if (lista_productos == true){
    
    	//for ( int i =0; i < carrito.size() ; i++){
	    	categoria="bi bi-controller" ;
	    	nombre="Grogu";
	    	precio = "4000";
	    	descripcion = "Cute grogu, The Mandalorian Star Wars";
	    	
		cout << "<div class=\"col-lg-3\">";
		cout << "	<div class=\"card\" style=\"width: 18rem;\">";
		cout << "	  <i class=\""<< categoria << "\" style=\"font-size: 10rem; margin: 20px; align-self: center; height:160;\"></i>";
		cout << " <hr/>";
		cout << "	  	<div class=\"card-body\" style=\" width: 286; height: 166\">";
		cout << "		    <h5 class=\"card-title\">" << nombre << "</h5>";
		cout << "		    <h7 lass=\"card-sub title\" style=\"color:blue\"> Precio=₡"<< precio  <<"</h7>";
		cout << "		    <p class=\"card-text\"> "<< descripcion <<"</p>";
		cout << "		</div>";
		cout << "		<div class = \"card-footer\"style=\"width: 18rem;\">";
		en_carrito = false;// = conn.en_carrito(correoUser,product);
		if ( en_carrito == true){ // to do -> revisar 
		cout << "		    <button class=\"btn btn-secondary\" disabled=\"true\" > Ya en carrito</button>";
		} else {
		cout << "		    <button class=\"btn btn-primary\">Añadir al carrito</button>";
		}
		cout << "	  	</div>";
		cout << "	</div>";
		cout << "</div>";
	// }
    }else{
    		cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        	cout << "	<div class=\"container\">";
        	cout << "		<h1 class=\"display-4\">No hay productos disponibles<i class=\"fas fa-time-circle text-info\"></i></h1>";	
        	cout << "	</div>";
        	cout << "</div>";
    }
    cout << "</div>";
    cout <<"</div>";
    cout << "</body>";
    cout << "</html>";
    printf(footer_content);

    free(header_content);
    free(list_products_content);
    free(footer_content);
    return 0;
}
