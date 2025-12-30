/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      *Atmosphere:
 *          .Temperature - (<Degrees C>)
 *          .Pressure - (<hPa>)
 *          .Humidity - (Relative Humidity <%>)
 *          .Wind - (2D Vector, components in <m/s>)
 *
 *  Returns:
 *      airDensity - (<kg * m^(-3)>)
 *
 */

#include "../Headers/airDensity.h"

#include <math.h>

double airDensity(struct Context *Atmosphere) {

    double airDensity;

    const double PressurePa = Atmosphere->Pressure * 100;

    if (Atmosphere->Humidity > 0) {
        const double pSat = 610.78 * pow(10, (7.5*Atmosphere->Temperature)/(Atmosphere->Temperature+237.3));
        const double vaporPressure = Atmosphere->Humidity * pSat;
        const double PP = PressurePa - vaporPressure;

        airDensity = (PP * 0.028964 + vaporPressure * 0.018016) / (8.314 * (Atmosphere->Temperature + 273.15));
    } else {
        airDensity = PressurePa / (287.058 * (Atmosphere->Temperature + 273.15));
    }

    return airDensity;
}