#include <Wire.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "lib.hpp"
#include "functions.hpp"

#define BUFFER_SIZE 5
#define NOISE_RANDOM_SCALE 30
#define THERMISTOR_ANALOG_PIN A0
#define BAUD_RATE 9600
#define LOOP_DELAY 200
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4
#define CELSIUS_SYMBOL ((char)223)
#define PIN_TRIG 2
#define PIN_ECHO 3
#define LCD_ROW_1 0
#define LCD_ROW_2 1
#define LCD_ROW_3 2
#define LCD_ROW_4 3
#define LCD_COL_1 0

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
int* tempBuffer = new int[BUFFER_SIZE];
int* distBuffer = new int[BUFFER_SIZE];
int* weights = new int[BUFFER_SIZE];
int tempBufferIndex = 0;
int distBufferIndex = 0;
int average = 0;
int weightedAverage = 0;
char floatBuffer[10];

void printTemp();
void printDistance();

void setup()
{
  initStdio();

  pinMode(THERMISTOR_ANALOG_PIN, INPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  lcd.init();
  lcd.backlight();

  for (int i = 0; i < BUFFER_SIZE; i++)
    weights[i] = BUFFER_SIZE;
}

void loop()
{
  ultrasonicBlink(PIN_TRIG);
  int rawUltrasonicDuration = addRandom(pulseIn(PIN_ECHO, HIGH), NOISE_RANDOM_SCALE);
  distBuffer[distBufferIndex++] = rawUltrasonicDuration;

  int tempAnalogValue = analogRead(THERMISTOR_ANALOG_PIN);
  int rawTemp = addRandom(tempAnalogValue, NOISE_RANDOM_SCALE);
  tempBuffer[tempBufferIndex++] = rawTemp;

  if (tempBufferIndex == BUFFER_SIZE)
    printTemp();

  if (distBufferIndex == BUFFER_SIZE)
    printDistance();

  delay(LOOP_DELAY);
}

void printTemp()
{
  average = getAverage(tempBuffer, BUFFER_SIZE);
  weightedAverage = getWeightedAverage(tempBuffer, weights, BUFFER_SIZE);

  float celsiusAverage = analogToCelsius(average);
  float celsiusWeightedAverage = analogToCelsius(weightedAverage);
  float celsiusAverageVoltage = mapToVoltage(celsiusAverage);
  float celsiusWeightedAverageVoltage = mapToVoltage(celsiusWeightedAverage);

  dtostrf(celsiusAverageVoltage, 7, 5, floatBuffer);
  printf("Temperature average voltage: %s V\r\n", floatBuffer);
  dtostrf(celsiusWeightedAverageVoltage, 7, 5, floatBuffer);
  printf("Temperature weighted average voltage: %s V\r\n", floatBuffer);

  clearBuffer(tempBuffer, BUFFER_SIZE);
  tempBufferIndex = 0;

  clearLcdRow(lcd, LCD_ROW_1, LCD_COLUMNS);
  clearLcdRow(lcd, LCD_ROW_2, LCD_COLUMNS);

  lcd.setCursor(LCD_COL_1, LCD_ROW_1);
  lcd.print(F("Average: "));
  lcd.print(celsiusAverage);

  lcd.setCursor(LCD_COL_1, LCD_ROW_2);
  lcd.print(F("Weighted: "));
  lcd.print(celsiusWeightedAverage);
}

void printDistance()
{
  average = getAverage(distBuffer, BUFFER_SIZE);
  weightedAverage = getWeightedAverage(distBuffer, weights, BUFFER_SIZE);

  float distAverage = durationToCm(average);
  float distWeightedAverage = durationToCm(weightedAverage);
  float distAverageVoltage = mapToVoltage(distAverage);
  float distWeightedAverageVoltage = mapToVoltage(distWeightedAverage);

  dtostrf(distAverageVoltage, 7, 5, floatBuffer);
  printf("Distance average voltage: %s V\r\n", floatBuffer);
  dtostrf(distWeightedAverageVoltage, 7, 5, floatBuffer);
  printf("Distance weighted average voltage: %s V\r\n\r\n", floatBuffer);

  clearBuffer(distBuffer, BUFFER_SIZE);
  distBufferIndex = 0;

  clearLcdRow(lcd, LCD_ROW_3, LCD_COLUMNS);
  clearLcdRow(lcd, LCD_ROW_4, LCD_COLUMNS);

  lcd.setCursor(LCD_COL_1, LCD_ROW_3);
  lcd.print(F("Average: "));
  lcd.print(distAverage);

  lcd.setCursor(LCD_COL_1, LCD_ROW_4);
  lcd.print(F("Weighted: "));
  lcd.print(distWeightedAverage);
}
