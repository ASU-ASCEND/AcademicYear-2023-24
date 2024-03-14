#include "MTK3339Sensor.h"

//Implementing virtual function: getSensorName()
const String& MTK3339Sensor::getSensorName() const {
  return nameCompiled;
}
//Implementing virtual function: verifyPin()
bool MTK3339Sensor::verifyPin() {
  return true;
}
//Implementing virtual function: readData()
String MTK3339Sensor::readData(){
  return ", ";
}
