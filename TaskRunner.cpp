#include "TaskRunner.h"


TaskRunner::TaskRunner() : currTask(0), started(false), shouldStartTask(false) {}

void TaskRunner::addTask(Task* t) {
  this->tasks.push_back(t);
  
  if (this->isFinished()) {
    // If the runner is finished when a task is added, update() won't call
    // its start function without otherwise being told to
    this->shouldStartTask = true;
  }            
}

Task* TaskRunner::currentTask() {
  if (this->currTask >= this->tasks.size()) {
    // Then all the tasks have finished
    return NULL;               
  } else {                     
    return this->tasks[ this->currTask ];
  }
}

bool TaskRunner::isStarted() {
  return this->started;
}

bool TaskRunner::isFinished() {
  return this->currentTask() == NULL;
}

void TaskRunner::start(unsigned long delayTime) {
  this->started = true;
  this->currentTask()->start(delayTime);
}

void TaskRunner::stop(unsigned long delayTime) {
  DBG << "Stopping current task" << endl;
  this->started = false;
  this->currentTask()->stop(delayTime);
}

void TaskRunner::resume(unsigned long delayTime) {
  this->started = true;
  this->currentTask()->resume(delayTime);
}

void TaskRunner::reset(unsigned long delayTime) {
  this->currTask = 0;
  this->currentTask()->start(delayTime);
  this->update(delayTime);
}

void TaskRunner::update(unsigned long delayTime) {
  if (this->started == false) {
    // Then we haven't started yet or have been paused
    return;
  } else if (this->currentTask() == NULL) {
    // Then all the tasks have run to completion
    return;    
  } else {
    if (this->currentTask()->isFinished(delayTime)) {
      // Finish the current task
      this->currentTask()->finish();
      // Go to the next task
      this->currTask++;
      if (this->currentTask() != NULL) {
        // Start the new task
        this->currentTask()->start(delayTime);
        this->shouldStartTask = false;
        // Immediately perform another update
        this->update(delayTime);
      }
    } else if (this->shouldStartTask) {
      // Start then update the current task
      this->currentTask()->start(delayTime);
      this->shouldStartTask = false;
      this->currentTask()->update(delayTime);
    } else {
      // Update the current task
      this->currentTask()->update(delayTime);
    }
  }
}

void TaskRunner::printState() {
  if (this->started == false) {
    DBG << "(Stopped) Next Task: ";
  }
  
  DBG << "Task " << this->currTask << ":  ";
  
  if (this->currentTask() == NULL) {
    DBG << "No task" << endl;
  } else {
    this->currentTask()->printDescription();
  }
}