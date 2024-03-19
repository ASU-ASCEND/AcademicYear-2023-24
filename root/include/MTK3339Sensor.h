#ifndef MTK3339SENSOR_H
#define MTK3339SENSOR_H
#include <string>
#include <Arduino.h>

#include "Sensor.h"
#include <Adafruit_GPS.h>
#include <Wire.h>

class MTK3339Sensor : public Sensor {
private:
    Adafruit_GPS GPS = Adafruit_GPS(&Wire);
    //Name for the sensor to be used in CSV header and console
    String nameCompiled = "MTK3339";
    String csvHeaderCompiled = "MTK3339 Date, MTK3339 Latitude, MTK3339 Longitude, MTK3339 Speed, MTK3339 Angle, MTK3339 Altitude, MTK3339 Satellites";
    
public:
    const String& getSensorName() const override;
    const String& getSensorCSVHeader() const;
    bool verifyPin() override;
    String readData() override; 
};

#endif
