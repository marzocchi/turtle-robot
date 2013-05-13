#include <Arduino.h>
#include <PinChangeInt.h>
#include <TimerOne.h>
#include <Button.h>
#include <LED.h>
#include "Potentiometer.h"
#include "IRSensor.h"
#include "RangeFinder.h"
#include "Turtle.h"

// A0 is pin 14 on the UNO, and pin 54 on the mega.
// Mega interrupts: 
// External Interrupts: 2 (interrupt 0), 3 (interrupt 1), 18 (interrupt 5),
// 19 (interrupt 4), 20 (interrupt 3), and 21 (interrupt 2). 

#define MOTOR_DX_ENABLE_PIN 9
#define MOTOR_DX_INPUT_PIN1 31
#define MOTOR_DX_INPUT_PIN2 30
#define MOTOR_SX_ENABLE_PIN 10
#define MOTOR_SX_INPUT_PIN1 32
#define MOTOR_SX_INPUT_PIN2 33

#define IR_DX_PIN 12
#define IR_SX_PIN 8
#define SPEED_LED_PIN 6
#define ACTIVE_LED_PIN 13
#define SWITCH_PIN 48

#define ULTRASOUND_TRIGGER 23
#define ULTRASOUND_ECHO 67

#define SPEED_POT_PIN 64
#define ENCODER_SX_PIN 65
#define ENCODER_DX_PIN 66


Turtle turtle(MOTOR_SX_ENABLE_PIN,
        MOTOR_SX_INPUT_PIN1,
        MOTOR_SX_INPUT_PIN2,
        MOTOR_DX_ENABLE_PIN,
        MOTOR_DX_INPUT_PIN1,
        MOTOR_DX_INPUT_PIN2,
        HIGH);

IRSensor irSx(IR_SX_PIN, HIGH);
IRSensor irDx(IR_DX_PIN, HIGH);
Button toggleSwitch(SWITCH_PIN, BUTTON_PULLUP_INTERNAL);
LED speedLed(SPEED_LED_PIN);
LED activeLed(ACTIVE_LED_PIN);
Potentiometer speedPot(SPEED_POT_PIN);
RangeFinder rangeFinder(ULTRASOUND_TRIGGER, ULTRASOUND_ECHO);

int lastPrintTime;
int speedPotValue;

unsigned char obstruction;
enum Obstructions {
    ObSx = 0x01,
    ObDx = 0x02,
    ObFront = 0x04
};

void onPulseFromRightEncoder() {
    turtle.motorDx.pulse();
}

void onPulseFromLeftEncoder() {
    turtle.motorSx.pulse();
}

void onEachSecond() {
    turtle.periodic();
}

void onToggleButtonClick(Button &button) {
    turtle.toggle();

    if (turtle.isEnabled()) {
        Timer1.attachInterrupt(onEachSecond);
    } else {
        Timer1.detachInterrupt();
    }
}

void onObstacleDetected() {
    obstruction = 0;

    if (irSx.getState() == LOW) {
        obstruction |= ObSx;
    } 

    if (irDx.getState() == LOW) {
        obstruction |= ObDx;
    }

    if (rangeFinder.isAlerted()) {
        obstruction |= ObFront;
    }
}

void onIRSensorStateChange(IRSensor &sensor) {
    onObstacleDetected();
}

void onRangeFinderAlertStateChange(RangeFinder &rangeFinder) {
    onObstacleDetected();
}

void handleObstacle() {
    if (obstruction == 0) {
        turtle.turn(TURN_NONE);
        return;
    }

    if (obstruction == ObDx) {

        // Turn left because there is obstacle on the right
        turtle.turn(TURN_LEFT);

    } else if ( (obstruction & ObDx) && (obstruction & ObFront) ) {

        // Turn left because there is obstacle both on the right and front
        turtle.turn(TURN_LEFT);

    } else if (obstruction == ObSx) {

        // Turn right because there is obstacle on the left
        turtle.turn(TURN_RIGHT);

    } else if ( (obstruction & ObSx) && (obstruction & ObFront) ) {

        // Turn right because there is obstacle both on the left and front
        turtle.turn(TURN_RIGHT);

    } else if ( (obstruction & ObFront) || ( (obstruction & ObSx) && (obstruction & ObDx) ) ) {

        // there is an obstacle up ahead, backtrack until we are clear or
        // for a second, then perform a small turn

        turtle.flip();
        delay(1000);
        turtle.flip();

        turtle.turn(TURN_RIGHT);
        delay(600);
        turtle.turn(TURN_NONE);
    }
}

void setup() {
    digitalWrite(SPEED_POT_PIN, HIGH); // pull up

    pinMode(ENCODER_SX_PIN, INPUT);
    digitalWrite(ENCODER_SX_PIN, HIGH); // pull up
    PCintPort::attachInterrupt(ENCODER_SX_PIN, onPulseFromLeftEncoder, CHANGE);

    pinMode(ENCODER_DX_PIN, INPUT);
    digitalWrite(ENCODER_DX_PIN, HIGH); // pull up
    PCintPort::attachInterrupt(ENCODER_DX_PIN, onPulseFromRightEncoder, CHANGE);

    pinMode(IR_SX_PIN, INPUT);
    pinMode(IR_DX_PIN, INPUT);

    toggleSwitch.clickHandler(onToggleButtonClick);
    irSx.onStateChange(onIRSensorStateChange);
    irDx.onStateChange(onIRSensorStateChange);

    rangeFinder.onAlert(10, onRangeFinderAlertStateChange);

    Timer1.initialize();

    turtle.setSpeed(0);

    activeLed.blink(100, 3);
    speedLed.blink(100, 3);

    Serial.begin(9600);
    Serial.println("Hi.");
}

void loop() {
    // Update the state of the trigger button and sensors
    toggleSwitch.isPressed();
    irSx.stateChanged();
    irDx.stateChanged();
    rangeFinder.ping();

    // make speed vary by increments of 5, to avoid insignificant changes
    // to the turtle and motor state when the pot floats
    speedPotValue = map(speedPot.getValue(), 0, 1023, 0, 52) * 5;
    turtle.setSpeed(speedPotValue);
    analogWrite(SPEED_LED_PIN, turtle.getSpeed());


    // Handle obstacles
    activeLed.setValue(obstruction);
    handleObstacle();

    int timeDiff = millis() - lastPrintTime;
    if (timeDiff > 500) {
        Serial.print("enabled: ");
        Serial.print(turtle.isEnabled());
        Serial.print(", turning: ");
        Serial.print(turtle.isTurning());
        Serial.print(", pulses sx: ");
        Serial.print(turtle.motorSx.getPulses());
        Serial.print(", dx: ");
        Serial.print(turtle.motorDx.getPulses());
        Serial.print(", speed sx: ");
        Serial.print(turtle.motorSx.getCorrectedSpeed());
        Serial.print(", dx: ");
        Serial.print(turtle.motorDx.getCorrectedSpeed());

        Serial.println("");
        lastPrintTime = millis();
    }

}

