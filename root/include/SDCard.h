#ifndef SDCARD_H
#define SDCARD_H

#include <Arduino.h>

class SDCard {
private:
  //Name for the sensor to be used in CSV header and console
  static constexpr const char* nameCompiled = "SDCard";
public:
  bool verifyPin();
  const String& getSDCardName() const;
};

#endif
