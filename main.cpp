#include <Arduino.h>
#include <PinChangeInt.h>
#include <TimerOne.h>
#include <Button.h>
#include <LED.h>
#include "Potentiometer.h"
#include "ObstacleSensor.h"
#include "Turtle.h"

// A0 is pin 14 on the UNO, and pin 54 on the mega.
// Mega interrupts: 
// External Interrupts: 2 (interrupt 0), 3 (interrupt 1), 18 (interrupt 5),
// 19 (interrupt 4), 20 (interrupt 3), and 21 (interrupt 2). 

#define MOTOR_DX_ENABLE_PIN 5
#define MOTOR_DX_DIRECTION_PIN 4
#define MOTOR_SX_ENABLE_PIN 6
#define MOTOR_SX_DIRECTION_PIN 7
#define ENCODER_SX_PIN 15
#define ENCODER_DX_PIN 16
#define IR_DX_PIN 8
#define IR_SX_PIN 12
#define SPEED_POT_PIN 14
#define SPEED_LED_PIN 11
#define ACTIVE_LED_PIN 13
#define SWITCH_PIN 10

Turtle turtle(MOTOR_SX_ENABLE_PIN, MOTOR_SX_DIRECTION_PIN, MOTOR_DX_ENABLE_PIN, MOTOR_DX_DIRECTION_PIN, LOW);
ObstacleSensor irSx(IR_SX_PIN, HIGH);
ObstacleSensor irDx(IR_DX_PIN, HIGH);
Button toggleSwitch(SWITCH_PIN, BUTTON_PULLDOWN);
LED speedLed(SPEED_LED_PIN);
LED activeLed(ACTIVE_LED_PIN);
Potentiometer speedPot(SPEED_POT_PIN);

int lastPrintTime;
bool obstructed;
bool ignoredFirstToggleClick = false;


void onPulseFromRightEncoder() {
    turtle.motorDx.pulse();
}

void onPulseFromLeftEncoder() {
    turtle.motorSx.pulse();
}

void onEachSecond() {
    turtle.applySpeedCorrections();
}

void onToggleButtonClick(Button &button) {
    if (!ignoredFirstToggleClick) {
        ignoredFirstToggleClick = true;
        return;
    }
    Serial.print("click at ");
    Serial.println(millis()); 
    turtle.toggle();
}

void onObstacleSensorStateChange(ObstacleSensor &sensor) {
    obstructed = irSx.getState() == LOW || irDx.getState() == LOW;
    activeLed.setValue(obstructed ? HIGH : LOW);

    if (obstructed) {
        turtle.turn(TURN_RIGHT);
    } else {
        turtle.turn(TURN_NONE);
    }

    Serial.println("Status change");
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

    Timer1.initialize();
    Timer1.attachInterrupt(onEachSecond);

    turtle.setSpeed(0);

    activeLed.blink(100, 3);
    speedLed.blink(100, 3);

    speedPot.setSectors(255);

    Serial.begin(9600);
    Serial.println("Hi.");
}


void loop() {
    // Update the state of the trigger button and the IR sensors
    toggleSwitch.isPressed();
    irSx.stateChanged();
    irDx.stateChanged();

    turtle.setSpeed(speedPot.getSector());

    analogWrite(SPEED_LED_PIN, turtle.getSpeed());

    return;

    if ((millis() - lastPrintTime) > 100) {
        Serial.print("ir: ");
        Serial.print(irSx.getState());
        Serial.print(", ");
        Serial.println(irDx.getState());

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

