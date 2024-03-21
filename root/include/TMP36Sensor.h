#ifndef TMP36SENSOR_H
#define TMP36SENSOR_H
#include <string.h>
// adds temperature sensor
#include "TMP36.h" 
#include <Arduino.h>

#include "Sensor.h"

class TMP36Sensor : public Sensor {
 private:
  //Name for the sensor to be used in CSV header and console
  String nameCompiled = "TMP36";
  //CSV header for the sensor to be used in CSV header and console
  String csvHeaderCompiled = "TMP36 Temperature, ";
public:
  const String& getSensorName() const override;
  const String& getSensorCSVHeader() const override; 
  bool verifyPin() override;
  String readData() override;
  String readEmpty() override {
      return "-, ";
  } 

};

#endif
