#ifndef RADIO_SLAVE_H
#define RADIO_SLAVE_H

#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
static RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00002";

void init_radioSlave();
void transmit(char* buf);

#endif
