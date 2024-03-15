#include <TMP36Sensor.h>

//Implementing virtual function: getSensorName()
const String& TMP36Sensor::getSensorName() const {
  return nameCompiled;
}

//Implementing virtual function: getSensorCSVHeader()
const String& TMP36Sensor::getSensorCSVHeader() const {
  return csvHeaderCompiled;
}

//Implementing virtual function: verifyPin()
bool TMP36Sensor::verifyPin() {
  // return false;
    return false;
}
//Implementing virtual function: readData()
String TMP36Sensor::readData(){
}