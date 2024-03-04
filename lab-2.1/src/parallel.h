#pragma once 

#include <Arduino.h>

#include "definitions.h"

volatile byte executeTasks = TASK_NONE;

ISR(TIMER1_OVF_vect)
{
  static int recToggleLed = REC_OFST_TOGGLE_LED;
  static int recChangeDelay = REC_OFST_CHANGE_DELAY;

  if (recToggleLed-- <= 0)
  {
    executeTasks |= TASK_TOGGLE_LED;
    recToggleLed = REC_TOGGLE_LED;
  }

  if (recChangeDelay-- <= 0)
  {
    executeTasks |= TASK_CHANGE_DELAY;
    recChangeDelay = REC_CHANGE_DELAY;
  }
}

void initTimer()
{
  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= PRESCALER_1;
  TIMSK1 |= OVF_INTERRUPT;

  interrupts();
}
