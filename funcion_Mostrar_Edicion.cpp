//funcion para la edicion de palabras ingresadas en el archivo 
void crear(const EntradaDiccionario &entrada) {
    ofstream archivo("diccionario.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Palabra: " << entrada.palabra << "\nTraduccion: " << entrada.traduccion
            << "\nSignificado: " << entrada.significado << "\n\n";
        archivo.close();
        cout << "Operacion de adicion completada." << endl;
    } else {
        cerr << "Error al abrir el archivo para adicion." << endl;
    }
}


//funcion para mostrar las palbras del diccionario
bool mostrarPalabra(const string &palabra) {
    ifstream archivo("diccionario.txt");
    string linea;
    bool palabraEncontrada = false;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.find("Palabra: " + palabra) != string::npos) {
                palabraEncontrada = true;
                cout << linea << endl;
                getline(archivo, linea);
                cout << linea << endl; 
                getline(archivo, linea);
                cout << linea << endl; 
                break;
            }
        }

        if (!palabraEncontrada) {
            cout << "La palabra no se encontro en el diccionario." << endl;
        }

        archivo.close();
        return palabraEncontrada;
    } else {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return false;
    }
}
