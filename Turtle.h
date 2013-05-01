#include "Motor.h"

#ifndef Turtle_H
#define	Turtle_H

const int TURN_LEFT = -1;
const int TURN_RIGHT = 1;
const int TURN_NONE = 0;

class Turtle {
    public:
        Turtle(int motorSxEnablePin,
                int motorSxInputPin1,
                int motorSxInputPin2,
                int motorDxEnablePin,
                int motorDxInputPin1,
                int motorDxInputPin2,
                int forwardDirection = HIGH):

            motorSx(motorSxEnablePin, motorSxInputPin1, motorSxInputPin2),
            motorDx(motorDxEnablePin, motorDxInputPin1, motorDxInputPin2),

            _lastPulsesSx(0),
            _lastPulsesDx(0),
            _enabled(false),
            _turning(false)
        {
                setDirection(forwardDirection);
        };
        Motor motorSx;
        Motor motorDx;

        /**
         * Set the speed the turtle should try to reach when moving.
         * 
         * @param target_speed
         * @return this turtle
         */
        Turtle &setSpeed(int targetSpeed);

        int getSpeed();

        /**
         * Set the direction to either LOW or HIGH.
         * 
         * Whether this means the turtle will go forward or backward depends
         * on the value of Turtle::_forwardDirection.
         * 
         * @param direction
         * @return this turtle
         */
        Turtle &setDirection(int direction);
        int getDirection();

        /**
         * Invert the direction of the turtle.
         * 
         * @return either LOW or HIGH, the new direction.
         */
        int flip();

        void periodic();

        bool isEnabled();
        Turtle &toggle();
        Turtle &enable();
        Turtle &disable();

        Turtle &turn(int direction);
        bool isTurning();


    private:
        int _direction;
        int _forwardDirection;
        int _targetSpeed;

        int _lastPulsesSx;
        int _lastPulsesDx;

        bool _enabled;
        bool _turning;

        int _getTurningSpeed();
};

#endif	/* Turtle_H */

