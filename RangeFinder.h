#ifndef RANGEFINDER_H
#define	RANGEFINDER_H

#include <Arduino.h>

class RangeFinder;
typedef void (*rangeFinderAlertCallback)(RangeFinder &rangeFinder);

class RangeFinder {
    
    public: 
        RangeFinder(int triggerPin, int echoPin):
            _triggerPin(triggerPin),
            _echoPin(echoPin),
            _alerted(false)
        {
            pinMode(triggerPin, OUTPUT);    
            pinMode(echoPin, INPUT);    
        };

        RangeFinder &onAlert(float threshold, rangeFinderAlertCallback alertCallback);
        float ping();
        float getRange();
        bool isAlerted();

    private:
        int _triggerPin;
        int _echoPin;
        float _threshold;
        float _range;
        bool _alerted;
        rangeFinderAlertCallback _alertCallback;

};


#endif	/* RANGEFINDER_H */

