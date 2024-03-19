#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h> //Needed for Arduino functionalities
#include <string.h> //Needed for returning string from writeData()

class Sensor {
 public:
  //Accessor Method to access name of sensor
  virtual const String& getSensorName() const = 0;
  //Accessor Method to access CSV header of sensor
  virtual const String& getSensorCSVHeader() const; 
  //Accessor Method to access status of successful pin connection 
  virtual bool verifyPin() = 0;
  //Accessor Method to access observed environmental changes
  virtual String readData() = 0;
};
#endif
