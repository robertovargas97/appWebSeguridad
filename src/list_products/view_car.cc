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
    printf(list_products_content);

    string correo = cookies["Email"];
    string categoria = "";
    string nombre = "";
    string precio = "";
    string descripcion = "";
    string codigo_producto = "1";
    long long int monto_total = 0;
    DBConnection conn = DBConnection();
    vector<vector<string>> list_cart = conn.get_my_cart(correo);

    cout << "<div class=\"container register mt-4\">";
    //cout << "<p align=\"right\"> <a href= \"\" class=\"btn btn-primary\" align=\"right\" id=\"/\">Vaciar carrito<span class=\"sr-only\"></span></a></p>";

    if (list_cart.size() != 0)
    {
        cout << "<div class=\"row\">";
        for (int i = 0; i < list_cart.size(); i++)
        {
            categoria = list_cart[i][7];
            codigo_producto = list_cart[i][3];
            nombre = list_cart[i][4];
            precio = list_cart[i][5];
            descripcion = list_cart[i][6];
            monto_total += atoi(precio.c_str()); //suma los precios
            cout << "<div class=\"col-lg-3 mt-3 ml-3\">";
            cout << "	<div class=\"card\" style=\"width: 18rem;\">";
            cout << "	  <i class=\"" << categoria << "\" style=\"font-size: 10rem; margin: 20px; align-self: center; height:160;\"></i>";
            cout << " <hr/>";
            cout << "	  	<div class=\"card-body\" style=\" width: 286; height: 166\">";
            cout << "		    <h5 class=\"card-title\">" << nombre << "</h5>";
            cout << "		    <h7 lass=\"card-sub title\" style=\"color:blue\"> Precio: ₡" << precio << "</h7>";
            cout << "		    <p class=\"card-text\"> " << descripcion << "</p>";
            cout << "		</div>";
            cout << "		<div class = \"card-footer\"style=\"width: 18rem;\">";
            cout << "<a href=\"\"> <button class=\"btn btn-info\" onclick=\"delete_from_cart_ajax('" << codigo_producto << "','" << correo << "')\"> Remover del carrito</button></a>";
            cout << "	  	</div>";
            cout << "	</div>";
            cout << "</div>";
        }
        cout << "</div>";
        cout << " <br/>";
        cout << "<h1 class=\"display-4\">Monto total a pagar: " << monto_total << "</h1>";
        cout << " <br/>";
        cout << "<button class=\"btn btn-info\" onclick=\"buy_cart_ajax('"<<codigo_producto <<"')\">Realizar compra</button> "; 
    }
    else
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">El carrito está vacío<i class=\"fas fa-time-circle text-info\"></i></h1>";
        cout << "</div>";
        cout << "</div>";
    }
    cout << "</div>";
    printf(footer_content);

    free(header_content);
    free(list_products_content);
    free(footer_content);
    return 0;
}