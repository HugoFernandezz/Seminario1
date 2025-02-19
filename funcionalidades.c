#include "funcionalidades.h"
#include "Estructuras.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void printError(char text[300]){
    printf(RED);
    puts(text);
    printf(COLOR_NORMAL);
}

void printSucces(char text[300]){
    printf(GREEN);
    puts(text);
    printf(COLOR_NORMAL);
}

void limpiarSaltoDeLinea(char *str) {
   size_t len = strlen(str);
    while(len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }
}


Trabajador *crearTrabajador(Trabajador *trabajadores, int *contador){

    if(*contador >= MAX_TRABAJADORES){
        printError("Has alcanzado el maximo de trabajadores.");
        return NULL;
    }

    char buffer[255];

    if(*contador == 0){
        trabajadores = (Trabajador*) malloc(sizeof(Trabajador));
    }
    else{
        trabajadores = (Trabajador*) realloc(trabajadores, sizeof(Trabajador) * (*contador+1));
    }

    printf("Introduzca el nombre del trabajador: ");
    fgets(buffer, sizeof(buffer), stdin);
    limpiarSaltoDeLinea(buffer);
    trabajadores[*contador].nombre = malloc(strlen(buffer)+1);
    strcpy(trabajadores[*contador].nombre, buffer);

    printf("Introduzca el NNSS del trabajador: ");
    fgets(buffer, sizeof(buffer), stdin);
    limpiarSaltoDeLinea(buffer);
    trabajadores[*contador].NNSS = malloc(strlen(buffer)+1);
    strcpy(trabajadores[*contador].NNSS, buffer);

    printf("Introduzca el ano de nacimiento del trabajador: ");
    scanf("%d", &trabajadores[*contador].ano_nacimiento);

    trabajadores[*contador].esta_inicializado = 1;
    (*contador)++;

    return trabajadores;

}

void mostarTrabajadores(Trabajador trabajadores[], int contador){

    for(int i = 0; i<contador; i++){
        if(trabajadores[i].esta_inicializado == 1){
            printf("\tNombre: ");
            puts(trabajadores[i].nombre);
            printf("\tNNSS: ");
            puts(trabajadores[i].NNSS);
            printf("\tAno de nacimiento: %d\n\n", trabajadores[i].ano_nacimiento);
        }
    }
}

Orden_trabajo *leerOrdenesFichero(FILE *file, Orden_trabajo *ordenes, int *contador){
    char nameFile[30];
    char buffer[100];  //Aqui guardo la linea de cada archivo


    printf("Escriba el nombre del fichero del cual quiere leer las ordenes de trabajo: ");
    gets(nameFile);

    if((file = fopen(nameFile, "r")) == NULL){
        printError("\t[x]Hubo un error al abrir el archivo en modo lectura.\n");
        return NULL;
    }

    if(*contador == 0){
        ordenes = (Orden_trabajo*)malloc(sizeof(Orden_trabajo));
    }


    Orden_trabajo orden;
    int indiceLinea = 0;
    int indiceCuadrilla = 0;
    //Lee linea a linea
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        limpiarSaltoDeLinea(buffer);

        switch(indiceLinea){

            //Guardo el ID (primer campo)
            case 0:
                orden.clave = malloc(strlen(buffer)+1);
                strcpy(orden.clave, buffer);
                break;
            //Guardo la descripcion (segundo campo)
            case 1:
                orden.descripcion = malloc(strlen(buffer)+1);
                strcpy(orden.descripcion, buffer);
                break;
            //Guardo el año de creacion (tercer campo)
            case 2:
                orden.ano = atoi(buffer);
                break;
            //Guardo el numero de cuadrillas (cuarto campo)
            case 3:
                orden.numero_cuadrillas = atoi(buffer);
                break;
            default:
                //Recorro tantos campos como cuadrillas indicadas en el cuarto campo
                if (indiceLinea >= 4 && indiceCuadrilla < orden.numero_cuadrillas){
                    orden.cuadrillas[indiceCuadrilla] = malloc(strlen(buffer)+1);
                    if (!orden.cuadrillas[indiceCuadrilla]) {
                        fprintf(stderr, "Error al asignar memoria para cuadrilla.\n");
                        exit(1);
                    }
                    strcpy(orden.cuadrillas[indiceCuadrilla], buffer);
                    indiceCuadrilla++;
                }
                /*Ya hemos leido toda la estructura de dicha orden y reiniciamos el lector a 0 para que vuelva a leer
                desde la linea 0 de la siguiente estructura

                NOTA: las estructuras tienen un minimo de 4 lineas, + cuadrillas, por eso 3 (contando que empieza por 0 son 4) + las cuadrillas

                */

                //Entra en este if si ha terminado de leer la orden entera
                if(indiceLinea == (3+orden.numero_cuadrillas)){
                    //Guardo la orden reservando el espacio justo para una orden
                    ordenes = (Orden_trabajo*)realloc(ordenes,sizeof(orden) * (*contador+1));
                    printSucces("[+]Orden guardada con exito!");
                    ordenes[*contador] = orden;

                    //Sumo 1 al contador de elementos que tiene el array de ordenes
                    (*contador)++;

                    //Reinicio contadores
                    indiceLinea = -1;
                    indiceCuadrilla = 0;
                }
                break;
            }
            indiceLinea++;
    }
