#include "utils.h"

using namespace std;

Utils::Utils(){};
Utils::~Utils(){};

char *Utils::read_file(char *file_name, char *file_content)
{
    char complete_path[PATH_MAX];
    getcwd(complete_path, sizeof(complete_path));
    strcat(complete_path, file_name);
    FILE *file = fopen(complete_path, "rt");
    size_t size = 0;
    // Mueve el puntero al fin del file
    fseek(file, 0, SEEK_END);
    // Cuenta los caracteres del archivo
    size = ftell(file);
    // Mueve el puntero al principio, para leer el archvio del principio
    fseek(file, 0, SEEK_SET);
    // Ahora, content siempre sera el size correcto
    file_content = (char *)malloc(size * sizeof(char));
    fread(file_content, sizeof(char), size, file);
    return file_content;
};

vector<string> Utils::split(string text, string delimiter)
{
    vector<string> words;
    int start = 0;
    int end = text.find(delimiter);
    while (end != -1)
    {
        words.push_back(text.substr(start, end - start));
        start = end + delimiter.size();
        end = text.find(delimiter, start);
    }
    words.push_back(text.substr(start, end - start));

    return words;
}

std::map<string, string> Utils::get_post_data()
{
    int post_data_length = atoi(getenv("CONTENT_LENGTH"));
    char post_data[post_data_length];
    fgets(post_data, post_data_length + 1, stdin);
    std::map<string, string> form_data;
    vector<string> cont;
    string token;
    stringstream ss(post_data);
    char delimiter = '&';
    while (getline(ss, token, delimiter))
    {
        //Replace "+" with space " "
        int plus_position = token.find('+');
        while (plus_position != -1)
        {
            token[plus_position] = 32;
            plus_position = token.find('+', plus_position + 1);
        }

        //Hexadecimals to decimal to char
        int hex_pos = token.find('%');
        while (hex_pos != -1)
        {
            string hexa = "";
            hexa += token[hex_pos + 1];
            hexa += token[hex_pos + 2];
            int hex_character = (int)strtol(hexa.c_str(), NULL, 16);
            //Erase the hexadecimal from the string
            token.erase(hex_pos, 3);
            //Insert the character
            token.insert(token.begin() + hex_pos, (char)hex_character);
            hex_pos = token.find('%', hex_pos + 1);
        }

        //Remove any scripts in the data. To prevent xss attacks
        int script = token.find("<script");
        if (script != -1)
        {
            token.erase(script, 8);
        }

        cont.push_back(token);
    }

    for (size_t i = 0; i < cont.size(); i++)
    {
        vector<string> key_and_value = split(cont[i], "=");
        form_data[key_and_value[0]] = key_and_value[1];
    }

    return form_data;
};

string Utils::replace_pattern(string text, string pattern, string new_value)
{
    string result = regex_replace(text, regex("\\" + pattern), new_value);
    return result;
}

string Utils::create_salt()
{
    int length = 4;
    string salt = "";
    string characters = "abcdefghijklmnopqrstuvwxyzABCDFGHIJKLMNOPQRSTUVWXYZ1234567890";
    srand(time(NULL));

    for (int x = 0; x < length; x++) // Genera length caracteres diferentes
    {
        AutoSeededRandomPool random;
        long random_number = rand() % (characters.size());
        salt += characters[random_number];
    }

    return salt;
};

string Utils::create_hash_sha2(string password, string salt)
{
    CryptoPP::SHA256 sha2;
    string hash = "";
    StringSource(password + salt, true, new CryptoPP::HashFilter(sha2, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));

    return hash;
};

std::map<string, string> Utils::get_cookies()
{
    std::map<string, string> cookies;
    cookies["Email"] = "-";
    cookies["Password"] = "-";
    std::vector<string> cookie;
    char *cookies_env = getenv("HTTP_COOKIE");

    if (cookies_env != NULL)
    {
        std::vector<string> cookies_list = split(cookies_env, ";");

        for (int i = 0; i < cookies_list.size(); ++i)
        {

            cookie = split(cookies_list[i], "=");

            if (cookie[0].find(char(32)) != std::string::npos)
            {
                cookie[0].erase(cookie[0].find(char(32)), 1);
            }

            if (cookie[0] == "Email" || cookie[0] == "Password")
            {
                cookies[cookie[0]] = cookie[1];
            }
        }
    }

    return cookies;
}

