#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#define MAX_CUADRILLAS_ORDEN  10   // Máximo de cuadrillas por orden de trabajo

typedef struct {
    char clave[20];
    char nombre[30];
    int numero_socios;
} Cooperativa;

typedef struct {
    char NNSS[20];
    char nombre[30];
    int ano_nacimiento;
    int esta_inicializado;
} Trabajador;

typedef struct {
    char clave[20];
    char descripcion[150];
    int numero_cuadrillas;
    char cuadrillas[30][MAX_CUADRILLAS_ORDEN];  //Array de strings (almaceno los 'id' de las cuadrillas)
} Orden_trabajo;

typedef struct {
    char id[25];   //Formato <Clave>_<Numero>
    char nombre[30];
    int numero_trabajadores;
    char identificador[30];
} Cuadrillas;

#endif
