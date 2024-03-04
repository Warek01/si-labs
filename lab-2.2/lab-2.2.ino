#include "./src/functions.h"
#include "./src/Button.h"
#include "./src/Timer.h"
#include "./src/Led.h"
#include "./src/definitions.h"
#include "./src/tasks.h"

void setup()
{
  initStdio();
  initTasks();

  xTaskCreate(toggleLedTask, "Toggle", 256, nullptr, 1, nullptr);
  xTaskCreate(changeDelayTask, "Delay", 256, nullptr, 1, nullptr);
  xTaskCreate(idleTask, "Idle", 256, nullptr, 2, nullptr);
  vTaskStartScheduler();

  printf("Should not print");
}

void loop()
{
}
