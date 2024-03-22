#ifndef GEIGERINTERRUPT_H
#define GEIGERINTERRUPT_H

#include "Sensor.h"
#include "Arduino.h"

#define GEIGER_PIN A2

static volatile int count;

class GeigerInterrupt : public Sensor {

    private:
        String nameCompiled = "GeigerInterrupt";
        String csvHeaderCompiled = "GeigerInterrupt CPS, ";
        int measuringPeriodStart = 0; 
        static void geigerCounter(){
            count++;
        }
    public: 
        const String& getSensorName() const override;
        const String& getSensorCSVHeader() const override;
        bool verifyPin() override;
        String readData() override;
        String readEmpty(){
            return "-, ";
        }

};

#endif