fclose(file);
return ordenes;

}


void mostrarOrdenesTrabajo(Orden_trabajo ordenes[], Cuadrillas cuadrillas[], int ordenes_contador){

    int cuadrillaEncontrada = 0;

    for(int i = 0; i<ordenes_contador;i++){
        if(ordenes[i].clave[0] != '\0'){
            cuadrillaEncontrada = 1;
            printf("--------------------------------------------\n");
            printf("Clave: ");
            puts(ordenes[i].clave);
            printf("Descripcion: ");
            puts(ordenes[i].descripcion);
            printf("Ano de creacion: %d\n", ordenes[i].ano);
            printf("Cantidad de cuadrillas: %d\n", ordenes[i].numero_cuadrillas);
            for(int j = 0; j<ordenes[i].numero_cuadrillas; j++){
                int encontrado = 0;
                for(int k = 0; k<MAX_CUADRILLAS;k++){
                    if(strcmp(ordenes[i].cuadrillas[j], cuadrillas[k].id)==0){
                        encontrado = 1;
                        puts(cuadrillas[k].nombre);
                    }
                }
                if(encontrado == 0) printError("Cuadrilla no registrada en el sistema");
            }
            printf("\n");
        }
    }

    if(cuadrillaEncontrada == 0){
        printError("[x]Todavia no hay ninguna orden de trabajo inicializada.\n");
    }

}


void eliminarOrden(Orden_trabajo ordenes[], FILE *file){

    printf("Escriba el nombre del archivo donde esta guardado las ordenes que quiera dar de baja: ");

    char nameFile[50];
    gets(nameFile);
    char buffer[50];

    file = fopen(nameFile, "r");

    if(file == NULL){
        printError("Hubo un error al abrir el archivo. Intentelo de nuevo.");
        return;
    }

    while(fgets(buffer,sizeof(buffer),file) != NULL){
        limpiarSaltoDeLinea(buffer);
        for(int i = 0; i<MAX_ORDENES; i++){
           if(strcmp(buffer, ordenes[i].clave) == 0){
                strcpy(ordenes[i].clave, "");
            }
        }
    }

    printSucces("Ordenes eliminadas con exito.");

    fclose(file);
}

int trabajadorExiste(char identificador[], Trabajador trabajadores[]){



    for(int i = 0; i<MAX_TRABAJADORES;i++){
        limpiarSaltoDeLinea(identificador);
        limpiarSaltoDeLinea(trabajadores[i].NNSS);
        if(strcmp(identificador, trabajadores[i].NNSS) == 0){
            return 1;
        }
    }
    return 0;
}

