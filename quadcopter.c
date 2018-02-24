
#include "quadcopter.h"

void update_motor_outputs(uint8_t throttle, Attitude *attitude, MotorOutputs *motor_outputs){
  motor_outputs->front_right = throttle - attitude->pitch.control_var + attitude->roll.control_var - attitude->yaw.control_var;
  motor_outputs->back_right  = throttle + attitude->pitch.control_var + attitude->roll.control_var + attitude->yaw.control_var;
  motor_outputs->back_left   = throttle + attitude->pitch.control_var - attitude->roll.control_var - attitude->yaw.control_var;
  motor_outputs->front_left  = throttle - attitude->pitch.control_var - attitude->roll.control_var - attitude->yaw.control_var;
}

void update_control_variables(Axis *axis){

  uint8_t error;
  uint8_t error_delta;

  error = axis->target_value - axis->current_value;
  axis->cumulative_error += error;
  error_delta = error - axis->previous_error;
  axis->previous_error = error;

  axis->control_var = axis->P*error + axis->I*axis->cumulative_error + axis->D*error_delta;
}
