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

    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    DBConnection conn_2 = DBConnection();
    std::map<string, string> cookies = utils.get_cookies();
    bool is_signed = conn_2.verify_session(cookies["Email"], cookies["Password"]);
    utils.get_navbar(is_signed);

    cout << "<div class=\"container register mt-4\">";
    cout << "<br/>";

    cout << "<div class=\"row\">";
    string correo = cookies["Email"];
    string categoria = "";
    string nombre = "";
    string precio = "";
    string descripcion = "";
    string esta_en_carrito = "false";
    string codigo_producto = "5";

    vector<vector<string>> my_cart;

    DBConnection conn = DBConnection();
    DBConnection conn_3 = DBConnection();

    vector<vector<string>> lista_productos = conn.get_all_products();
    

    if (lista_productos.size() != 0)
    {
        vector<vector<string>> my_cart;
        if(is_signed){
            my_cart = conn_3.get_my_cart(correo);
        }
        for (int i = 0; i < lista_productos.size(); i++)
        {
            categoria = lista_productos[i][4];
            codigo_producto = lista_productos[i][0];
            nombre = lista_productos[i][1];
            precio = lista_productos[i][2];
            descripcion = lista_productos[i][3];

            cout << "<div class=\"col-lg-3 mt-3 ml-3\">";
            cout << "	<div class=\"card\" style=\"width: 18rem;\">";
            cout << "	  <i class=\"" << categoria << "\" style=\"font-size: 10rem; margin: 20px; align-self: center; height:160;\"></i>";
            cout << " <hr/>";
            cout << "	  	<div class=\"card-body\" style=\" width: 286; height: 166\">";
            cout << "		    <h5 class=\"card-title\">" << nombre << "</h5>";
            cout << "		    <h7 lass=\"card-sub title\" style=\"bold\"> Precio: ₡" << precio << "</h7>";
            cout << "		    <p class=\"card-text\"> " << descripcion << "</p>";
            cout << "		</div>";
            cout << "		<div class = \"card-footer\"style=\"width: 18rem;\">";

            if (is_signed)
            {
                //esta_en_carrito = conn_3.exist_in_cart(cookies["Email"], codigo_producto);
                esta_en_carrito = "false";
                for(int j =0; j < my_cart.size(); j ++){
                        if(my_cart[j][3]==codigo_producto){
                                esta_en_carrito = "true";
                        }

                }
                if (esta_en_carrito == "true")
                { // existe
                    cout << "<button class=\"btn btn-secondary\" disabled=\"true\" > Ya en carrito</button>";
                }
                else
                {
                    //no existe
                    cout << "<button id='prod_" << codigo_producto << "' class=\"btn btn-info\" onclick=\"add_to_cart_ajax('" << codigo_producto << "','" << correo << "')\"> Añadir al carrito</button>";
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