#include "Arduino.h"
#include "Motor.h"

int Motor::pulse() {
    _pulses++;
    return _pulses;
}

int Motor::getPulses() {
    return _pulses;
}

bool Motor::isEnabled() {
    return _enabled;
}

Motor &Motor::disable() {
    _enabled = false;
    _writeToPins();
    return *this;
}

Motor &Motor::enable() {
    _pulses = 0;
    _speedCorrection = 1;
    _enabled = true;

    _writeToPins();
    return *this;
}

Motor &Motor::setSpeed(int targetSpeed) {
    if (targetSpeed < _minSpeed) {
        targetSpeed = 0;
    }
    _targetSpeed = targetSpeed;
    _writeToPins();
    return *this;
}

int Motor::getSpeed() {
    return _targetSpeed;
}

int Motor::getDirection() {
    return _direction;
}

Motor &Motor::setDirection(int direction) {
    _direction = direction;
    _writeToPins();
    return *this;
}

void Motor::_writeToPins() {

    if (_direction == HIGH) {
        digitalWrite(_inputPin1, HIGH);
        digitalWrite(_inputPin2, LOW);
    } else {
        digitalWrite(_inputPin1, LOW);
        digitalWrite(_inputPin2, HIGH);
    }
    if (_enabled) {
        // Serial.print("speed: ");
        // Serial.print(_targetSpeed);
        // Serial.print(", direction: ");
        // Serial.println(_direction);
        analogWrite(_enablePin, getCorrectedSpeed());
    } else {
        analogWrite(_enablePin, 0);
    }
}

Motor &Motor::setSpeedCorrection(float correction) {
    _speedCorrection = correction;
    _writeToPins();
    return *this;
}

float Motor::getSpeedCorrection() {
    return _speedCorrection;
}

int Motor::getCorrectedSpeed() {
    return round(_targetSpeed * _speedCorrection);
}

float Motor::getTraveledMeters() {
    static const float pi = 3.1416f;
    float circ = pi * _wheelDiameter; 
    return circ * _pulses / _ppr;
}
