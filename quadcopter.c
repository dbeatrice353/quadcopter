#include "quadcopter.h"

void update_motor_outputs(UINT8 throttle, Attitude *control_variables, MotorOutputs *motor_outputs){
  motor_outputs->frontRight = throttle - control_variables->pitch + control_variables->roll - control_variables->yaw;
  motor_outputs->backRight  = throttle + control_variables->pitch + control_variables->roll + control_variables->yaw;
  motor_outputs->backLeft   = throttle + control_variables->pitch - control_variables->roll - control_variables->yaw;
  motor_outputs->frontLeft  = throttle - control_variables->pitch - control_variables->roll - control_variables->yaw;
}

void update_control_variables(UINT8 current_value,
                              UINT8 target_value,
                              UINT8 *previous_error,
                              UINT8 *cumulative_error,
                              UINT8 *control_variable){
  const UINT8 P = 30;
  const UINT8 I = 30;
  const UINT8 D = 30;

  UINT8 error;
  UINT8 error_delta;

  error = target_value - current_value;
  *cumulative_error += error;
  error_delta = error - *previous_error;
  *previous_error = error;

  *control_variable = P*error + I*cumulative_error + D*error_delta;
}
