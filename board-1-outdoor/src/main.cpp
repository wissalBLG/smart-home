
#include <Arduino.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "hal/GreenhouseHAL.h"
#include "hal/ExteriorHAL.h"
#include "domain/OutdoorState.h"

const int WATER_SENSOR_PIN   = 6;  
const int SOIL_MOISTURE_PIN  = 4;  
const int DHT_PIN            = 14; 
const int PUMP_1_PIN         = 15; 
const int PUMP_2_PIN         = 16; 
const int FAN_PIN            = 17; 

const int EXTERIOR_LAMP_PIN  = 7;  
const int DOOR_LOCK_PIN      = 18; 
const int SS_PIN             = 8;  
const int RST_PIN            = 5;  
const int SCK_PIN            = 12; 
const int MISO_PIN           = 13; 
const int MOSI_PIN           = 11; 

GreenhouseHAL greenhouse(DHT_PIN, SOIL_MOISTURE_PIN, WATER_SENSOR_PIN, PUMP_1_PIN, PUMP_2_PIN, FAN_PIN);
ExteriorHAL exterior(SS_PIN, RST_PIN, DOOR_LOCK_PIN, EXTERIOR_LAMP_PIN);

unsigned long bootMillis = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN);

    greenhouse.begin();
    exterior.begin();
    bootMillis = millis();

    Serial.println("OUTDOOR ESP32 (Greenhouse + Exterior) Initialized");
}

String getCurrentTime() {
    unsigned long sec = (millis() - bootMillis) / 1000;
    char buf[16];
    sprintf(buf, "%02lu:%02lu:%02lu", (sec / 3600) % 24, (sec / 3600) / 60, sec % 60);
    return String(buf);
}

void loop() {
    unsigned long currentMillis = millis();
    OutdoorState state;
    state.timestamp = getCurrentTime();

    exterior.updateState(state, currentMillis);
    greenhouse.updateState(state, currentMillis);

    JsonDocument doc;
    doc["time"] = state.timestamp;
    doc["greenhouse"]["temp"] = state.greenhouse.temperature;
    doc["greenhouse"]["soil"] = state.greenhouse.soilMoisturePercent;
    doc["greenhouse"]["pump1"] = state.greenhouse.pump1Active;
    doc["greenhouse"]["pump2"] = state.greenhouse.pump2Active;
    doc["greenhouse"]["fan"] = state.greenhouse.fanActive;

    doc["exterior"]["door_unlocked"] = state.exterior.doorUnlocked;
    doc["exterior"]["lamp_on"] = state.exterior.exteriorLampOn;
    doc["exterior"]["last_rfid"] = state.exterior.lastRfidUid;

    String output;
    serializeJsonPretty(doc, output);
    Serial.println(output);
    Serial.println("-------------------------------------------------");

    delay(2000);
}