void Utils::get_navbar(bool is_signed)
{

    if (is_signed)
    {

        cout << "<nav class=\"navbar navbar-expand-lg navbar-dark bg-dark\">";
        cout << "    <button class=\"navbar-toggler\" type=\"button\"";
        cout << "        data-toggle=\"collapse\" data-target=\"#navbarNavAltMarkup\"";
        cout << "        aria-controls=\"navbarNavAltMarkup\" aria-expanded=\"false\"";
        cout << "        aria-label=\"Toggle navigation\">";
        cout << "        <span class=\"navbar-toggler-icon\"></span>";
        cout << "    </button>";
        cout << "    <div class=\"collapse navbar-collapse\" id=\"navbarNavAltMarkup\">";
        cout << "        <div class=\"navbar-nav\" id='navbar'>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/home.cgi\" id=\"/\">Inicio<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/add_product.cgi\" id=\"/oficios\">Agregar Producto</a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/list_products.cgi\" id=\"/\">Lista de Productos<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/comments.cgi\" id=\"/oficios\">Comentarios</a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/view_car.cgi\" id=\"/oficios\">Ver Carrito</a>";
        cout << "        </div>";
        cout << "    </div>";

        cout << "<form method=\"post\" action=\"/search_product.cgi\" class='form-inline my-2 my-lg-0' id=\"search_product_form\">";
        cout << "<input type=\"text\" id=\"product_to_search\" name=\"product_to_search\" maxlength='50' required class=\"form-control mr-sm-2\" placeholder=\"Buscar\"/>";
        cout << "<button class='btn btn-outline-info my-2 my-sm-0' type='submit'>Buscar</button>";
        cout << "</form>";

        cout << "    <div class=\"navbar-nav align-left\" id=\"navbar\">";
        cout << "            <a class=\"ml-2 nav-link text-whiter\"> Bienvenido(a)</a>";
        cout << "            <a class=\"ml-2 nav-link text-white\" href=\"/logout_response.cgi\">Cerrar sesión <i class=\"fas fa-sign-out-alt\"></i></a>";
        cout << "    </div>";
        cout << "</nav>";
    }
    else
    {
        cout << "<nav class=\"navbar navbar-expand-lg navbar-dark bg-dark\">";
        cout << "    <button class=\"navbar-toggler\" type=\"button\"";
        cout << "        data-toggle=\"collapse\" data-target=\"#navbarNavAltMarkup\"";
        cout << "        aria-controls=\"navbarNavAltMarkup\" aria-expanded=\"false\"";
        cout << "        aria-label=\"Toggle navigation\">";
        cout << "        <span class=\"navbar-toggler-icon\"></span>";
        cout << "    </button>";
        cout << "    <div class=\"collapse navbar-collapse\" id=\"navbarNavAltMarkup\">";
        cout << "        <div class=\"navbar-nav\" id='navbar'>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/home.cgi\" id=\"/\">Inicio<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/list_products.cgi\" id=\"/\">Lista de Productos<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/comments.cgi\" id=\"/oficios\">Comentarios</a>";
        cout << "        </div>";
        cout << "    </div>";
        cout << "<form method=\"post\" action=\"/search_product.cgi\" class='form-inline my-2 my-lg-0' id=\"search_product_form\">";
        cout << "<input type=\"text\" id=\"product_to_search\" maxlength='50' name=\"product_to_search\" required class=\"form-control mr-sm-2\" placeholder=\"Buscar\"/>";
        cout << "<button class='btn btn-outline-info my-2 my-sm-0' type='submit'>Buscar</button>";
        cout << "</form>";
        cout << "    <div class=\"navbar-nav align-left\" id=\"navbar\">";
        cout << "    <li class=\"nav-item\">";
        cout << "    <a class=\"ml-2 nav-link\" href=\"/login.cgi\">Iniciar sesión<i class=\"fas fa-sign-out-alt\"></i></a>";
        cout << "    </li>";
        cout << "    </div>";
        cout << "</nav>";
    }
}

