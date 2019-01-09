#ifndef RADIO_ADMIN_H
#define RADIO_ADMIN_H

#include <nRF24L01.h>
#include <RF24.h>
# include "ft_lib.h"

static RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void  init_radioAdmin();
void  loop_radioAdmin();

#endif
