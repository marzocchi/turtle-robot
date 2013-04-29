#ifndef MOTOR_H
#define	MOTOR_H

/**
 * Command a motor and its attached encoder
 * 
 * @param enable_pin 
 * @param input_pin1
 * @param input_pin2
 * @param forward_direction Either HIGH or LOW, defines the direction that
 *        we'll consider to be "forward"
 * @param encoderPpr Number of pulses that make up a full wheel revolution,
 *        for this motor's Encoder initialization
 * @param encoderWheelDiameter Wheel diameter, used by the Encoder to calculate
 *        the travelled distance
 */
class Motor {
    public:
        Motor(int enablePin, int inputPin1, int inputPin2, int forwardDirection = HIGH, float ppr = 20.0, float wheelDiameter = 0.065, int minSpeed = 10):  
            _enablePin(enablePin),
            _inputPin1(inputPin1),
            _inputPin2(inputPin2),
            _direction(forwardDirection),
            _ppr(ppr),
            _wheelDiameter(wheelDiameter),
            _minSpeed(minSpeed),
            _speedCorrection(1),
            _targetSpeed(0),
            _enabled(false),
            _pulses(0)
        {
            pinMode(_enablePin, OUTPUT);
            pinMode(_inputPin1, OUTPUT);
            pinMode(_inputPin2, OUTPUT);
        }

        Motor &setSpeed(int targetSpeed);
        int getSpeed();

        Motor &setSpeedCorrection(float correction);
        float getSpeedCorrection();

        int getCorrectedSpeed();
        
        Motor &setDirection(int direction);
        int getDirection();

        int pulse();

        int getPulses();
        float getTraveledMeters();

        bool isEnabled();

        Motor &enable();
        Motor &disable();

    private:
        int _enablePin;
        int _inputPin1;
        int _inputPin2;
        int _direction;
        float _ppr;
        float _wheelDiameter;
        int _minSpeed;
        float _speedCorrection;
        int _targetSpeed;

        bool _enabled;

        int _pulses;

        void _writeToPins();

};
#endif	/* MOTOR_H */
