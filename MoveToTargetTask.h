#ifndef MOVE_TO_TARGET_TASK
#define MOVE_TO_TARGET_TASK

#include "BaseTask.h"
#include <Servo.h>

/*
 * Move a sensor to target
 */
class MoveToTargetTask : public Task {
protected:
  float targetSpd;
  int targetPos;
  int distanceThreshold; // 10
  float speedThreshold; // 0.01
  int targetCountThreshold; // 5
  int minUpdatePeriod; // 50
  int minMotorSpeed; // 12
  int maxMotorSpeed; // 168
  unsigned long prevTime;
  
  // Implementation details that are up to the subclass to provide
  virtual int getSensorVal() = 0;
  virtual bool isAtTarget(int sensorVal) = 0;
  virtual float getSpeed(int sensorVal, int deltaT) = 0;
  virtual bool driveReverse(int sensorVal) = 0;
  
private:
  int targetCount;
  unsigned short motorPin;
  
  // This needs to be static because if over 12 instances are allocated
  // then Servo takes over Timer1, making heartbeats stop
  static Servo srv;
  
public:
  // NOTE: Subclasses must set _all_ the protected variables in their constructor
  MoveToTargetTask(unsigned short pin) : motorPin(pin) {}
  virtual void start(unsigned long currTime);
  virtual void stop(unsigned long currTime);
  // Subclasses should override this, reset their sensor values, and call MoveToTargetTask::resume
  virtual void resume(unsigned long currTime); 
  virtual void finish(); // Called when the task is finished
  void update(unsigned long currTime);
  bool isFinished(unsigned long currTime);
  void printProgress();
};

#endif