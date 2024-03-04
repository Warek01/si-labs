#pragma once

#include "Arduino.h"

class Led
{
public:
  Led();
  Led(int8_t pin);

  bool isOn();
  void toggle();
  void on();
  void off();

private:
  int8_t _pin;

  void powerOff();
  void powerOn();
};
