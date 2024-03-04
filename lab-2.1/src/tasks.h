#pragma once

#include <Arduino.h>

#include "Timer.h"
#include "definitions.h"
#include "Button.h"
#include "Led.h"
#include "functions.h"

void onSwcBtnUp();
void onRstBtnUp();
void onIncBtnUp();
void onDecBtnUp();

Button swcBtn;
Button incBtn;
Button decBtn;
Button rstBtn;
Led led1;
Led led2;

int ledDelay = LED_INITIAL_DELAY;
byte event = EVENT_NONE;

void initTasks()
{
  led1 = Led(LED_1_PIN);
  led2 = Led(LED_2_PIN);
  swcBtn = Button(BTN_SWC_PIN);
  incBtn = Button(BTN_INC_PIN);
  decBtn = Button(BTN_DEC_PIN);
  rstBtn = Button(BTN_RST_PIN);

  led1.on();
  led2.off();

  swcBtn.onUp = onSwcBtnUp;
  incBtn.onUp = onIncBtnUp;
  decBtn.onUp = onDecBtnUp;
  rstBtn.onUp = onRstBtnUp;
}

void toggleLedTask()
{
  // printf("aaaaa\r\n");
  swcBtn.update();
}

void changeDelayTask()
{
  incBtn.update();
  decBtn.update();

  static Timer t;

  if (led1.isOn() || t.elapsed() < ledDelay) return;

  led2.toggle();
  t.reset();
}

void idleTask()
{
  rstBtn.update();

  // if (event & EVENT_RESET) printf("Reset\r\n");
  // if (event & EVENT_TOGGLE_LED) printf("Toggle\r\n");
  // if (event & EVENT_INC_DELAY) printf("Increment (%d)\r\n", ledDelay);
  // if (event & EVENT_DEC_DELAY) printf("Decrement (%d)\r\n", ledDelay);

  event = EVENT_NONE;
}

// ----------------
// Button callbacks
void onSwcBtnUp()
{
  led1.toggle();
  led2.off();
  event |= EVENT_TOGGLE_LED;
}

void onIncBtnUp()
{
  event |= EVENT_INC_DELAY;

  if (ledDelay < MAX_LED_DELAY)
    ledDelay += LED_DELAY_STEP;
}

void onDecBtnUp()
{
  event |= EVENT_DEC_DELAY;

  if (ledDelay > MIN_LED_DELAY)
    ledDelay -= LED_DELAY_STEP;
}

void onRstBtnUp()
{
  led1.on();
  led2.off();
  event |= EVENT_RESET;
  ledDelay = LED_INITIAL_DELAY;
}

