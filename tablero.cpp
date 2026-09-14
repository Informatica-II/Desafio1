#include "tablero.h"
#include <iostream>
#include <bitset>
#include <cstdlib>
#include <ctime>

using namespace std;

tablero::tablero(unsigned short f, unsigned short c)
{
    filas = f;
    columnas = c;
    unsigned short int numFichas = filas * columnas;
    unsigned short int numBits = numFichas * 3;
    NumBytes = (numBits + 7) / 8;

    Tablero = new unsigned char[NumBytes];
    for (int i = 0; i < NumBytes; i++) {
        Tablero[i] = 0;
    }
}

// Guardar ficha en bloque dinámico
void tablero::setFicha(int fila, int columna, unsigned char valor)
{
    int indice = fila * columnas + columna;   // posición lógica
    int bitInicial = indice * 3;                  // posición en bits
    int byteDondeEsta = bitInicial / 8;                // byte correspondiente
    int posicionDentroDelByte = bitInicial % 8;                 // posicion dentro del byte

    // limpiar los 3 bits en esa posición
    Tablero[byteDondeEsta] &= ~(7 << posicionDentroDelByte);
    // escribir el valor
    Tablero[byteDondeEsta] |= (valor & 7) << posicionDentroDelByte;

    // caso especial: si los 3 bits cruzan al siguiente byte
    if (posicionDentroDelByte > 5) {
        int bitsRestantes = (posicionDentroDelByte + 3) - 8;
        Tablero[byteDondeEsta + 1] &= ~( (1 << bitsRestantes) - 1 );
        Tablero[byteDondeEsta + 1] |= (valor >> (3 - bitsRestantes));
    }
}

void tablero::eliminarFicha(int fila, int columna)
{
    // Paso 1: desplazar todas las fichas hacia abajo en esa columna
    for (int i = fila; i > 0; i--) {
        unsigned char arriba = getFicha(i - 1, columna);
        setFicha(i, columna, arriba);
    }

    // Paso 2: generar nueva ficha aleatoria en la primera fila
    unsigned char nueva = rand() % 6;
    setFicha(0, columna, nueva);
}

// Leer ficha desde bloque dinámico
unsigned char tablero::getFicha(int fila, int columna)
{
    int indice = fila * columnas + columna;   // posición lógica
    int bitInicial = indice * 3;                  // posición en bits
    int byteDondeEsta = bitInicial / 8;                // byte correspondiente
    int posicionDentroDelByte = bitInicial % 8;             // posicion dentro del byte

    unsigned char valor = (Tablero[byteDondeEsta] >> posicionDentroDelByte) & 7;

    if (posicionDentroDelByte > 5) {
        int bitsRestantes = (posicionDentroDelByte + 3) - 8;
        unsigned char extra = Tablero[byteDondeEsta + 1] & ((1 << bitsRestantes) - 1);
        valor |= extra << (3 - bitsRestantes);
    }

    return valor;
}

void tablero::GenerarFichasAleatorias()
{
    srand(time(0));

    cout << "Tablero generado aleatoriamente: " << endl;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            unsigned char ficha = rand() % 6;
            setFicha(i, j, ficha);
        }
    }
}

void tablero::imprimirFicha()
{
    cout << endl;
    cout << "Tablero en fichas: " << endl;
    cout << endl;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << (int)getFicha(i, j) << "\t";
        }
        cout << endl;
    }
}

void tablero::imprimirFichaBinaria()
{
    cout << endl;
    cout << "Tablero en fichas binarias (3 bits): " << endl;
    cout << endl;

    int k = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
        }
        cout << endl;
    }
}

tablero::~tablero()
{
    delete[] Tablero;
}
