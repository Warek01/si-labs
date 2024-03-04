#pragma once

#include <Arduino.h>
#include <stdint.h>

// Wrapper around button with debounce
class Button
{
public:
  static int debounceMs;

  bool isPressed = false;
  
  void (*onChange)() = nullptr;
  void (*onUp)() = nullptr;
  void (*onDown)() = nullptr;

  Button();
  Button(int pin);

  void update();

private:
  int pin = 0;
  bool prevPressed = false;
  unsigned long changeTimestamp = 0;
};
