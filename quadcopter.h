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


struct Attitude{
  UINT8 roll;
  UINT8 pitch;
  UINT8 yaw;
};

struct MotorOutputs{
  UINT8 frontLeft;
  UINT8 frontRight;
  UINT8 backLeft;
  UINT8 backRight;
}

void update_motor_outputs(UINT8 throttle, Attitude *control_variables, MotorOutputs *motor_outputs);

void update_control_variables(UINT8 current_value,
                              UINT8 target_value,
                              UINT8 *previous_error,
                              UINT8 *cumulative_error,
                              UINT8 *control_variable);

#endif
