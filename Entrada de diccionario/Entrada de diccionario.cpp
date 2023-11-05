#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <limits>

using namespace std;

struct EntradaDiccionario {
    string palabra;
    string traduccion;
    string significado;
};

unordered_map<string, EntradaDiccionario> diccionario;

void cargarDiccionario(const string& archivoDiccionario) {
    ifstream archivo(archivoDiccionario);
    string palabra, traduccion, significado;

    while (archivo >> palabra >> traduccion >> significado) {
        EntradaDiccionario entrada;
        entrada.palabra = palabra;
        entrada.traduccion = traduccion;
        entrada.significado = significado;
        diccionario[palabra] = entrada;
    }

    archivo.close();
}