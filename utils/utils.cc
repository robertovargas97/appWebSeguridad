#include "utils.h"

using namespace std;

Utils::Utils() {};
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

map<string, string> Utils::get_post_data()
{
    int post_data_length = atoi(getenv("CONTENT_LENGTH"));
    char *post_data = new char[post_data_length];
    fread((void *)post_data, 1, post_data_length, stdin);
    string content = post_data;
    delete[] post_data;

    map<string, string> form_data;
    vector<string> cont;
    string token;
    stringstream ss(content);
    char delimiter = '&';
    while (std::getline(ss, token, delimiter))
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

// int post_data_length = atoi(getenv("CONTENT_LENGTH"));

// char *post_data = new char[post_data_length];
// fread((void *)post_data, 1, post_data_length, stdin);
// string content = post_data;
// delete[] post_data;

// vector<string> fields = split(content, "&");
// for (size_t i = 0; i < fields.size(); i++)
// {
//     cout << "<h2>" << fields[i] << "</h2>" << endl;
// }
// }

// int main(int argc, char const *argv[])
// {
//     Utils u = Utils();
//     char *content = u.read_file("/templates/login.html", content);
//     printf(content);
//     free(content);

//     return 0;
// }
