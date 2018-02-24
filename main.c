
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
    /*
    uint8_t i;
    uint8_t temp[2];
    Axis roll;
    Axis pitch;
    Axis yaw;
    */
    MotorOutputs motor_outputs;
    PWMCounters pwm_counters;
    
    __delay_ms(100);

    I2C_init();
    status_leds_init();
    push_button_init();
    output_init();
    IMU_init();
    PWM_init();
    
    red_status_off();
    green_status_on();
    
    pwm_counters.front_left = 0;
    pwm_counters.front_right = 0;
    pwm_counters.back_left = 0;
    pwm_counters.back_right = 0;
            
    motor_outputs.front_left = 50;
    motor_outputs.front_right = 100;
    motor_outputs.back_left = 150;
    motor_outputs.back_right = 200;
    
    write_to_output(TRISC_buffer);


    //OPTION = 0x07;
    while(1){
        
        //update_motor_outputs(&motor_outputs, &pwm_counters);
        /*
        // sample IMU output
        for(i=0;i<FILTER_LENGTH;i++){
            IMU_READ(IMU_GYRO_X_L,&temp[0]);
            IMU_READ(IMU_GYRO_X_U,&temp[1]);
            roll.current_value += ((int16_t)temp[0] | (int16_t)temp[1] << 8)/FILTER_LENGTH;
            IMU_READ(IMU_GYRO_Y_L,&temp[0]);
            IMU_READ(IMU_GYRO_Y_U,&temp[1]);
            pitch.current_value += ((int16_t)temp[0] | (int16_t)temp[1] << 8)/FILTER_LENGTH;
            IMU_READ(IMU_GYRO_Z_L,&temp[0]);
            IMU_READ(IMU_GYRO_Z_U,&temp[1]);
            yaw.current_value += ((int16_t)temp[0] | (int16_t)temp[1] << 8)/FILTER_LENGTH;
        }
        
        update_control_variables(&roll);
        update_control_variables(&pitch);
        update_control_variables(&yaw);
        
        update_motor_outputs(&pitch, &yaw, &roll, 1, &motor_outputs);
         */ 
        __delay_ms(100);
        //write_to_output(0x0F);
        FRONT_LEFT_LOW();
        FRONT_RIGHT_LOW();
        BACK_LEFT_LOW();
        BACK_RIGHT_LOW();
         __delay_ms(10);
        //write_to_output(0xF0);
        FRONT_LEFT_HIGH();
        FRONT_RIGHT_HIGH();
        BACK_LEFT_HIGH();
        BACK_RIGHT_HIGH();
 
    }

    return 0;
}
