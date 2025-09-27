// main.cpp
#include <iostream>
#include <fstream>
#include <cstring>
#include "solver.h"

using namespace std;

static char* leerArchivoBinario(const char* nombre, int& tam) {
    ifstream f(nombre, ios::binary);
    if (!f.is_open()) return NULL;
    f.seekg(0, f.end);
    tam = (int)f.tellg();
    f.seekg(0, f.beg);
    char* buf = new char[tam];
    if (tam > 0) f.read(buf, tam);
    f.close();
    return buf;
}

static char* leerArchivoTexto(const char* nombre, int& tam) {
    ifstream f(nombre);
    if (!f.is_open()) return NULL;
    f.seekg(0, f.end);
    tam = (int)f.tellg();
    f.seekg(0, f.beg);
    char* buf = new char[tam + 1];
    if (tam > 0) f.read(buf, tam);
    buf[tam] = '\0';
    f.close();
    return buf;
}

int main() {
    int n;
    cout << "¿Cuántos archivos desea evaluar? ";
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        char nombreEnc[64], nombrePista[64];
        sprintf(nombreEnc, "Encriptado%d.txt", i);
        sprintf(nombrePista, "pista%d.txt", i);

        int tamEnc = 0;
        char* enc = leerArchivoBinario(nombreEnc, tamEnc);
        if (!enc || tamEnc <= 0) {
            cout << "No se pudo abrir o archivo vacío: " << nombreEnc << endl;
            if (enc) delete[] enc;
            continue;
        }

        int tamP = 0;
        char* pista = leerArchivoTexto(nombrePista, tamP);
        if (!pista) {
            cout << "No se pudo abrir pista: " << nombrePista << endl;
            delete[] enc;
            continue;
        }

        const char* metodo = NULL;
        int rot = 0;
        unsigned char k = 0;
        char* original = NULL;

        bool ok = buscarParametrosYReconstruir(enc, tamEnc, pista,
                                               &metodo, &rot, &k, &original);
        cout << "\n=== Caso " << i << " ===\n";
        if (ok) {
            cout << "Compresión: " << metodo << endl;
            cout << "Rotación: " << rot << endl;
            cout << "Key= 0x" << hex << (int)k << dec << endl;
            cout << "Texto original:\n" << original << endl;

            // guardar resultado
            char outName[64];
            sprintf(outName, "Resultado%d.txt", i);
            ofstream out(outName, ios::binary);
            if (out.is_open()) {
                out.write(original, strlen(original));
                out.close();
            }
            delete[] original;
        } else {
            cout << "No se encontró combinación válida." << endl;
        }

        delete[] enc;
        delete[] pista;
    }

    return 0;
}
