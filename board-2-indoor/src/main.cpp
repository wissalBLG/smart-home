
#include <Arduino.h>
#include <ArduinoJson.h>
#include "hal/InteriorHAL.h"
#include "domain/IndoorState.h"

const int ROOM_1_LED_PIN     = 21; 
const int ROOM_2_LED_PIN     = 22; 
const int ROOM_3_LED_PIN     = 23; 
const int KITCHEN_LED_PIN    = 19; 
const int GAS_SENSOR_PIN     = 34; 
const int BUZZER_PIN         = 25; 

InteriorHAL interior(ROOM_1_LED_PIN, ROOM_2_LED_PIN, ROOM_3_LED_PIN, KITCHEN_LED_PIN, GAS_SENSOR_PIN, BUZZER_PIN);

unsigned long bootMillis = 0;

void setup() {
    Serial.begin(115200);
    while (!Serial);

    interior.begin();
    bootMillis = millis();

    Serial.println("INDOOR ESP32 (Rooms & Kitchen Safety) Initialized");
}

String getCurrentTime() {
    unsigned long sec = (millis() - bootMillis) / 1000;
    char buf[16];
    sprintf(buf, "%02lu:%02lu:%02lu", (sec / 3600) % 24, (sec / 3600) / 60, sec % 60);
    return String(buf);
}

void loop() {
    unsigned long currentMillis = millis();
    IndoorState state;
    state.timestamp = getCurrentTime();

    interior.updateState(state, currentMillis);

    JsonDocument doc;
    doc["time"] = state.timestamp;
    doc["interior"]["room1_light"] = state.interior.room1Light;
    doc["interior"]["room2_light"] = state.interior.room2Light;
    doc["interior"]["room3_light"] = state.interior.room3Light;
    doc["interior"]["kitchen_light"] = state.interior.kitchenLight;
    doc["interior"]["gas_leak"] = state.interior.gasLeakDetected;
    doc["interior"]["alarm_active"] = state.interior.alarmBuzzerActive;

    String output;
    serializeJsonPretty(doc, output);
    Serial.println(output);
    Serial.println("-------------------------------------------------");

    delay(2000);
}