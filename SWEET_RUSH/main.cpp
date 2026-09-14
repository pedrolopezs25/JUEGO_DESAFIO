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
    int desplazamiento = BITS_POR_BYTE - BITS_POR_FICHA - bitOffset;
    return desplazamiento;
}

unsigned char leerFicha(const unsigned char* memoria, int posicionLogica) {
    int bitInicial = calcularBitInicial(posicionLogica);
    int byteIndex = calcularByteIndex(bitInicial);
    int bitOffset = calcularBitOffset(bitInicial);

    const unsigned char MASCARA_3_BITS = 7;

    // Por ahora, solo manejamos fichas completas en un byte.
    if (bitOffset <= 5) {
        int desplazamiento = calcularDesplazamientoLectura(bitOffset);
        unsigned char ficha = (memoria[byteIndex] >> desplazamiento) & MASCARA_3_BITS;
        return ficha;
    }
    else {
        int desplazamiento = calcularDesplazamientoLectura(bitOffset);
        unsigned char ficha1 = (memoria[byteIndex] << desplazamiento*-1) & MASCARA_3_BITS;
        if(bitOffset == 6){
            unsigned char ficha2 = (memoria[byteIndex+1] >> 7) & MASCARA_3_BITS;
            return ficha1|ficha2;}
        else if(bitOffset == 7){
            unsigned char ficha2 = (memoria[byteIndex+1] >> 6) & MASCARA_3_BITS;
            return ficha1|ficha2;
        }
        return ficha1;
    }


    return 0;
}
void escribirFicha(unsigned char* memoria,int posicionLogica,unsigned char ficha) {
    int bitInicial = calcularBitInicial(posicionLogica);
    int byteIndex = calcularByteIndex(bitInicial);
    int bitOffset = calcularBitOffset(bitInicial);

    const unsigned char MASCARA_3_BITS = 7;

    // Por ahora, solo manejamos fichas completas en un byte.
    if (bitOffset <= 5) {
        int desplazamiento = calcularDesplazamientoLectura(bitOffset);
        // Llevar la máscara a la posición que ocupa la ficha
        unsigned char mascaraFicha =
            MASCARA_3_BITS << desplazamiento;

        unsigned char mascaraLimpieza = ~mascaraFicha;
        memoria[byteIndex] = memoria[byteIndex] & mascaraLimpieza; //limpiar
        unsigned char fichaUbicada = (ficha & MASCARA_3_BITS) << desplazamiento; // Mover la nueva ficha a la posición correcta
        memoria[byteIndex] = memoria[byteIndex] | fichaUbicada;
    }
    else if (bitOffset == 6) {
        unsigned char partePrimerByte = (ficha >> 1) & MASCARA_3_BITS;
        unsigned char parteSegundoByte = ficha & MASCARA_3_BITS;

        memoria[byteIndex] = memoria[byteIndex] & 0b11111100;
        memoria[byteIndex] = memoria[byteIndex] | partePrimerByte;

        memoria[byteIndex + 1] = memoria[byteIndex + 1] & 0b01111111;
        memoria[byteIndex + 1] = memoria[byteIndex + 1] | (parteSegundoByte << 7);
    }
    else if (bitOffset == 7) {
        unsigned char partePrimerByte = (ficha >> 2) & MASCARA_3_BITS;
        unsigned char parteSegundoByte = ficha & MASCARA_3_BITS;

        memoria[byteIndex] = memoria[byteIndex] & 0b11111110;
        memoria[byteIndex] = memoria[byteIndex] | partePrimerByte;

        memoria[byteIndex + 1] = memoria[byteIndex + 1] & 0b00111111;
        memoria[byteIndex + 1] = memoria[byteIndex + 1] | (parteSegundoByte << 6);
    }
}
// MAIN
//  MAIN
// MAIN
int main() {
    unsigned char* tablero = new unsigned char[3];

    tablero[0] = 0b10110110;
    tablero[1] = 0b11011011;
    tablero[2] = 0b01101101;

    cout << "Byte 0: " << (int)tablero[0] << endl;
    cout << "Byte 1: " << (int)tablero[1] << endl;

    cout << endl;

    for (int posicion = 0; posicion < 8; posicion++) {
        cout << "Ficha " << posicion << ": " << (int)leerFicha(tablero, posicion)<< endl;
        int bitInicial = calcularBitInicial(posicion);
        int bitOffset = calcularBitOffset(bitInicial);
        int desplazamiento = calcularDesplazamientoLectura(bitOffset);
        //cout << desplazamiento << "" << endl;
    }
    cout << "cambio ficha 1 aqui " << endl;
    escribirFicha(tablero, 1, FICHA_4);
    escribirFicha(tablero, 2, FICHA_4);
    escribirFicha(tablero, 5, FICHA_4);
    for (int posicion = 0; posicion < 8; posicion++) {
        cout << "Ficha " << posicion << ": " << (int)leerFicha(tablero, posicion)<< endl;
        int bitInicial = calcularBitInicial(posicion);
        int bitOffset = calcularBitOffset(bitInicial);
        int desplazamiento = calcularDesplazamientoLectura(bitOffset);
        //cout << desplazamiento << "" << endl;
    }
    delete[] tablero;

    return 0;
}