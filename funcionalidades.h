#ifndef FUNCIONALIDADES_H_INCLUDED
#define FUNCIONALIDADES_H_INCLUDED
#include <stdio.h>
#include "Estructuras.h"

//Aqui simplemente declaro las funciones, en "funcionalidades.c" las implemento.

Trabajador *crearTrabajador(Trabajador trabajadores[], int *contador);
Trabajador *crearTrabajadores(Trabajador trabajadores[], int *contador);
void mostarTrabajadores(Trabajador trabajadores[], int contador);
void mostrarOrdenesTrabajo(Orden_trabajo ordenes[], Cuadrillas cuadrillas[], int ordenes_contador);
Orden_trabajo *leerOrdenesFichero(FILE *file, Orden_trabajo ordenes[], int *contador);
void eliminarOrden(Orden_trabajo ordenes[], FILE *file);
Cuadrillas *leerCuadrilla(FILE *file, Cuadrillas cuadrillas[], Trabajador trabajadores[], int *contador);
void mostrarCuadrillas(Cuadrillas cuadrillas[], Trabajador trabajadores[], int contador_cuadrilla, int contador_trabajadores);
void eliminarCuadrilla(FILE *file, Cuadrillas cuadrillas[]);
void guardar(FILE *file, Cooperativa cooperativas[], Trabajador trabajadores[], Orden_trabajo ordenes[], Cuadrillas cuadrillas[]);
void cargar(FILE *file, Cooperativa cooperativas[], Trabajador trabajadores[], Orden_trabajo ordenes[], Cuadrillas cuadrillas[]);
void mostrarTrabajadoresTXT(Trabajador trabajadores[]);
void mostrarOrdenesTrabajoTXT(Orden_trabajo ordenes[], Cuadrillas cuadrillas[]);
void mostrarCuadrillasTXT(Cuadrillas cuadrillas[], Trabajador trabajadores[]);
void printError(char text[300]);
void printSucces(char text[300]);


#endif // FUNCIONALIDADES_H_INCLUDED
