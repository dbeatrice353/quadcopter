
#include "interfaces.h"
#include "quadcopter.h"

void PWM_init(void){
    TRISC_buffer &= 0xC3;
    TRISC = TRISC_buffer;
    
    FRONT_LEFT_LOW();
    FRONT_RIGHT_LOW();
    BACK_LEFT_LOW();
    BACK_RIGHT_LOW();
}

void PWM_update(Axis *pitch, Axis *yaw, Axis *roll, uint8_t throttle, MotorOutputs *motor_outputs){
  motor_outputs->front_right = throttle - pitch->control_var + roll->control_var - yaw->control_var;
  motor_outputs->back_right = throttle + pitch->control_var + roll->control_var + yaw->control_var;
  motor_outputs->back_left = throttle + pitch->control_var - roll->control_var - yaw->control_var;
  motor_outputs->front_left = throttle - pitch->control_var - roll->control_var - yaw->control_var;
}

void update_control_variables(Axis *axis){

  int16_t error;
  int16_t error_delta;

  error = axis->target_value - axis->current_value;
  axis->cumulative_error += error;
  error_delta = error - axis->previous_error;
  axis->previous_error = error;

  axis->control_var = (axis->P*error)>>8;
  axis->control_var += (axis->I*axis->cumulative_error)>>8;
  axis->control_var += (axis->D*error_delta)>>8;
}

void update_motor_outputs(MotorOutputs *motor_outputs, PWMCounters *pwm_counters){
    if(motor_outputs->front_left > pwm_counters->front_left++){
        FRONT_LEFT_LOW();
    }else{
        FRONT_LEFT_HIGH();
    }
    
    if(motor_outputs->front_right > pwm_counters->front_right++){
        FRONT_RIGHT_LOW();
    }else{
        FRONT_RIGHT_HIGH();
    }
 
    if(motor_outputs->back_left > pwm_counters->back_left++){
        BACK_LEFT_LOW();
    }else{
        BACK_LEFT_HIGH();
    }
    
    if(motor_outputs->back_right > pwm_counters->back_right++){
        BACK_RIGHT_LOW();
    }else{
        BACK_RIGHT_HIGH();
    }
}


void IMU_init(void){

    uint8_t control_bits = 0x00;
    // initialize the accelerometer in the IMU
    control_bits = IMU_ACC_BANDWIDTH_100Hz | IMU_ACC_RANGE_16G | IMU_ACC_SAMPLE_RATE_416Hz;
    IMU_WRITE(IMU_CTRL1, control_bits);
    IMU_READ(IMU_CTRL4, &control_bits);
    control_bits |= IMU_ACC_BANDWIDTH_SELECT;
    IMU_WRITE(IMU_CTRL4, control_bits);

    // initialize the gyroscope in the IMU
    IMU_WRITE(IMU_CTRL2, IMU_GYRO_RANGE_2000dps | IMU_GYRO_SAMPLE_RATE_416Hz);
 }
