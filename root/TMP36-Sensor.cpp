#include <TMP36-Sensor.h"

//Implementing virtual function: getSensorName()
const String& TMP36-Sensor::getSensorName() const {
  return nameCompiled;
}
