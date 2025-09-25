// descompresion.h
#ifndef DESCOMPRESION_H
#define DESCOMPRESION_H

#include <cstdlib>
#include <cstring>

char* decompressRLE(const char* input);
char* decompressLZ78(const char* input, int pairsCount);

#endif // DESCOMPRESION_H
