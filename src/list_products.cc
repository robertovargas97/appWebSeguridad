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
    char *view_carrito = "/appWebSeguridad/view_car.cgi";

    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    printf(navbar_content);
    

    cout << "<div class=\"container register\">";
    cout << "<br/>";
    cout << "<p align=\"right\"> <a href= " << view_carrito << " class=\"btn btn-primary\" align=\"right\" id=\"/\">Ver carrito<span class=\"sr-only\"></span></a></p>";
    cout << "<div class=\"row\">";
    string correo = "hellen@gmail.com";
    string categoria = "";
    string nombre = "";
    string precio = "";
    string descripcion = "";
    bool esta_en_carrito = false;
    string codigo_producto = "5";

    vector<vector<string>> lista_productos;

    DBConnection conn = DBConnection();
    lista_productos = conn.get_all_products();
    // 	    vector<string> productos;
           
    //         productos.push_back("1");//codigo_producto 
    //         productos.push_back("Gro"); //nombre 
    //         productos.push_back("4000"); //precio 
    //         productos.push_back("peluche"); //descripcion
    // 	    productos.push_back("bi bi-emoji-heart-eyes");// categoria
    //    lista_productos.push_back(productos);  
    //    vector<string> productos2;
 
    //         productos2.push_back("2");//codigo_producto 
    //         productos2.push_back("play"); //nombre 
    //         productos2.push_back("400000"); //precio 
    //         productos2.push_back("video game"); //descripcion
    // 	    productos2.push_back("bi bi-emoji-heart-eyes");// categoria
    //     lista_productos.push_back(productos2);
    //         cout << "<br/>";
    // 		cout << "<div class=\"form-group pull-right\">";
	// 	cout << "  <input type=\"text\" class=\"search form-control\" placeholder=\"Buscar\">";
	// 	cout << "</div>";
	// 	cout << "<span class=\"counter pull-right\"></span>";
	// 	cout << "<table class=\"table table-hover table-bordered results\">";
	// 	cout << "   <thead>";
	// 	cout << "   <tr>";
	// 	cout << "    <th>#</th>"; 
	// 	cout << "    <th class=\"col-md-3 col-xs-3\">          </th>";
	// 	cout << "    <th class=\"col-md-5 col-xs-5\">Nombre</th>";
	// 	cout << "    <th class=\"col-md-4 col-xs-4\">Precio</th>";
	// 	cout << "    <th class=\"col-md-4 col-xs-4\">Descripción</th>";
		 
	// 	cout << "    <th class=\"col-md-3 col-xs-3\">Añadir</th>";
	// 	cout << "  </tr>";
	// 	cout << "</thead> ";
	// 	cout << " <tbody>";
	if (lista_productos.size() != 0)
    {
		
		  
		  
		  //int num=0;
        for (int i = 0; i < lista_productos.size(); i++)
        {
            categoria = lista_productos[i][4];
            codigo_producto = lista_productos[i][0];
            nombre = lista_productos[i][1];
            precio = lista_productos[i][2];
            descripcion = lista_productos[i][3];
	    //  num=i+1;
		
		//       cout << "<tr>";
		//       cout << "<th scope=\"row\">"<<num<<"</th>";
		//       cout << "<td class=\"center aligned\"> ";
		//       cout << "<i class=\"fas fa-gamepad\"></i>";
		//       cout <<" </td> ";
		//       cout << "<td>"<<nombre<<"</td>";
		//       cout << "<td>"<< precio <<"</td>";
		//       cout << "<td>"<<descripcion<<"</td>";
		//      cout << "<td>";
		//      en_carrito = conn.exist_in_cart(correo, codigo_producto);
		//      if (en_carrito == false){ // existe
		// 		cout << "<button class=\"btn btn-secondary\" disabled=\"true\" > + </button>";
		// 	}else{//no existe
		// 		cout << "<button class=\"btn btn-primary\" onclick=\"add_to_cart_ajax('" << codigo_producto << "','" << correo << "')\"> + </button>";
		// 	    }
		//    cout << "</td>";
		//    cout << "</tr>";

	
            cout << "<div class=\"col-lg-3\">";
            cout << "	<div class=\"card\" style=\"width: 18rem;\">";
            cout << "	  <i class=\"" << categoria << "\" style=\"font-size: 10rem; margin: 20px; align-self: center; height:160;\"></i>";
            cout << " <hr/>";
            cout << "	  	<div class=\"card-body\" style=\" width: 286; height: 166\">";
            cout << "		    <h5 class=\"card-title\">" << nombre << "</h5>";
            cout << "		    <h7 lass=\"card-sub title\" style=\"color:blue\"> Precio=₡" << precio << "</h7>";
            cout << "		    <p class=\"card-text\"> " << descripcion << "</p>";
            cout << "		</div>";
            cout << "		<div class = \"card-footer\"style=\"width: 18rem;\">";
            esta_en_carrito = conn.exist_in_cart("hellen@gmail.com", "7");
            cout<<esta_en_carrito<<endl;
            if (esta_en_carrito)
            { // existe
                cout << "		    <button class=\"btn btn-secondary\" disabled=\"true\" > Ya en carrito</button>";
            }
            else
            {
                //no existe
                cout << "<button class=\"btn btn-primary\" onclick=\"add_to_cart_ajax('" << codigo_producto << "','" << correo << "')\"> Añadir al carrito</button>";
            }
            cout << "	  	</div>";
            cout << "	</div>";
            cout << "</div>";
        }
        
    }	  
    else
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        cout << "	<div class=\"container\">";
        cout << "		<h1 class=\"display-4\">No hay productos disponibles<i class=\"fas fa-time-circle text-info\"></i></h1>";
        cout << "	</div>";
        cout << "</div>";
        //cout << "  <tr class=\"warning no-result\">";
	// cout << "    <td colspan=\"4\"><i class=\"fa fa-warning\"></i> No resulto</td>";
	// cout << "  </tr>";
        
    }
	//cout << "</tbody>";
	//cout << "</table>";
    cout << "</div>";
    cout << "</div>";
 
    printf(list_products_content);
    printf(footer_content);

    free(header_content);
    free(navbar_content);
    free(list_products_content);
    free(footer_content);
    return 0;
}
