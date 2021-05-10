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

// int main(int argc, char const *argv[])
// {
//     Utils u = Utils();
//     char *content = u.read_file("/templates/login.html", content);
//     printf(content);
//     free(content);

//     return 0;
// }
