#ifndef SDCARD_H
#define SDCARD_H
#include "Arduino.h"

#include <SPI.h>
#include <SD.h>

#define SD_CHIP_SELECT 7

class SDCard {
private:
  //Name for the sensor to be used in CSV header and console
  String sdCardName = "SDCard";
  //creates a file object 
  SDLib::File fileObject;
  //Name for a saved file
  String logFileName;
public:
  ~SDCard(){
    fileObject.close();
  }
  //Accessor method to verify pin connection
  bool verifyPin();
  //Accessor method to get name of SD card sensor
  const String& getSDCardName() const;
  //Setter method to write data to SD card
  bool writeData(String dataRecord);
};

#endif
