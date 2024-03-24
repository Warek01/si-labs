#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define THERMISTOR_BETA 3950

float analogToCelsius(int value)
{
  return 1 / (log(1 / (1023. / value - 1)) / THERMISTOR_BETA + 1.0 / 298.15) - 273.15;
}

int addRandom(int value, int scale)
{
  return value + random(scale) - scale / 2;
}

int getAverage(int* buffer, int bufferSize)
{
  long total = 0;

  for (int i = 0; i < bufferSize; i++)
    total += buffer[i];

  return total / bufferSize;
}

int getWeightedAverage(int* buffer, int* weights, int bufferSize)
{
  float filtered = 0.0;

  for (int i = 0; i < bufferSize; i++)
    filtered += buffer[i] / weights[i];

  return (int)filtered;
}

void clearBuffer(int* buffer, int bufferSize)
{
  for (int i = 0; i < bufferSize; i++)
    buffer[i] = 0;
}

float mapToVoltage(int analog)
{
  static const float inputMax = 1023.0;
  static const float outputMax = 5.0;

  return analog * outputMax / inputMax;
}

int mapToAnalog(float voltage)
{
  static const float inputRange = 1023.0;
  static const float outputRange = 5.0;

  float analogValue = inputRange * voltage / outputRange;

  return (int)analogValue + 0.5;
}

void ultrasonicBlink(int trigPin, int delay = 10)
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(delay);
  digitalWrite(trigPin, LOW);
}

void clearLcdRow(LiquidCrystal_I2C& lcd, int row, int colsCount)
{
  lcd.setCursor(0, row);

  for (int i = 0; i < colsCount; i++)
    lcd.print(" ");
}

float durationToCm(int duration)
{
  return (float) duration / 58;
}
