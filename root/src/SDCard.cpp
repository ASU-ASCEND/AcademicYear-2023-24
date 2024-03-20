#include "SDCard.h"

const String& SDCard::getSDCardName() const {
    // Return the SD card name
    return sdCardName;
}

bool SDCard::verifyPin() {
    if (!SD.begin(SD_CHIP_SELECT)) {
        return false;
    }

    // Find an unused filename
    // for (int i = 0; i < 1000; i++) {
    //     sprintf(logFileName, "savedDataFileNo_%d.CSV", i);
    //     if (!SD.exists(logFileName)) {
    //         // Open the file for writing
    //         fileObject = SD.open(logFileName, FILE_WRITE);
    //         break;
    //     }
    // }

    // fileObject = SD.open("log.csv", FILE_WRITE);
    // delay(100);
    // if(fileObject){
    //     fileObject.close();
    // }
    // else {
    //     Serial.println("ERROR - FILE NOT OPENING IN VERIFYPIN()");
    // }
    logFileName = "dLog.csv";

    return true;
}

bool SDCard::writeData(String dataRecord) {
    Serial.println("WRITEDATA()...");
    fileObject = SD.open(logFileName, FILE_WRITE);
    Serial.println("DONE");

    // Check if the file is successfully opened
    if (fileObject) {
        Serial.println("STARTING WRITE...");
        // Write the dataRecord to the file
        fileObject.println(dataRecord);
        // Close the file to ensure data is written to the SD card
        fileObject.close();
        //fileObject.flush();
        Serial.println("DONE, FILE CLOSED.");

        // Return true to indicate success
        return true;
    }
    else {
        Serial.println("Error opening .csv");
    }

    // Return false if the file wasn't opened successfully
    return false;
}

