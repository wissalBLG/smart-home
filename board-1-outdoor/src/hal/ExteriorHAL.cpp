
#include "ExteriorHAL.h"

ExteriorHAL::ExteriorHAL(uint8_t ssPin, uint8_t rstPin, int doorLockPin, int lampPin) 
    : rfid(ssPin, rstPin), doorLockPin(doorLockPin), lampPin(lampPin),
      doorUnlockMillis(0), lightOnMillis(0), lightTriggeredByRfid(false) {}

void ExteriorHAL::begin() {
    rfid.PCD_Init();
    pinMode(doorLockPin, OUTPUT);
    pinMode(lampPin, OUTPUT);

    digitalWrite(doorLockPin, LOW);
    digitalWrite(lampPin, LOW);
}

void ExteriorHAL::updateState(OutdoorState &state, unsigned long currentMillis) {
    state.exterior.rfidDetected = false;

    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
        String scannedUid = "";
        for (byte i = 0; i < rfid.uid.size; i++) {
            if (rfid.uid.uidByte[i] < 0x10) scannedUid += "0";
            scannedUid += String(rfid.uid.uidByte[i], HEX);
            if (i < rfid.uid.size - 1) scannedUid += " ";
        }
        scannedUid.toUpperCase();

        state.exterior.rfidDetected = true;
        state.exterior.lastRfidUid = scannedUid;
        state.exterior.doorUnlocked = true;
        doorUnlockMillis = currentMillis; 

        lightTriggeredByRfid = true;
        lightOnMillis = currentMillis;

        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
    }

    if (state.exterior.doorUnlocked && (currentMillis - doorUnlockMillis > DOOR_OPEN_DURATION_MS)) {
        state.exterior.doorUnlocked = false;
    }

    if (lightTriggeredByRfid && (currentMillis - lightOnMillis > LIGHT_ON_DURATION_MS)) {
        lightTriggeredByRfid = false;
    }
    state.exterior.exteriorLampOn = lightTriggeredByRfid;

    digitalWrite(doorLockPin, state.exterior.doorUnlocked ? HIGH : LOW);
    digitalWrite(lampPin, state.exterior.exteriorLampOn ? HIGH : LOW);
}