void guardarCuadrilla(Cuadrillas cuadrillas[], Cuadrillas cuadrilla){

    for(int i = 0; i<MAX_CUADRILLAS;i++){
        if(cuadrillas[i].id[0] == '\0'){
            cuadrillas[i] = cuadrilla;
            printSucces("[+]Cuadrilla guardada con exito!");
            break;
        }
    }

}


Cuadrillas *leerCuadrilla(FILE *file, Cuadrillas cuadrillas[], Trabajador trabajadores[], int *contador){

    printf("Escriba el nombre del archivo donde esta guardado las cuadrillas que quiera dar de baja: ");

    char nameFile[50];
    gets(nameFile);
    char buffer[50];
    int lineaLeida = 0;
    int indiceTrabajador = 0;

    file = fopen(nameFile, "r");

    if(file == NULL){
        printError("Hubo un error al abrir el archivo. Intentelo de nuevo.");
        return;
    }

    if(*contador == 0){
        cuadrillas = (Cuadrillas*) malloc(sizeof(Cuadrillas));
    }

    Cuadrillas cuadrilla;

    while(fgets(buffer, sizeof(buffer), file) != NULL){
        limpiarSaltoDeLinea(buffer);
        switch(lineaLeida){
        case 0:
            cuadrilla.id = malloc(strlen(buffer)+1);
            strcpy(cuadrilla.id, buffer);
            break;
        case 1:
            cuadrilla.nombre = malloc(strlen(buffer)+1);
            strcpy(cuadrilla.nombre, buffer);
            break;
        case 2:
            cuadrilla.numero_trabajadores = atoi(buffer);
            break;
        default:
            if(lineaLeida >= 3 && indiceTrabajador < cuadrilla.numero_trabajadores){
                if(trabajadorExiste(buffer, trabajadores) == 1){
                    cuadrilla.identificador[indiceTrabajador] = malloc(strlen(buffer)+1);
                    strcpy(cuadrilla.identificador[indiceTrabajador], buffer);
                    indiceTrabajador++;
                }
                else{
                    printError("Un trabajador apuntado en el texto no esta dado de alta.\nAsegurate de que todos los identificadores de trabajadores estan dados de alta");
                    return;
                }
            }

            if(lineaLeida == (2+cuadrilla.numero_trabajadores)){

                    cuadrillas = realloc(cuadrillas, sizeof(cuadrilla) * (*contador + 1));
                    cuadrillas[*contador] = cuadrilla;
                    printSucces("[+]Cuadrilla guardada con exito!");

                    (*contador)++;
                    lineaLeida = -1;
                    indiceTrabajador = 0;
                }
            break;
        }
        lineaLeida++;
    }

    return cuadrillas;
    fclose(file);
}

void mostrarCuadrillas(Cuadrillas cuadrillas[], Trabajador trabajadores[], int contador_cuadrilla, int contador_trabajadores){


    for(int i = 0; i<contador_cuadrilla;i++){
            printf("--------------------------------------------\n");
            puts(cuadrillas[i].id);
            puts(cuadrillas[i].nombre);
            printf("%d", cuadrillas[i].numero_trabajadores);
            printf("\n");
            for(int j=0; j<cuadrillas[i].numero_trabajadores;j++){
                int encontrado = 0;
                for(int k = 0; k<contador_trabajadores;k++){
                    if(strcmp(cuadrillas[i].identificador[j], trabajadores[k].NNSS) == 0){
                        encontrado = 1;
                        puts(trabajadores[k].nombre);
                    }
                }
                //Realmente nunca voy a entrar aqui ya que directamente el sistema no te deja dar de alta cuadrillas si entre ellas hay un trabajador que no esta en el sistema
                if(encontrado == 0){
                    printError("Trabajador no dado de alta en el sistema");
                }
            }
    }

    if(contador_cuadrilla == 0){
        printError("Aun no hay ninguna cuadrilla dada de alta.\n(Cuando vayas a dar de alta una cuadrilla asegurate de que los identificadores estan dados de alta.)");
    }

}

