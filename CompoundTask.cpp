#include "CompoundTask.h"

void CompoundTask::printDescription() { 
  tasks.printState(); 
}

void CompoundTask::stop(unsigned long currTime) {
  tasks.stop(currTime);
}

void CompoundTask::resume(unsigned long currTime) {
  tasks.resume(currTime);
}