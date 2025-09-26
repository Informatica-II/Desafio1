// descompresion.cpp
#include "descompresion.h"
#include <iostream>  // aquí sí puedes usar cout para debug
#include "descompresion.h"
#include <iostream>

// --- RLE Decompression ---
char* decompressRLE(const char* input) {
    int len = strlen(input);
    int outSize = 0;

    // Calcular tamaño de salida
    for (int i = 0; i < len;) {
        int count = 0;
        while (i < len && input[i] >= '0' && input[i] <= '9') {
            count = count * 10 + (input[i] - '0');
            i++;
        }
        if (i < len) {
            outSize += count;
            i++;
        }
    }

    char* output = new char[outSize + 1];
    int pos = 0;

    // Reconstrucción
    for (int i = 0; i < len;) {
        int count = 0;
        while (i < len && input[i] >= '0' && input[i] <= '9') {
            count = count * 10 + (input[i] - '0');
            i++;
        }
        if (i < len) {
            char symbol = input[i++];
            for (int j = 0; j < count; j++) {
                output[pos++] = symbol;
            }
        }
    }

    output[pos] = '\0';
    return output;
}

// --- LZ78 Decompression ---
struct DictEntry {
    char* str;
};

char* decompressLZ78(const char* input, int pairsCount) {
    DictEntry* dict = new DictEntry[pairsCount + 1];
    for (int i = 0; i <= pairsCount; i++) dict[i].str = NULL;

    int outCapacity = 1024;
    char* output = new char[outCapacity];
    int outLen = 0;

    int idx = 0;
    for (int k = 0; k < pairsCount; k++) {
        // Leer índice
        int num = 0;
        while (input[idx] >= '0' && input[idx] <= '9') {
            num = num * 10 + (input[idx] - '0');
            idx++;
        }
        if (input[idx] == ',') idx++;

        // Leer caracter
        char c = input[idx++];
        if (input[idx] == ';') idx++;

        // Construir nueva cadena
        int prefixLen = (num > 0 && dict[num].str) ? strlen(dict[num].str) : 0;
        char* newStr = new char[prefixLen + 2];
        if (num > 0 && dict[num].str) strcpy(newStr, dict[num].str);
        newStr[prefixLen] = c;
        newStr[prefixLen + 1] = '\0';
        dict[k + 1].str = newStr;

        // Ampliar buffer de salida si es necesario
        int needed = outLen + prefixLen + 1;
        if (needed >= outCapacity) {
            outCapacity *= 2;
            char* tmp = new char[outCapacity];
            memcpy(tmp, output, outLen);
            delete[] output;
            output = tmp;
        }
        memcpy(output + outLen, newStr, prefixLen + 1);
        outLen += prefixLen + 1;
    }

    output[outLen] = '\0';

    // Liberar memoria del diccionario
    for (int i = 0; i <= pairsCount; i++) {
        if (dict[i].str) delete[] dict[i].str;
    }
    delete[] dict;

    return output;
}
