#include "funcionalidades.h"
#include "Estructuras.h"
#include <stdio.h>
#include <string.h>

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
            printSucces("\t[*]Trabajador dado de alta correctamente!\n");
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

void leerOrdenesFichero(FILE *file, Orden_trabajo ordenes[]){
    char nameFile[30];
    char buffer[100];  //Aqui guardo la linea de cada archivo


    printf("Escriba el nombre del fichero del cual quiere leer las ordenes de trabajo: ");
    gets(nameFile);

    if((file = fopen(nameFile, "rb")) == NULL){
        printError("\t[x]Hubo un error al abrir el archivo en modo lectura binaria.\n");
        return;
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
                strcpy(orden.clave, buffer);
                break;
            //Guardo la descripcion (segundo campo)
            case 1:
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
                    strcpy(orden.cuadrillas[indiceCuadrilla], buffer);
                    indiceCuadrilla++;
                }
                /*Ya hemos leido toda la estructura de dicha orden y reiniciamos el lector a 0 para que vuelva a leer
                desde la linea 0 de la siguiente estructura

                NOTA: las estructuras tienen un minimo de 4 lineas, + cuadrillas, por eso 3 (contando que empieza por 0 son 4) + las cuadrillas

                */

                if(indiceLinea == (3+orden.numero_cuadrillas)){
                    guardarOrdenTrabajo(orden, ordenes);
                    indiceLinea = -1;
                    indiceCuadrilla = 0;
                }
                break;
            }
            indiceLinea++;
    }

fclose(file);

}

void guardarOrdenTrabajo(Orden_trabajo orden, Orden_trabajo ordenes[]){
    //Busco el primer hueco libre en el array de ordenes para guardalo ahi
    for(int i = 0; i<MAX_ORDENES; i++){
        if(ordenes[i].clave[0] == '\0'){
            ordenes[i] = orden;
            printSucces("[+]Orden guardada con exito!");
            break;
        }
    }
}

void mostrarOrdenesTrabajo(Orden_trabajo ordenes[]){

    int cuadrillaEncontrada = 0;

    for(int i = 0; i<MAX_ORDENES;i++){
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
                puts(ordenes[i].cuadrillas[j]);
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

    file = fopen(nameFile, "rb");

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


void leerCuadrilla(FILE *file, Cuadrillas cuadrillas[], Trabajador trabajadores[]){

    printf("Escriba el nombre del archivo donde esta guardado las cuadrillas que quiera dar de baja: ");

    char nameFile[50];
    gets(nameFile);
    char buffer[50];
    int lineaLeida = 0;
    int indiceTrabajador = 0;

    file = fopen(nameFile, "rb");

    if(file == NULL){
        printError("Hubo un error al abrir el archivo. Intentelo de nuevo.");
        return;
    }

    Cuadrillas cuadrilla;

    while(fgets(buffer, sizeof(buffer), file) != NULL){
        limpiarSaltoDeLinea(buffer);
        switch(lineaLeida){
        case 0:
            strcpy(cuadrilla.id, buffer);
            break;
        case 1:
            strcpy(cuadrilla.nombre, buffer);
            break;
        case 2:
            cuadrilla.numero_trabajadores = atoi(buffer);
            break;
        default:
            if(lineaLeida >= 3 && indiceTrabajador < cuadrilla.numero_trabajadores){
                if(trabajadorExiste(buffer, trabajadores) == 1){
                    strcpy(cuadrilla.identificador[indiceTrabajador], buffer);
                    indiceTrabajador++;
                }
                else{
                    printError("Un trabajador apuntado en el texto no esta dado de alta.\nAsegurate de que todos los identificadores de trabajadores estan dados de alta");
                    return;
                }
            }

            if(lineaLeida == (2+cuadrilla.numero_trabajadores)){
                    guardarCuadrilla(cuadrillas, cuadrilla);
                    lineaLeida = -1;
                    indiceTrabajador = 0;
                }
            break;
        }
        lineaLeida++;
    }

    fclose(file);
}

void mostrarCuadrillas(Cuadrillas cuadrillas[]){

    int cuadrillasEncontradas = 0;

    for(int i = 0; i<MAX_CUADRILLAS;i++){
        if(cuadrillas[i].id[0] != '\0'){
            printf("--------------------------------------------\n");
            cuadrillasEncontradas++;
            puts(cuadrillas[i].id);
            puts(cuadrillas[i].nombre);
            printf("%d", cuadrillas[i].numero_trabajadores);
            for(int j=0; j<cuadrillas[i].numero_trabajadores;j++){
                puts(cuadrillas[i].identificador[j]);
            }
        }
    }

    if(cuadrillasEncontradas == 0){
        printError("Aun no hay ninguna cuadrilla dada de alta.\n(Cuando vayas a dar de alta una cuadrilla asegurate de que los identificadores estan dados de alta.)");
    }

}

void eliminarCuadrilla(FILE *file, Cuadrillas cuadrillas[]){

    printf("Escriba el nombre del archivo donde esta guardado las ordenes que quiera borrar: ");

    char nameFile[50];
    gets(nameFile);
    char buffer[50];

    file = fopen(nameFile, "rb");

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
