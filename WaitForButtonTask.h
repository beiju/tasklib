/*
 * Waits for a button to be pressed
 */

#ifndef WAIT_FOR_BUTTON_TASK_H
#define WAIT_FOR_BUTTON_TASK_H

#include "BaseTask.h"

class WaitForButtonTask : public Task {
private:
  int pin;
  volatile bool pushed;
  bool paused;
  
  static void isr();
  static WaitForButtonTask* instance;
  
public:
  WaitForButtonTask(int pin) : pin(pin), pushed(false), paused(false) {};
  void start(unsigned long currTime);
  void stop(unsigned long currTime);
  void resume(unsigned long currTime);
  void update(unsigned long currTime) { return; }
  bool isFinished(unsigned long currTime);
  void printDescription();

  static int interruptFromPin(int pin);
};

#endif
