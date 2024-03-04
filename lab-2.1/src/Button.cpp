#include "Button.h"

int Button::debounceMs = 50;

Button::Button() = default;

Button::Button(int _pin) : pin { _pin }
{
  pinMode(pin, INPUT_PULLUP);
}

void Button::update()
{
  unsigned long now = millis();

  if (now - changeTimestamp <= debounceMs) return;

  changeTimestamp = now;
  prevPressed = isPressed;
  isPressed = digitalRead(pin) == LOW;

  if (isPressed == prevPressed) return;

  if (!prevPressed && isPressed && onDown != nullptr) onDown();
  if (prevPressed && !isPressed && onUp != nullptr) onUp();
  if (onChange != nullptr) onChange();
}
