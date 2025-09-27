// solver.cpp
#include "solver.h"
#include "descompresion.h"
#include "crypto.h"

#include <cstring>

// buscar si pat está en txt
static bool contiene(const char* txt, const char* pat) {
    if (!txt || !pat) return false;
    int lt = 0; while (txt[lt] != '\0') lt++;
    int lp = 0; while (pat[lp] != '\0') lp++;
    if (lp == 0 || lp > lt) return false;
    for (int i = 0; i <= lt - lp; i++) {
        int j = 0;
        while (j < lp && txt[i + j] == pat[j]) j++;
        if (j == lp) return true;
    }
    return false;
}

static char* duplicarBufferConCero(const char* src, int tam) {
    if (tam < 0) tam = 0;
    char* p = new char[tam + 1];
    for (int i = 0; i < tam; i++) p[i] = src[i];
    p[tam] = '\0';
    return p;
}

bool buscarParametrosYReconstruir(
    const char* encBuf, int tamEnc,
    const char* pista,
    const char** metodoOut, int* rotacionOut, unsigned char* claveOut,
    char** originalOut
    ) {
    if (!encBuf || tamEnc <= 0 || !pista || !metodoOut || !rotacionOut || !claveOut || !originalOut)
        return false;

    *metodoOut = NULL;
    *rotacionOut = 0;
    *claveOut = 0;
    *originalOut = NULL;

    // probar todas las claves y rotaciones; por cada (k,n) desencriptar primero: XOR->rotRight, luego intentar descomprimir.
    for (int k = 0; k <= 255; ++k) {
        for (int n = 0; n <= 8; ++n) {

            char* candidato = duplicarBufferConCero(encBuf, tamEnc);

            // 1) desencriptar: XOR luego rotación derecha
            aplicarXOR(candidato, tamEnc, (unsigned char)k);
            aplicarRotacionDerecha(candidato, tamEnc, n);

            // 2) intentar RLE
            char* rleOut = decompressRLE(candidato, tamEnc);
            if (rleOut) {
                if (contiene(rleOut, pista)) {
                    *metodoOut = "RLE";
                    *rotacionOut = n;
                    *claveOut = (unsigned char)k;
                    *originalOut = rleOut;
                    delete[] candidato;
                    return true;
                }
                delete[] rleOut;
            }

            // 3) intentar LZ78
            char* lzOut = decompressLZ78(candidato, tamEnc);
            if (lzOut) {
                if (contiene(lzOut, pista)) {
                    *metodoOut = "LZ78";
                    *rotacionOut = n;
                    *claveOut = (unsigned char)k;
                    *originalOut = lzOut;
                    delete[] candidato;
                    return true;
                }
                delete[] lzOut;
            }

            delete[] candidato;
        }
    }

    return false;
}
