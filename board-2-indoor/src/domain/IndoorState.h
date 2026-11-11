
#pragma once
#include <Arduino.h>

struct IndoorState {
    String timestamp;

    struct {
        bool room1Light = false;
        bool room2Light = false;
        bool room3Light = false;
        bool kitchenLight = false;
        int gasSensorRaw = 0;
        bool gasLeakDetected = false;
        bool alarmBuzzerActive = false;
    } interior;
};