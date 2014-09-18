#include "ServoTask.h"

// Initialize the static Servo
Servo ServoTask::srv = Servo();


void ServoTask::start(unsigned long currTime) {
  // Set the servo value
  // (The integer value of the action is set to the correct position of the servo)
  this->getServo().attach(this->pin);
  this->getServo().write(this->pos);
  
  // Then start the parent delay task to wait for the servo to actuate
  this->DelayTask::start(currTime);
}

void ServoTask::finish() {
  this->getServo().detach();
}

Servo& ServoTask::getServo() {
  return this->srv;
}