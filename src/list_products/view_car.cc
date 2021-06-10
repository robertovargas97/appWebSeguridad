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
    // char *transaction_modal = "/templates/transaction_modal.html";
    // char *transaction_modal_content = utils.read_file(transaction_modal, transaction_modal_content);
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
            cout << "		    <h5 class=\"card-sub title\"> Precio: ₡" << precio << "</h5>";
            cout << "		    <p class=\"card-text\"> " << descripcion << "</p>";
            cout << "		</div>";
            cout << "		<div class = \"card-footer\"style=\"width: 18rem;\">";
            cout << "<button class=\"btn btn-info\" onclick=\"delete_from_cart_ajax('" << codigo_producto << "','" << correo << "')\"><i class='bi bi-cart-dash-fill' style='font-size: 1rem;'></i> Remover del carrito </button>";
            cout << "	  	</div>";
            cout << "	</div>";
            cout << "</div>";
        }
        cout << "</div>";
        cout << " <br/>";
        cout << " <hr/>";
        cout << "<h4 class=\"ml-4\">Monto total a pagar: ₡" << monto_total << "</h4>";
        cout << " <br/>";
        cout << "<button type='button' class='btn btn-info ml-4' data-toggle='modal' data-target='#exampleModal'>Realizar compra <i class='bi bi-cart-check-fill'></i></button>";

        cout << "    <div class='modal fade' id='exampleModal' tabindex='-1' aria-labelledby='exampleModalLabel' aria-hidden='true'>";
        cout << "<div class='modal-dialog'> ";
        cout << "<div class='modal-content'>";
        cout << "  <div class='modal-header'>";
        cout << "    <h5 class='modal-title' id='exampleModalLabel'>Agregue información de pago</h5>";
        cout << "    <button type='button' class='close' data-dismiss='modal' aria-label='Close'>";
        cout << "      <span aria-hidden='true'>&times;</span>";
        cout << "    </button>";
        cout << "  </div>";
        cout << "  <div class='modal-body'>";
        cout << "    <form method='POST' action='/buy_car.cgi' autocomplete='off'>";
        cout << "        <div class='form-group'>";
        cout << "            <input type='hidden' class='form-control' id='price' name='price' value='" << monto_total << "'>";
        cout << "          </div>";
        cout << "      <div class='form-group'>";
        cout << "        <label for='card_number' class='col-form-label'>Número de tarjeta</label>";
        cout << "        <input type='number' class='form-control' id='card_number' name='card_number' min='1000000000000' max='99999999999999999' minlength='13' maxlength='17' placeholder='xxxxxxxxxxxxxxx' required autocomplete='off' >";
        cout << "      </div>";
        cout << "      <div class='form-group'>";
        cout << "        <label for='card_expiry' class='col-form-label'>Fecha de vencimiento de la tarjeta</label>";
        cout << "        <input pattern='(((0[123456789]|10|11|12)\/(([0-9][0-9]))))' type='text' class='form-control' id='card_expiry' name='card_expiry' maxlength='5' placeholder='mm/yy' required>";
        cout << "      </div>";
        cout << "      <div class='form-group'>";
        cout << "        <label for='card_cvv' class='col-form-label'>Código de seguridad de la tarjeta</label>";
        cout << "        <input type='password' class='form-control' id='card_cvv' name='card_cvv' maxlength='4' placeholder='xxx' required autocomplete='off' >";
        cout << "      </div>";

        cout << "      <div class='form-group'>";
        cout << "        <label for='card_owner' class='col-form-label'>Dueño de la tarjeta</label>";
        cout << "        <input type='text' class='form-control' id='card_owner' name='card_owner' maxlength='30' placeholder='Pepe Perez' required>";
        cout << "      </div>";

        cout << "      <div class='form-group'>";
        cout << "        <label for='card_type'>Eije un tipo de tarjeta</label>";
        cout << "        <select class='form-control' id='card_type' name='card_type' required>";
        cout << "          <option value='Visa'>Visa</option>";
        cout << "          <option value='Mastercard'>Mastercard</option>";
        cout << "          <option value='AmericanExpress'>American Express</option>";
        cout << "        </select>";
        cout << "      </div>";
        cout << "  </div>";
        cout << "  <div class='modal-footer'>";
        cout << "    <button type='button' class='btn btn-secondary' data-dismiss='modal'>Cancelar <i class='bi bi-x-square-fill'></i></button>";
        cout << "    <button type='submit' class='btn btn-info'>Comprar <i class='bi bi-credit-card-fill' style='font-size: 1rem;'></i></button>";
        cout << "  </div>";
        cout << "</form>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
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
    // printf(transaction_modal_content);
    printf(footer_content);

    free(header_content);
    free(list_products_content);
    // free(transaction_modal_content);
    free(footer_content);
    return 0;
}