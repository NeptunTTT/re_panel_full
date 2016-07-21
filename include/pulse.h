/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#ifndef PULSE_H_INCLUDED
#define PULSE_H_INCLUDED

#include "ch.h"
#include "hal.h"

enum logStates
{
  PULSE_AB,
  PULSE_AC,
  PULSE_BC,
  PULSE_BA,
  PULSE_CA,
  PULSE_CB,
};

void pulseInit(void);
void pulseControl(uint32_t degree, uint32_t width);
void pulseWidth(uint32_t in);
void pulseDirection(uint16_t direction);
//void pulseFunction(uint32_t in);
int16_t pulseGetValue();
void cmd_pulseValues(BaseSequentialStream *chp, int argc, char *argv[]);

#endif