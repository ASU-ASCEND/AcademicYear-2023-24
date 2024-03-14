/* TMP36 library
 
 Copyright 2020 Isaac100

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an "AS IS" BASIS, 
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 This library converts the analog values from a TMP36 temperature
 sensor directly into Celsius and Fahrenheit so you don't have to. 
 */

#include "Arduino.h"
#include "TMP36.h"

TMP36::TMP36(uint8_t pin, float aref) {
  pinMode(pin, INPUT);
  _aref = aref;
  _pin = pin;  
}

void TMP36::getValues() {
  _value = analogRead(_pin);
  _voltage = (_value/1024.0) * _aref;
  _tempC = (_voltage - .5) * 100;  
  _tempF = (_tempC * 1.8) + 32; 
} 

float TMP36::getVoltage() {
  getValues(); 
  return _voltage;
}

float TMP36::getTempC() {
  getValues(); 
  return _tempC;
}

float TMP36::getTempF() {
  getValues();
  return _tempF;
}

float TMP36::getTempK() {
  getValues();
  return _tempC + 273.15;
}
