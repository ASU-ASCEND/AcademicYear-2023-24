#include "BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

const String& BME680::getSensorName() const {
    return nameCompiled;
}

const String& BME680::getSensorCSVHeader() const {
    return csvHeaderCompiled;
}

bool BME680::verifyPin() {
    if(!bme.begin()){
        return false;
    }

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms

    return true;
}

// "BME680 Temp C, BME680 Pressure hPa, BME680 Humidity %, BME680 Gas KOhms, BME680 Approx Alt m, "
String BME680::readData() {
    if(!bme.performReading()){
        return "-, -, -, -, -, ";
    }

    return String(bme.temperature) + ", " + String(bme.pressure / 100.0) + ", " + String(bme.humidity) + ", " 
        + String(bme.gas_resistance) + ", " + String(bme.readAltitude(SEALEVELPRESSURE_HPA)) + ", ";
}