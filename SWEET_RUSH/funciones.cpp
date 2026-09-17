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
void mostrarTableroNumerico(const unsigned char* tablero, int filas, int columnas) {
    cout << "     ";
    for (int columna = 1; columna <= columnas; columna++) {
        cout << "C" << columna << " ";
    }

    cout << endl;

    for (int fila = 0; fila < filas; fila++) {
        cout << "F" << fila + 1 << ":  ";

        for (int columna = 0; columna < columnas; columna++) {
            int posicionLogica =
                calcularPosicionLogica(fila, columna, columnas);

            unsigned char ficha =
                leerFicha(tablero, posicionLogica);

            cout << (int)ficha << "  ";
        }

        cout << endl;
    }
}
void llenarTablero(unsigned char* tablero, int filas, int columnas, unsigned char ficha) {
    int totalFichas = filas * columnas;
    for (int posicion = 0; posicion < totalFichas; posicion++) {
        escribirFicha(tablero, posicion, ficha);
    }
}
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()

void llenarTableroAleatorio(unsigned char* tablero, int filas,int columnas) {
    int totalFichas = filas * columnas;

    for (int posicion = 0; posicion < totalFichas; posicion++) {
        unsigned char ficha = rand() % 6;  // 0,1,2,3,4,5
        escribirFicha(tablero, posicion, ficha);
    }
}



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
            if(fila == 0){
                for (int columna = columnas-1; columna>=0; columna -- ){
                    if (esFichaVacia(tablero, filas, columnas, fila, columna)) {
                        int posicion = calcularPosicionLogica(fila, columna, columnas);
                        unsigned char ficha = rand() % 6;  // 0,1,2,3,4,5
                        escribirFicha(tablero, posicion, ficha);

                    }
                }
        }

        }}
}

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

    for (int posicion = 0; posicion < totalFichas; posicion++) {
        if (marcadores[posicion]) {
            escribirFicha(tablero, posicion, FICHA_VACIA);
        }
        aplicarGravedadEnColumna(tablero, filas, columnas);
    }
}