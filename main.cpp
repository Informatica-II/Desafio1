#include <iostream>
#include <fstream>
#include "descompresion.h"

using namespace std;

int main() {
    ifstream archivo("Encriptado1.txt");
    if (!archivo.is_open()) {
        cout << "Falla al abrir el archivo." << endl;
        return 1;
    }

    // Reservamos buffer temporal para cada línea
    const int MAX_LINE = 1024;
    char* linea = new char[MAX_LINE];

    // Para guardar todo el archivo en memoria
    int capacity = 4096;
    char* contenido = new char[capacity];
    int length = 0;

    cout << "Contenido del archivo línea por línea:" << endl;

    while (archivo.getline(linea, MAX_LINE)) {
        cout << linea << endl;

        int len = 0;
        while (linea[len] != '\0') len++;

        // Asegurar espacio suficiente en 'contenido'
        if (length + len >= capacity) {
            capacity *= 2;
            char* tmp = new char[capacity];
            for (int i = 0; i < length; i++) tmp[i] = contenido[i];
            delete[] contenido;
            contenido = tmp;
        }

        // Copiar la línea al buffer final
        for (int i = 0; i < len; i++) {
            contenido[length++] = linea[i];
        }
    }
    contenido[length] = '\0';

    archivo.close();

    cout << "\nArchivo completo en memoria:" << endl;
    cout << contenido << endl;

    delete[] linea;
    delete[] contenido;

    return 0;
}
