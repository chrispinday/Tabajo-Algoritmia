#ifndef LISTADINAMICA_H
#define LISTADINAMICA_H

#include <stdbool.h>

typedef struct tipoDia {
    float minTemp;
    float maxTemp;
    float rainfall;
    float windGustSpeed;
    float humidity9am;
    float pressure9am;
    float humidity3pm;
    float pressure3pm;

    bool rainToday;
    bool rainTomorrow;
} tipoDia;


typedef tipoDia tipoElementoListaDinamicaDeDias;

typedef struct celdaL {
	tipoElementoListaDinamicaDeDias elem;
	struct celdaL *sig;
} celdaListaDeDias;

typedef struct tipoL {

    float minMinTemp;
    float maxMinTemp;
    float minMaxTemp;
    float maxMaxTemp;
    float minRainfall;
    float maxRainfall;
    float minWindGustSpeed;
    float maxWindGustSpeed;
    float minHumidity9am;
    float maxHumidity9am;
    float minHumidity3pm;
    float maxHumidity3pm;
    float minPressure9am;
    float maxPressure9am;
    float minPressure3pm;
    float maxPressure3pm;

	celdaListaDeDias *ini;
	celdaListaDeDias *fin;
} tipoListaDinamicaDeDias;


void nuevaListaDinamicaDeDias(tipoListaDinamicaDeDias *);
void insertarListaDinamicaDeDias(tipoListaDinamicaDeDias *, tipoElementoListaDinamicaDeDias);
void vaciarListaDias(tipoListaDinamicaDeDias *);
void eliminarListaDinamicaDeDias(tipoListaDinamicaDeDias *, celdaListaDeDias *);
bool esNulaListaDinamicaDeDias(tipoListaDinamicaDeDias);
void imprimirListaDinamicaDeDias(tipoListaDinamicaDeDias);

#endif
