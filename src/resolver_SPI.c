/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#include <stdio.h>
#include <math.h>

#include "resolver_SPI.h"

#include "chprintf.h"

#define SCK           13  //GPIOB_13
#define MISO          14  //GPIOB_14
#define MOSI          15  //GPIOB_15
#define CS            12  //GPIOB_12
#define SAMPLE        10  //GPIOE_10

#define MAX_RESOLVER  4095
#define MIN_RESOLVER  0

#define MAP_MAX       359
#define MAP_MIN       0

#define AVG_SIZE      100
#define AVG_SIZE_10   10

uint16_t pos;
uint16_t rdvel;
uint16_t dos;
uint16_t lot;
uint16_t par;

uint8_t rxbuf[2];

uint8_t bits[16];
int rd = 0;
int db = 0;
uint16_t assis;

uint16_t deg;
uint32_t szam;

static const SPIConfig hs_spicfg = {
  NULL,
  GPIOB,
  12,
  SPI_CR1_BR_2
};

/* ----- Resolver read ---- */
int32_t rsSPIRead(){

  uint8_t i;
  uint32_t szam_seged;

    rxbuf[0] = 0;
    rxbuf[1] = 0; 
    palClearPad(GPIOE, SAMPLE);
    spiAcquireBus(&SPID2);              /* Acquire ownership of the bus.    */
    spiStart(&SPID2, &hs_spicfg);       /* Setup transfer parameters.       */
    spiSelect(&SPID2);                  /* Slave Select assertion.          */

    spiReceive(&SPID2, 2, rxbuf);
    
    spiUnselect(&SPID2);                /* Slave Select de-assertion.       */
    spiReleaseBus(&SPID2);              /* Ownership release.               */

    palSetPad(GPIOE, SAMPLE);

    //chSysLock();
    pos = 0;
    pos = rxbuf[0] << 8;
    pos += rxbuf[1];
    szam = 0;
    assis = 0;
    assis = pos;
    db = 16;
    while (assis!=0)
    {
        db--;
        rd = assis%2;
        assis /= 2;
        bits[db] = rd;

        if (rd)
        {
          szam_seged = 1;
          for (i = 0; i < db; ++i)
          {
            szam_seged *= 2;
          }
          szam += szam_seged;
        }

        if(db == 0){
          break;
        }
    }
    db = 16;
    pos = pos >> 4;

    par = bits[15];
    lot = bits[14];
    dos = bits[13];
    rdvel = bits[12];
    //chSysUnlock();
    return pos;
}
/* ----------------------------*/

void rsSPIInit(void) {
  palSetPad(GPIOE, 10);
  palSetPad(GPIOB, 12);

  palSetPad(GPIOE, GPIOE_RDVEL);
}

void rsSPICalc(void) {
  deg = rsSPIRead();
}

uint16_t rsSPIValues(uint32_t num){
  return num == 1 ? rdvel : \
         num == 2 ? dos :   \
         num == 3 ? lot :   \
         num == 4 ? par : 0;
}

void cmd_rsSPIValues(BaseSequentialStream *chp, int argc, char *argv[]) {

  int i;

  (void)argc;
  (void)argv;
  chprintf(chp, "\x1B\x63");
  chprintf(chp, "\x1B[2J");
  while (chnGetTimeout((BaseChannel *)chp, TIME_IMMEDIATE) == Q_TIMEOUT) {
      chprintf(chp, "\x1B[%d;%dH", 0, 0);

      chprintf(chp, "rxbuf[0]: %15d\r\n", rxbuf[0]);
      chprintf(chp, "rxbuf[1]: %15d\r\n", rxbuf[1]);
      chprintf(chp, "\r\n\r\n");
      chprintf(chp, "pos: %15d\r\n", pos);
      chprintf(chp, "rdvel: %15d\r\n", rdvel);
      chprintf(chp, "dos: %15d\r\n", dos);
      chprintf(chp, "lot: %15d\r\n", lot);
      chprintf(chp, "par: %15d\r\n", par);
      chprintf(chp, "\r\n");
      for (i = 0; i < 16; ++i)
      {
        chprintf(chp, "%d", bits[i]);
        if (i == 7)
        {
          chprintf(chp, " ");
        }
        if (i == 11)
        {
          chprintf(chp, " ");
        }
      }
      chprintf(chp, "\r\n");
      chprintf(chp, "deg: %15d\r\n", deg);
      chprintf(chp, "szam: %15d\r\n", szam);

      chThdSleepMilliseconds(10);
  }
}




/*

10100000 1111 1000
10100001 0111 1000
10100001 1111 0000
10100010 0111 1000



*/