void Utils::log_app_action(string action, string result, string user, string description)
{

    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    string log_path = "";
    string message = "";
    if (result == "success")
    {
        log_path = LOGS_PATH;
        message = "Action: " + action + " -- User: " + user + " -- Result: " + result + " -- Datetime: " + std::ctime(&end_time) + "\n";
    }
    else
    {

        log_path = ERROR_LOGS_PATH;
        message = "Action: " + action + " -- User: " + user + " -- Result: " + result + " -- Error description: " + description + " -- Datetime: " + std::ctime(&end_time) + "\n";
    }

    ofstream myfile;
    myfile.open(log_path, std::ios_base::app);
    myfile << message;
    myfile.close();
}

string Utils::mask_card_number(string card_number)
{
    string masked_number = "";
    int card_size = card_number.size();
    for (int i = 0; i < card_size; i++)
    {
        if (i == card_size - 1 || i == card_size - 2 || i == card_size - 3 || i == card_size - 4)
        {
            masked_number += card_number[i];
        }
        else
        {
            masked_number += "x";
        }
    }
    return masked_number;
}

bool Utils::verify_card(string numeroTarjeta)
{
    const char *numero = numeroTarjeta.c_str();

    char *n;
    int digito;
    bool par = false;
    int res = 0;

    n = new char[strlen(numero) + 1];
    strcpy(n, numero);
    do
    {
        digito = n[strlen(n) - 1] - '0';
        n[strlen(n) - 1] = 0;
        res += digito;
        if (par)
        {
            res += digito;
            if (digito > 4)
                res -= 9;
        }
        par = !par;

    } while (strlen(n));
    delete[] n;
    return !(res % 10);
}

bool Utils::is_valid_visa_card_no(string card_number)
{
    bool valid = false;
    // Regex to check valid Visa Card number
    const regex pattern("^4[0-9]{12}(?:[0-9]{3})?$");
    cout << "<h1>   SIII </h1>";
    // If the Visa Card number
    // is empty return false
    if (card_number.empty())
    {
        valid = false;
    }
    // Return true if the Visa Card number
    // matched the ReGex
    if (regex_match(card_number, pattern))
    {
        valid = true;
    }
    cout << "<h1>   SIII 2 </h1>";
    return valid;
}

bool Utils::is_valid_masterCard_no(string card_number)
{
    bool valid = false;

    // Regex to check valid Master Card number
    const regex pattern("^5[1-5][0-9]{14}|^(222[1-9]|22[3-9]\\d|2[3-6]\\d{2}|27[0-1]\\d|2720)[0-9]{12}$");

    // If the Master Card number
    // is empty return false
    if (card_number.empty())
    {
        valid = false;
    }
    // Return true if the Master Card number
    // matched the ReGex
    if (regex_match(card_number, pattern))
    {
        valid = true;
    }
    return valid;
}

bool Utils::is_valid_amex_card_no(string card_number)
{
    bool valid = false;

    // Regex to check valid Master Card number
    const regex pattern("^3[47][0-9]{13}$");

    // If the Master Card number
    // is empty return false
    if (card_number.empty())
    {
        valid = false;
    }
    // Return true if the Master Card number
    // matched the ReGex
    if (regex_match(card_number, pattern))
    {
        valid = true;
    }
    return valid;
}

bool Utils::verify_card_no_type(string card_number, string type)
{
    bool valid = false;

    if (verify_card(card_number))
    {
        if (type == "Visa")
        {
            valid = is_valid_visa_card_no(card_number);
            cout << "<h1>"<< valid << "</h1>";
        }
        else
        {
            if (type == "Mastercard")
            {
                valid = is_valid_masterCard_no(card_number);
            }
            else
            {
                if ((type == "AmericanExpress"))
                {
                    valid = is_valid_amex_card_no(card_number);
                }
            }
        }
    }
    return valid;
}

