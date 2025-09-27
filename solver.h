#ifndef SOLVER_H
#define SOLVER_H

// Busca automáticamente los parámetros (método, rotación y clave)
// que producen un texto original que contenga la pista.
//
// Parámetros de entrada:
//   encBuf/tamEnc: contenido del archivo encriptado.
//   pista: contenido textual de la pista.
//
// Parámetros de salida (si devuelve true):
//   metodoOut: "RLE" o "LZ78" (literal, no liberar).
//   rotacionOut: número de bits de rotación (0..8).
//   claveOut: clave de XOR encontrada.
//   originalOut: buffer dinámico con el texto original (delete[] tras usar).
//
// Devuelve true si encuentra una combinación válida.
bool buscarParametrosYReconstruir(
    const char* encBuf, int tamEnc,
    const char* pista,
    const char** metodoOut, int* rotacionOut, unsigned char* claveOut,
    char** originalOut
    );

#endif // SOLVER_H
