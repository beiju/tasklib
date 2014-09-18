/*
 * Restart Task Runner -- set the task runner to start from the beginning
 */

#include "BaseTask.h"
#include "TaskRunner.h"

class RestartTaskRunnerTask : public Task {
private:
  TaskRunner& taskRunner;
public:
  RestartTaskRunnerTask(TaskRunner& runner) : taskRunner(runner) {};
  void start(unsigned long currTime) { taskRunner.reset(currTime); }
  void update(unsigned long currTime) {}
  bool isFinished(unsigned long currTime) { return true; }
  void printDescription() { Serial << "Reset Task Mamager" << endl; }
};
