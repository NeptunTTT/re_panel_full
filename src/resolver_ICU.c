/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#include <stdio.h>
#include <math.h>

#include "resolver_ICU.h"
#include "resolver_SPI.h"

#include "chprintf.h"

/*
 *PE5 - CH_A  - TIM9_CH1
 *PA1 - CH_B  - TIM5_CH2
 *PB5 - CH_NM - TIM3_CH2
 *PA0 - CH_DIR
 */

uint32_t encoder_degree_max;
uint32_t encoder_degree;
uint32_t count;
uint32_t count_save;

uint32_t count_a;
uint32_t count_b;
uint32_t count_nm;

bool first_rotation = TRUE;

/*----- Encoder - A -----*/
static void icu_up_a(ICUDriver *icup) {
  if (palReadPad(GPIOA, GPIOA_CH_B) == FALSE)
  {
    encoder_degree++;
  }

  if (palReadPad(GPIOA, GPIOA_CH_B))
  {
    encoder_degree--;
  }
  count ++;
  count_a++;
}

static void icu_down_a(ICUDriver *icup) {
  if (palReadPad(GPIOA, GPIOA_CH_B))
  {
    encoder_degree++;
  }
  if (palReadPad(GPIOA, GPIOA_CH_B) == FALSE)
  {
    encoder_degree--;
  }
  count ++;
  count_a++;
}
/*------------------------*/



/*----- Encoder - B -----*/
static void icu_up_b(ICUDriver *icup) {
  if (palReadPad(GPIOE, GPIOE_CH_A))
  {
    encoder_degree++;
  }
  if (palReadPad(GPIOE, GPIOE_CH_A) == FALSE)
  {
    encoder_degree--;
  }
  count ++;
  count_b++;
}

static void icu_down_b(ICUDriver *icup) {
  if (palReadPad(GPIOE, GPIOE_CH_A) == FALSE)
  {
    encoder_degree++;
  }
  if (palReadPad(GPIOE, GPIOE_CH_A))
  {
    encoder_degree--;
  }
  count ++;
  count_b++;
}
/*------------------------*/



/*----- Encoder - NM -----*/
static void icu_up_nm(ICUDriver *icup) {
  if (first_rotation)
  {
    first_rotation = FALSE;
  }

  if (encoder_degree < 4094 && encoder_degree > 4098)
  {  
    motorOff();
  }
  
  encoder_degree_max = encoder_degree;
  encoder_degree = palReadPad(GPIOA, GPIOA_CH_DIR) ? 0 : 4096 ;
  count_save = count;
  count = 0;
  count_nm++;
}

/*------------------------*/



static ICUConfig icu_a = {
  ICU_INPUT_ACTIVE_HIGH,
  28e6,
  icu_down_a,
  icu_up_a,
  NULL,
  ICU_CHANNEL_1,
  0
};

static ICUConfig icu_b = {
  ICU_INPUT_ACTIVE_HIGH,
  28e6,
  icu_down_b,
  icu_up_b,
  NULL,
  ICU_CHANNEL_2,
  0
};

static ICUConfig icu_nm = {
  ICU_INPUT_ACTIVE_HIGH,
  28e6,
  icu_up_nm,
  NULL,
  NULL,
  ICU_CHANNEL_2,
  0
};

void rsICUInit(void) {
  encoder_degree = 0;

  icuStart(&ICUD9, &icu_a);
  icuStart(&ICUD5, &icu_b);
  icuStart(&ICUD3, &icu_nm);

  icuStartCapture(&ICUD9);
  icuStartCapture(&ICUD5);
  icuStartCapture(&ICUD3);

  icuEnableNotifications(&ICUD9);
  icuEnableNotifications(&ICUD5);
  icuEnableNotifications(&ICUD3);

  encoder_degree = rsSPIRead();
}

uint16_t rsICUValues(void){
  return (uint16_t)encoder_degree;
}

void rsICUSetValues(uint32_t in){

  if (encoder_degree != in)
  {
    chSysLock();
    count = in;
    encoder_degree = in;
    chSysUnlock();
  }
}

void cmd_rsICUValues(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argc;
  (void)argv;
  chprintf(chp, "\x1B\x63");
  chprintf(chp, "\x1B[2J");
  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
      chprintf(chp, "\x1B[%d;%dH", 0, 0);

      chprintf(chp, "encoder_degree: %15d\r\n", encoder_degree);
      chprintf(chp, "encoder_degree_max: %15d\r\n", encoder_degree_max);
      chprintf(chp, "\r\n");
      chprintf(chp, "A: %15d\r\n", count_a);
      chprintf(chp, "B: %15d\r\n", count_b);
      chprintf(chp, "NM: %15d\r\n", count_nm);
      chprintf(chp, "\r\n");
      chprintf(chp, "DIR: %15d\r\n", palReadPad(GPIOA, GPIOA_CH_DIR) ? 1 : 0);
      chprintf(chp, "LOT: %15d\r\n", palReadPad(GPIOA, GPIOD_LOT) ? 1 : 0);
      chprintf(chp, "DOS: %15d\r\n", palReadPad(GPIOA, GPIOD_DOS) ? 1 : 0);
      //chprintf(chp, "spi_degree: %15d\r\n", rsSPIRead());
      //chprintf(chp, "count: %15d\r\n", count);
      //chprintf(chp, "count: %15d\r\n", count_save);
      //chprintf(chp, "\r\n");
      //chprintf(chp, "controlValues: %15d\r\n", controlValues());

      chThdSleepMilliseconds(10);
  }
}