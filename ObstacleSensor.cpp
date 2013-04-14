#include "ObstacleSensor.h"

int ObstacleSensor::getState() {
  return _state;
}

ObstacleSensor &ObstacleSensor::onStateChange(obstacleSensorStateChangeCallback callback) {
    _callback = callback;
    return *this;
}

bool ObstacleSensor::stateChanged() {
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

bool ObstacleSensor::operator==(ObstacleSensor &sensor) {
  return this == &sensor;
}
