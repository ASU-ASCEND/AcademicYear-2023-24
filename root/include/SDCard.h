#ifndef SDCARD_H
#define SDCARD_H
#include "Arduino.h"

#include <Arduino.h>

class SDCard {
private:
  //Name for the sensor to be used in CSV header and console
  static constexpr const char* sdCardName = "SDCard";
public:
<<<<<<< HEAD
  bool verifyPin();
  const String& getSDCardName() const;
=======
  const arduino::String& getSDCardName() const;
>>>>>>> main
};

#endif
