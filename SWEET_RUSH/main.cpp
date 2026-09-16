#include <iostream>
#include "fichas.h"
#include "funciones.h"
using namespace std;

bool detectarCombinaciones(const unsigned char* tablero,bool* marcadores,int filas,int columnas) {
    int totalFichas = filas * columnas;

    // 1. Inicializar marcadores en false
    for (int i = 0; i < totalFichas; i++) {
        marcadores[i] = false;
    }
    bool hayCombinacion = false;

    // 2. Detectar combinaciones en filas
    for (int fila = 0; fila < filas; fila++) {
        int columna = 0;
        while (columna < columnas) {
            int posicionActual = calcularPosicionLogica(fila, columna, columnas);
            unsigned char fichaActual = leerFicha(tablero, posicionActual);

            // Contar fichas iguales consecutivas
            int contador = 1;
            while (columna + contador < columnas) {
                int posicionSiguiente = calcularPosicionLogica(fila, columna + contador, columnas);
                unsigned char fichaSiguiente = leerFicha(tablero, posicionSiguiente);

                if (fichaSiguiente == fichaActual && fichaActual != FICHA_VACIA) {
                    contador++;
                } else {
                    break;
                }
            }

            // Si hay 3 o más, marcar
            if (contador >= 3) {
                hayCombinacion = true;
                for (int k = 0; k < contador; k++) {
                    int posicionMarcar = calcularPosicionLogica(fila, columna + k, columnas);
                    marcadores[posicionMarcar] = true;
                }
            }

            columna += contador;
        }
    }

    // 3. Detectar combinaciones en columnas
    for (int columna = 0; columna < columnas; columna++) {
        int fila = 0;
        while (fila < filas) {
            int posicionActual = calcularPosicionLogica(fila, columna, columnas);
            unsigned char fichaActual = leerFicha(tablero, posicionActual);

            // Contar fichas iguales consecutivas
            int contador = 1;
            while (fila + contador < filas) {
                int posicionSiguiente = calcularPosicionLogica(fila + contador, columna, columnas);
                unsigned char fichaSiguiente = leerFicha(tablero, posicionSiguiente);

                if (fichaSiguiente == fichaActual && fichaActual != FICHA_VACIA) {
                    contador++;
                } else {
                    break;
                }
            }

            // Si hay 3 o más, marcar
            if (contador >= 3) {
                hayCombinacion = true;
                for (int k = 0; k < contador; k++) {
                    int posicionMarcar = calcularPosicionLogica(fila + k, columna, columnas);
                    marcadores[posicionMarcar] = true;
                }
            }

            fila += contador;
        }
    }

    return hayCombinacion;
}
void eliminarFichasMarcadas(unsigned char* tablero, const bool* marcadores, int filas, int columnas) {
    int totalFichas = filas * columnas;

    // 1. Eliminar las fichas marcadas
    for (int posicion = 0; posicion < totalFichas; posicion++) {
        if (marcadores[posicion]) {
            escribirFicha(tablero, posicion, FICHA_VACIA);
        }
    aplicarGravedadEnColumna(tablero, filas, columnas);
    }

    // 2. Aplicar gravedad y rellenar (usando tu función integrada)

}
// MAIN
//  MAIN
// MAIN
int main() {
    srand(time(nullptr));
    unsigned char* tablero = new unsigned char[4];

    int filas = 6;
    int columnas = 10;
    bool* marcadores = new bool[filas * columnas];

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
    eliminarFicha(tablero, filas, columnas, 4, 5);
    eliminarFicha(tablero, filas, columnas, 5, 9);
    eliminarFicha(tablero, filas, columnas, 4, 9);

    mostrarTableroNumerico(tablero, filas, columnas);

    aplicarGravedadEnColumna(tablero,filas,columnas);
     mostrarTableroNumerico(tablero, filas, columnas);

    bool hayCombinacion = detectarCombinaciones(tablero, marcadores, filas, columnas);
    if (hayCombinacion) {
         cout << "Se encontraron combinaciones!" << endl;

         // Mostrar cuáles fichas están marcadas
         for (int fila = 0; fila < filas; fila++) {
             cout << "Fila " << fila << ": ";
             for (int columna = 0; columna < columnas; columna++) {
                 int posicion = calcularPosicionLogica(fila, columna, columnas);
                 cout << (marcadores[posicion] ? "X" : ".") << " ";
             }
             cout << endl;
         }
     } else {
         cout << "No hay combinaciones." << endl;
     }
    eliminarFichasMarcadas(tablero, marcadores,filas, columnas);
    mostrarTableroNumerico(tablero, filas, columnas);
    delete[] tablero;


    return 0;
}