// descompresion.cpp
#include "descompresion.h"
#include <cstring> //

// Helpers minimos
// encuentra el tamaño del encriptado
static size_t mi_strlen(const char* s) {
    size_t i = 0;
    if (!s) return 0;
    while (s[i] != '\0') i++;
    return i;
}

// copia segura de buffer con límite
static void mi_strcpy_seguro(char* dest, const char* src, size_t tamDestino) {
    if (!dest || !src || tamDestino == 0) return;
    size_t i = 0;
    while (i + 1 < tamDestino && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// concatena src en dest
static void mi_strcat_inplace(char* dest, const char* src) {
    if (!dest || !src) return;
    size_t p = 0;
    while (dest[p] != '\0') p++;
    size_t i = 0;
    while (src[i] != '\0') {
        dest[p++] = src[i++];
    }
    dest[p] = '\0';
}

// ---------------- RLE----------------
// Según el ejemplo del amigo: el archivo debe tener longitud %3==0
// y cada bloque (b0,b1,b2): b1 = count (0..255), b2 = char a repetir.
//
char* decompressRLE(const char* input, int tamInput) {
    if (!input || tamInput <= 0) return NULL;
    if (tamInput % 3 != 0) return NULL;

    // estimación inicial
    int capacity = tamInput * 2 + 16;
    char* out = new char[capacity];
    int outLen = 0;

    for (int i = 0; i < tamInput; i += 3) {
        unsigned char count = (unsigned char)input[i + 1];
        char ch = input[i + 2];
        if (count == 0) continue;
        // asegurar espacio
        if (outLen + (int)count + 1 > capacity) {
            while (outLen + (int)count + 1 > capacity) capacity *= 2;
            char* tmp = new char[capacity];
            // copiar contenido existente
            for (int j = 0; j < outLen; j++) tmp[j] = out[j];
            delete[] out;
            out = tmp;
        }
        for (int c = 0; c < count; c++) out[outLen++] = ch;
    }
    // terminar C-string
    if (outLen + 1 > capacity) {
        char* tmp = new char[outLen + 1];
        for (int j = 0; j < outLen; j++) tmp[j] = out[j];
        delete[] out;
        out = tmp;
        capacity = outLen + 1;
    }
    out[outLen] = '\0';
    return out;
}

// ---------------- LZ78 ----------------
// Cada bloque: byte0 (alto índice), byte1 (bajo índice), byte2 (carácter).
char* decompressLZ78(const char* input, int tamInput) {
    if (!input || tamInput <= 0) return NULL;
    if (tamInput % 3 != 0) return NULL;

    const int INITIAL_DICT = 1024;
    char** dict = new char*[INITIAL_DICT];
    for (int i = 0; i < INITIAL_DICT; ++i) dict[i] = NULL;
    int dictCap = INITIAL_DICT;
    int nextIndex = 1; // posiciones conceptuales 1..N

    int outCap = tamInput * 5 + 16;
    char* out = new char[outCap];
    out[0] = '\0';
    int outLen = 0;

    for (int i = 0; i < tamInput; i += 3) {
        unsigned char byteAlto = (unsigned char)input[i];
        unsigned char byteBajo = (unsigned char)input[i + 1];
        char ch = input[i + 2];
        unsigned int index = (unsigned int)byteAlto * 256u + (unsigned int)byteBajo;

        // construir cadenaActual
        char* cadenaActual = NULL;
        if (index == 0) {
            cadenaActual = new char[2];
            cadenaActual[0] = ch;
            cadenaActual[1] = '\0';
        } else {
            int dictPos = index - 1; // usando mapeo
            if (dictPos < 0 || dictPos >= nextIndex - 1 || dict[dictPos] == NULL) {
                // formato inválido
                // limpieza
                for (int t = 0; t < nextIndex - 1; ++t) if (dict[t]) delete[] dict[t];
                delete[] dict;
                delete[] out;
                return NULL;
            }
            size_t prefLen = mi_strlen(dict[dictPos]);
            cadenaActual = new char[prefLen + 2];
            mi_strcpy_seguro(cadenaActual, dict[dictPos], prefLen + 2);
            cadenaActual[prefLen] = ch;
            cadenaActual[prefLen + 1] = '\0';
        }

        // escribir en salida (redimensionar si hace falta)
        size_t addLen = mi_strlen(cadenaActual);
        if (outLen + (int)addLen + 1 > outCap) {
            while (outLen + (int)addLen + 1 > outCap) outCap *= 2;
            char* tmp = new char[outCap];
            for (int j = 0; j < outLen; ++j) tmp[j] = out[j];
            delete[] out;
            out = tmp;
        }
        mi_strcat_inplace(out, cadenaActual);
        outLen += (int)addLen;

        // insertar copia en diccionario
        if (nextIndex - 1 >= dictCap) {
            // demasiadas entradas: expandir diccionario
            int newCap = dictCap * 2;
            char** tmp = new char*[newCap];
            for (int t = 0; t < dictCap; ++t) tmp[t] = dict[t];
            for (int t = dictCap; t < newCap; ++t) tmp[t] = NULL;
            delete[] dict;
            dict = tmp;
            dictCap = newCap;
        }
        char* copia = new char[mi_strlen(cadenaActual) + 1];
        mi_strcpy_seguro(copia, cadenaActual, mi_strlen(cadenaActual) + 1);
        dict[nextIndex - 1] = copia;
        nextIndex++;

        delete[] cadenaActual;
    }

    // terminar
    out[outLen] = '\0';

    // limpiar diccionario
    for (int i = 0; i < nextIndex - 1; ++i) {
        if (dict[i]) delete[] dict[i];
    }
    delete[] dict;
    return out;
}
