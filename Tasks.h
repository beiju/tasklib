/**
 * This helper file includes all tasks. It exists to avoid cluttering up the
 * Bot.ino file with includes.
 */

#ifndef TASKS_H
#define TASKS_H

// Base Classes
#include "BaseTask.h"
#include "CompoundTask.h"

// General simple tasks
#include "EmptyTask.h"
#include "DelayTask.h"
#include "WaitForButtonTask.h"
#include "ResetTaskRunnerTask.h"

// Template tasks
#include "MoveToTargetTask.h"
#include "ServoTask.h"

// Specific simple tasks
#include "DriveAtSpeedTask.h"
#include "GripperGripTask.h"
#include "GripperMoveTask.h"
#include "RadiationStatusTask.h"
#include "BrakeTask.h"

// Specific compound tasks
#include "DriveTask.h"
#include "GripTask.h"

#endif