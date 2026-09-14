#include <iostream>
#include "fichas.h"

using namespace std;

int calcularCantidadBytes(int filas, int columnas) {
    int bitsTotales = filas * columnas * BITS_POR_FICHA;
    int bitsTotalesRedondeo = (bitsTotales + BITS_POR_BYTE - 1) / BITS_POR_BYTE; // se suma un bit para en la division redondear hacia arriba
    return bitsTotalesRedondeo;
}

int calcularPosicionLogica(int fila, int columna, int columnas) {
    int posicion = fila * columnas + columna; //Columnas (tablero) - columna (a buscar)
    return posicion; //posicion en el tablero de la ficha
}

int calcularBitInicial(int posicionLogica) {
    return posicionLogica * BITS_POR_FICHA;
}

int calcularByteIndex(int bitInicial) {
    return bitInicial / BITS_POR_BYTE; //saber en que byte empieza
}

int calcularBitOffset(int bitInicial) { //en que posicion del byte está para ver si esta partida o no
    return bitInicial % BITS_POR_BYTE;
}
// ============================================
// FUNCIÓN PRINCIPAL
// ============================================

int main() {
    // ========================================
    // Prueba 1: calcularCantidadBytes
    // ========================================
    int filas = 3;
    int columnas = 4;
    int bytes = calcularCantidadBytes(filas, columnas);
    cout << "Tablero " << filas << "x" << columnas
         << " necesita " << bytes << " bytes" << endl;

    // ========================================
    // Prueba 2: calcularPosicionLogica
    // ========================================
    int filaPrueba = 0;
    int columnaPrueba = 2;
    int posicion = calcularPosicionLogica(filaPrueba, columnaPrueba, columnas);
    cout << "Posicion (" << filaPrueba << "," << columnaPrueba
         << ") = " << posicion << endl;

    // ========================================
    // Prueba 3: calcularBitInicial
    // ========================================
    int bit = calcularBitInicial(posicion);
    cout << "Bit inicial para la posicion " << posicion << " = " << bit << endl;

    // ========================================
    // Prueba 4: Calcular byte y offset usando funciones
    // ========================================
    int byteIndex = calcularByteIndex(bit);
    int bitOffset = calcularBitOffset(bit);

    cout << "Byte index = " << byteIndex << endl;
    cout << "Bit offset = " << bitOffset << endl;

    // ¿Cruza dos bytes?
    if (bitOffset > 5) {
        cout << "La ficha cruza DOS bytes" << endl;
    } else {
        cout << "La ficha esta completa en UN byte" << endl;
    }

    // ========================================
    // Probar con varias posiciones
    // ========================================
    cout << "\n--- Probando todas las posiciones del tablero ---" << endl;

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            int pos = calcularPosicionLogica(f, c, columnas);
            int bitI = calcularBitInicial(pos);
            int byteI = calcularByteIndex(bitI);
            int bitO = calcularBitOffset(bitI);

            cout << "(" << f << "," << c << ") -> pos=" << pos
                 << ", bit=" << bitI
                 << ", byte=" << byteI
                 << ", offset=" << bitO;

            if (bitO > 5) {
                cout << " [CRUZA 2 bytes]";
            }
            cout << endl;
        }
    }

    return 0;
}