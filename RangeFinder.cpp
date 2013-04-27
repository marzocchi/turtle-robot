#include "RangeFinder.h"

float RangeFinder::ping() {
    digitalWrite( _triggerPin, LOW );
    delayMicroseconds(2);
    digitalWrite( _triggerPin, HIGH );
    delayMicroseconds( 10 );
    digitalWrite( _triggerPin, LOW );

    float duration = pulseIn( _echoPin, HIGH );
    _range = duration / 29 / 2;

    if (!_threshold) {
        return _range;
    }

    bool shouldAlert = _range <= _threshold;

    if (shouldAlert != _alerted) {
        _alerted = shouldAlert;
        if (_alertCallback) {
            _alertCallback(*this);
        }
    }
    
    return _range;
}

RangeFinder &RangeFinder::onAlert(float threshold, rangeFinderAlertCallback alertCallback) {
    _threshold = threshold;
    _alertCallback = alertCallback;
    return *this;
}

bool RangeFinder::isAlerted() {
    return _alerted;
}

float RangeFinder::getRange() {
    return _range;
}