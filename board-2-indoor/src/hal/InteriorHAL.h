
#pragma once
#include <Arduino.h>
#include "domain/IndoorState.h"

class InteriorHAL {
private:
    int room1Pin;
    int room2Pin;
    int room3Pin;
    int kitchenPin;
    int gasSensorPin;
    int buzzerPin;

public:
    InteriorHAL(int r1Pin, int r2Pin, int r3Pin, int kPin, int gasPin, int bPin);
    void begin();
    void updateState(IndoorState &state, unsigned long currentMillis);
};