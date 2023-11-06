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


//funcion cargar diccionario o archivo.txt
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


//cargar los archivos en tiempo real
int main() {
    cargarDiccionario("diccionario.txt");

    int opcion;
    EntradaDiccionario entrada;
    string palabraBuscada;
//switch como menu de opciones
    do {
        cout << "Que desea hacer?\n 1) Ingresar una palabra.\n 2) Borrar una palabra.\n 3) Mostrar una palabra o buscar.\n 4) Mostrar todo.\n 5) Traducir codigo en C++.\n 6) Salir" << endl;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                cout << "Ingresa la palabra que deseas agregar: ";
                getline(cin, entrada.palabra);
                cout << "Ingresa la traduccion al espanol: ";
                getline(cin, entrada.traduccion);
                cout << "Ingresa el significado: ";
                getline(cin, entrada.significado);
                crear(entrada);
                break;
            case 2:
                cout << "Ingresa la palabra que deseas borrar: ";
                getline(cin, entrada.palabra);
                borrar(entrada.palabra);
                break;
            case 3:
                cout << "Ingresa la palabra que deseas buscar: ";
                getline(cin, palabraBuscada);
                mostrarPalabra(palabraBuscada);
                break;
            case 4:
                mostrar();
                break;
            case 5:
                traducirCodigo();
                break;
            case 6:
                return 0;
            default:
                cout << "Debe ingresar un numero del 1 al 6." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}

