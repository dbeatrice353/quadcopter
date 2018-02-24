#ifndef QUADCOPTER
#define QUADCOPTER

#include <stdint.h>

typedef struct {
  uint8_t current_value;
  uint8_t target_value;
  uint8_t previous_error;
  uint8_t cumulative_error;
  uint8_t control_var;
  uint8_t P;
  uint8_t I;
  uint8_t D;
} Axis;

typedef struct{
  Axis roll;
  Axis pitch;
  Axis yaw;
} Attitude;

typedef struct{
  uint8_t front_right;
  uint8_t front_left;
  uint8_t back_right;
  uint8_t back_left;
} MotorOutputs;

extern void update_motor_outputs(Axis *pitch, Axis *yaw, Axis *roll, uint8_t throttle, MotorOutputs *motor_outputs);

extern void update_control_variables(Axis *axis);

#endif
