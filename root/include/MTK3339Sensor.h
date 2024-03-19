#ifndef MTK3339SENSOR_H
#define MTK3339SENSOR_H
#include <string>
#include <Arduino.h>
#include <Adafruit_GPS.h>

#include "Sensor.h"
Adafruit_GPS GPS(&Wire);

class MTK3339Sensor : public Sensor {
private:
    //Name for the sensor to be used in CSV header and console
    static constexpr const char* nameCompiled = "MTK3339";
    static constexpr const char* csvHeaderCompiled = "MTK3339";
    
public:
    const String& getSensorName() const override;
    const String& getSensorCSVHeader() const;
    bool verifyPin() override;
    String readData() override; 
};

#endif
