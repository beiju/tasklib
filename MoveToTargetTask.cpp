#include "MoveToTargetTask.h"

// Initialize the static Servo
Servo MoveToTargetTask::srv = Servo();

void MoveToTargetTask::start(unsigned long currTime) { 
//  DBG << "Starting MTTT with speed " << this->targetSpd << endl;
  srv.attach(this->motorPin); 
  srv.write(90);
  // Reset target count and prevTime
  this->targetCount = 0;
  this->prevTime = currTime;
}

void MoveToTargetTask::stop(unsigned long currTime) {
  srv.write(90);
}

void MoveToTargetTask::resume(unsigned long currTime) {
  // Don't update immediately because sensor values will be all wonky
  this->prevTime = currTime;
  // Subclasses are responsible for resetting their sensor values
}

void MoveToTargetTask::finish() {
  srv.write(0); 
  delay(100); // TODO: No delays!
  srv.detach();
  
}

void MoveToTargetTask::update(unsigned long currTime) {
  int sensorVal = this->getSensorVal();
//  DBG << "sensor val: " << sensorVal << "\t";
    
  // If system is at target, increment the target counter
  if (this->isAtTarget(sensorVal)) {
    this->targetCount++;
  }
  
  // If the target counter is at or above its threshold, we are at setpoint 
  if (this->targetCount >= this->targetCountThreshold) {
    srv.write(90);
    return;
  }
    
  // If the minimum update period has not passed, skip this
  // (this also avoids a divide by zero error when cacluating spd)
  // DBG << "CurrT: " << currTime << "\tPrevT: " << this->prevTime << "\t";
  // DBG << "Delta t: " << (currTime - this->prevTime) << "\t" << endl;
  int deltaT = currTime - this->prevTime;
  if (deltaT < this->minUpdatePeriod) return; // Update at most every 50 ms
  this->prevTime = currTime;
  
  // Speed is delta pos over delta time
  float spd = this->getSpeed(sensorVal, deltaT);
  
  // Speed target is the target speed in the correct direction
  float spdTarget = this->targetSpd * (this->driveReverse(sensorVal) ? -1 : 1);
  
//  DBG << "Speed: " << spd << "\ttarget:" << spdTarget << "\t";
//  DBG << "Spd: " << spd << "\ttarget:" << spdTarget;
  
  if (spdTarget - spd <= this->speedThreshold * -1 && srv.read() < this->maxMotorSpeed) {
    //x If the speed is lower than the threshold but higher than the max speed, slow down
    srv.write(srv.read() + 1);
  } else if (spdTarget - spd >= this->speedThreshold && srv.read() > this->minMotorSpeed) {
    //x If the speed is higher than the threshold but higher than the max speed, speed up
    srv.write(srv.read() - 1);
  }
  
//  DBG << "motor val: " << srv.read() << "\t";
  
  
//  DBG << endl;
  return;
}

bool MoveToTargetTask::isFinished(unsigned long currTime) {
  return this->targetCount >= this->targetCountThreshold;
}

void MoveToTargetTask::printProgress() {
  DBG << "Target: " << this->targetPos << ", Currently: " << this->getSensorVal() << endl;
}
