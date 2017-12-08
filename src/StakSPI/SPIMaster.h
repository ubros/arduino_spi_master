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
        STANDBY = 0x01,             //送受信可能
        SEND_READY = 0x11,           //送信準備
        SEND_TRANSFER = 0x12,       //送信中
        SEND_COMPLETE = 0x13,       //送信完了
        RECEIVE_READY = 0x21,        //受信準備
        RECEIVE_TRANSFER = 0x22,    //受信中
        RECEIVE_COMPLETE = 0x23,    //受信完了
    } STATUS;

    typedef enum {
        SUCCESS = 0x01,             //成功
        ERROR = 0x02,               //失敗
    } RESPONSE;

    struct {
        STATUS status;
    } status_t;

    struct {
        char buf[1024];
        volatile byte pos;
        volatile boolean process_it;
    } data_t;

public:
    void begin();

    void handler();

    bool send(const char *message);

    void MASTER_CALLBACK(char *message);

private:
    bool _status_confirm(STATUS status);

    bool _send(const char *message);
    void _receive();
};


#endif //ARDUINO_SPI_MASTER_SPIMASTER_H
