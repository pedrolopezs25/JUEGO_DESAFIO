#include <iostream>
#include "fichas.h"
#include "funciones.h"
using namespace std;

// MAIN
//  MAIN
// MAIN
int main() {
    srand(time(nullptr));
    unsigned char* tablero = new unsigned char[4];
    int filas = 3;
    int columnas = 2;

    llenarTablero(tablero, filas, columnas, FICHA_1);
    llenarTableroAleatorio(tablero, filas, columnas);
    mostrarTableroNumerico(tablero, filas, columnas);

    // tablero[0] = 0b10110110;
    // tablero[1] = 0b11011011;
    // tablero[2] = 0b01101101;
    // tablero[3] = 0b10110110;

    cout << endl;

    // for (int posicion = 0; posicion <= filas*columnas; posicion++) {
    //     cout << "Ficha " << posicion << ": " << (int)leerFicha(tablero, posicion)<< endl;
    //     int bitInicial = calcularBitInicial(posicion);
    //     int bitOffset = calcularBitOffset(bitInicial);
    //     int desplazamiento = calcularDesplazamientoLectura(bitOffset);
    //     //cout << desplazamiento << "" << endl;
    // }
    // cout << "cambio ficha 1 aqui " << endl;
    escribirFicha(tablero, 1, FICHA_4);
    escribirFicha(tablero, 2, FICHA_4);
    escribirFicha(tablero, 5, FICHA_4);
    // for (int posicion = 0; posicion <= filas*columnas; posicion++) {
    //     cout << "Ficha " << posicion << ": " << (int)leerFicha(tablero, posicion)<< endl;
    //     int bitInicial = calcularBitInicial(posicion);
    //     int bitOffset = calcularBitOffset(bitInicial);
    //     int desplazamiento = calcularDesplazamientoLectura(bitOffset);
    //     //cout << desplazamiento << "" << endl;
    // }

    mostrarTableroNumerico(tablero, filas, columnas);
    delete[] tablero;

    return 0;
}