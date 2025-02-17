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
    Orden_trabajo orden_trabajos[MAX_ORDENES] = {0};
    Trabajador trabajadores[MAX_TRABAJADORES] = {0};
    Cooperativa cooperativas[MAX_COOPERATIVAS] = {0};
    Cuadrillas cuadrillas[MAX_CUADRILLAS] = {0};

    FILE *file;

    crearTrabajadores(trabajadores);

    int index = 0;

    while(index != 10){
        showMenu();
        scanf("%d", &index);
        fflush(stdin);
        switch(index){
        case 1:
            crearTrabajador(trabajadores);
            break;
        case 2:
            leerOrdenesFichero(file, orden_trabajos);
            break;
        case 3:
            eliminarOrden(orden_trabajos, file);
            break;
        case 4:
            leerCuadrilla(file, cuadrillas,trabajadores);
            break;
        case 5:
            eliminarCuadrilla(file, cuadrillas);
            break;
        case 6:
            guardar(file, cooperativas, trabajadores, orden_trabajos, cuadrillas);
            break;
        case 7:
            cargar(file, cooperativas, trabajadores, orden_trabajos, cuadrillas);
            break;
        case 8:
            showMenuPrint();
            int index = 0;
            scanf("%d", &index);
            fflush(stdin);
            //Submenu
            switch(index){

                case 1:
                    mostarTrabajadores(trabajadores);
                    break;
                case 2:
                    mostrarOrdenesTrabajo(orden_trabajos, cuadrillas);
                    break;
                case 3:
                    mostrarCuadrillas(cuadrillas,trabajadores);
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


void crearTrabajadores(Trabajador trabajadores[]){

// Le he pedido a la IA que me inicialice 8 trabajadores para aligerar los testeos
    strcpy(trabajadores[0].NNSS, "281234567830");
    strcpy(trabajadores[0].nombre, "Juan Pérez");
    trabajadores[0].ano_nacimiento = 1980;
    trabajadores[0].esta_inicializado = 1;

    strcpy(trabajadores[1].NNSS, "361234567860");
    strcpy(trabajadores[1].nombre, "María López");
    trabajadores[1].ano_nacimiento = 1981;
    trabajadores[1].esta_inicializado = 1;

    strcpy(trabajadores[2].NNSS, "251234567830");
    strcpy(trabajadores[2].nombre, "Carlos García");
    trabajadores[2].ano_nacimiento = 1982;
    trabajadores[2].esta_inicializado = 1;

    strcpy(trabajadores[3].NNSS, "751234567880");
    strcpy(trabajadores[3].nombre, "Ana Martínez");
    trabajadores[3].ano_nacimiento = 1983;
    trabajadores[3].esta_inicializado = 1;

    strcpy(trabajadores[4].NNSS, "121234567820");
    strcpy(trabajadores[4].nombre, "Miguel Rodríguez");
    trabajadores[4].ano_nacimiento = 1984;
    trabajadores[4].esta_inicializado = 1;

    strcpy(trabajadores[5].NNSS, "361234567810");
    strcpy(trabajadores[5].nombre, "Laura Sánchez");
    trabajadores[5].ano_nacimiento = 1985;
    trabajadores[5].esta_inicializado = 1;

    strcpy(trabajadores[6].NNSS, "981234567880");
    strcpy(trabajadores[6].nombre, "José Díaz");
    trabajadores[6].ano_nacimiento = 1986;
    trabajadores[6].esta_inicializado = 1;

    strcpy(trabajadores[7].NNSS, "691234567810");
    strcpy(trabajadores[7].nombre, "Sofía Hernández");
    trabajadores[7].ano_nacimiento = 1987;
    trabajadores[7].esta_inicializado = 1;

}
