#include "Compass.h"


float Compass::getHeading() {
    _compass.SetMeasurementMode(Measurement_SingleShot);
    MagnetometerScaled data = _compass.ReadScaledAxis();
    _compass.SetMeasurementMode(Measurement_Idle);
  
    float radians = atan2(data.YAxis, data.XAxis);
   
    // Correct for when signs are reversed.
    if(radians < 0) {
        radians += 2 * PI;
    }
   
    _heading = radians * 180/M_PI; 
    return _heading;
}

Compass &Compass::setup() {
    _compass = HMC5883L();
    _compass.SetScale(_scale);
    return *this;
}
