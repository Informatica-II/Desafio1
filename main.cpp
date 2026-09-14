#include <iostream>
#include "tablero.h"

using namespace std;

int main()
{
    unsigned short int f = 0;
    unsigned short int c = 0;

    cout << "Ingrese numero de filas: ";
    cin >> f;
    cout << "Ingrese numero de columnas: ";
    cin >> c;

    tablero t(f, c);
    t.GenerarFichasAleatorias();
    t.imprimirFicha();
    t.imprimirFichaBinaria();

    return 0;
}
