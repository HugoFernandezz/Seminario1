#include "funcionalidades.h"
#include "Estructuras.h"
#include <stdio.h>

#define MAX_ORDENES           50   // Máximo de órdenes de trabajo
#define MAX_CUADRILLAS        20   // Máximo de cuadrillas en total
#define MAX_COOPERATIVAS      10   // Máximo de cooperativas
#define MAX_TRABAJADORES      100  // Máximo de trabajadores

/*----------------------
 colores para la consola
 -----------------------*/

#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define COLOR_NORMAL "\e[0m"


void crearTrabajador(Trabajador trabajadores[]){
    Trabajador trabajador;
    printf("Introduzca el nombre del trabajador: ");
    gets(trabajador.nombre);
    printf("Introduzca el NNSS del trabajador: ");
    gets(trabajador.NNSS);
    printf("Introduzca el ano de nacimiento del trabajador: ");
    scanf("%d", &trabajador.ano_nacimiento);
    trabajador.esta_inicializado = 1;

    for(int i = 0; i<MAX_TRABAJADORES; i++){
        if(trabajadores[i].esta_inicializado != 1){
            trabajadores[i] = trabajador;
            printf(GREEN);
            printf("\t[*]Trabajador dado de alta correctamente!\n");
            printf(COLOR_NORMAL);
            break;
        }
    }
}

void mostarTrabajadores(Trabajador trabajadores[]){

    for(int i = 0; i<MAX_TRABAJADORES; i++){
        if(trabajadores[i].esta_inicializado == 1){
            printf("\tNombre: ");
            puts(trabajadores[i].nombre);
            printf("\tNNSS: ");
            puts(trabajadores[i].NNSS);
            printf("\tAno de nacimiento: %d\n\n", trabajadores[i].ano_nacimiento);
        }
    }
}

void leerOrdenesFichero(FILE *file){
    char nameFile[30];
    printf("Escriba el nombre del fichero del cual quiere leer las ordenes de trabajo: ");
    gets(nameFile);

    if((file = fopen(nameFile, "rb")) == NULL){
        printf(RED);
        printf("\t[x]Hubo un error al abrir el archivo en modo lectura binaria.\n");
        printf(COLOR_NORMAL);
    }
}
