
#include "InteriorHAL.h"

InteriorHAL::InteriorHAL(int r1Pin, int r2Pin, int r3Pin, int kPin, int gasPin, int bPin)
    : room1Pin(r1Pin), room2Pin(r2Pin), room3Pin(r3Pin), kitchenPin(kPin), gasSensorPin(gasPin), buzzerPin(bPin) {}

void InteriorHAL::begin() {
    pinMode(room1Pin, OUTPUT);
    pinMode(room2Pin, OUTPUT);
    pinMode(room3Pin, OUTPUT);
    pinMode(kitchenPin, OUTPUT);
    pinMode(gasSensorPin, INPUT);
    pinMode(buzzerPin, OUTPUT);

    digitalWrite(room1Pin, LOW);
    digitalWrite(room2Pin, LOW);
    digitalWrite(room3Pin, LOW);
    digitalWrite(kitchenPin, LOW);
    digitalWrite(buzzerPin, LOW);
}

void InteriorHAL::updateState(IndoorState &state, unsigned long currentMillis) {
    state.interior.room1Light = false;
    state.interior.room2Light = false;
    state.interior.room3Light = false;
    state.interior.kitchenLight = false;

    state.interior.gasSensorRaw = analogRead(gasSensorPin);
    state.interior.gasLeakDetected = (state.interior.gasSensorRaw > 2000); 
    state.interior.alarmBuzzerActive = state.interior.gasLeakDetected;

    digitalWrite(room1Pin, state.interior.room1Light ? HIGH : LOW);
    digitalWrite(room2Pin, state.interior.room2Light ? HIGH : LOW);
    digitalWrite(room3Pin, state.interior.room3Light ? HIGH : LOW);
    digitalWrite(kitchenPin, state.interior.kitchenLight ? HIGH : LOW);
    digitalWrite(buzzerPin, state.interior.alarmBuzzerActive ? HIGH : LOW);
}