/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#include <stdio.h>
#include <math.h>

#include "calc.h"

#define	MAX_ADC		4096
#define MIN_ADC		0

#define MAX_DEG		359
#define MIN_DEG		0

const uint16_t degree[] = {
    0,   5,  10,  15,  20,  25, 30,
   35,  40,  45,  50,  55,  60,
   65,  70,  75,  80,  85,  90,
   95, 100, 105, 110, 115, 120,
  125, 130, 135, 140, 145, 150,
  155, 160, 165, 170, 175, 180
};

const uint16_t sin_degree[] = {
     0,  872, 1736, 2588, 3420,  4226, 5000,
  5736, 6428, 7071, 7660, 8192,  8660,
  9063, 9397, 9659, 9848, 9962, 10000,
  9962, 9848, 9659, 9397, 9063,  8660,
  8192, 7660, 7071, 6428, 5736,  5000,
  4226, 3420, 2588, 1736,  872,     0
};
/*
const uint16_t sin_degree[] = {
  10000, 10000, 10000, 10000, 10000,  10000, 10000,
  10000, 10000, 10000, 10000, 10000,  10000,
  10000, 10000, 10000, 10000, 10000,  10000,
  10000, 10000, 10000, 10000, 10000,  10000,
  10000, 10000, 10000, 10000, 10000,  10000,
  10000, 10000, 10000, 10000, 10000,  10000
};*/

uint32_t adc_cycle;
uint32_t calc_pos;
uint16_t map_pos;

/* --- Degree calculation -- */
uint32_t calcAdc2Deg(uint16_t position, uint16_t phase_pair){
	position = position > MAX_ADC ? MAX_ADC : position;
	position = position < MIN_ADC ? MIN_ADC : position;

  adc_cycle = MAX_ADC / phase_pair;

  calc_pos = position % adc_cycle;

  calc_pos = map(calc_pos, MIN_ADC, adc_cycle, MAX_DEG, MIN_DEG);

  return calc_pos;
}

long map(long x, long in_min, long in_max, long out_min, long out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int16_t multiMap(int16_t val, int16_t* _in, int16_t* _out, uint8_t size)
{

  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  uint8_t pos = 1;
  while(val > _in[pos]) pos++;
  map_pos = pos;

  if (val == _in[pos]) return _out[pos];

  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

uint32_t calcDegOffset(uint16_t pos, int16_t offset){
	uint32_t motor_control;

    motor_control = pos + (359 - offset);
    motor_control = motor_control % 360;

    return motor_control;
}

uint16_t degAndThrottleToPWM(uint16_t in_deg, uint16_t in_throttle){
	double out;
	double inter_num;

	out = multiMap(in_deg, degree, sin_degree, 37);
	inter_num = in_throttle*100;
	inter_num = 1000000 / inter_num;
	out = out/inter_num;
  
  out = out > 10000 ? 10000 : out;
  out = out < 0 ? 0 : out;

  return (uint16_t)out;
}

void cmd_calcValues(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argc;
  (void)argv;

  uint16_t throttle = 0;
  uint16_t deg = 90;

  chprintf(chp, "\x1B\x63");
  chprintf(chp, "\x1B[2J");
  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
      chprintf(chp, "\x1B[%d;%dH", 0, 0);
      chprintf(chp, "deg : %d; throttle: %d | %5d\r\n", deg, throttle, degAndThrottleToPWM(deg, throttle));
      chprintf(chp, "map_pos : %d\r\n", map_pos);
      chThdSleepMilliseconds(10);
  }
}