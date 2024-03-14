#ifndef MTK3339SENSOR_H
#define MTK3339SENSOR_H
#include <string>
#include <Arduino.h>
#include <Adafruit_GPS.h>

#include "Sensor.h"

class MTK3339Sensor : public Sensor {
private:
    //Name for the sensor to be used in CSV header and console
    static constexpr const char* nameCompiled = "MTK3339";
public:
    const String& getSensorName() const override;
    bool verifyPin() override;
    String readData() override; 
};

#endif
