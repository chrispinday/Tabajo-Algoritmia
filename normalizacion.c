#include <stdlib.h>
#include "normalizacion.h"


//normalziar toda la lista
void normalizarDataset(tipoListaDinamicaDeDias *entradaDeValores) {
    celdaListaDeDias *celdaRecorrido;
    celdaRecorrido = entradaDeValores->ini;


    while (celdaRecorrido != NULL) {
        normalizarCelda(entradaDeValores, celdaRecorrido);
        celdaRecorrido = celdaRecorrido->sig;
    }
}

// funcion que usa la formula: valor - Min / (Max-Min)
void normalizarCelda(tipoListaDinamicaDeDias *entradaDeValores, celdaListaDeDias *celdaTratar) {

    double rango;

    // 1. MinTemp
    rango = entradaDeValores->maxMinTemp - entradaDeValores->minMinTemp;
    if(rango != 0)
        celdaTratar->elem.minTemp = (celdaTratar->elem.minTemp - entradaDeValores->minMinTemp) / rango;
    else celdaTratar->elem.minTemp = 0;

    // 2. MaxTemp
    rango = entradaDeValores->maxMaxTemp - entradaDeValores->minMaxTemp;
    if(rango != 0)
        celdaTratar->elem.maxTemp = (celdaTratar->elem.maxTemp - entradaDeValores->minMaxTemp) / rango;
    else celdaTratar->elem.maxTemp = 0;

    // 3. Rainfall
    rango = entradaDeValores->maxRainfall - entradaDeValores->minRainfall;
    if(rango != 0)
        celdaTratar->elem.rainfall = (celdaTratar->elem.rainfall - entradaDeValores->minRainfall) / rango;
    else celdaTratar->elem.rainfall = 0;

    // 4. WindGustSpeed
    rango = entradaDeValores->maxWindGustSpeed - entradaDeValores->minWindGustSpeed;
    if(rango != 0)
        celdaTratar->elem.windGustSpeed = (celdaTratar->elem.windGustSpeed - entradaDeValores->minWindGustSpeed) / rango;
    else celdaTratar->elem.windGustSpeed = 0;

    // 5. Humidity9am
    rango = entradaDeValores->maxHumidity9am - entradaDeValores->minHumidity9am;
    if(rango != 0)
        celdaTratar->elem.humidity9am = (celdaTratar->elem.humidity9am - entradaDeValores->minHumidity9am) / rango;
    else celdaTratar->elem.humidity9am = 0;

    // 6. Pressure9am
    rango = entradaDeValores->maxPressure9am - entradaDeValores->minPressure9am;
    if(rango != 0)
        celdaTratar->elem.pressure9am = (celdaTratar->elem.pressure9am - entradaDeValores->minPressure9am) / rango;
    else celdaTratar->elem.pressure9am = 0;

    // 7. Humidity3pm
    rango = entradaDeValores->maxHumidity3pm - entradaDeValores->minHumidity3pm;
    if(rango != 0)
        celdaTratar->elem.humidity3pm = (celdaTratar->elem.humidity3pm - entradaDeValores->minHumidity3pm) / rango;
    else celdaTratar->elem.humidity3pm = 0;

    // 8. Pressure3pm
    rango = entradaDeValores->maxPressure3pm - entradaDeValores->minPressure3pm;
    if(rango != 0)
        celdaTratar->elem.pressure3pm = (celdaTratar->elem.pressure3pm - entradaDeValores->minPressure3pm) / rango;
    else celdaTratar->elem.pressure3pm = 0;
}
