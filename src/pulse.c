/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#include "pulse.h"

#include "chprintf.h"

#define MEDIUM_RATIO  2
#define LOW_RATIO     3

/*
 *PD12   - U_H
 *PC6   - U_L

 *PD13  - V_H
 *PC7   - V_L

 *PD14  - W_H
 *PC8   - W_L
 */

static PWMConfig high_side = {
  28e6,                                   /* 10kHz PWM clock frequency.   */
  28e6/20000,                             /* Initial PWM period 1S.       */
  NULL,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},        /* PD12 - U_H */
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},        /* PD13 - V_H */
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},        /* PD14 - W_H */
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
  0
};

static PWMConfig low_side = {
  28e6,                                   /* 10kHz PWM clock frequency.   */
  28e6/20000,                             /* Initial PWM period 1S.       */
  NULL,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},        /* PC6  - U_L */
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},        /* PC7  - V_L */
   {PWM_OUTPUT_ACTIVE_HIGH, NULL},        /* PC8  - W_L */
   {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  0,
  0
};

uint32_t level_l; //low    - full / 10
uint32_t level_m; //medium - full / 2
uint32_t level_h; //height - full

uint32_t section;

uint8_t u_h;
uint8_t v_h;
uint8_t w_h;

uint8_t u_l;
uint8_t v_l;
uint8_t w_l;

static uint16_t u_deg;   //U Height side
static uint16_t v_deg;   //V Height side
static uint16_t w_deg;   //W Height side

void pulseInit(void) {

  pwmStart(&PWMD4, &high_side);
  pwmStart(&PWMD8, &low_side);
}

void pulseControl(uint32_t degree, uint32_t width){
  uint32_t pwm_level;

  degree = degree > 359 ? 359 : degree;
  degree = degree < 0 ? 0 : degree;

  u_deg = degree;
  v_deg = 120 + degree;
  w_deg = 240 + degree;

  v_deg = v_deg % 360;
  w_deg = w_deg % 360;

/* U Phase */
  if (u_deg <= 180)
  {
    pwmEnableChannelI(&PWMD4, u_h, PWM_PERCENTAGE_TO_WIDTH(&PWMD4, degAndThrottleToPWM(u_deg, width)));
    pwmDisableChannelI(&PWMD8, u_l);
  }
  else if (u_deg > 180)
  {
    pwmDisableChannelI(&PWMD4, u_h);
    pwmEnableChannelI(&PWMD8, u_l, PWM_PERCENTAGE_TO_WIDTH(&PWMD8, degAndThrottleToPWM(u_deg-180, width)));
  }

/* V Phase */
  if (v_deg <= 180)
  {
    pwmEnableChannelI(&PWMD4, v_h, PWM_PERCENTAGE_TO_WIDTH(&PWMD4, degAndThrottleToPWM(v_deg, width)));
    pwmDisableChannelI(&PWMD8, v_l);
  }
  else if (v_deg > 180)
  {
    pwmDisableChannelI(&PWMD4, v_h);
    pwmEnableChannelI(&PWMD8, v_l, PWM_PERCENTAGE_TO_WIDTH(&PWMD8, degAndThrottleToPWM(v_deg-180, width)));
  }

/* W Phase */
  if (w_deg <= 180)
  {
    pwmEnableChannelI(&PWMD4, w_h, PWM_PERCENTAGE_TO_WIDTH(&PWMD4, degAndThrottleToPWM(w_deg, width)));
    pwmDisableChannelI(&PWMD8, w_l);
  }
  else if (w_deg > 180)
  {
    pwmDisableChannelI(&PWMD4, w_h);
    pwmEnableChannelI(&PWMD8, w_l, PWM_PERCENTAGE_TO_WIDTH(&PWMD8, degAndThrottleToPWM(w_deg-180, width)));
  }
}

void pulseWidth(uint32_t in){
  in = in > 10000 ? 10000 : in;
  in = in < 0 ? 0 : in;

  level_h = (uint32_t)in;
  level_m = (uint32_t)(in / MEDIUM_RATIO);
  level_l = (uint32_t)(in / LOW_RATIO);
}

/*void pulseFunction(uint32_t in){
  pulseControl(in);
}*/

void pulseDirection(uint16_t direction){
  if(direction == 1){
    u_h = 0;
    v_h = 1;
    w_h = 2;

    u_l = 0;
    v_l = 1;
    w_l = 2;
  }

  else if(direction == 2){
    u_h = 1;
    v_h = 0;
    w_h = 2;

    u_l = 1;
    v_l = 0;
    w_l = 2;
  }
}

int16_t pulseGetValue(){
}

void cmd_pulseValues(BaseSequentialStream *chp, int argc, char *argv[]) {

    (void)argc;
  (void)argv;
  chprintf(chp, "\x1B\x63");
  chprintf(chp, "\x1B[2J");
  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
      chprintf(chp, "\x1B[%d;%dH", 0, 0);

      pulseControl_2(360, 10000);

      chprintf(chp, "u_deg: %5d\r\n", u_deg);
      chprintf(chp, "v_deg: %5d\r\n", v_deg);
      chprintf(chp, "w_deg: %5d\r\n", w_deg);
      
      chThdSleepMilliseconds(1000);
  }
}