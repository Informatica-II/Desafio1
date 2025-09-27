#ifndef DESCOMPRESION_H
#define DESCOMPRESION_H

// Descompresión RLE: trabaja con bloques de 3 bytes (binario).
// Devuelve buffer dinámico terminado en '\0'. Caller debe liberar con delete[].
char* decompressRLE(const char* input, int tamInput);

// Descompresión LZ78: trabaja con bloques de 3 bytes (binario).
// Devuelve buffer dinámico terminado en '\0'. Caller debe liberar con delete[].
char* decompressLZ78(const char* input, int tamInput);

#endif // DESCOMPRESION_H
