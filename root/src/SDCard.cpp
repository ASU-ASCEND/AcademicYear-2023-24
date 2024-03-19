#include "SDCard.h"

const String& SDCard::getSDCardName() const {
    // Return the SD card name
    return sdCardName;
}

bool SDCard::verifyPin() {
    if (!SD.begin(7)) {
        return false;
  }
    return true;
}

bool SDCard::writeData(String dataRecord) {
    // Find an unused filename
    for (int i = 0; i < 1000; i++) {
        sprintf(logFileName, "savedDataFileNo_%d.CSV", i);
        if (!SD.exists(logFileName)) {
            // Open the file for writing
            fileObject = SD.open(logFileName, FILE_WRITE);
            break;
        }
    }

    // Check if the file is successfully opened
    if (fileObject) {
        // Write the dataRecord to the file
        fileObject.println(dataRecord);

        // Close the file to ensure data is written to the SD card
        fileObject.close();

        // Return true to indicate success
        return true;
    }

    // Return false if the file wasn't opened successfully
    return false;
}

