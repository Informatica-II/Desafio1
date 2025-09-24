#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream archivo;
    string linea;
    int tam = 0;

    archivo.open("Encriptado1.txt");  //Abrir el archivo para lectura
    if (!archivo.is_open()) {
        cout << "Falla al abrir el archivo." << endl;
        return 1;  // Exit the program with an error code
    }
    archivo.seekg(0, archivo.end);
    tam = archivo.tellg();
    archivo.seekg(0, archivo.beg);
    cout << "Este es el tamanio: " << tam << endl;

    string *archi = new string[tam];

    while (getline(archivo, linea)) { // Lee línea por línea
        *archi += linea;
        //cout << linea << endl; // Muestra la línea en la consola
    }
    archivo.close();

    cout << *archi << endl;

    delete[] archi;

    return 0;
}
