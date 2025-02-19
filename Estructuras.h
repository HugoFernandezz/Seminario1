#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#define MAX_CUADRILLAS_ORDEN  10   // Máximo de cuadrillas por orden de trabajo
#define MAX_TRABAJADORES_CUADRILLA 30// Máximo de trabajadores por cuadrilla

typedef struct {
    char *clave;
    char *nombre;
    int numero_socios;
} Cooperativa;

typedef struct {
    char *NNSS;
    char *nombre;
    int ano_nacimiento;
    int esta_inicializado;
} Trabajador;

typedef struct {
    char *clave;
    char *descripcion;
    int ano;
    int numero_cuadrillas;
    char *cuadrillas[MAX_CUADRILLAS_ORDEN];  //Array de strings (almaceno los 'id' de las cuadrillas)
} Orden_trabajo;

typedef struct {
    char *id;   //Formato <Clave>_<Numero>
    char *nombre;
    int numero_trabajadores;
    char *identificador[MAX_TRABAJADORES_CUADRILLA];
} Cuadrillas;

#endif
