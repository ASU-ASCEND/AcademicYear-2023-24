#include "SDCard.h"

const String& SDCard::getSDCardName() const {
    // Return the SD card name
    return nameCompiled;
}

bool SDCard::verifyPin() {
    return true;
}

