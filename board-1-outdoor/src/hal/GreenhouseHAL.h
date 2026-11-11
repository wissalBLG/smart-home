
#pragma once
#include <Arduino.h>
#include <DHT.h>
#include "domain/OutdoorState.h"

class GreenhouseHAL {
private:
    DHT dht;
    int soilPin;
    int waterPin;
    int pump1Pin;
    int pump2Pin;
    int fanPin;

    unsigned long lastPump1TriggerTime;
    bool pump1ActiveTimer;
    unsigned long pump1StartMillis;
    const unsigned long PUMP_1_INTERVAL_MS = 3UL * 24UL * 60UL * 60UL * 1000UL; 
    const unsigned long PUMP_1_DURATION_MS = 10UL * 1000UL; 

public:
    GreenhouseHAL(int dhtPin, int soilPin, int waterPin, int pump1Pin, int pump2Pin, int fanPin);
    void begin();
    void updateState(OutdoorState &state, unsigned long currentMillis);
};