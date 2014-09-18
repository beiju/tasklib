/*
 * Empty task -- does nothing.
 */
#ifndef EMPTY_TASK
#define EMPTY_TASK

#include "BaseTask.h"

class EmptyTask : public Task {
public:
  void start(unsigned long currTime) {}
  void update(unsigned long currTime) {}
  bool isFinished(unsigned long currTime) { return true; }
  bool isEmptyTask() { return true; }
  void printDescription() { Serial << "Empty task" << endl; }
  void stop(unsigned long currTime) {}
  void resume(unsigned long currTime) {}
  
};

#endif
