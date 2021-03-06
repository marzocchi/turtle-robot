#include "IRSensor.h"

int IRSensor::getState() {
  return _state;
}

IRSensor &IRSensor::onStateChange(irSensorCallback callback) {
    _callback = callback;
    return *this;
}

bool IRSensor::stateChanged() {
  int reading = digitalRead(_pin);
  bool changed = false;

  if (reading != _previousReading) {
    _lastCheckTime = millis();
  } 
  
  if ((millis() - _lastCheckTime) > _debounceDelay) {
    if (reading != _state) {
      _state = reading;
      changed = true;
      if (_callback) {
          _callback(*this);
      }
    }
  }
  
  _previousReading = reading;
    
  return changed;
}

bool IRSensor::operator==(IRSensor &sensor) {
  return this == &sensor;
}
