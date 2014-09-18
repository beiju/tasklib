/*
 * WaitForButtonTask
 */

#include "WaitForButtonTask.h"

WaitForButtonTask* WaitForButtonTask::instance = NULL;

void WaitForButtonTask::start(unsigned long currTime) {
  this->pushed = false;
  if (WaitForButtonTask::instance != NULL) {
    DBG << "Another WaitForButtonTask instance task is running. This one will not start." << endl; 
  } else {
    WaitForButtonTask::instance = this;
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(interruptFromPin(pin), WaitForButtonTask::isr, RISING);
  }
}

void WaitForButtonTask::stop(unsigned long currTime) {
  this->paused = true;
}

void WaitForButtonTask::resume(unsigned long currTime) {
  // If the button was pushed while it was paused, ignore it
  this->pushed = false;
  this->paused = false;
}

void WaitForButtonTask::isr() {
  if (WaitForButtonTask::instance != NULL) WaitForButtonTask::instance->pushed = true;
}

int WaitForButtonTask::interruptFromPin(int pin) {
  switch(pin) {
    case 2: return 0;
    case 3: return 1;
    case 21: return 2;
    case 20: return 3;
    case 19: return 4;
    case 18: return 5;
    
    default: return -1;
  }
}

bool WaitForButtonTask::isFinished(unsigned long currTime) {
  if (this->pushed && !this->paused) {
    detachInterrupt(interruptFromPin(pin));
    WaitForButtonTask::instance = NULL;
    return true;
  } else {
    return false;
  }
}

void WaitForButtonTask::printDescription() {
  DBG << "Waiting for button press on pin " << this->pin << endl;
}
