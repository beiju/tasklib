/*
 * Base Task class -- all tasks inherit from this
 * 
 * This Task cannot be instantiated directly, and exists only to be the 
 * superclass of every other Task. It provides standard methods and forces
 * subclasses to implement them through the use of pure virtual functions. 
 * The comments in this file are the official documentation for the Task 
 * interface.
 */

#ifndef BASE_TASK_H
#define BASE_TASK_H

// These libraries are used in most Tasks, so I import them here for convenience
#include <Streaming.h> 
#include "Constants.h"


class Task {
public:
  /**
   * Every Task is required to have a start function. This function runs 
   * exactly once when the task begins, before the update function is called.
   * 
   * @param currTime The time at which the function is being called
   */
  virtual void start(unsigned long currTime) = 0;
  
  /**
   * Every Task is required to have an update function. This function is called
   * repeatedly while the task is running. It should update the state of the
   * task as quickly as possible and then return. There are no guarantees about
   * how often this function will be called. An update function may choose to
   * enforce a maximum frequency, but cannot enforce a minimum frequency.
   * 
   * @param currTime The time at which the function is being called
   */
  virtual void update(unsigned long currTime) = 0;
  
  /**
   * Every Task is required to have an isFinished function. This function is
   * called frequently and must return as quickly as possible. The first time
   * this function returns true, the task is regarded as complete. Its update
   * method will not be called again. Its finish function will be called exactly
   * once soon after the isFinished function returns true.
   * 
   * @param currTime The time at which the function is being called
   */
  virtual bool isFinished(unsigned long currTime) = 0;
  
  /**
   * Every Task is required to have a printDescription function. This function 
   * may be called at any time and should print a concise description of the 
   * task. The task may choose to report its name, its progress, and any other
   * useful information. This function return as quickly as possible.
   */
  virtual void printDescription() = 0;
  
  /**
   * Every Task may have a finish function. This function is called soon after
   * the function's isFinished function returns true. It should reverse any
   * changes made in the start function that may interfere with other parts of
   * the program.
   */
  virtual void finish() {}; // Optional
  
  /**
   * Every Task is required to have a stop function. This function may be called
   * at any time and signifies that the task should halt progress if at all 
   * possible. The Task's update function will not be called after its stop 
   * function is called but before its resume function is called. The task must
   * not complete in response to any event that occurs between a call to stop
   * and a call to resume, including the passage of time. Treat this function
   * like an emergency stop -- it is mandatory and must be followed.
   * 
   * @param currTime The time at which the function is being called.
   */
  virtual void stop(unsigned long currTime) = 0;
  
  /**
   * Every Task is required to have a resume function. This function may be
   * called at any time after the stop function has been called. It signifies
   * that the stop command has ended and the Task should resume. The Task should
   * ask as if program execution was frozen in the time between the call to stop
   * and the call to start, and the only thing that should be affected by a stop
   * and resume is the running time of the task.
   * 
   * @param currTime The time at which the function is being called.
   */
  virtual void resume(unsigned long currTime) = 0;
};

#endif