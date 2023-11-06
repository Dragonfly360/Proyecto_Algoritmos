//funcion para traduccion de codigo de c++
string traducirPalabra(const string& palabra) {
    ifstream archivo("diccionario.txt");
    string linea;
    string palabraBuscada = "Palabra: " + palabra;
    string traduccion;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            // buscar la linea que contiene la palabra buscada en el archivo
            if (linea.find(palabraBuscada) != string::npos) {
                // obtener la linea siguiente que contiene la traduccion
                getline(archivo, linea);
                if (linea.find("Traduccion: ") != string::npos) {
                    // obtener la traduccion desde la linea
                    traduccion = linea.substr(linea.find("Traduccion: ") + 12);
                    // eliminar espacios en blanco al inicio y al final
                    traduccion.erase(0, traduccion.find_first_not_of(" \t\n\r\f\v"));
                    traduccion.erase(traduccion.find_last_not_of(" \t\n\r\f\v") + 1);
                    return traduccion;
                }
            }
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo para lectura." << endl;
    }

    // Si no se encuentra la traduccion mostrar la palabra original
    return palabra;
}


//funcion mostrar las palabras del archivo
void mostrar() {
    ifstream archivo("diccionario.txt");
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo para lectura." << endl;
    }
}
