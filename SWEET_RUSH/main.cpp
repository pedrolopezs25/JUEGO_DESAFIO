#include <iostream>
#include "fichas.h"
#include "funciones.h"
using namespace std;


void eliminarFicha(unsigned char* tablero, int filas, int columnas, int fila, int columna) {
    int posicion = calcularPosicionLogica(fila, columna, columnas);
    escribirFicha(tablero, posicion, FICHA_VACIA);
}
bool esFichaVacia(const unsigned char* tablero, int filas, int columnas, int fila, int columna) {
    int posicion = calcularPosicionLogica(fila, columna, columnas);
    unsigned char ficha = leerFicha(tablero, posicion);
    return ficha == FICHA_VACIA;
}
void aplicarGravedadEnColumna(unsigned char* tablero, int filas, int columnas) {
    for (int fila = filas - 1; fila >= 0; fila--) {
        for (int columna = columnas-1; columna>=0; columna -- ){
        if (esFichaVacia(tablero, filas, columnas, fila, columna)&&fila>0) {
            int filaOrigen = -1;
            for (int f = fila - 1; f >= 0; f--) {
                if (!esFichaVacia(tablero, filas, columnas, f, columna)) {
                    filaOrigen = f;
                    break;
                }
            }

            if (filaOrigen != -1) {
                int posicionOrigen = calcularPosicionLogica(filaOrigen, columna, columnas);
                unsigned char ficha = leerFicha(tablero, posicionOrigen);

                int posicionDestino = calcularPosicionLogica(fila, columna, columnas);
                escribirFicha(tablero, posicionDestino, ficha);

                escribirFicha(tablero, posicionOrigen, FICHA_VACIA);
            }
        }
        }
        if(fila == 0){
            for (int columna = columnas-1; columna>=0; columna -- ){
                if (esFichaVacia(tablero, filas, columnas, fila, columna)) {
                    int posicion = calcularPosicionLogica(fila, columna, columnas);
                    unsigned char ficha = rand() % 6;  // 0,1,2,3,4,5
                    escribirFicha(tablero, posicion, ficha);

                }
            }
        }}

}
// MAIN
//  MAIN
// MAIN
int main() {
    srand(time(nullptr));
    unsigned char* tablero = new unsigned char[4];
    int filas = 4;
    int columnas = 8;

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

    eliminarFicha(tablero, filas, columnas, 2, 1);
    eliminarFicha(tablero, filas, columnas, 1, 3);
     mostrarTableroNumerico(tablero, filas, columnas);

    aplicarGravedadEnColumna(tablero,filas,columnas);
     mostrarTableroNumerico(tablero, filas, columnas);
    delete[] tablero;

    return 0;
}