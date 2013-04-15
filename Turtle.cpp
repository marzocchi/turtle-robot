#include "Arduino.h"
#include "Motor.h"
#include "Turtle.h"

int Turtle::flip() {
    setDirection(_direction == HIGH ? LOW : HIGH);
    return _direction;
}

Turtle &Turtle::setDirection(int direction) {
    motorSx.setDirection(direction);
    motorDx.setDirection(direction);
    return *this;
}

Turtle &Turtle::setSpeed(int targetSpeed) {
    _targetSpeed = targetSpeed;
    motorSx.setSpeed(targetSpeed);
    motorDx.setSpeed(targetSpeed);
    return *this;
}

int Turtle::getSpeed() {
    return _targetSpeed;
}

void Turtle::periodic() {
    int pulsesSx = motorSx.getPulses();
    int pulsesDx = motorDx.getPulses();

    // no corrections if not enabled nor while turning
    if (isTurning() || !isEnabled()) {
        motorSx.setSpeedCorrection(1);
        motorDx.setSpeedCorrection(1);
        return;
    }

    float r = 0;
    float sx = pulsesSx - _lastPulsesSx;
    float dx = pulsesDx - _lastPulsesDx;

    if (sx > dx) {
        r = dx / sx;
        motorSx.setSpeedCorrection(r);
        motorDx.setSpeedCorrection(1);
    } else if (dx > sx) {
        r = sx / dx;
        motorDx.setSpeedCorrection(r);
        motorSx.setSpeedCorrection(1);
    } else {
        motorSx.setSpeedCorrection(1);
        motorDx.setSpeedCorrection(1);
    }

    _lastPulsesSx = pulsesSx;
    _lastPulsesDx = pulsesDx;
}

Turtle &Turtle::enable() {
    _enabled = true;
    Serial.println("enabling motors");
    motorDx.enable();
    motorSx.enable();
    return *this;
}

Turtle &Turtle::disable() {
   _enabled = false;
   motorSx.disable();
   motorDx.disable();
   return *this;
}

bool Turtle::isEnabled() {
    return _enabled;
}

Turtle &Turtle::toggle() {
    if (isEnabled()) {
        disable(); 
    } else {
        enable();
    }
    return *this;
}

bool Turtle::isTurning() {
    return _turning;
}

Turtle &Turtle::turn(int direction) {
    switch (direction) {
        case TURN_NONE:
            motorSx.setSpeed(_targetSpeed).setDirection(_direction);
            motorDx.setSpeed(_targetSpeed).setDirection(_direction);
            _turning = false;
            break;
        case TURN_LEFT:
            _turning = true;
            motorSx.setSpeed(_getTurningSpeed()).setDirection(!_direction);
            motorDx.setSpeed(_getTurningSpeed()).setDirection(_direction);
            break;
        case TURN_RIGHT:
            _turning = true;
            motorSx.setSpeed(_getTurningSpeed()).setDirection(_direction);
            motorDx.setSpeed(_getTurningSpeed()).setDirection(!_direction);
            break;
    }
    return *this;
}

int Turtle::_getTurningSpeed() {
   int turningSpeed = round(_targetSpeed / 2);
   if (turningSpeed < 50) {
       turningSpeed = 50;
   }
   return turningSpeed;
}