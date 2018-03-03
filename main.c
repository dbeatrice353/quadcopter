
#ifdef __XC8
    #include <htc.h>
    #include <pic16f57.h>

    #pragma config OSC = XT   // Oscillator selection bits
    #pragma config WDT = OFF  // Watchdog timer enable bit (WDT disabled)
    #pragma config CP = OFF   // Code protection bit (Code protection off)

    #ifndef _XTAL_FREQ
    #define _XTAL_FREQ 4000000 // 4MHz
    #endif //_XTAL_FREQ
#else
    #include "dev_htc.h"
#endif //__XC8

#include <stdint.h>
#include "quadcopter.h"
#include "interfaces.h"

#define FILTER_LENGTH 5

int main(void){
    //char buffer;

    uint8_t i;
    uint8_t temp[2];
    Axis roll;
    Axis pitch;
    Axis yaw;

    MotorOutputs motor_outputs;
    PWMCounters pwm_counters;

    __delay_ms(100);

    axis_init(&pitch);
    axis_init(&yaw);
    axis_init(&roll);

    I2C_init();
    status_leds_init();
    push_button_init();
    output_init();
    IMU_init();
    PWM_init(&motor_outputs, &pwm_counters);

    red_status_off();
    green_status_on();

    write_to_output(0x81);

    //OPTION = 0x07;
    int j = 0;
    while(j++ < 10){

        // sample IMU output
        IMU_READ(IMU_GYRO_X_L,&temp[0]);
        IMU_READ(IMU_GYRO_X_U,&temp[1]);
        //roll.current_value += ((int16_t)temp[0] | (int16_t)temp[1] << 8)/FILTER_LENGTH;
        roll.current_value = 0;
        IMU_READ(IMU_GYRO_Y_L,&temp[0]);
        IMU_READ(IMU_GYRO_Y_U,&temp[1]);
        //pitch.current_value += ((int16_t)temp[0] | (int16_t)temp[1] << 8)/FILTER_LENGTH;
        pitch.current_value = 1000;
        IMU_READ(IMU_GYRO_Z_L,&temp[0]);
        IMU_READ(IMU_GYRO_Z_U,&temp[1]);
        //yaw.current_value += ((int16_t)temp[0] | (int16_t)temp[1] << 8)/FILTER_LENGTH;
        yaw.current_value = 0;

        update_control_variables(&roll);
        update_control_variables(&pitch);
        update_control_variables(&yaw);

        printf("ctrl: %i, %i, %i\n",roll.control_var,pitch.control_var, yaw.control_var);
        printf("Mout: %i, %i, %i\n",motor_outputs.front_right,motor_outputs.front_left,motor_outputs.back_right,motor_outputs.back_left);

        PWM_update(&pitch, &yaw, &roll, 1, &motor_outputs);

        print_motor_outputs();
        int i;
        for(i=0; i< 10; i++){
          update_motor_outputs(&motor_outputs, &pwm_counters);
          print_motor_outputs();
        }
        printf("-----------\n");
    }

    return 0;
}
