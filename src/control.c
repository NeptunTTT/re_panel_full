/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#include "control.h"
#include "pulse.h"
#include "resolver_SPI.h"
#include "resolver_ICU.h"
#include "calc.h"
//#include "current_control.h"

#include "chprintf.h"

#define PHASE_PAIR		10

#define MAX_PWM			10000
#define MIN_PWM			0

#define SET_CURRENT		5

#define MAX_P		1000000
#define MAX_I		1000000
#define MAX_D		1000000

#define P_TAG		30
#define I_TAG		4
#define D_TAG		500

#define AVG_10_TMB  100

static int32_t cl_degree;
static int32_t cl_degree_SPI;
static int32_t cl_degree_ICU;
static int32_t cl_degree_ass;
static int32_t cl_width;

static int32_t cl_rdvel;
static int32_t cl_dos;
static int32_t cl_lot;
static int32_t cl_par;
static int32_t cl_different;
static int32_t cl_auto_mod_different;
static int32_t cl_direction;

static uint16_t spi_icu_calib_cycle;

/* Auto calib values */
static bool auto_calib;
static uint32_t task_cycle = 0;
static uint32_t calib_degree = 0;

static double diffasis;
static int i;
static int diff_index;
static uint16_t avg_diff[AVG_10_TMB];


static void gptcb(GPTDriver *gptp) {

  (void)gptp;
  	
  chSysLockFromISR();
  palTogglePad(GPIOD, GPIOD_LED6);
  	
/* ---------- Normal use ---------- */
  if (auto_calib == FALSE)
	{
		task_cycle = 0;
    calib_degree = 0;

    cl_degree_ICU = rsICUValues();
    cl_different = 58;
    cl_degree_ass = calcAdc2Deg(cl_degree_ICU, PHASE_PAIR);
    cl_degree = calcDegOffset(cl_degree_ass, cl_different);
		/* -----Motor control section----- */

    pulseDirection(cl_direction);
		//pulseDirection(cl_direction);
    pulseControl_2(cl_degree, cl_width);
	}

	gptStartOneShotI(&GPTD14, 250);
	chSysUnlockFromISR();
}


static const GPTConfig gpt4cfg = {
  28e6,    /* 10kHz timer clock.*/
  gptcb,    /* Timer callback.*/
  0,
  0
};

void controlInit(void) {
	cl_width = 9000;
	cl_direction = 1;
	auto_calib = FALSE;
  spi_icu_calib_cycle = 0;

	gptStart(&GPTD14, &gpt4cfg);

	gptStartOneShot(&GPTD14, 1000);
}

void controlCalc(void) {
	/* -----Limit & block section----- */

  /* ------------------------------- */
  /* ------- Auto offset calib mod -------- */
    if (auto_calib)
    {
      cl_degree_ICU = rsICUValues();
      cl_degree_ICU = calcAdc2Deg(cl_degree_ICU, PHASE_PAIR);

      task_cycle++;
      if (task_cycle > 1)
      {
        task_cycle = 0;
        calib_degree += 10;
        calib_degree = calib_degree > 359 ? 0 : calib_degree;
      }
      pulseDirection(cl_direction);
      pulseControl_2(calib_degree, cl_width);

      if (calib_degree > cl_degree_ICU)
      {
        cl_auto_mod_different = calib_degree - cl_degree_ICU;

        diff_index++;
        if(diff_index > (AVG_10_TMB - 1)){
          diff_index = 0;
        }
        avg_diff[diff_index] = cl_auto_mod_different;
        diffasis = 0;
        for (i = 0; i < AVG_10_TMB; i++){
          diffasis += avg_diff[i];
        }
        cl_auto_mod_different = diffasis / AVG_10_TMB;
        if(cl_auto_mod_different < 0){
          cl_auto_mod_different = 0;
        }
      }
    }
    /* ------------------------------- */
}

void degreeCalibOn(void) {
	calib_degree = 0;
	auto_calib = TRUE;
}

void degreeCalibOff(void) {
  auto_calib = FALSE;
}

void motorOff(void) {
  cl_width = 0;
}

uint16_t controlValues(void){
  return cl_auto_mod_different;
}

void cmd_controlSet(BaseSequentialStream *chp, int argc, char *argv[]) {
 
  (void)argc;
  (void)argv;

  uint32_t in;
 
  if ((argc == 2) && (strcmp(argv[0], "direction") == 0)){
    in = atol(argv[1]);

    if (in < 1 || in > 2)
    {
      goto ERROR;
    }
    else
    {
      cl_direction = (uint32_t)in;
      chprintf(chp,"Set direction: %d\r\n", cl_direction);
      return;
    }
  }

  else{
  goto ERROR;
  }

ERROR:
  chprintf(chp, "Usage: direction (1 - 2)\r\n");
  return;
}

void cmd_motorSet(BaseSequentialStream *chp, int argc, char *argv[]) {
 
  (void)argc;
  (void)argv;
 
  if ((argc == 1) && (strcmp(argv[0], "on") == 0)){
    cl_width = 9000;
  }

  else if ((argc == 1) && (strcmp(argv[0], "off") == 0)){
    cl_width = 0;
  }

  else{
  goto ERROR;
  }

ERROR:
  chprintf(chp, "Usage: motor on/off\r\n");
  return;
}

void cmd_autoCalib(BaseSequentialStream *chp, int argc, char *argv[]) {
 
  (void)argc;
  (void)argv;

  if ((argc == 1) && (strcmp(argv[0], "on") == 0)){
    degreeCalibOn();
    chprintf(chp,"Automatic calibration on!\r\n");
  }

  else if ((argc == 1) && (strcmp(argv[0], "off") == 0)){
    degreeCalibOff();
    chprintf(chp,"Automatic calibration off!\r\n");
  }

  else{
  goto ERROR;
  }

ERROR:
  chprintf(chp, "Usage: auto_calib on/off\r\n");
  return;
}
//3264
void cmd_controlValues(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argc;
  (void)argv;
  chprintf(chp, "\x1B\x63");
  chprintf(chp, "\x1B[2J");
  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
      chprintf(chp, "\x1B[%d;%dH", 0, 0);

      chprintf(chp, "Degree motor control: %5d\r\n", cl_degree);
      chprintf(chp, "\r\n");
      chprintf(chp, "RDVEL: %20d\r\n", cl_rdvel);
      chprintf(chp, "DOS: %22d\r\n", cl_dos);
      chprintf(chp, "LOT: %22d\r\n", cl_lot);
      chprintf(chp, "PAR: %22d\r\n", cl_par);
      chprintf(chp, "\r\n");
      chprintf(chp, "Manual different: %9d\r\n", cl_different);
      chprintf(chp, "\r\n");
      chprintf(chp, "auto_calib: %15d\r\n", auto_calib);
      chprintf(chp, "calib_degree: %13d\r\n", calib_degree);
      chprintf(chp, "\r\n");
      chprintf(chp, "Degree SPI: %15d\r\n", cl_degree_SPI);
      chprintf(chp, "Degree ICU: %15d\r\n", cl_degree_ICU);
      chprintf(chp, "\r\n");
      chprintf(chp, "Auto mod different: %7d\r\n", cl_auto_mod_different);

      chThdSleepMilliseconds(100);
  }
}