void eliminarCuadrilla(FILE *file, Cuadrillas cuadrillas[]){

    printf("Escriba el nombre del archivo donde esta guardado las ordenes que quiera borrar: ");

    char nameFile[50];
    gets(nameFile);
    char buffer[50];

    file = fopen(nameFile, "r");

    if(file == NULL){
        printError("Hubo un error al abrir el archivo. Intentelo de nuevo.");
        return;
    }

    while(fgets(buffer, sizeof(buffer), file)){
        limpiarSaltoDeLinea(buffer);
        for(int i = 0; i<MAX_CUADRILLAS;i++){
           if(strcmp(buffer,cuadrillas[i].id) == 0){
                strcpy(cuadrillas[i].id, "");
                printSucces("Cuadrilla borrada con exito.");
            }
        }
    }

    fclose(file);
}

void guardar(FILE *file, Cooperativa cooperativas[], Trabajador trabajadores[], Orden_trabajo ordenes[], Cuadrillas cuadrillas[]){

    printf("Escriba el nombre del archivo donde quiera guardar los datos: ");

    char nameFile[50];
    gets(nameFile);
    char buffer[50];

    file = fopen(nameFile, "wb");

    if(file == NULL){
        printError("Hubo un error al crear el archivo. Intentelo de nuevo.");
        return;
    }

    fwrite(cooperativas, sizeof(cooperativas[0]), MAX_COOPERATIVAS, file);
    fwrite(trabajadores, sizeof(trabajadores[0]), MAX_TRABAJADORES, file);
    fwrite(ordenes, sizeof(ordenes[0]), MAX_ORDENES, file);
    fwrite(cuadrillas, sizeof(cuadrillas[0]), MAX_CUADRILLAS, file);

    printSucces("Datos guardados con exito.");

    fclose(file);

}

void cargar(FILE *file, Cooperativa cooperativas[], Trabajador trabajadores[], Orden_trabajo ordenes[], Cuadrillas cuadrillas[]){

    printf("Escriba el nombre del archivo del que quiere cargar los datos: ");

    char nameFile[50];
    gets(nameFile);
    char buffer[50];

    file = fopen(nameFile, "rb");

    if(file == NULL){
        printError("Hubo un error al crear el archivo. Intentelo de nuevo.");
        return;
    }

    fread(cooperativas, sizeof(cooperativas[0]), MAX_COOPERATIVAS, file);
    fread(trabajadores, sizeof(trabajadores[0]), MAX_TRABAJADORES, file);
    fread(ordenes, sizeof(ordenes[0]), MAX_ORDENES, file);
    fread(cuadrillas, sizeof(cuadrillas[0]), MAX_CUADRILLAS, file);

    printSucces("Datos cargados con exito.");

    fclose(file);

}

void mostrarTrabajadoresTXT(Trabajador trabajadores[]){

    FILE *file = fopen("Trabajadores.txt", "w");

    if(file == NULL){
        printError("Hubo un error al crear el archivo. Intentelo de nuevo.");
        return;
    }

    for(int i = 0; i<MAX_TRABAJADORES; i++){
        if(trabajadores[i].esta_inicializado == 1){
            fprintf(file, "Nombre: %s\n", trabajadores[i].nombre);
            fprintf(file, "NNSS: %s\n", trabajadores[i].NNSS);
            fprintf(file, "Año de nacimiento: %d\n", trabajadores[i].ano_nacimiento);
            fprintf(file, "\n");
        }
    }

    printSucces("Contenido guardado exitosamente en Trabajadores.txt\n");

    fclose(file);
}

