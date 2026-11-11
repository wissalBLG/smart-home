
#pragma once
#include <Arduino.h>

struct OutdoorState {
    String timestamp;

    struct {
        float temperature = 0.0f;
        float humidity = 0.0f;
        bool airValid = false;
        int soilMoisturePercent = 0;
        int waterDepthPercent = 0;
        int waterRaw = 0;
        bool pump1Active = false; 
        bool pump2Active = false; 
        bool fanActive = false;   
    } greenhouse;

    struct {
        String lastRfidUid = "NULL";
        bool rfidDetected = false;
        bool doorUnlocked = false;
        bool exteriorLampOn = false;
    } exterior;
};