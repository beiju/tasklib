/*
 * Delay a certian amount of time
 */

#ifndef DELAY_TASK
#define DELAY_TASK

#include "BaseTask.h"
#include "Constants.h"

class DelayTask : public Task {
private:
  unsigned long endTime;
  unsigned long delayTime;
  unsigned long pausedTime;
public:
  DelayTask(unsigned long d) : delayTime(d), endTime(0), pausedTime(0) {};
  void start(unsigned long currTime);
  void stop(unsigned long currTime);
  void resume(unsigned long currTime);
  void update(unsigned long currTime) { return; }
  bool isFinished(unsigned long currTime);
  void printDescription();
};

#endif
