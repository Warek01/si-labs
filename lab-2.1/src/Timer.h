#pragma once

#include <Arduino.h>

class Timer
{
public:
  Timer();

  void reset();
  unsigned long elapsed();

private:
  unsigned long _start;
};
