// crypto.cpp
#include "crypto.h"

// Aplica XOR con clave de 1 byte (modifica buffer)
void aplicarXOR(char* data, int tam, unsigned char clave) {
    for (int i = 0; i < tam; i++) {
        unsigned char b = (unsigned char)data[i];
        data[i] = (char)(b ^ clave);
    }
}

// Aplica rotación a la derecha de n bits (0..8 validos; si n==0 no hace nada)
void aplicarRotacionDerecha(char* data, int tam, int n) {
    if (n <= 0) return;
    n = n & 7; // asegurar 0-7
    for (int i = 0; i < tam; i++) {
        unsigned char b = (unsigned char)data[i];
        data[i] = (char)((b >> n) | (b << (8 - n)));
    }
}
