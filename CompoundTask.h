/*
 * Base compound task class -- all compound tasks inherit from this
 */

#ifndef COMPOUND_TASK_H
#define COMPOUND_TASK_H

#include "BaseTask.h"
#include "TaskRunner.h"

class CompoundTask : public Task {
protected:
  TaskRunner tasks;
  
public:
  CompoundTask() {}
  // All methods are implemented, the subclass only needs to override the constructor
  virtual void start(unsigned long currTime) { tasks.start(currTime); };
  virtual void update(unsigned long currTime) { tasks.update(currTime); }
  virtual bool isFinished(unsigned long currTime) { return tasks.isFinished(); }
  virtual void printDescription();
  virtual void stop(unsigned long currTime);
  virtual void resume(unsigned long currTime);
};

#endif