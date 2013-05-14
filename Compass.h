#ifndef COMPASS_H
#define	COMPASS_H

#include "Compass.h"
#include "Wire.h"
#include "HMC5883L.h"

// Valid values: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1
#define DEFAULT_COMPASS_SCALE 0.88

class Compass {
    public:
        Compass(float scale = DEFAULT_COMPASS_SCALE): 
            _scale(scale) { };

        Compass &setup();
        float getHeading();

    private:
        float _scale;
        float _heading;
        HMC5883L _compass;
};



#endif	/* COMPASS_H */

