#include "SDCard.h"

const std::string& SDCard::getSDCardName() const {
    // Return the SD card name
    static const std::string sdCardName(SDCARD_NAME); // Using the compile-time constant defined in the class
    return sdCardName;
}
