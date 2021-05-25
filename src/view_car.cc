#include "../utils/utils.h"
#include "../utils/product.h"
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
    cout << "<div class=\"container register\">";
    cout << "<p align=\"right\"> <a href= \"\" class=\"btn btn-primary\" align=\"right\" id=\"/\">Vaciar carrito<span class=\"sr-only\"></span></a></p>";
    cout << "<div class=\"row\">"; 

    string correo="hellen@gmail.com";
    string categoria="" ;
    string nombre="";
    string precio = "";
    string descripcion = "";
    string producto="1";
    double monto_total = 0.0;
    DBConnection conn = DBConnection();
   vector<vector<string> > list_cart= conn.get_my_cart(correo);

    if ( list_cart.size() != 0){
    	for ( int i =0; i < list_cart.size() ; i++){
	    	categoria=list_cart[i][7];
            producto = list_cart[i][3];
	    	nombre=list_cart[i][4];
	    	precio = list_cart[i][5];
	    	descripcion =list_cart[i][6];
            monto_total += atof(precio.c_str()); //suma los precios 
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
                cout << "		    <button class=\"btn btn-secondary\">Quitar del carrito</button>"; // conn.delete_from_cart(correoUser,product); -> delete_from_car.cgi
                cout << "	  	</div>";
                cout << "	</div>";
                cout << "</div>";
        }
        cout << "<h1 class=\"display-4\">Monto total a pagar: "<< monto_total << "</h1>";
        cout << "<button class=\"btn btn-primary\">Realizar compra</button>"; // conn.empty_cart(correoUser,product); -> buy_car.cgi
        
	} else {
		cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        	cout << "<div class=\"container\">";
        	cout << "<h1 class=\"display-4\">El carrito está vacío<i class=\"fas fa-time-circle text-info\"></i></h1>";	
        	cout << "</div>";
        	cout << "</div>";
	}
    cout <<"</div>";
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
