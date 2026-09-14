#ifndef TABLERO_H
#define TABLERO_H

class tablero
{
private:
    unsigned short int filas;
    unsigned short int columnas;
    unsigned short int NumBytes;
    unsigned char* Tablero;
    void setFicha(int fila, int columna, unsigned char valor);
    unsigned char getFicha(int fila, int columna);
    void eliminarFicha(int fila, int columna);

public:
    tablero(unsigned short int f, unsigned short int c);
    void GenerarFichasAleatorias();
    void imprimirFicha();
    void imprimirFichaBinaria();
    ~tablero();
};

#endif // TABLERO_H
