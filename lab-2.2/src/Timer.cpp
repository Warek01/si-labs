#include "Timer.h"

Timer::Timer()
{
  reset();
}

void Timer::reset()
{
  _start = millis();
}

unsigned long Timer::elapsed()
{
  return millis() - _start;
}
