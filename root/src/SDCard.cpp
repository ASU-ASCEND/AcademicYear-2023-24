#include "SDCard.h"

const String& SDCard::getSDCardName() const {
    // Return the SD card name
    return sdCardName;
}

bool SDCard::verifyPin() {
    return true;
}

