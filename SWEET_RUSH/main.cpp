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
    int bitInicial= posicionLogica * BITS_POR_FICHA;
    return bitInicial;
}

int calcularByteIndex(int bitInicial) {
    return bitInicial / BITS_POR_BYTE; //saber en que byte empieza
}

int calcularBitOffset(int bitInicial) { //en que posicion del byte está para ver si esta partida o no
    return bitInicial % BITS_POR_BYTE;
}

int calcularDesplazamientoLectura(int bitOffset) {
    return BITS_POR_BYTE - BITS_POR_FICHA - bitOffset;
}

unsigned char leerFicha(const unsigned char* memoria, int posicionLogica) {
    int bitInicial = calcularBitInicial(posicionLogica);

    int byteIndex = calcularByteIndex(bitInicial);
    int bitOffset = calcularBitOffset(bitInicial);

    const unsigned char MASCARA_3_BITS = 7;

    // Por ahora, solo manejamos fichas completas en un byte.
    if (bitOffset <= 5) {
        int desplazamiento = calcularDesplazamientoLectura(bitOffset);

        return (memoria[byteIndex] >> desplazamiento) & MASCARA_3_BITS;
    }

    // Todavía no implementamos el caso de ficha partida.
    return 0;
}
// MAIN
//  MAIN
// MAIN
int main() {
    unsigned char* tablero = new unsigned char[2];

    // Inicializar los bytes.
    tablero[0] = 0b10010101;
    tablero[1] = 0b00111001;

    cout << "Byte 0: " << (int)tablero[0] << endl;
    cout << "Byte 1: " << (int)tablero[1] << endl;

    cout << endl;

    cout << "Ficha 0: " << (int)leerFicha(tablero, 0) << endl;
    cout << "Ficha 1: " << (int)leerFicha(tablero, 1) << endl;

    delete[] tablero;

    return 0;
}