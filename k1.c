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


    //MENU PRINCIPAL
    do {
        printf("\n------- MENU K-NN (K=1) -------- \n");
        printf("1 - Introducir un dia nuevo y clasificarlo (K=1)\n");
        printf("2 - Comparar todos con todos, k=1 // Limite 1000\n");
        printf("3 - Salir\n");
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
        else if (opcion == 2) {
            int LIMITE_PRUEBA = 1000; //Limite 1000
            printf("\nComparar todos con todos, k=1 // Calculando Matriz de Confusión\n");

            int TP = 0;
            int TN = 0;
            int FP = 0;
            int FN = 0;

            int aciertos = 0;
            int totalEvaluados = 0;
            celdaListaDeDias *actual = listaDeDias.ini;

            int idx;
            float dist;
            bool pred;

            while(actual != NULL && totalEvaluados < LIMITE_PRUEBA) {
                ejecutarK1(&listaDeDias, actual->elem, actual, &idx, &dist, &pred);

                if (pred == actual->elem.rainTomorrow) {
                    aciertos++;
                }

                bool real = actual->elem.rainTomorrow;

                if (real == 1 && pred == 1) {
                    TP++; // Llovio y acertamos
                }
                else if (real == 0 && pred == 0) {
                    TN++; // No llovio y acertamos
                }
                else if (real == 0 && pred == 1) {
                    FP++; // Dijimos que llovia, pero no
                }
                else if (real == 1 && pred == 0) {
                    FN++; // Dijimos que no llovia, pero llovio
                }

                totalEvaluados++;
                actual = actual->sig; // Pasamos al siguiente dia


            }

            float accuracy = (float)(TP + TN) / totalEvaluados;
            float sensibilidad = (float)TP / (TP + FN);
            float especificidad = (float)TN / (TN + FP);
            float precision = (float)TP / (TP + FP);

            // --- IMPRESIÓN DE RESULTADOS ---
            printf("\n\n");
            printf("=========================================\n");
            printf("          MATRIZ DE CONFUSIÓN            \n");
            printf("=========================================\n");
            printf("                 | Pred: YES | Pred: NO |\n");
            printf("-----------------|-----------|----------|\n");
            printf(" Real: YES (1)   |   %4d    |   %4d   |\n", TP, FN);
            printf(" Real: NO  (0)   |   %4d    |   %4d   |\n", FP, TN);
            printf("=========================================\n\n");

            printf("--- MÉTRICAS DETALLADAS ---\n");
            printf("1. Accuracy (Exactitud):   %.2f%%\n", accuracy * 100.0);
            printf("2. Sensibilidad (Recall):  %.2f%%\n", sensibilidad * 100.0);
            printf("3. Especificidad:          %.2f%%\n", especificidad * 100.0);
            printf("4. Precision:              %.2f%%\n", precision * 100.0);
            printf("-----------------------------------------\n");
            printf("Total Evaluados: %d\n", totalEvaluados);

        }


    } while (opcion != 3);


    free(stringDia);
    vaciarListaDias(&listaDeDias);

    return 0;
}


