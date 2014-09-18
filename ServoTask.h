/*
 * Run a servo
 * 
 * This class controls a non-continuous servo using the Servo library. It uses
 * DelayTask to give the servo enough time to reach its setpoint (that time
 * can be configured in Constants.h). This is the only task that will not 
 * completely stop when its stop() method is called, because a servo cannot be
 * reliably stopped while moving to its setpoint. The Servo object is static
 * to avoid allocating more than 12 servos, which causes the Servo class to 
 * take over Timer1.
 */

#ifndef SERVO_TASK
#define SERVO_TASK

#include "DelayTask.h"
#include <Servo.h>

class ServoTask : public DelayTask {
public: 
  ServoTask(unsigned int pin, int pos, unsigned long delayTime)
    : pin(pin), pos(pos), DelayTask(delayTime) {}
  
  // Override standard Task functions
  void start(unsigned long currTime);
  virtual void finish();
  
  // Cannot relably stop a servo, so don't try
  // (only driving is actually required to stop)
  void stop(unsigned long currTime) {}
  void resume(unsigned long currTime) {}
  
  // Do not override printDescription to enforce subclassing of this class
  // rather than using it directly.
  virtual void printDescription() = 0;
  
  // Use an overridable getter to get a reference to the servo rather than
  // referring to it directly so subclasses can provide their own Servo object.
  // For example, BrakeTask uses this feature to keep its own Servo instance 
  // that is never detached so the brake is never lowered by gravity.
  virtual Servo& getServo();

private:
  unsigned short pin;
  int pos;
  
  // This needs to be static because if over 12 instances are allocated
  // then Servo takes over Timer1, making heartbeats stop
  static Servo srv;
};

#endif
