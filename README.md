TaskLib
=======

TaskLib is a flexible library for programming a task-based robot. It is ideal for rapid development of a bot that may have complex behaviors but does not have a complex decision chain. It is _not_ good for applications that require a small memory footprint or behavior that's heavily dependent on branching conditionals.

The core of TaskLib is the Task class. It defines a protocol/interface to describe any task that has a defined start and end and (ideally) can be paused for an indeterminate amount of time. The Task class is used by a TaskRunner, an object that runs a series of tasks sequentially. To use TaskLib, simply create a TaskRunner and give it a list of tasks.

```
TaskRunner tasks;

void setup() {
  tasks.addTask(new WaitForButtonTask(BUTTON_PIN));
  tasks.addTask(new DelayTask(1000 /*ms*/));
  tasks.addTask(new ServoTask(SERVO_PIN, 180));
  
  tasks.start(millis());
}

void loop() {
  tasks.update(millis());
}
```

The TaskRunner will run the WaitForButtonTask until it reports that the task has finished, which it does when the button is pressed. It will then run the DelayTask, which finishes after 1000ms, then it will run the ServoTask to move the servo to position 180. Once the TaskRunner is finished it will do nothing when the .update() method is called.

For more complex applications, it is recommended that users create subclasses of the tasks and make use of CompoundTasks to combine related tasks.

Built-In Tasks
--------------

* `EmptyTask`: Task that does nothing and is immediately finished.
* `DelayTask`: Task that does nothing for a certain amount of time (provided in milliseconds), then finishes.
* `WaitForButtonTask`: Task that does nothing until a button is pressed, then finishes.
* `ServoTask`: Task that sets a servo's position, then waits a certain amount of time. This is to give the servo time to reach its target, because servos' positions cannot be measured directly without some additional sensor.
* `MoveToTargetTask`: Task that moves a motor to a target based on a sensor. This task must be subclassed and the subclass must provide the implementation details for the sensor.
* `ResetTaskRunnerTask`: Task that restarts its own (or another) TaskRunner from the beginning. Useful for basic looping tasks. The TaskRunner to reset must be provided to the Task.
* `CompoundTask`: Task that represents several subtasks. This Task must be subclassed and the constructor overridden to create its own internal TaskRunner with the subtasks. This Task finishes when its internal TaskRunner finishes.

Potential Useful Tasks
----------------------

* `ParallelTask`: Task that operates similarly to CompoundTask but runs its tasks in parallel. Could finish when the first subtask finishes or when all subtasks finish.
* `LEDTask`: Task that blinks or toggles an LED.
* `SimpleTask`: Task that runs a given function, then finishes. Useful for incorporating external code into the TaskRunner system.

Usage
-----

* Include `TaskRunner.h` and `Tasks.h`. `Tasks.h` is a utility file that includes all the built-in tasks.
* Create a TaskRunner in setup() and fill it with tasks. Call start() to start the TaskRunner.
* Important: in loop(), call `taskrunner.update()`. Without this, your program will do nothing and you will be sad.
