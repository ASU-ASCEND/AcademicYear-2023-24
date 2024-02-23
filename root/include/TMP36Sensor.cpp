#include <TMP36Sensor.h>

//Implementing virtual function: getSensorName()
const std::string& TMP36Sensor::getSensorName() const {
  return nameCompiled;
}

//implements the constructor
TMP36Sensor::TMP36Sensor() {
    nameCompiled = "TMP36"; 
}

  TMP36
//Implementing virtual function: verifyPin()
bool TMP36Sensor::verifyPin() override{
  return true;
}
//Implementing virtual function: readData()
std::string TMP36Sensor::readData(){
}
