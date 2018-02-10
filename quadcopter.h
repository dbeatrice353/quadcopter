#ifndef QUADCOPTER
#define QUADCOPTER

#ifdef __XC8
// pic 8-bit architecture
#define UINT8 int
#else
// development on x86
#include <stdint.h>
#define UINT8 uint8_t
#define

struct Axis{
  UINT8 current_value;
  UINT8 target_value;
  UINT8 previous_error;
  UINT8 cumulative_error;
  UINT8 control_variable;
  UINT8 P;
  UINT8 I;
  UINT8 D;
  UINT8 gyro;
}

struct Attitude{
  Axis roll;
  Axis pitch;
  Axis yaw;
};

void update_motor_outputs(UINT8 throttle, Attitude *control_variables, MotorOutputs *motor_outputs);

void update_control_variables(Axis *axis);

#endif
