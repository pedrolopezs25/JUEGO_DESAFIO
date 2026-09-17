#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "fichas.h"

// Cálculos básicos de memoria
int calcularCantidadBytes(int filas, int columnas);
int calcularPosicionLogica(int fila, int columna, int columnasTotales);
int calcularBitInicial(int posicionLogica);
int calcularByteIndex(int bitInicial);
int calcularBitOffset(int bitInicial);
int calcularDesplazamientoLectura(int bitOffset);

// Operaciones sobre fichas
unsigned char leerFicha(const unsigned char* memoria, int posicionLogica);
void escribirFicha(unsigned char* memoria, int posicionLogica, unsigned char ficha);

// Visualización
void mostrarTableroNumerico(const unsigned char* tablero, int filas, int columnas);

// Inicialización
void llenarTablero(unsigned char* tablero, int filas, int columnas, unsigned char ficha); //llena con 0
void llenarTableroAleatorio(unsigned char* tablero, int filas, int columnas);

void eliminarFicha(unsigned char* tablero, int filas, int columnas, int fila, int columna);
bool esFichaVacia(const unsigned char* tablero, int filas, int columnas, int fila, int columna);
void aplicarGravedadEnColumna(unsigned char* tablero, int filas, int columnas);
bool detectarCombinaciones(const unsigned char* tablero,bool* marcadores,int filas,int columnas);
void eliminarFichasMarcadas(unsigned char* tablero, const bool* marcadores, int filas, int columnas);

#endif // FUNCIONES_H

