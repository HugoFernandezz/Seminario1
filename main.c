#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"
#include "funcionalidades.h"
#define MAX_ORDENES           50   // Máximo de órdenes de trabajo
#define MAX_CUADRILLAS        20   // Máximo de cuadrillas en total
#define MAX_COOPERATIVAS      10   // Máximo de cooperativas
#define MAX_TRABAJADORES      100  // Máximo de trabajadores

int main()
{
    Orden_trabajo *orden_trabajos;
    Trabajador *trabajadores;
    Cooperativa cooperativas[MAX_COOPERATIVAS] = {0};
    Cuadrillas *cuadrillas;

    int orden_trabajos_contador = 0;
    int trabajadores_contador = 0;
    int cuadrillas_contador = 0;

    FILE *file;

    trabajadores = crearTrabajadores(trabajadores, &trabajadores_contador);

    int index = 0;

    while(index != 10){
        showMenu();
        scanf("%d", &index);
        fflush(stdin);
        switch(index){
        case 1:
            trabajadores = crearTrabajador(trabajadores, &trabajadores_contador);
            break;
        case 2:
            orden_trabajos = leerOrdenesFichero(file, orden_trabajos, &orden_trabajos_contador);
            break;
        case 3:
            eliminarOrden(orden_trabajos, file);   //TODO
            break;
        case 4:
            cuadrillas = leerCuadrilla(file, cuadrillas,trabajadores, &cuadrillas_contador);
            break;
        case 5:
            eliminarCuadrilla(file, cuadrillas);    //TODO
            break;
        case 6:
            guardar(file, cooperativas, trabajadores, orden_trabajos, cuadrillas);
            break;
        case 7:
            cargar(file, cooperativas, trabajadores, orden_trabajos, cuadrillas);   //TODO
            break;
        case 8:
            showMenuPrint();
            int index = 0;
            scanf("%d", &index);
            fflush(stdin);
            //Submenu
            switch(index){

                case 1:
                    mostarTrabajadores(trabajadores, trabajadores_contador);
                    break;
                case 2:
                    mostrarOrdenesTrabajo(orden_trabajos, cuadrillas, orden_trabajos_contador);
                    break;
                case 3:
                    mostrarCuadrillas(cuadrillas,trabajadores, cuadrillas_contador, trabajadores_contador);
                    break;
                case 4:
                    mostrarTrabajadoresTXT(trabajadores);
                    break;
                case 5:
                    mostrarOrdenesTrabajoTXT(orden_trabajos,cuadrillas);
                    break;
                case 6:
                    mostrarCuadrillasTXT(cuadrillas, trabajadores);
                    break;
                case 7:
                    break;
                default:
                    printError("Entrada no valida");
                    break;
                }

            break;
        case 9:
            guiaArchivos();
            break;
        case 10:
            printf("Saliendo...");
            return;
        default:
            printError("[x]Entrada no valida.\n\n");
            break;


        }
    }

    return 0;
}

void showMenu(){
    printf("============================================\n");
    printf("             MENU PRINCIPAL               \n");
    printf("============================================\n");
    printf("Elija la opcion que desea:\n");
    printf("   [1] Dar de alta un trabajador.\n");
    printf("   [2] Leer ordenes de trabajo (fichero.txt).\n");
    printf("   [3] Eliminar orden de trabajo (fichero.txt).\n");
    printf("   [4] Leer cuadrilla (fichero.txt).\n");
    printf("   [5] Eliminar cuadrilla (fichero.txt).\n");
    printf("   [6] Guardar informacion del sistema.\n");
    printf("   [7] Cargar informacion del sistema.\n");
    printf("   [8] Menu de listados.\n");
    printf("   [9] Guia de archivos.\n");
    printf("   [10] Salir.\n");
    printf("============================================\n");
}

