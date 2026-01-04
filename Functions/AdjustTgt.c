/*
 *  Created By Simon Bergmann
 *
 *  Last Edit: 28/12-2025
 *
 *  Arguments:
 *      Tgt - (3D vector, components in <m>)
 *      Gun - (3D vector, components in <m>)
 *      *Adjust:
 *          .Range - (Adjustment along deflection, <m>)
 *          .Lat - (Adjustment perpendicular to deflection, <m>)
 *          .NS - (Adjustment North/South, positive/negative, <m>)
 *          .EW - (Adjustment East/West, positive/negative, <m>)
 *
 *  Returns:
 *      Adjusted Tgt - (3D Vector, components in <m>)
 *
 */

#include "../Headers/AdjustTgt.h"
#include "../Headers/VectorDir.h"
#include <math.h>
#include "structs.h"

Vector3D AdjustTgt(Vector3D Tgt, Vector3D Gun, struct Adjustments *Adjust) {

    Vector3D TempTgt = Tgt;

    if (Adjust->Range != 0 || Adjust->Lat != 0) {
        double TempDir = VectorDir(Gun, Tgt);

        double RangeXAdj = sin(TempDir) * Adjust->Range;
        double RangeYAdj = cos(TempDir) * Adjust->Range;
        double LatXAdj = cos(TempDir - M_PI/2) * Adjust->Lat;
        double LatYAdj = sin(TempDir - M_PI/2) * Adjust->Lat;

        TempTgt.x += RangeXAdj + LatXAdj;
        TempTgt.y += RangeYAdj + LatYAdj;
    }

    if (Adjust->NS != 0 || Adjust->EW != 0) {
        TempTgt.x += Adjust->EW;
        TempTgt.y += Adjust->NS;
    }

    return TempTgt;
}