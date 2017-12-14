//
// Created by ryo on 2017/12/02.
//
#include <SPI.h>
#include "Arduino.h"
#include "StakSPI/SPIMaster.h"

SPIMaster SPIMaster;

void setup() {
    Serial.begin(115200);

    SPIMaster.begin();
}

uint16_t irSignal[] = {9000, 4500, 560, 560, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 560,
                       560, 1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560,
                       560, 560, 560, 560, 560, 560, 1690, 560, 560, 560, 560, 560, 560, 560, 560, 560, 1690, 560,
                       1690, 560, 1690, 560, 560, 560, 1690, 560, 1690, 560, 1690, 560, 1690, 560, 39416, 9000,
                       2210, 560};

//uint8_t uint8_number[] = {100, 200, 255, 1};
uint8_t uint8_message[] = {'u', 'e', 'm', 'o', 't', 'o'};

char message[] = "led:on";

void loop() {

    if (Serial.read() != -1) {
//        SPIMaster.send(uint8_number, sizeof(uint8_number));
//        SPIMaster.send(uint8_message, sizeof(uint8_message));
//        SPIMaster.send16(irSignal, sizeof(irSignal));
        SPIMaster.send_char(message, sizeof(message));
    }

    SPIMaster.handler();
}

void SPIMaster::MASTER_CALLBACK(const uint8_t *message) {
    Serial.println(*message);
}