#include <stdio.h>
#include <stdlib.h>
#include "listaDinamicaDeDias.h"
#include "fragmenta.h"
#include "normalizacion.h"
#include "distancia.h"


void ejecutarK1(tipoListaDinamicaDeDias *lista, tipoDia diaObjetivo, celdaListaDeDias *celdaAIgnorar, int *mejorIndice, float *minDistancia, bool *clasePredicha) {

    celdaListaDeDias *recorrido = lista->ini;
    *minDistancia = 100000.0;
    *mejorIndice = -1;
    int i = 1;

    while (recorrido != NULL) {
        if (recorrido != celdaAIgnorar) { //para no comaprrse consigo mismo

            float dist = calcularDistancia(diaObjetivo, recorrido->elem);

            if (dist < *minDistancia) {
                *minDistancia = dist;
                *clasePredicha = recorrido->elem.rainTomorrow;
                *mejorIndice = i;
            }
        }
        recorrido = recorrido->sig;
        i++;
    }
}

int main() {
    tipoListaDinamicaDeDias listaDeDias;
    FILE *dataset;
    char *stringDia;
    tipoDia dia;
    int numeroDeDias = 0;
    int opcion;

    // 1. Inicializar la lista
    nuevaListaDinamicaDeDias(&listaDeDias);

    // 2. Abrir el archivo CSV limpio
    dataset = fopen("weatherAUS_limpio.csv", "r");
    if (dataset == NULL) {
        perror("Error: No se encuentra 'weatherAUS_limpio.csv'");
        return -1;
    }

    // Reservar memoria para leer líneas
    stringDia = (char*)malloc(256 * sizeof(char));

    // Saltar primer afila (nombre columnas)
    fscanf(dataset, " %[^\n]", stringDia);

    // 3. Cargar Datos
    printf("Cargando datos...\n");
    while (fscanf(dataset, " %[^\n]", stringDia) != EOF) {
        dia = fragmenta(stringDia);
        insertarListaDinamicaDeDias(&listaDeDias, dia);
        numeroDeDias++;
    }
    fclose(dataset);
    printf("Datos cargados: %d dias.\n", numeroDeDias);

    // 4. NORMALIZACIÓN
    // Esto transforma todos los datos a rango 0-1
    normalizarDataset(&listaDeDias);
    printf("Datos normalizados correctamente.\n");


    // --- MENÚ PRINCIPAL ---
    do {
        printf("\n------- MENU K-NN (K=1) -------- \n");
        printf("1 - Introducir un dia nuevo y clasificarlo (K=1)\n");
        printf("2 - Salir\n");
        printf("Escoja una opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            printf("\nIntroduzca los datos del dia (CSV):\n");
            printf("Formato: MinTemp,MaxTemp,Rainfall,WindGustSpeed,Hum9am,Pres9am,Hum3pm,Pres3pm,RainToday,RainTomorrow\n");
            printf("Ejemplo: 13.4,22.9,0.6,44.0,71.0,1007.7,22.0,1007.1,0,0\n");
            printf("> ");
            scanf("%s", stringDia);


            tipoDia nuevoDia = fragmenta(stringDia);
            celdaListaDeDias celda;
            celda.elem = nuevoDia;
            normalizarCelda(&listaDeDias, &celda);
            tipoDia nuevoDiaNorm = celda.elem;

            // Recorrer toda la lista para buscar el vecino más cercano
            int mejorIndice;
            float distanciaMin;
            bool prediccion;

            //funcion compra
            ejecutarK1(&listaDeDias, nuevoDiaNorm, NULL, &mejorIndice, &distanciaMin, &prediccion);

            printf("\n--- RESULTADO ---\n");
            printf("Vecino mas cercano: Indice %d (Distancia: %.4f)\n", mejorIndice, distanciaMin);

            char* predStr = prediccion ? "Yes" : "No";
            char* realStr = nuevoDia.rainTomorrow ? "Yes" : "No";

            printf("Prediccion: %s\n", predStr);
            printf("Realidad:   %s\n", realStr);

            if (prediccion == nuevoDia.rainTomorrow) {
                printf(">> CORRECTO\n");
            } else {
                printf(">> INCORRECTO\n");
            }
        }

    } while (opcion != 2);


    free(stringDia);
    vaciarListaDias(&listaDeDias);

    return 0;
}


