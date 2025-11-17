#include "distancia.h"
#include <math.h>

float calcularDistancia(tipoDia dia1, tipoDia dia2) {
    float sumatorio = 0;

    //atributos numeroicos

    sumatorio += pow(dia1.minTemp - dia2.minTemp, 2);

    sumatorio += pow(dia1.maxTemp - dia2.maxTemp, 2);

    sumatorio += pow(dia1.rainfall - dia2.rainfall, 2);

    sumatorio += pow(dia1.windGustSpeed - dia2.windGustSpeed, 2);

    sumatorio += pow(dia1.humidity9am - dia2.humidity9am, 2);

    sumatorio += pow(dia1.pressure9am - dia2.pressure9am, 2);

    sumatorio += pow(dia1.humidity3pm - dia2.humidity3pm, 2);

    sumatorio += pow(dia1.pressure3pm - dia2.pressure3pm, 2);

    //atributo categorico
    //ci son diferentes suma 1, si son iguales suma 0
    sumatorio += (dia1.rainToday != dia2.rainToday);

    return sqrt(sumatorio);
}
