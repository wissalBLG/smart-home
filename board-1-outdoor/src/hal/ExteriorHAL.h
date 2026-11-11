
#pragma once
#include <Arduino.h>
#include <MFRC522.h>
#include "domain/OutdoorState.h"

class ExteriorHAL {
private:
    MFRC522 rfid;
    int doorLockPin;
    int lampPin;

    unsigned long doorUnlockMillis;
    unsigned long lightOnMillis;
    bool lightTriggeredByRfid;
    const unsigned long DOOR_OPEN_DURATION_MS = 5000; 
    const unsigned long LIGHT_ON_DURATION_MS = 10000; 

public:
    ExteriorHAL(uint8_t ssPin, uint8_t rstPin, int doorLockPin, int lampPin);
    void begin();
    void updateState(OutdoorState &state, unsigned long currentMillis);
};