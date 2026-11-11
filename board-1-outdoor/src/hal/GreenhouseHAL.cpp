
#include "GreenhouseHAL.h"

GreenhouseHAL::GreenhouseHAL(int dhtPin, int soilPin, int waterPin, int pump1Pin, int pump2Pin, int fanPin) 
    : dht(dhtPin, DHT11), soilPin(soilPin), waterPin(waterPin), pump1Pin(pump1Pin), pump2Pin(pump2Pin), fanPin(fanPin),
      lastPump1TriggerTime(0), pump1ActiveTimer(false), pump1StartMillis(0) {}

void GreenhouseHAL::begin() {
    dht.begin();
    pinMode(soilPin, INPUT);
    pinMode(waterPin, INPUT);
    pinMode(pump1Pin, OUTPUT);
    pinMode(pump2Pin, OUTPUT);
    pinMode(fanPin, OUTPUT);

    digitalWrite(pump1Pin, LOW);
    digitalWrite(pump2Pin, LOW);
    digitalWrite(fanPin, LOW);
    
    lastPump1TriggerTime = millis();
}

void GreenhouseHAL::updateState(OutdoorState &state, unsigned long currentMillis) {
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();

    if (isnan(hum) || isnan(temp)) {
        state.greenhouse.airValid = false;
        state.greenhouse.temperature = 0.0f;
        state.greenhouse.humidity = 0.0f;
    } else {
        state.greenhouse.airValid = true;
        state.greenhouse.temperature = temp;
        state.greenhouse.humidity = hum;
    }

    int soilRaw = analogRead(soilPin);
    state.greenhouse.soilMoisturePercent = constrain(map(soilRaw, 4095, 0, 0, 100), 0, 100);

    state.greenhouse.waterRaw = analogRead(waterPin);
    state.greenhouse.waterDepthPercent = constrain(map(state.greenhouse.waterRaw, 0, 4095, 0, 100), 0, 100);

    if (!pump1ActiveTimer && (currentMillis - lastPump1TriggerTime >= PUMP_1_INTERVAL_MS)) {
        pump1ActiveTimer = true;
        pump1StartMillis = currentMillis;
        lastPump1TriggerTime = currentMillis; 
    }
    if (pump1ActiveTimer && (currentMillis - pump1StartMillis >= PUMP_1_DURATION_MS)) {
        pump1ActiveTimer = false; 
    }
    state.greenhouse.pump1Active = pump1ActiveTimer;

    state.greenhouse.pump2Active = (state.greenhouse.soilMoisturePercent < 30);
    state.greenhouse.fanActive = (state.greenhouse.airValid && state.greenhouse.temperature > 28.0f);

    digitalWrite(pump1Pin, state.greenhouse.pump1Active ? HIGH : LOW);
    digitalWrite(pump2Pin, state.greenhouse.pump2Active ? HIGH : LOW);
    digitalWrite(fanPin, state.greenhouse.fanActive ? HIGH : LOW);
}