/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include "ch.h"
#include "hal.h"
#include "math.h"

uint32_t calcAdc2Deg(uint16_t position, uint16_t phase_pair);
long map(long x, long in_min, long in_max, long out_min, long out_max);
int16_t multiMap(int16_t val, int16_t* _in, int16_t* _out, uint8_t size);
uint32_t calcDegOffset(uint16_t pos, int16_t offset);
uint16_t degAndThrottleToPWM(uint16_t in_deg, uint16_t in_throttle);
void cmd_calcValues(BaseSequentialStream *chp, int argc, char *argv[]);

#endif