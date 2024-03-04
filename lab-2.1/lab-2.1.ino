#include <Arduino.h>

#include "./src/functions.h"
#include "./src/Button.h"
#include "./src/Timer.h"
#include "./src/Led.h"
#include "./src/definitions.h"
#include "./src/tasks.h"
#include "./src/parallel.h"

void setup()
{
  initStdio();
  initTasks();
  initTimer();
}

void loop()
{
  delay(LOOP_DELAY);

  if (executeTasks & TASK_TOGGLE_LED)
    toggleLedTask();

  if (executeTasks & TASK_CHANGE_DELAY)
    changeDelayTask();

  idleTask();

  executeTasks = TASK_NONE;
}
