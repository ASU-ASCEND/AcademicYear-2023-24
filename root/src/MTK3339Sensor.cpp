#include "MTK3339Sensor.h"

//Implementing virtual function: getSensorName()
const String& MTK3339Sensor::getSensorName() const {
<<<<<<< HEAD:root/src/MTK3339Sensor.cpp
  return nameCompiled;
=======
    return nameCompiled;
>>>>>>> main:root/include/MTK3339Sensor.cpp
}
//Implementing virtual function: getSensorType()
const String& MTK3339Sensor::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}
//Implementing virtual function: verifyPin()
<<<<<<< HEAD:root/src/MTK3339Sensor.cpp
bool MTK3339Sensor::verifyPin() {
  return true; 
}
//Implementing virtual function: readData()
String MTK3339Sensor::readData(){
  return ", ";
=======
bool MTK3339Sensor::verifyPin() override {
    return true;
}
//Implementing virtual function: readData()
String MTK3339Sensor::readData(){
>>>>>>> main:root/include/MTK3339Sensor.cpp
}
