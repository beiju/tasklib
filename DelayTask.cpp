#include "DelayTask.h"

void DelayTask::start(unsigned long currTime) {
  this->endTime = currTime + this->delayTime;
//  Serial << "Started delay task, now is " << currTime << ", ending at "  << this->endTime << endl; 
}

void DelayTask::stop(unsigned long currTime) {
  this->pausedTime = currTime;
}

void DelayTask::resume(unsigned long currTime) {
  // Add the time it was stopped for to the end time
  this->endTime += currTime - this->pausedTime;
  this->pausedTime = 0; // pausedTime needs to be 0 for the task to finish
}

bool DelayTask::isFinished(unsigned long currTime) {
  return this->endTime != 0 && this->pausedTime == 0 && currTime >= this->endTime;
}

void DelayTask::printDescription() {
  DBG << "Delay for " << this->delayTime << "ms";
  
  if (this->endTime != 0) DBG << " (until " << this->endTime << ")";
  
  DBG << endl;
}