char *Utils::get_date()
{
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    return std::ctime(&end_time);
}

// int main()
// {

// //Se compila asi: g++ utils/utils.cc -o u -std=c++11 -w -lcryptopp -l:libcgicc.a `mysql_config --cflags --libs`

// Utils u = Utils();
// cout<<"======VISA====="<<endl;
// string numeroTarjetaVisa= "4012888888881881"; //si
// //string numeroTarjetaVisa= "6155279860457"; //no
// string visa = "Visa";
// bool visa_valida = u.verify_card_no_type(numeroTarjetaVisa, visa);
// cout<<"La tarjeta "<<visa<< " es valida? "<<visa_valida<<endl;

// cout<<"======MASTERCARD====="<<endl;
// string numeroTarjetaMasterCard= "5200828282828210"; //si
// //string numeroTarjetaMasterCard= "6082822463100051"; //no
// string mastercard = "Mastercard";
// bool mc_valida = u.verify_card_no_type(numeroTarjetaMasterCard, mastercard);
// cout<<"La tarjeta "<<mastercard<< " es valida? "<<mc_valida<<endl;

// cout<<"======AMEX====="<<endl;
// string numeroTarjetaAmex= "371449635398431";//si
// //string numeroTarjetaAmex= "5200828282828210";//no
// string amex = "AmericanExpress";
// bool amex_valida = u.verify_card_no_type(numeroTarjetaAmex, amex);
// cout<<"La tarjeta "<<amex<< " es valida? "<<amex_valida<<endl;

// cout<<"======VISA====="<<endl;

// string str1 = "4155279860457";
// cout << u.is_valid_visa_card_no(str1) << endl;

// // Test Case 2:
// string str2 = "4155279860457201";
// cout << u.is_valid_visa_card_no(str2) << endl;

// // Test Case 3:
// string str3 = "4155279";
// cout << u.is_valid_visa_card_no(str3) << endl;

// // Test Case 4:
// string str4 = "6155279860457";
// cout << u.is_valid_visa_card_no(str4) << endl;

// // Test Case 5:
// string str5 = "415a27##60457";
// cout << u.is_valid_visa_card_no(str5) << endl;

// cout<<"======MASTERCARD====="<<endl;
// // Test Case 1:
// string str11 = "5114496353984312";
// cout << u.is_valid_masterCard_no(str11) << endl;

// // Test Case 2:
// string str12 = "2720822463109651";
// cout << u.is_valid_masterCard_no(str12) << endl;

// // Test Case 3:
// string str13 = "5582822410";
// cout << u.is_valid_masterCard_no(str13) << endl;

// // Test Case 4:
// string str14 = "6082822463100051";
// cout << u.is_valid_masterCard_no(str14) << endl;

// // Test Case 5:
// string str15 = "2221149a635##843";
// cout << u.is_valid_masterCard_no(str15) << endl;

// cout<<"======AMERICAN EXPRESS====="<<endl;

//  string str24 = "378282246310005"; //si es valida
// cout << u.is_valid_amex_card_no(str24) << endl;

// // Test Case 5:
// string str25 = "2221149a635##843";
// cout << u.is_valid_amex_card_no(str25) << endl;

// string str26 = "371449635398431"; //si es valida
// cout << u.is_valid_amex_card_no(str26) << endl;

//     return 0;
// }

// int main(int argc, char const *argv[])
// {
//     Utils u = Utils();
//     cout << u.get_date();
//     // std::map<string, string> cookies = u.get_cookies();
//     // cout << cookies["Email"];
//     // cout << cookies["Password"];

//     // string salt = u.create_salt();
//     // cout << salt << endl;
//     // string hash = u.create_hash_sha2("pass", salt);
//     // cout << hash << endl;

//     // cout << u.mask_card_number("1234567890");
//     // u.log_app_action("login", "error", "form_data", "Email or password incorrect");

//     // free(content);

//     return 0;
// }
