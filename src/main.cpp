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

void loop() {

    if (Serial.read() != -1) {
        SPIMaster.send("スレーブにデータを贈りたい");
    }

    SPIMaster.handler();
}

void SPIMaster::MASTER_CALLBACK(char *message){
    Serial.println(message);
}