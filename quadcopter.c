#include "quadcopter.h"

void update_motor_outputs(UINT8 throttle, Attitude *control_variables, MotorOutputs *motor_outputs){
  motor_outputs->frontRight = throttle - control_variables->pitch + control_variables->roll - control_variables->yaw;
  motor_outputs->backRight  = throttle + control_variables->pitch + control_variables->roll + control_variables->yaw;
  motor_outputs->backLeft   = throttle + control_variables->pitch - control_variables->roll - control_variables->yaw;
  motor_outputs->frontLeft  = throttle - control_variables->pitch - control_variables->roll - control_variables->yaw;
}

void update_control_variable(Axis *axis){

  UINT8 error;
  UINT8 error_delta;

  error = axis->target_value - axis->current_value;
  axis->cumulative_error += error;
  error_delta = error - axis->previous_error;
  axis->previous_error = error;

  axis->control_variable = axis->P*error + axis->I*cumulative_error + axis->D*error_delta;
}
