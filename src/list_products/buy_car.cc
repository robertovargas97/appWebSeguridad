#include "../../utils/utils.h"
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
    "SERVER_SIGNATURE", "SERVER_SOFTWARE", "CONTENT_LENGTH", "HTTP_COOKIE"};

int main(int argc, const char *argv[], const char *env[])
{
    int length = 10;
    string receipt = "";
    string products_list = "";
    string characters = "1234567890";
    srand(time(NULL));

    for (int x = 0; x < length; x++) // Genera length caracteres diferentes
    {
        AutoSeededRandomPool random;
        long random_number = rand() % (characters.size());
        receipt += characters[random_number];
    }

    Utils utils = Utils();
    char *header = "/templates/header.html";

    char *footer = "/templates/footer.html";
    char *header_content = utils.read_file(header, header_content);

    char *footer_content = utils.read_file(footer, footer_content);
    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    DBConnection conn_2 = DBConnection();
    std::map<string, string> cookies = utils.get_cookies();
    bool is_signed = conn_2.verify_session(cookies["Email"], cookies["Password"]);
    utils.get_navbar(is_signed);

    DBConnection conn = DBConnection();
    std::map<string, string> form_data = utils.get_post_data();
    bool is_valid_card = utils.verify_card_no_type(form_data["card_number"], form_data["card_type"]);
    bool buy_car_result = false;
    cout << is_valid_card;
    if (is_signed)
    {
        // Here we should send the payment to some processor to verify the purchase
        if (is_valid_card) //  && form_data["card_expiry"] == "01/22" && form_data["card_cvv"] == "123"
        {
            DBConnection conn4 = DBConnection();
            vector<vector<string>> cart_list = conn4.get_my_cart(cookies["Email"]);

            cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent mb-0 pb-1\">";
            cout << "<div class=\"container\">";
            cout << "<h3 class=\"display-4\">Se realizó la compra correctamente <i class='bi bi-cart-check-fill text-info'></i></h3>";
            cout << "<hr>";
            cout << "</div>";
            cout << "</div>";
            cout << " <div class = 'comments animated fadeIn fast mt-0'>";

            cout << " <div class='center-add-product bg-transparent'>";
            cout << " <form>";
            cout << "   <div class='row'>";
            cout << "     <div class='form-group col-sm-12'>";
            cout << "       <br>";
            cout << "       <h3>Recibo (Toma un screenshot de tu recibo de compra) <i class='fas fa-handshake'></i></h3>";
            cout << "      <hr class='new4 mb-1'>";
            cout << "     </div>";

            cout << "    <div class='col-12'>";
            cout << "       <label class='login-label' for='email'>Número de recibo</label>";
            cout << "       <div class='input-group mb-2'>";
            cout << "         <div class='input-group-prepend'>";
            cout << "           <div class='input-group-text'><i class='bi bi-award-fill'></i></div>";
            cout << "         </div>";
            cout << "         <input type='email' class='form-control' id='id_email' name='email' required placeholder='example@mail.com' required maxlength='50' value = '" << receipt << "' disabled > ";
            cout << "       </div>";
            cout << "     </div>";

            cout << "    <div class='col-12'>";
            cout << "       <label class='login-label' for='email'>Fecha de Compra</label>";
            cout << "       <div class='input-group mb-2'>";
            cout << "         <div class='input-group-prepend'>";
            cout << "           <div class='input-group-text'> <i class='bi bi-calendar-check-fill'></i> </div>";
            cout << "         </div>";
            cout << "         <input type='email' class='form-control' id='id_email' name='email' required placeholder='example@mail.com' required maxlength='50' value = '" << utils.get_date() << "' disabled > ";
            cout << "       </div>";
            cout << "     </div>";

            cout << "       <div class='col-12'>";
            cout << "        <label class='login-label' for='email'>Nombre del comprador</label>";
            cout << "        <div class='input-group mb-2'>";
            cout << "          <div class='input-group-prepend'>";
            cout << "            <div class='input-group-text'><i class='fas fa-user'></i></div>";
            cout << "          </div>";
            cout << "          <input type='email' class='form-control' id='id_email' name='email' required placeholder='example@mail.com' required maxlength='50' value='" << form_data["card_owner"] << "' disabled>";
            cout << "        </div>";
            cout << "      </div>";

            cout << "         <div class='col-12'>";
            cout << "           <label class='login-label' for='email'>Correo del comprador</label>";
            cout << "           <div class='input-group mb-2'>";
            cout << "             <div class='input-group-prepend'>";
            cout << "               <div class='input-group-text'><i class='fas fa-at'></i></div>";
            cout << "             </div>";
            cout << "             <input type='email' class='form-control' id='id_email' name='email' required placeholder='example@mail.com' required maxlength='50' value='" << cookies["Email"] << "' disabled>";
            cout << "           </div>";
            cout << "         </div>";

            cout << "         <div class='col-12'>";
            cout << "           <label class='login-label' for='email'>Tarjeta utilizada</label>";
            cout << "           <div class='input-group mb-2'>";
            cout << "             <div class='input-group-prepend'>";
            cout << "               <div class='input-group-text'><i class='bi bi-credit-card-2-back-fill'></i></div>";
            cout << "             </div>";
            cout << "             <input type='email' class='form-control' id='id_email' name='email' required placeholder='example@mail.com' equired maxlength='50' value='" << utils.mask_card_number(form_data["card_number"]) << "' disabled>";
            cout << "           </div>";
            cout << "         </div>";
            cout << "         <br>";
            cout << "         <br>";
            cout << "         <label class='ml-3 mt-3'>Lista de productos</label>";
            cout << "         <hr>";

            for (int i = 0; i < cart_list.size(); i++)
            {
                cout << "         <div class='col-12'>";
                cout << "           <div class='input-group mb-2'>";
                cout << "             <div class='input-group-prepend'>";
                cout << "               <div class='input-group-text'><i class='bi bi-arrow-right-short'></i></div>";
                cout << "             </div>";
                cout << "             <input type='email' class='form-control' id='id_email' name='email' required placeholder='example@mail.com' required maxlength='50' value='" << cart_list[i][4] << "'disabled>";
                cout << "           </div>";
                cout << "         </div>";
                string product_p = cart_list[i][4];
                if (i != cart_list.size() - 1)
                {
                    product_p += ", ";
                }
                products_list += product_p;
            }

            cout << "         <div class='col-12'>";
            cout << "           <label class='login-label' for='email'>Total</label>";
            cout << "           <div class='input-group mb-2'>";
            cout << "             <div class='input-group-prepend'>";
            cout << "               <div class='input-group-text'><i class='bi bi-cash-coin'></i></div>";
            cout << "             </div>";
            cout << "             <input type='email' class='form-control' id='id_email' name='email' required placeholder='example@mail.com' required maxlength='50' value='" << form_data["price"] << "' disabled>";
            cout << "           </div>";
            cout << "         </div>";
            cout << "     </form>";
            cout << "   </div>";
            cout << " </div>";

            DBConnection conn3 = DBConnection();
            DBConnection conn5 = DBConnection();
            bool resu = conn5.add_receipt(receipt, form_data["card_owner"], cookies["Email"], utils.mask_card_number(form_data["card_number"]), products_list, form_data["price"]);
            buy_car_result = conn3.erase_products(cookies["Email"], cart_list);
            utils.log_app_action("buy products", "success", cookies["email"]);
        }
        else
        {
            cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
            cout << "<div class=\"container\">";
            cout << "<h1 class=\"display-4\">Algo ha salido mal con tu pago , por favor verifica la informacion y vuelve a intentarlo<i class=\"fas fa-info-circle text-info\"></i></h1>";
            cout << "<hr>";
            cout << "</div>";
            cout << "</div>";
            utils.log_app_action("buy products", "error", cookies["email"], "There was a problem while processing the order");
        }
    }
    else
    {
        cout << "<div class=\"jumbotron jumbotron-fluid bg-transparent\">";
        cout << "<div class=\"container\">";
        cout << "<h1 class=\"display-4\">No hay sesión iniciada <i class=\"fas fa-info-circle text-info\"></i></h1>";
        cout << "<hr>";
        cout << "</div>";
        cout << "</div>";
    }
    printf(footer_content);
    free(header_content);
    free(footer_content);
    /* Utils utils = Utils();
    char *header = "/templates/header.html";
    char *header_content = utils.read_file(header, header_content);
    printf("Content-type:text/html\r\n\r\n");
    printf(header_content);
    DBConnection conn = DBConnection();
    std::map<string, string> form_data = utils.get_post_data();
    bool buy_car_result = conn.erase_products(form_data["correo"]);
    free(header_content);*/

    return 1;
}