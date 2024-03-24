#pragma once

#include <Arduino.h>
#include <stdio.h>

void initSerial(unsigned long baudRate = 115200ul)
{
  Serial.begin(baudRate);
  while (!Serial);
}

int customStdioGet(FILE* f)
{
  while (!Serial.available());
  return Serial.read();
}

int customStdioPut(char c, FILE* f)
{
  return Serial.write(c);
}

void initStdio()
{
  initSerial();
  stdin = stdout = fdevopen(customStdioPut, customStdioGet);
}
