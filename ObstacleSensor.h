#ifndef OBSTACLESENSOR_H
#define	OBSTACLESENSOR_H

#include <Arduino.h>

class ObstacleSensor;
typedef void (*obstacleSensorStateChangeCallback)(ObstacleSensor&);

class ObstacleSensor {

    public:
        ObstacleSensor(int pin, int initialState = 0, int debounceDelay = 50):
            _pin(pin), _state(initialState), _debounceDelay(debounceDelay) {}

        bool stateChanged();
        int getState();

        ObstacleSensor &onStateChange(obstacleSensorStateChangeCallback callback);

        bool operator==(ObstacleSensor &sensor);

    private:
        int _pin;
        int _state;
        int _previousReading;
        int _lastCheckTime;
        int _debounceDelay;
        obstacleSensorStateChangeCallback _callback;
    

};


#endif	/* OBSTACLESENSOR_H */