void mostrarOrdenesTrabajoTXT(Orden_trabajo ordenes[], Cuadrillas cuadrillas[]){

    int cuadrillaEncontrada = 0;

    FILE *file = fopen("OrdenesTrabajo.txt", "w");

    if(file == NULL){
        printError("Hubo un error al crear el archivo ""OrdenesTrabajo.txt""");
    }

    for(int i = 0; i<MAX_ORDENES;i++){
        if(ordenes[i].clave[0] != '\0'){
            cuadrillaEncontrada = 1;
            fprintf(file, "--------------------------------------------\n");
            fprintf(file, "Clave: %s\n", ordenes[i].clave);
            fprintf(file, "Descripcion: %s\n", ordenes[i].descripcion);
            fprintf(file, "Ano de creacion: %d\n", ordenes[i].ano);
            fprintf(file, "Cantidad de cuadrillas: %d\n", ordenes[i].numero_cuadrillas);
            for(int j = 0; j<ordenes[i].numero_cuadrillas; j++){
                int encontrado = 0;
                for(int k = 0; k<MAX_CUADRILLAS;k++){
                    if(strcmp(ordenes[i].cuadrillas[j], cuadrillas[k].id)==0){
                        encontrado = 1;
                        fprintf(file, "%s\n", cuadrillas[k].nombre);
                    }
                }
                if(encontrado == 0) fprintf(file, "Cuadrilla no registrada en el sistema\n");
            }
            fprintf(file, "\n");
        }
    }

    if(cuadrillaEncontrada == 0){
        printError("[x]Todavia no hay ninguna orden de trabajo inicializada.\n");
        fprintf(file, "No hay ninguna cuadrilla inicializada.");
    }

    printSucces("Contenido guardado exitosamente en OrdenesTrabajo.txt\n");

    fclose(file);
}

void mostrarCuadrillasTXT(Cuadrillas cuadrillas[], Trabajador trabajadores[]){

    int cuadrillaEncontrada = 0;

    FILE *file = fopen("CuadrillasMostradas.txt", "w");

    if(file == NULL){
        printError("Hubo un error al crear el archivo ""CuadrillasMostradas.txt""");
    }

    int cuadrillasEncontradas = 0;

    for(int i = 0; i<MAX_CUADRILLAS;i++){
        if(cuadrillas[i].id[0] != '\0'){
            fprintf(file, "--------------------------------------------\n");
            cuadrillasEncontradas++;
            fprintf(file, "%s\n", cuadrillas[i].id);
            fprintf(file, "%s\n", cuadrillas[i].nombre);
            fprintf(file, "%d", cuadrillas[i].numero_trabajadores);
            fprintf(file, "\n");
            for(int j=0; j<cuadrillas[i].numero_trabajadores;j++){
                int encontrado = 0;
                for(int k = 0; k<MAX_TRABAJADORES;k++){
                    if(strcmp(cuadrillas[i].identificador[j], trabajadores[k].NNSS) == 0){
                        encontrado = 1;
                        fprintf(file, "%s\n", trabajadores[k].nombre);
                    }
                }
                //Realmente nunca voy a entrar aqui ya que directamente el sistema no te deja dar de alta cuadrillas si entre ellas hay un trabajador que no esta en el sistema
                if(encontrado == 0){
                    fprintf(file, "Trabajador no dado de alta en el sistema");
                }
            }
        }
    }

    if(cuadrillasEncontradas == 0){
        printError("Aun no hay ninguna cuadrilla dada de alta.\n(Cuando vayas a dar de alta una cuadrilla asegurate de que los identificadores estan dados de alta.)");
        fprintf(file, "Aun no hay ninguna cuadrilla dada de alta.\n(Cuando vayas a dar de alta una cuadrilla asegurate de que los identificadores estan dados de alta.)");
    }

    fclose(file);
    printSucces("Contenido guardado exitosamente en CuadrillasMostradas.txt\n");
}
