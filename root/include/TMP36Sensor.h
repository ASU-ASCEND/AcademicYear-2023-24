#ifndef TMP36SENSOR_H
#define TMP36SENSOR_H
#include <string.h>
// adds temperature sensor
#include "TMP36.h" 
#include <Arduino.h>

#include "Sensor.h"

class TMP36Sensor : public Sensor {
<<<<<<< HEAD
  private:
    //Name for the sensor to be used in CSV header and console
    static constexpr const char* nameCompiled = "TMP36";
  public:
    const String& getSensorName() const override;
    bool verifyPin() override;
    String readData() override; 
=======
private:
  //Name for the sensor to be used in CSV header and console
  static constexpr const char* nameCompiled = "TMP36";
  //CSV header for the sensor to be used in CSV header and console
  static constexpr const char* csvHeaderCompiled = "TMP36 Temperature, ";
public:
  const String& getSensorName() const override;
  const String& getSensorCSVHeader() const override; 
  bool verifyPin() override;
  String readData() override; 
>>>>>>> main
};

#endif
