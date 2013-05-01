#ifndef IRSENSOR_H
#define	IRSENSOR_H

#include <Arduino.h>

class IRSensor;
typedef void (*irSensorCallback)(IRSensor&);

class IRSensor {

    public:
        IRSensor(int pin, int initialState = 0, int debounceDelay = 50):
            _pin(pin), _state(initialState), _debounceDelay(debounceDelay) {}

        bool stateChanged();
        int getState();

        IRSensor &onStateChange(irSensorCallback callback);

        bool operator==(IRSensor &sensor);

    private:
        int _pin;
        int _state;
        int _previousReading;
        int _lastCheckTime;
        int _debounceDelay;
        irSensorCallback _callback;
    

};


#endif	/* IRSENSOR_H */
