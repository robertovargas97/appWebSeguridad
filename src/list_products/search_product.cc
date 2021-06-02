#include "../../utils/utils.h"
#include "../../utils/product.h"
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
    "SERVER_SIGNATURE", "SERV ER_SOFTWARE", "CONTENT_LENGTH", "HTTP_COOKIE"};

int main(int argc, char const *argv[])
{

    Utils utils = Utils();
    char *header = "/templates/header.html";
    char *list_products = "/templates/list_products.html";
    char *footer = "/templates/footer.html";
    char *header_content = utils.read_file(header, header_content);
    char *list_products_content = utils.read_file(list_products, list_products_content);
    char *footer_content = utils.read_file(footer, footer_content);
    char *view_carrito = "/appWebSeguridad/view_car.cgi";

    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    DBConnection conn_2 = DBConnection();
    std::map<string, string> cookies = utils.get_cookies();
    bool is_signed = conn_2.verify_session(cookies["Email"], cookies["Password"]);
    utils.get_navbar(is_signed);

    cout << "<div class=\"container register\">";
    cout << "<br/>";
    if (is_signed)
    {
        cout << "<p align=\"right\"> <a href= " << view_carrito << " class=\"btn btn-primary\" align=\"right\" id=\"/\">Ver carrito<span class=\"sr-only\"></span></a></p>";
    }

    cout << "<form method=\"post\" action=\"/appWebSeguridad/search_product.cgi\" id=\"search_product_form\">";
    cout << "<div>";
    cout << " <div class=\"input-group .center\">";
    cout << "<div class=\"form-group\">";
    cout << "<input type=\"text\" id=\"product_to_search\" name=\"product_to_search\" class=\"form-control\" placeholder=\"Buscar\"/>";
    cout << "</div>";
    cout << "<button type=\"submit\" class=\"btn btn-primary\">";
    cout << "<i class=\"fas fa-search\"></i>";
    cout << "</button>";
    cout << "</div>";
    cout << "</br>";
    cout << "</div>";
    cout << "</form>";

    cout << "<div class=\"row\">";
    string correo = cookies["Email"];
    string categoria = "";
    string nombre = "";
    string precio = "";
    string descripcion = "";
    string esta_en_carrito = "false";
    string codigo_producto = "5";

    vector<vector<string>> lista_productos;

    DBConnection conn = DBConnection();
    DBConnection conn_3 = DBConnection();
    std::map<string, string> form_data = utils.get_post_data();
    //cout<<"form_data["search_product_form"]";
    lista_productos = conn.search_product(form_data["product_to_search"]);
    //lista_productos = conn.search_product("agua");

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

            cout << "<div class=\"col-lg-3\">";
            cout << "	<div class=\"card\" style=\"width: 18rem;\">";
            cout << "	  <i class=\"" << categoria << "\" style=\"font-size: 10rem; margin: 20px; align-self: center; height:160;\"></i>";
            cout << " <hr/>";
            cout << "	  	<div class=\"card-body\" style=\" width: 286; height: 166\">";
            cout << "		    <h5 class=\"card-title\">" << nombre << "</h5>";
            cout << "		    <h7 lass=\"card-sub title\" style=\"color:blue\"> Precio: ₡" << precio << "</h7>";
            cout << "		    <p class=\"card-text\"> " << descripcion << "</p>";
            cout << "		</div>";
            cout << "		<div class = \"card-footer\"style=\"width: 18rem;\">";
            if (is_signed)
            {
                esta_en_carrito = conn_3.exist_in_cart(cookies["Email"], codigo_producto);
                cout << esta_en_carrito << endl;
                if (esta_en_carrito == "true")
                { // existe
                    cout << "<button class=\"btn btn-secondary\" disabled=\"true\" > Ya en carrito</button>";
                }
                else
                {
                    //no existe
                    cout << "<button class=\"btn btn-primary\" onclick=\"add_to_cart_ajax('" << codigo_producto << "','" << correo << "')\"> Añadir al carrito</button>";
                }
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
    }

    cout << "</div>";
    cout << "</div>";

    printf(list_products_content);
    printf(footer_content);

    free(header_content);
    free(list_products_content);
    free(footer_content);
    return 0;
}