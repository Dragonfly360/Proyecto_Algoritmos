//funcion para borrar las palabras del diccionario
void borrar(const string &palabraABorrar) {
    ifstream archivoLectura("diccionario.txt");
    string contenidoActualizado;
    string linea;

    if (archivoLectura.is_open()) {
        while (getline(archivoLectura, linea)) {
            if (linea.find("Palabra: " + palabraABorrar) != string::npos) {
                for (int i = 0; i < 3; ++i) {
                    getline(archivoLectura, linea);
                }
            } else {
                contenidoActualizado += linea + "\n";
            }
        }
        archivoLectura.close();
    } else {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    ofstream archivoEscritura("diccionario.txt", ios::trunc);

    if (archivoEscritura.is_open()) {
        archivoEscritura << contenidoActualizado;
        archivoEscritura.close();
        cout << "Operacion de borrado completada." << endl;
    } else {
        cerr << "Error al abrir el archivo para escritura." << endl;
    }
}


//funcion 2 de traduccion de codigo
void traducirCodigo() {
    cout << "Ingrese el codigo en C++ (ingrese una linea vacia para finalizar):\n";
    string codigo;
    stringstream codigoTraducido;

    int contadorLlaves = 0;
    bool dentroDeEstructura = false;
    string estructuraActual;

    while (true) {
        getline(cin, codigo);
        if (codigo.empty()) {
            break;
        }

        // traducir palabras y detectar estructuras de control
        stringstream ss(codigo);
        string palabra, traducida, resultado;

        while (ss >> palabra) {
            // traducir las llaves
            if (palabra == "{") {
                contadorLlaves++;
                resultado += "inicio ";
                if (dentroDeEstructura) {
                    resultado += estructuraActual + " ";
                }
            } else if (palabra == "}") {
                contadorLlaves--;
                resultado += "fin ";
                if (dentroDeEstructura) {
                    resultado += estructuraActual + " ";
                }
            } else {
                traducida = traducirPalabra(palabra);
                resultado += traducida + " ";
            }

            // detectar inicio de estructuras de control
            if (palabra == "if" || palabra == "else" || palabra == "while" || palabra == "for") {
                dentroDeEstructura = true;
                // obtener el nombre de la estructura de control
                estructuraActual = traducirPalabra(palabra);
            }
        }

        // Si el contador de llaves es 0 salir de la estructura de control
        if (contadorLlaves == 0) {
            dentroDeEstructura = false;
        }

        codigoTraducido << resultado << endl;
    }

    cout << "\nCodigo traducido:\n" << codigoTraducido.str();
}
