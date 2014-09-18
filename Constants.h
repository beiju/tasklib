/**
 * Constants is a container for all the constant values needed by an Arduino
 * program, such as pin assignments and speed values.
 * 
 * Arduino pins that DON'T work (and the reason):
 * 11-13 (unknown), 9 - 10 (TimerOne)
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Motor/Servo Pins
#define GRIPPER_MOTOR_PIN 6
#define GRIPPER_SERVO_PIN 45
#define DRIVE_MOTOR_PIN 8
#define BRAKE_SERVO_PIN 7

// Sensor Pins
#define START_BTN_PIN 20
#define GRIPPER_POT_PIN A1
#define BUMP_SWITCH_PIN 3 // Must be interrupt-capable
// Encoder pin A must be interrupt-capable. 
#define DRIVE_ENCODER_PIN_A 2
// Encoder pin B should be interrupt-capable if possible.
#define DRIVE_ENCODER_PIN_B 33

// LED Pins
#define HEARTBEAT_LED 13
#define DEBUG_LED 25
#define RADIATION_MAX_LED A10
#define RADIATION_MIN_LED A11

// Other numbers
#define MY_ID 18

// Define DBG as a macro so it can be changed to different ports. Originally 
// we had a second Bluetooth module (our own, not from the RBE lab) that we were
// planning to use as a remote debugging tool. It went missing a few weeks ago.
#define DBG Serial

// Driving speeds (NOTE: cannot be the same because they're used as enum values)
#define DRIVE_SPD_LOW 1 // 1 counts/ms * (1 rev/3200 counts) * (1.375pi inches/ 1 rev) * (1000 ms / 1 sec) = 1.72 inches/sec
#define DRIVE_SPD_HIGH 5 // 5 counts/ms * (1 rev/3200 counts) * (1.375pi inches/ 1 rev) * (1000 ms / 1 sec) = 8.6 inches/sec

// Gripper track position values (NOTE: cannot be the same because they're used as enum values)
#define GRIPPER_RETRACTED_POS 930
#define GRIPPER_HORIZONTAL_POS 630
#define GRIPPER_LOVETAP_POS 660
#define GRIPPER_VERTICAL_POS 210

// Gripper open/close values (NOTE: cannot be the same because they're used as enum values)
#define GRIPPER_OPEN_POS 90
#define GRIPPER_CLOSED_POS 180
#define GRIPPER_GRIP_DELAY 500 // milliseconds

// Brake values (NOTE: cannot be the same because they're used as enum values)
#define BRAKE_DOWN_POS 90
#define BRAKE_UP_POS 160
#define BRAKE_DELAY 1000
#endif