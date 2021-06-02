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
    cookies["Email"] = "guest";
    cookies["Password"] = "none";
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
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/appWebSeguridad/home.cgi\" id=\"/\">Inicio<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/appWebSeguridad/add_product.cgi\" id=\"/oficios\">Agregar Producto</a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/appWebSeguridad/list_products.cgi\" id=\"/\">Lista de Productos<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/appWebSeguridad/comments.cgi\" id=\"/oficios\">Comentarios</a>";
        cout << "        </div>";
        cout << "    </div>";
        cout << "    <div class=\"navbar-nav align-left\" id=\"navbar\">";
        cout << "            <a class=\"ml-2 nav-link text-whiter\"> Bienvenido(a)</a>";
        cout << "            <a class=\"ml-2 nav-link text-white\" href=\"/appWebSeguridad/logout_response.cgi\">Cerrar sesión <i class=\"fas fa-sign-out-alt\"></i></a>";
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
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/appWebSeguridad/home.cgi\" id=\"/\">Inicio<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/appWebSeguridad/list_products.cgi\" id=\"/\">Lista de Productos<span class=\"sr-only\"></span></a>";
        cout << "            <a class=\"ml-3 nav-link text-white\" href=\"/appWebSeguridad/comments.cgi\" id=\"/oficios\">Comentarios</a>";
        cout << "        </div>";
        cout << "    </div>";
        cout << "    <div class=\"navbar-nav align-left\" id=\"navbar\">";
        cout << "    <li class=\"nav-item\">";
        cout << "    <a class=\"ml-2 nav-link\" href=\"/appWebSeguridad/login.cgi\">Iniciar sesión<i class=\"fas fa-sign-out-alt\"></i></a>";
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

// int main(int argc, char const *argv[])
// {
//     Utils u = Utils();

//     // string salt = u.create_salt();
//     // cout << salt << endl;
//     // string hash = u.create_hash_sha2("pass", salt);
//     // cout << hash << endl;

//     u.log_app_action("login", "error", "form_data", "Email or password incorrect");

//     // free(content);

//     return 0;
// }
