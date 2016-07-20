/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include "ch.h"
#include "hal.h"

void controlInit(void);
void controlCalc(void);

void degreeCalibOn(void);
void degreeCalibOff(void);

void motorOff(void);

uint16_t controlValues(void);

void cmd_controlSet(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_motorSet(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_autoCalib(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_controlValues(BaseSequentialStream *chp, int argc, char *argv[]);
#endif