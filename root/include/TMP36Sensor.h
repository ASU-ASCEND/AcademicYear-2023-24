#ifndef TMP36SENSOR_H
#define TMP36SENSOR_H
#include <string>
// adds temperature sensor
#include "TMP36.h" 

#include "Sensor.h"

class TMP36Sensor : public Sensor {
private:
  //Name for the sensor to be used in CSV header and console
  static constexpr const char* nameCompiled = "TMP36";
public:
  const std::string& getSensorName() const override;
  bool verifyPin() override;
  std::string readData() override; 
};

#endif
