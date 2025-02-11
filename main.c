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

    int index = 0;

    while(index != 5){
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
            leerOrdenesFichero(file);
            break;
        case 5:
            break;
        default:
            printf("[x]Entrada no valida.[x]\n\n");
            break;


        }
    }

    return 0;
}

void showMenu(){
    printf("Elija la opcion que desea:\n\t[1] Dar de alta un trabajador.\n\t[2] Dar de baja un trabajador.\n\t[3] Mostrar trabajadores.\n\t[4] Leer ordenes de fichero.\n");
}
