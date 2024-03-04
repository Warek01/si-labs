#pragma once

#include <Arduino.h>
#include <stdio.h>

// Returns available memory in bytes for debug purposes
int availableMemory()
{
  int size = 2048;
  byte* buf;

  while ((buf = new byte[size--]) == nullptr);

  delete buf;
  return size;
}

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
  Serial.write(c);
}

void initStdio()
{
  initSerial();
  stdin = stdout = fdevopen(customStdioPut, customStdioGet);
}
