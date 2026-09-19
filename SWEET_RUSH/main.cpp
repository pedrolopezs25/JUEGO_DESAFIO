#include <iostream>
#include "fichas.h"
#include "funciones.h"
using namespace std;

//-------------------------------
//-----------  MAIN  ------------
//-------------------------------
int main() {
    srand(time(nullptr));

    int filas = 6;
    int columnas = 10;
    int cantidaddebytes = calcularCantidadBytes(filas, columnas);
    unsigned char* tablero = new unsigned char[cantidaddebytes];

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
    int filaNueva;
    cout << "Ingrese la fila a agregar" << endl;
    cin >> filaNueva;
    agregarFila(tablero,filas,columnas, filaNueva);
    mostrarTableroNumerico(tablero, filas, columnas);

    cout << "Ingrese la fila a eliminar" << endl;
    cin >> filaNueva;
    eliminarFila(tablero,filas,columnas, filaNueva);
    mostrarTableroNumerico(tablero, filas, columnas);

    int posicionNuevaColumna;
    cout << "Ingrese la columna a agregar" << endl;
    cin >> posicionNuevaColumna;
    agregarColumna(tablero,filas, columnas,posicionNuevaColumna);
    mostrarTableroNumerico(tablero, filas, columnas);

    cout << "Ingrese la columna a agregar" << endl;
    cin >> posicionNuevaColumna;
    eliminarColumna(tablero,filas, columnas,posicionNuevaColumna);
    mostrarTableroNumerico(tablero, filas, columnas);

    delete[] tablero;


    return 0;
}