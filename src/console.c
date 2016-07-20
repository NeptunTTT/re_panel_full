/*
    Motor Controller - Copyright (C) 2016
    Neptun TTT Kft.              
*/

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ch.h"
#include "hal.h"

#include "test.h"
#include "shell.h"
#include "chprintf.h"

#include "console.h"
#include "resolver_ICU.h"
#include "resolver_SPI.h"
#include "control.h"

/* libc stub */
int _getpid(void) {return 1;}
/* libc stub */
void _exit(int i) {(void)i;}
/* libc stub */
#include <errno.h>
#undef errno
extern int errno;
int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  errno = EINVAL;
  return -1;
}

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)
#define TEST_WA_SIZE    THD_WORKING_AREA_SIZE(256)


static SerialConfig ser_cfg = {
  115200,
  0,
  0,
  0,
};

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
  size_t n, size;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreGetStatusX());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
  static const char *states[] = {CH_STATE_NAMES};
  thread_t *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: threads\r\n");
    return;
  }
  chprintf(chp, "    addr    stack prio refs     state time\r\n");
  tp = chRegFirstThread();
  do {
    chprintf(chp, "%08lx %08lx %4lu %4lu %9s\r\n",
            (uint32_t)tp, (uint32_t)tp->p_ctx.r13,
            (uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
            states[tp->p_state]);
    tp = chRegNextThread(tp);
  } while (tp != NULL);
}

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[]) {
  thread_t *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: test\r\n");
    return;
  }
  tp = chThdCreateFromHeap(NULL, TEST_WA_SIZE, chThdGetPriorityX(),
                           TestThread, chp);
  if (tp == NULL) {
    chprintf(chp, "out of memory\r\n");
    return;
  }
  chThdWait(tp);
}

void cmd_clear(BaseSequentialStream *chp, int argc, char *argv[]){

  (void)argv;
  chprintf(chp, "\x1B\x63");
  chprintf(chp, "\x1B[2J");
  chprintf(chp, "\x1B[%d;%dH", 0, 0);
}

thread_t *consoleThread;

static const ShellCommand commands[] = {
  {"mem", cmd_mem},
  {"threads", cmd_threads},
  {"test", cmd_test},
  {"clear", cmd_clear},

/* resolver_ICU.c */
  {"encoder", cmd_rsICUValues},

/* resolver_SPI.c */
  {"spi", cmd_rsSPIValues},

/* control.c */
  {"motor", cmd_motorSet},
  {"autocalib", cmd_autoCalib},
  {"control_values", cmd_controlValues},

  {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream  *)&SD1,
  commands
};

void consoleInit(void){
  /* Shell initialization.*/
  sdStart(&SD1, &ser_cfg);
  shellInit();
  consoleThread = NULL;
}

void consoleStart(void){
  if (!consoleThread) {
    consoleThread = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO);
  }
  else if (chThdTerminatedX(consoleThread)) {
    chThdRelease(consoleThread);    /* Recovers memory of the previous shell.   */
    consoleThread = NULL;           /* Triggers spawning of a new shell.        */
  }
}