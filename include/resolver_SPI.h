/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#ifndef RESOLVER_SPI_H_INCLUDED
#define RESOLVER_SPI_H_INCLUDED

#include "ch.h"
#include "hal.h"

int32_t rsSPIRead();
void rsSPIInit(void);
void rsSPICalc(void);
uint16_t rsSPIValues(uint32_t num);

void cmd_rsSPIValues(BaseSequentialStream *chp, int argc, char *argv[]);

#endif