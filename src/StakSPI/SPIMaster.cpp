//
// Created by ryo on 2017/12/03.
//

#include "SPIMaster.h"

/**************************************************************
 * public method
 **************************************************************/

void SPIMaster::begin() {
    Serial.println("Master init");
    pinMode(SS, OUTPUT);
    SPI.setClockDivider(SPI_CLOCK_DIV4);
    SPI.begin();
    status_t.status = STANDBY;
    data_t.process_it = false;
}

void SPIMaster::handler() {

    if (!data_t.process_it && _status_confirm(RECEIVE_READY)) {
        status_t.status = RECEIVE_TRANSFER;
        data_t.process_it = true;
        data_t.pos = 0;
        data_t.buf[data_t.pos] = 0;
        return;
    }

    switch (status_t.status) {
        case RECEIVE_TRANSFER:
            _receive();
            break;
        case RECEIVE_COMPLETE:
            if(_status_confirm(RECEIVE_COMPLETE)){
                status_t.status = STANDBY;
                data_t.process_it = false;
                MASTER_CALLBACK(data_t.buf);
                data_t.pos = 0;
                data_t.buf[data_t.pos] = 0;
            }
            break;
        default:
            break;
    }
}

bool SPIMaster::send(const char *message) {
    uint8_t retry = 0;
    while (++retry < RETRY_COUNT) {
        if (status_t.status == STANDBY && _send(message))
            return true;
    }
    return false;
}

/**************************************************************
 * private method
 **************************************************************/

bool SPIMaster::_send(const char *message) {

    status_t.status = SEND_READY;
    if (!_status_confirm(SEND_READY)) {
        status_t.status = STANDBY;
        return false;
    }

    status_t.status = SEND_TRANSFER;
    for (; char c = *message; message++) {
        SPI.transfer(c);
        delayMicroseconds(10);
    }

    status_t.status = SEND_COMPLETE;
    if (!_status_confirm(SEND_COMPLETE)) {
        status_t.status = STANDBY;
        return false;
    }

    status_t.status = STANDBY;
    return true;
}

void SPIMaster::_receive() {
    SPI.transfer(RECEIVE_TRANSFER);
    delay(1);
    byte c = SPI.transfer(0);

    if (c == RECEIVE_COMPLETE) {
        status_t.status = RECEIVE_COMPLETE;
        return;
    }
    data_t.buf[data_t.pos++] = c;
}

bool SPIMaster::_status_confirm(STATUS status) {
    SPI.transfer(status);
    delay(1);
    byte c = SPI.transfer(0);
    return SUCCESS == c;
}