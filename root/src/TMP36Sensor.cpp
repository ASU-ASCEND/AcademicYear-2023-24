#include "TMP36Sensor.h"

//Implementing virtual function: getSensorName()
const String& TMP36Sensor::getSensorName() const {
  return nameCompiled;
}

//Implementing virtual function: verifyPin()
bool TMP36Sensor::verifyPin() {
  return true;
}
//Implementing virtual function: readData()
String TMP36Sensor::readData() {
  return ", ";
}
