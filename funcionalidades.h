#ifndef FUNCIONALIDADES_H_INCLUDED
#define FUNCIONALIDADES_H_INCLUDED
#include <stdio.h>
#include "Estructuras.h"

//Aqui simplemente declaro las funciones, en "funcionalidades.c" las implemento.

void crearTrabajador(Trabajador trabajadores[]);
void mostarTrabajadores(Trabajador trabajadores[]);
void leerOrdenesFichero(FILE *file);


#endif // FUNCIONALIDADES_H_INCLUDED
