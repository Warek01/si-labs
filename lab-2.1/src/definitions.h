#pragma once

enum Event
{
  EVENT_NONE = 0,
  EVENT_RESET = 1,
  EVENT_TOGGLE_LED = 2,
  EVENT_INC_DELAY = 4,
  EVENT_DEC_DELAY = 8,
};

enum Prescaler
{
  PRESCALER_0 = 0,
  PRESCALER_1 = (1 << CS10),
  PRESCALER_8 = (1 << CS11),
  PRESCALER_64 = (1 << CS11) | (1 << CS10),
  PRESCALER_256 = (1 << CS12),
  PRESCALER_1024 = (1 << CS12) | (1 << CS11)
};

enum Interrupt
{
  COMPA_INTERRUPT = (1 << OCIE1A),
  COMPB_INTERRUPT = (1 << OCIE1B),
  OVF_INTERRUPT = (1 << TOIE1)
};

enum Task
{
  TASK_NONE = 0,
  TASK_TOGGLE_LED = 1,
  TASK_CHANGE_DELAY = 2
};

#define LOOP_DELAY 100

#define REC_OFST_TOGGLE_LED 2
#define REC_OFST_CHANGE_DELAY 0

#define REC_TOGGLE_LED 1
#define REC_CHANGE_DELAY 0

#define LED_INITIAL_DELAY 500
#define MIN_LED_DELAY 100
#define MAX_LED_DELAY 2000
#define LED_DELAY_STEP 100

#define LED_1_PIN 2
#define LED_2_PIN 3
#define BTN_RST_PIN 4
#define BTN_SWC_PIN 5
#define BTN_DEC_PIN 6
#define BTN_INC_PIN 7
