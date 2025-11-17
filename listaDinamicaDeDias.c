
#include "listaDinamicaDeDias.h"
#include <stdio.h>
#include <stdlib.h>


void nuevaListaDinamicaDeDias(tipoListaDinamicaDeDias *l)
{

	l->minMinTemp = 0;
	l->maxMinTemp = 0;
	l->minMaxTemp = 0;
	l->maxMaxTemp = 0;
	l->minRainfall = 0;
	l->maxRainfall = 0;
	l->minWindGustSpeed = 0;
	l->maxWindGustSpeed = 0;
	l->minHumidity9am = 0;
	l->maxHumidity9am = 0;
	l->minPressure9am = 0;
	l->maxPressure9am = 0;
	l->minHumidity3pm = 0;
	l->maxHumidity3pm = 0;
	l->minPressure3pm = 0;
	l->maxPressure3pm = 0;

	l->ini = NULL;
	l->fin = NULL;
}


void insertarListaDinamicaDeDias(tipoListaDinamicaDeDias *l, tipoElementoListaDinamicaDeDias e){
	celdaListaDeDias *nuevaCelda;


	if ((nuevaCelda=malloc(sizeof(celdaListaDeDias)))==NULL)
    {
        printf("no hay memoria para insertar\n");
		exit(-1);
    }
    nuevaCelda->elem = e;
    nuevaCelda->sig = NULL;


    if(esNulaListaDinamicaDeDias(*l)){
        l->ini = nuevaCelda;
        l->fin = nuevaCelda;
        l->minMinTemp = e.minTemp;
        l->maxMinTemp = e.minTemp;
        l->minMaxTemp = e.maxTemp;
        l->maxMaxTemp = e.maxTemp;
        l->minRainfall = e.rainfall;
        l->maxRainfall = e.rainfall;
        l->minWindGustSpeed = e.windGustSpeed;
        l->maxWindGustSpeed = e.windGustSpeed;
        l->minHumidity9am = e.humidity9am;
        l->maxHumidity9am = e.humidity9am;
        l->minPressure9am = e.pressure9am;
        l->maxPressure9am = e.pressure9am;
        l->minHumidity3pm = e.humidity3pm;
        l->maxHumidity3pm = e.humidity3pm;
        l->minPressure3pm = e.pressure3pm;
        l->maxPressure3pm = e.pressure3pm;

    } else {
        l->fin->sig = nuevaCelda;
        l->fin = nuevaCelda;


        if(l->minMinTemp > e.minTemp) l->minMinTemp = e.minTemp;
        else if(l->maxMinTemp < e.minTemp) l->maxMinTemp = e.minTemp;

        if(l->minMaxTemp > e.maxTemp) l->minMaxTemp = e.maxTemp;
        else if(l->maxMaxTemp < e.maxTemp) l->maxMaxTemp = e.maxTemp;

        if(l->minRainfall > e.rainfall) l->minRainfall = e.rainfall;
        else if(l->maxRainfall < e.rainfall) l->maxRainfall = e.rainfall;

        if(l->minWindGustSpeed > e.windGustSpeed) l->minWindGustSpeed = e.windGustSpeed;
        else if(l->maxWindGustSpeed < e.windGustSpeed) l->maxWindGustSpeed = e.windGustSpeed;

        if(l->minHumidity9am > e.humidity9am) l->minHumidity9am = e.humidity9am;
        else if(l->maxHumidity9am < e.humidity9am) l->maxHumidity9am = e.humidity9am;

        if(l->minPressure9am > e.pressure9am) l->minPressure9am = e.pressure9am;
        else if(l->maxPressure9am < e.pressure9am) l->maxPressure9am = e.pressure9am;

        if(l->minHumidity3pm > e.humidity3pm) l->minHumidity3pm = e.humidity3pm;
        else if(l->maxHumidity3pm < e.humidity3pm) l->maxHumidity3pm = e.humidity3pm;


        if(l->minPressure3pm > e.pressure3pm) l->minPressure3pm = e.pressure3pm;
        else if(l->maxPressure3pm < e.pressure3pm) l->maxPressure3pm = e.pressure3pm;
    }
}

void vaciarListaDias(tipoListaDinamicaDeDias *l){

	celdaListaDeDias *celdaRecorrido;
	celdaRecorrido = l->ini;


	l->minMinTemp = 0;
	l->maxMinTemp = 0;
	l->minMaxTemp = 0;
	l->maxMaxTemp = 0;
	l->minRainfall = 0;
	l->maxRainfall = 0;
	l->minWindGustSpeed = 0;
	l->maxWindGustSpeed = 0;
	l->minHumidity9am = 0;
	l->maxHumidity9am = 0;
	l->minPressure9am = 0;
	l->maxPressure9am = 0;
	l->minHumidity3pm = 0;
	l->maxHumidity3pm = 0;
	l->minPressure3pm = 0;
	l->maxPressure3pm = 0;

	int i = 1;
	while(celdaRecorrido != NULL){
		eliminarListaDinamicaDeDias(l, celdaRecorrido);
		i++;
		celdaRecorrido = l->ini;
	}
	l->ini = NULL;
	l->fin = NULL;
}


void eliminarListaDinamicaDeDias(tipoListaDinamicaDeDias *l, celdaListaDeDias *c){


	celdaListaDeDias *aux = l->ini;
    if(c != NULL){
        if(aux == c){
            l->ini = l->ini->sig;
            free(c);
        } else {
            while(aux->sig != c && aux != NULL){
                aux = aux->sig;
            }
            if(aux != NULL){
                if(aux->sig == c){
                aux->sig = c->sig;
                if(c->sig == NULL) l->fin = aux;
                free(c);
                } else printf("La celda introducida para eliminar no existe en la listaDinamicaDeDias\n");
            } else printf("La celda introducida para eliminar no existe en la listaDinamicaDeDias\n");
        }
    } else printf("El puntero introducido en eliminarListaDinamicaDeDias es Nulo\n");
}


bool esNulaListaDinamicaDeDias(tipoListaDinamicaDeDias l){
    return (l.ini == NULL);
}


void imprimirListaDinamicaDeDias(tipoListaDinamicaDeDias l){


	 if(esNulaListaDinamicaDeDias(l)){
        printf("La lista esta vacía \n");
    } else {

		celdaListaDeDias *aux;


		if ((aux=malloc(sizeof(celdaListaDeDias)))==NULL)
        {
            printf("No hay memoria para imprimirListaDinamicaDeDias\n");
            exit(-1);
        }
        aux = l.ini;
        int z = 1;
        while(aux!=NULL){
			printf("Indice: %d ", z);
            printf("MinTemp: %f ", aux->elem.minTemp);
            printf("MaxTemp: %f ", aux->elem.maxTemp);
            printf("Rainfall: %f ", aux->elem.rainfall);
            printf("WindGustSpeed: %f ", aux->elem.windGustSpeed);
            printf("Hum9am: %f ", aux->elem.humidity9am);
            printf("Pres9am: %f ", aux->elem.pressure9am);
            printf("Hum3pm: %f ", aux->elem.humidity3pm);
            printf("Pres3pm: %f ", aux->elem.pressure3pm);
            printf("RainToday: %d ", aux->elem.rainToday);
            printf("RainTomorrow: %d ", aux->elem.rainTomorrow);
            printf("\n");
            z++;
            aux = aux->sig;
        }
        printf("\n");
    }
}
