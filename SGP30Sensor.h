#ifndef TMP36SENSOR_H
#define TMP36SENSOR_H

#include "Sensor.h"
#include "Adafruit_SGP30.h"
#include <Wire.h>


class SGP30Sensor : public Sensor {
private:
  //Name for the sensor to be used in CSV header and console
  Adafruit_SGP30 sgp;
  static constexpr const char* nameCompiled = "SGP30";
  //What do you even name this?
  static constexpr const char* csvHeaderCompiled;
public:
  const std::string& getSensorName() const override;
  bool verifyPin() override;
  std::string readData() override; 
};

#endif
