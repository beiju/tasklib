#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include <vector.h>
#include <Streaming.h>
#include "BaseTask.h"

class TaskRunner {
private:
  Vector<Task*> tasks;
  int currTask;
  bool started;
  bool shouldStartTask;
  
public:
  TaskRunner();
  
  void addTask(Task* t);
  
  Task* currentTask();
  
  bool isStarted();
  bool isFinished();
  
  void start(unsigned long delayTime);
  void stop(unsigned long delayTime);
  void resume(unsigned long delayTime);

  void update(unsigned long delayTime);
  
  // May only called in a task's start() function
  void reset(unsigned long delayTime);
  
  void printState();
};

#endif