#ifndef FUNCIONALIDADES_H_INCLUDED
#define FUNCIONALIDADES_H_INCLUDED
#include <stdio.h>
#include "Estructuras.h"

//Aqui simplemente declaro las funciones, en "funcionalidades.c" las implemento.

void crearTrabajador(Trabajador trabajadores[]);
void mostarTrabajadores(Trabajador trabajadores[]);
void mostrarOrdenesTrabajo(Orden_trabajo ordenes[]);
void leerOrdenesFichero(FILE *file, Orden_trabajo ordenes[]);
void eliminarOrden(Orden_trabajo ordenes[], FILE *file);
void leerCuadrilla(FILE *file, Cuadrillas cuadrillas[], Trabajador trabajadores[]);
void mostrarCuadrillas(Cuadrillas cuadrillas[]);
void eliminarCuadrilla(FILE *file, Cuadrillas cuadrillas[]);
void guardar(FILE *file, Cooperativa cooperativas[], Trabajador trabajadores[], Orden_trabajo ordenes[], Cuadrillas cuadrillas[]);
void cargar(FILE *file, Cooperativa cooperativas[], Trabajador trabajadores[], Orden_trabajo ordenes[], Cuadrillas cuadrillas[]);
void printError(char text[300]);
void printSucces(char text[300]);


#endif // FUNCIONALIDADES_H_INCLUDED
