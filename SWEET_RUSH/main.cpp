#include <iostream>
#include "fichas.h"
#include "funciones.h"
using namespace std;


void agregarFila(unsigned char*& tablero, int& filas, int columnas, int posicionNuevaFila) {

    if (posicionNuevaFila < 0 || posicionNuevaFila > filas) {
        cout << "usted está agregando en una posicion que no existe" << endl;
        return;
    }

    int filasNuevas = filas + 1;
    int bytesNuevos = calcularCantidadBytes(filasNuevas, columnas);
    unsigned char* tableroNuevo = new unsigned char[bytesNuevos];

    for (int i = 0; i < bytesNuevos; i++) {
        tableroNuevo[i] = 0;
    }

    // Copiar las filas originales antes de la nueva fila.
    for (int fila = 0; fila < posicionNuevaFila; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int posicionVieja = calcularPosicionLogica(fila, columna, columnas);
            int posicionNueva = calcularPosicionLogica(fila, columna, columnas);
            unsigned char ficha = leerFicha(tablero, posicionVieja);
            escribirFicha(tableroNuevo, posicionNueva, ficha);
        }
    }

    // Llenar la fila insertada con fichas aleatorias.
    for (int columna = 0; columna < columnas; columna++) {
        int posicionNueva = calcularPosicionLogica(posicionNuevaFila, columna, columnas);
        unsigned char ficha = rand() % 6;
        escribirFicha(tableroNuevo, posicionNueva, ficha);
    }

    // Copiar las filas originales desde la posición de inserción.
    // Su destino se desplaza una fila hacia abajo.
    for (int fila = posicionNuevaFila; fila < filas; fila++) {
        for (int columna = 0; columna < columnas; columna++) {
            int posicionVieja = calcularPosicionLogica(fila, columna, columnas);
            int posicionNueva = calcularPosicionLogica(fila + 1, columna, columnas);
            unsigned char ficha = leerFicha(tablero, posicionVieja);
            escribirFicha(tableroNuevo, posicionNueva, ficha);
        }
    }
    delete[] tablero;
    tablero = tableroNuevo;
    filas = filasNuevas;
}

void eliminarFila(unsigned char*& tablero, int& filas, int columnas, int filaEliminar) {
    if (filaEliminar < 0 || filaEliminar >= filas) {
        cout << "Esa fila no existe" << endl;
        return;
    }
    if (filas <= 1) {
        cout << "el tablero no puede quedar sin filas" << endl;
        return;
    }

    int filasNuevas = filas - 1;

    int bytesNuevos = calcularCantidadBytes(filasNuevas, columnas);
    unsigned char* tableroNuevo = new unsigned char[bytesNuevos];

    for (int i = 0; i < bytesNuevos; i++) {
        tableroNuevo[i] = 0;
    }

    // Copiar todas las filas excepto la que será eliminada.
    for (int filaVieja = 0; filaVieja < filas; filaVieja++) {
        if (filaVieja != filaEliminar) {
            int filaNueva;

            // Las filas antes de la eliminada quedan en la misma posición.
            if (filaVieja < filaEliminar) {
                filaNueva = filaVieja;
            } else {
                // Las posteriores suben una posición.
                filaNueva = filaVieja - 1;
            }

            for (int columna = 0; columna < columnas; columna++) {
                int posicionVieja = calcularPosicionLogica(filaVieja, columna, columnas);
                int posicionNueva = calcularPosicionLogica(filaNueva, columna, columnas);
                unsigned char ficha = leerFicha(tablero, posicionVieja);
                escribirFicha(tableroNuevo, posicionNueva, ficha);
            }
        }
    }

    delete[] tablero;
    tablero = tableroNuevo;
    filas = filasNuevas;
}
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


    delete[] tablero;


    return 0;
}