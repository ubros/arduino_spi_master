//
// Created by ryo on 2017/12/03.
//

#ifndef ARDUINO_SPI_MASTER_SPIMASTER_H
#define ARDUINO_SPI_MASTER_SPIMASTER_H

#include "Arduino.h"
#include "SPI.h"

class SPIMaster {

    typedef enum {
        RETRY_COUNT = 5,             //リトライ回数
    } DEFINE;

    typedef enum {
        STANDBY = '\1',             //送受信可能
        SEND_READY = '\2',           //送信準備
        SEND_NEGOTIATION_UINT8 = '\15',      //送信種別決定
        SEND_NEGOTIATION_UINT16 = '\16',      //送信種別決定
        SEND_NEGOTIATION_CHAR = '\17',      //送信種別決定
        SEND_TRANSFER = '\6',       //送信中
        SEND_COMPLETE = '\77',       //送信完了

        RECEIVE_READY = '\11',        //受信準備
        RECEIVE_TRANSFER = '\12',    //受信中
        RECEIVE_COMPLETE = '\13',    //受信完了
    } STATUS;

    typedef enum {
        SUCCESS = '\20',             //成功
        ERROR = '\21',               //失敗
    } RESPONSE;

    struct {
        STATUS status;
    } status_t;

    struct {
        STATUS type;
        uint8_t buf[1024];
        volatile byte pos;
        volatile boolean process_it;
    } data_t;

public:
    void begin();

    void handler();

    bool send(uint8_t *message, size_t length);

    bool send16(uint16_t *message, size_t length);

    bool send_char(const char *message, size_t length);

    void MASTER_CALLBACK(const uint8_t *message);

private:
    bool _status_confirm(STATUS status);

    bool _send(uint8_t *message, size_t length);

    void _receive();
};


#endif //ARDUINO_SPI_MASTER_SPIMASTER_H
