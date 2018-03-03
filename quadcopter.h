#ifndef QUADCOPTER
#define QUADCOPTER

#ifdef __XC8
#include <htc.h>
#else
#include "dev_htc.h"
#endif

#include <stdint.h>

typedef struct {
  int8_t current_value;
  int8_t target_value;
  int8_t previous_error;
  int8_t cumulative_error;
  uint8_t P;
  uint8_t I;
  uint8_t D;
  int8_t control_var;
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

typedef struct{
  uint8_t front_right;
  uint8_t front_left;
  uint8_t back_right;
  uint8_t back_left;
}PWMCounters;

extern void IMU_init(void);
extern void PWM_init(MotorOutputs *motor_outputs, PWMCounters *pwm_counters);
extern void axis_init(Axis *axis);
extern void PWM_update(Axis *pitch, Axis *yaw, Axis *roll, uint8_t throttle, MotorOutputs *motor_outputs);
extern void reset_pwm_counters(PWMCounters *pwm_counters);
extern void update_motor_outputs(MotorOutputs *motor_outputs, PWMCounters *pwm_counters);
extern void update_control_variables(Axis *axis);

#endif
