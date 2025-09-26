#include <iostream>
#include <fstream>
#include "descompresion.h"

using namespace std;

void aplicarXOR(char* data, int tam, unsigned char clave) {
    for (int i = 0; i < tam; i++) {
        unsigned char byte = static_cast<unsigned char>(data[i]);
        data[i] = byte ^ clave;
    }
}

void aplicarRotacionDerecha(char* data, int tam, int n) {
    for (int i = 0; i < tam; i++) {
        unsigned char byte = static_cast<unsigned char>(data[i]);
        data[i] = (byte >> n) | (byte << (8 - n));
    }
}

int main() {
    ifstream archivo("Encriptado1.txt", ios::binary);
    const unsigned char claveXOR = 0x5A;

    if (!archivo.is_open()) {
        cout << "Falla al abrir el archivo." << endl;
        return 1;
    }

    // Obtener tamaño del archivo
    archivo.seekg(0, archivo.end);
    int tam = archivo.tellg();
    archivo.seekg(0, archivo.beg);

    cout << "Este es el tamaño del archivo: " << tam << " bytes" << endl;

    // Reservar memoria y guardar el contenido del archivo
    char* contenido = new char[tam];
    archivo.read(contenido, tam);
    archivo.close();

    ofstream nuevo("Nuevo.txt");

    aplicarXOR(contenido, tam, claveXOR);

    aplicarRotacionDerecha(contenido, tam, 3);

    // Escribir el contenido en el nuevo archivo
    nuevo.write(contenido, tam);
    nuevo.close();

    delete[] contenido;
    return 0;
}
