# Simple Relay State Machine for Arduino

## Circuit

Connect signal 1 of relay to `pin 4` and signal 2 to `pin 3`.

## States

To change the state into clockwise rotation `CWTURN_STATE`, send the string `CW` to the Serial Monitor.

To change the state into counter-clockwise rotation `CCWTURN_STATE`, send the string `CCW` to the Serial Monitor.

Any other string will stop rotation and set the state machine to the `IDLE_STATE` state.

***
(c) TOROS Dev Team - 2018
