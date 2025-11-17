#include "fragmenta.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

tipoDia fragmenta(const char *string){

    tipoDia dia;
    char *token;
    char *string2 = strdup(string);

    // 1. MinTemp (atof)
    token = strtok(string2, ",");
    dia.minTemp = atof(token);

    // 2. MaxTemp
    token = strtok(NULL, ",");
    dia.maxTemp = atof(token);

    // 3. Rainfall
    token = strtok(NULL, ",");
    dia.rainfall = atof(token);

    // 4. WindGustSpeed
    token = strtok(NULL, ",");
    dia.windGustSpeed = atof(token);

    // 5. Humidity9am
    token = strtok(NULL, ",");
    dia.humidity9am = atof(token);

    // 6. Pressure9am
    token = strtok(NULL, ",");
    dia.pressure9am = atof(token);

    // 7. Humidity3pm
    token = strtok(NULL, ",");
    dia.humidity3pm = atof(token);

    // 8. Pressure3pm
    token = strtok(NULL, ",");
    dia.pressure3pm = atof(token);

    // 9. RainToday
    token = strtok(NULL, ",");
    dia.rainToday = atoi(token);

    // 10. RainTomorrow
    token = strtok(NULL, ",");
    dia.rainTomorrow = atoi(token);

    free(string2);
    return dia;
}
