#include <Arduino.h>
#include <PinChangeInt.h>
#include <TimerOne.h>
#include <Button.h>
#include <LED.h>
#include "Potentiometer.h"
#include "ObstacleSensor.h"
#include "RangeFinder.h"
#include "Turtle.h"

// A0 is pin 14 on the UNO, and pin 54 on the mega.
// Mega interrupts: 
// External Interrupts: 2 (interrupt 0), 3 (interrupt 1), 18 (interrupt 5),
// 19 (interrupt 4), 20 (interrupt 3), and 21 (interrupt 2). 

#define MOTOR_DX_ENABLE_PIN 9
#define MOTOR_DX_INPUT_PIN1 30
#define MOTOR_DX_INPUT_PIN2 31
#define MOTOR_SX_ENABLE_PIN 10
#define MOTOR_SX_INPUT_PIN1 33
#define MOTOR_SX_INPUT_PIN2 32

#define IR_DX_PIN 12
#define IR_SX_PIN 8
#define SPEED_LED_PIN 6
#define ACTIVE_LED_PIN 13
#define SWITCH_PIN 48

#define ULTRASOUND_TRIGGER 23
#define ULTRASOUND_ECHO 22

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

ObstacleSensor irSx(IR_SX_PIN, HIGH);
ObstacleSensor irDx(IR_DX_PIN, HIGH);
Button toggleSwitch(SWITCH_PIN, BUTTON_PULLUP_INTERNAL);
LED speedLed(SPEED_LED_PIN);
LED activeLed(ACTIVE_LED_PIN);
Potentiometer speedPot(SPEED_POT_PIN);
// RangeFinder rangeFinder(ULTRASOUND_TRIGGER, ULTRASOUND_ECHO);

int lastPrintTime;
int speedPotValue;
bool obstructed;


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
    Serial.println("click");
    turtle.toggle();

    if (turtle.isEnabled()) {
        Timer1.attachInterrupt(onEachSecond);
    } else {
        Timer1.detachInterrupt();
    }
}

void onObstacleSensorStateChange(ObstacleSensor &sensor) {
    obstructed = irSx.getState() == LOW || irDx.getState() == LOW;
    activeLed.setValue(obstructed ? HIGH : LOW);
    int turnDirection = sensor == irSx ? TURN_RIGHT : TURN_LEFT;

    if (obstructed) {
        turtle.turn(turnDirection);
    } else {
        turtle.turn(TURN_NONE);
    }
}

void unstuck() {
    Serial.println("Unstuck!");
    turtle.turn(TURN_NONE);
    Timer1.attachInterrupt(onEachSecond);
}

void onTurtleIsStuck(Turtle &turtle) {
    Serial.println("Stuck!");
    turtle.turn(TURN_LEFT);
    Timer1.attachInterrupt(unstuck);
}

void onRangeFinderAlertStateChange(RangeFinder &rangeFinder) {
    return;
    activeLed.setValue( rangeFinder.isAlerted() ? HIGH : LOW );

    if (turtle.isEnabled()) {
        turtle.turn(rangeFinder.isAlerted() ? TURN_LEFT : TURN_NONE);
    }

    Serial.print("Alert: ");
    Serial.print(rangeFinder.isAlerted());
    Serial.print(", range: ");
    Serial.println(rangeFinder.getRange());
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
    irSx.onStateChange(onObstacleSensorStateChange);
    irDx.onStateChange(onObstacleSensorStateChange);

    // rangeFinder.onAlert(15, onRangeFinderAlertStateChange);

    Timer1.initialize();

    turtle.setSpeed(0);
    turtle.whenStuck(onTurtleIsStuck);

    activeLed.blink(100, 3);
    speedLed.blink(100, 3);

    Serial.begin(9600);
    Serial.println("Hi.");
    turtle.enable();
}

void loop() {
    // Update the state of the trigger button and the IR sensors
    toggleSwitch.isPressed();
    irSx.stateChanged();
    irDx.stateChanged();

    speedPotValue = map(speedPot.getValue(), 0, 1023, 0, 255);

    // write speed only if it differs more than 5 from current speed
    if (abs(speedPotValue - turtle.getSpeed()) > 5) {
        turtle.setSpeed(speedPotValue);
        analogWrite(SPEED_LED_PIN, turtle.getSpeed());
    }

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
        
        // Serial.print("Target speed: ");
        // Serial.print(turtle.getSpeed());
        // Serial.print(", speed sx: ");
        // Serial.print(turtle.motorSx.getCorrectedSpeed());
        // Serial.print(", dx: ");
        // Serial.println(turtle.motorDx.getCorrectedSpeed());

        //Serial.print(", obstructed sx: ");
        //Serial.print(obstructedSx);
        //Serial.print(", dx: ");
        //Serial.println(obstructedDx);

        lastPrintTime = millis();
    }

}

