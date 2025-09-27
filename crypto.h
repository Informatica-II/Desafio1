#ifndef CRYPTO_H
#define CRYPTO_H

// Aplica XOR con una clave de un byte sobre el buffer (in-place)
void aplicarXOR(char* data, int tam, unsigned char clave);

// Aplica rotación a la derecha de n bits (0..7) sobre cada byte (in-place)
void aplicarRotacionDerecha(char* data, int tam, int n);

#endif // CRYPTO_H