void showMenuPrint(){
    printf("============================================\n");
    printf("           MENU DE LISTADOS               \n");
    printf("============================================\n");
    printf("LISTAR EN PANTALLA:\n");
    printf("   [1] Listar trabajadores.\n");
    printf("   [2] Listar ordenes de trabajo.\n");
    printf("   [3] Listar cuadrillas.\n");
    printf("--------------------------------------------\n");
    printf("LISTAR EN ARCHIVO DE TEXTO:\n");
    printf("   [4] Listar trabajadores (.txt).\n");
    printf("   [5] Listar ordenes de trabajo (.txt).\n");
    printf("   [6] Listar cuadrillas (.txt).\n");
    printf("--------------------------------------------\n");
    printf("   [7] <- Volver.\n");
    printf("============================================\n");
}


void guiaArchivos(){
    printf("========================================\n");
    printf("         GUIA DE ARCHIVOS               \n");
    printf("========================================\n");
    printf("[cuadrilla.txt]         --> Dar de alta cuadrillas\n");
    printf("[ordenes.txt]           --> Dar de alta las ordenes\n");
    printf("[eliminarCuadrilla.txt] --> Eliminar cuadrilla\n");
    printf("[eliminarOrden.txt]     --> Eliminar ordenes\n");
    printf("========================================\n\n");
}


Trabajador *crearTrabajadores(Trabajador *trabajadores, int *contador){

    //Creo directamente el espacio para 8 trabajadores, lo hago para poder testear la aplicacion rapido

    trabajadores = (Trabajador*) malloc(sizeof(Trabajador)*8);

    //Todos estos datos son inventados y generados por chatgpt
    trabajadores[*contador].NNSS = malloc(strlen("281234567830") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 0)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "281234567830");

    trabajadores[*contador].nombre = malloc(strlen("Juan Pérez") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 0)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "Juan Pérez");

    trabajadores[*contador].ano_nacimiento = 1980;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    // Trabajador 1
    trabajadores[*contador].NNSS = malloc(strlen("361234567860") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 1)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "361234567860");

    trabajadores[*contador].nombre = malloc(strlen("María López") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 1)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "María López");

    trabajadores[*contador].ano_nacimiento = 1981;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    // Trabajador 2
    trabajadores[*contador].NNSS = malloc(strlen("251234567830") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 2)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "251234567830");

    trabajadores[*contador].nombre = malloc(strlen("Carlos García") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 2)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "Carlos García");

    trabajadores[*contador].ano_nacimiento = 1982;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    // Trabajador 3
    trabajadores[*contador].NNSS = malloc(strlen("751234567880") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 3)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "751234567880");

    trabajadores[*contador].nombre = malloc(strlen("Ana Martínez") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 3)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "Ana Martínez");

    trabajadores[*contador].ano_nacimiento = 1983;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    // Trabajador 4
    trabajadores[*contador].NNSS = malloc(strlen("121234567820") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 4)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "121234567820");

    trabajadores[*contador].nombre = malloc(strlen("Miguel Rodríguez") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 4)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "Miguel Rodríguez");

    trabajadores[*contador].ano_nacimiento = 1984;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    // Trabajador 5
    trabajadores[*contador].NNSS = malloc(strlen("361234567810") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 5)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "361234567810");

    trabajadores[*contador].nombre = malloc(strlen("Laura Sánchez") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 5)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "Laura Sánchez");

    trabajadores[*contador].ano_nacimiento = 1985;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    // Trabajador 6
    trabajadores[*contador].NNSS = malloc(strlen("981234567880") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 6)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "981234567880");

    trabajadores[*contador].nombre = malloc(strlen("José Díaz") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 6)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "José Díaz");

    trabajadores[*contador].ano_nacimiento = 1986;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    // Trabajador 7
    trabajadores[*contador].NNSS = malloc(strlen("691234567810") + 1);
    if (!trabajadores[*contador].NNSS) { fprintf(stderr, "Error al asignar memoria para NNSS (trabajador 7)\n"); exit(1); }
    strcpy(trabajadores[*contador].NNSS, "691234567810");

    trabajadores[*contador].nombre = malloc(strlen("Sofía Hernández") + 1);
    if (!trabajadores[*contador].nombre) { fprintf(stderr, "Error al asignar memoria para nombre (trabajador 7)\n"); exit(1); }
    strcpy(trabajadores[*contador].nombre, "Sofía Hernández");

    trabajadores[*contador].ano_nacimiento = 1987;
    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    return trabajadores;
}
