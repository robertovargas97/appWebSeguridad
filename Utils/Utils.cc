#include "Utils.h"

using namespace std;

Utils::Utils(){};
Utils::~Utils(){};

char *Utils::read_file(char *file_name, char *file_content)
{
    char complete_path[_MAX_PATH];
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

// int main(int argc, char const *argv[])
// {
//     char *content = read_file("Login.html", content);
//     printf(content);
//     free(content);

//     return 0;
// }
