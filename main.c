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

    while(index != 12){
        showMenu();
        scanf("%d", &index);
        fflush(stdin);
        switch(index){

        case 1:
            crearTrabajador(trabajadores);
            break;
        case 2:
            //DarDeBajaTrabajador();
            break;
        case 3:
            mostarTrabajadores(trabajadores);
            break;
        case 4:
            leerOrdenesFichero(file, orden_trabajos);
            break;
        case 5:
            mostrarOrdenesTrabajo(orden_trabajos);
            break;
        case 6:
            eliminarOrden(orden_trabajos, file);
            break;
        case 7:
            leerCuadrilla(file, cuadrillas,trabajadores);
            break;
        case 8:
            mostrarCuadrillas(cuadrillas);
            break;
        case 9:
            eliminarCuadrilla(file, cuadrillas);
            break;
        case 10:
            guardar(file, cooperativas, trabajadores, orden_trabajos, cuadrillas);
            break;
        case 11:
            cargar(file, cooperativas, trabajadores, orden_trabajos, cuadrillas);
            break;
        default:
            printError("[x]Entrada no valida.\n\n");
            break;


        }
    }

    return 0;
}

void showMenu(){
    printf("Elija la opcion que desea:\n\t[1] Dar de alta un trabajador.\n\t[2] Dar de baja un trabajador.\n\t[3] Mostrar trabajadores.\n\t[4] Leer ordenes de fichero.\n\t[5] Mostrar ordenes\n\t[6] Eliminar orden\n\t[7] Dar de alta cuadrilla\n\t[8] Mostrar cuadrillas\n\t[9] Eliminar cuadrilla\n\t[10] Guardar\n\t[11] Cargar\n");
}

void crearTrabajadores(Trabajador trabajadores[]){

// Le he pedido a la IA que me inicialice 8 trabajadores para aligerar los testeos
    strcpy(trabajadores[0].NNSS, "281234567830");
    strcpy(trabajadores[0].nombre, "Trabajador 1");
    trabajadores[0].ano_nacimiento = 1980;
    trabajadores[0].esta_inicializado = 1;

    strcpy(trabajadores[1].NNSS, "361234567860");
    strcpy(trabajadores[1].nombre, "Trabajador 2");
    trabajadores[1].ano_nacimiento = 1981;
    trabajadores[1].esta_inicializado = 1;

    strcpy(trabajadores[2].NNSS, "251234567830");
    strcpy(trabajadores[2].nombre, "Trabajador 3");
    trabajadores[2].ano_nacimiento = 1982;
    trabajadores[2].esta_inicializado = 1;

    strcpy(trabajadores[3].NNSS, "751234567880");
    strcpy(trabajadores[3].nombre, "Trabajador 4");
    trabajadores[3].ano_nacimiento = 1983;
    trabajadores[3].esta_inicializado = 1;

    strcpy(trabajadores[4].NNSS, "121234567820");
    strcpy(trabajadores[4].nombre, "Trabajador 5");
    trabajadores[4].ano_nacimiento = 1984;
    trabajadores[4].esta_inicializado = 1;

    strcpy(trabajadores[5].NNSS, "361234567810");
    strcpy(trabajadores[5].nombre, "Trabajador 6");
    trabajadores[5].ano_nacimiento = 1985;
    trabajadores[5].esta_inicializado = 1;

    strcpy(trabajadores[6].NNSS, "981234567880");
    strcpy(trabajadores[6].nombre, "Trabajador 7");
    trabajadores[6].ano_nacimiento = 1986;
    trabajadores[6].esta_inicializado = 1;

    strcpy(trabajadores[7].NNSS, "691234567810");
    strcpy(trabajadores[7].nombre, "Trabajador 8");
    trabajadores[7].ano_nacimiento = 1987;
    trabajadores[7].esta_inicializado = 1;

}
