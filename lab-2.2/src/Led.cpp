#include "Led.h"

Led::Led() = default;

Led::Led(int8_t pin)
{
  pinMode(pin, OUTPUT);

  _pin = pin;
}

void Led::toggle()
{
  if (isOn()) off();
  else on();
}

bool Led::isOn()
{
  return (digitalRead(_pin) == HIGH);
}

void Led::on()
{
  digitalWrite(_pin, HIGH);
}

void Led::off()
{
  digitalWrite(_pin, LOW);
}
