#include <iostream>
#include "fichas.h"
#include "funciones.h"
using namespace std;

// void eliminarFichaYAplicarGravedad(unsigned char* tablero,int filas,int columnas,int fila,int columna) {
//     eliminarFicha(tablero, filas, columnas, fila, columna);
//     int fichas, cascadas = procesarCombinaciones(tablero, filas, columnas);
//     cout << "cascadas completadas: " << cascadas << " fichas eliminadas:  " << fichas << endl;
//     aplicarGravedadEnColumna(tablero, filas, columnas);
// }
// MAIN
//  MAIN
// MAIN
int main() {
    srand(time(nullptr));
    unsigned char* tablero = new unsigned char[4];

    int filas = 6;
    int columnas = 10;
    //bool* marcadores = new bool[filas * columnas];

//##################################################################

    llenarTableroAleatorio(tablero, filas, columnas);
    int fila, columna;
    cout << "Tablero inicial:" << endl;
    mostrarTableroNumerico(tablero, filas, columnas);
    cout << "Ingrese fila y columna de ficha a eliminar, empiece a contar desde 0" << endl;
    cout<< "Fila: " ;
    cin >> fila;
    cout<< "\nColumna: ";
    cin >> columna;
    eliminarFicha(tablero, filas, columnas, fila, columna);
    aplicarGravedadEnColumna(tablero, filas, columnas);

    cout << "\nEliminando ficha en fila: " << fila << "& Columa:" << columna << endl;
    mostrarTableroNumerico(tablero, filas, columnas);
    int cascadas = 0;
    int fichasEliminadas = 0;

    procesarCombinaciones(tablero, filas, columnas, cascadas, fichasEliminadas);

    cout << "cascadas ejecutadas: " << cascadas << endl;
    cout << "fichas eliminadas: " << fichasEliminadas << endl;

    cout << "Tablero despues de eliminar:" << endl;
    mostrarTableroNumerico(tablero, filas, columnas);

    delete[] tablero;


    return 0;
}