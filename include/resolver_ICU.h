/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#ifndef RESOLVER_ICU_H_INCLUDED
#define RESOLVER_ICU_H_INCLUDED

#include "ch.h"
#include "hal.h"

void rsICUInit(void);
uint16_t rsICUValues(void);
void rsICUGetValues(uint32_t in);
void cmd_rsICUValues(BaseSequentialStream *chp, int argc, char *argv[]);

#endif