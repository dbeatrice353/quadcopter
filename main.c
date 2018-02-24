
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

#define FILTER_LENGTH 10

int main(void) {
    char buffer;
    uint8_t i;
    int8_t temp;
    Axis roll;
    Axis pitch;
    Axis yaw;

    __delay_ms(100);

    I2C_init();
    status_leds_init();
    push_button_init();
    output_init();
    IMU_init();

    red_status_off();
    green_status_on();

    //OPTION = 0x07;
    while(1){

        // sample IMU output
        for(i=0;i<FILTER_LENGTH;i++){
            IMU_READ(IMU_GYRO_X_U,&temp);
            roll.current_value += temp/FILTER_LENGTH;
            IMU_READ(IMU_GYRO_Y_U,&temp);
            pitch.current_value += temp/FILTER_LENGTH;
            IMU_READ(IMU_GYRO_Z_U,&temp);
            yaw.current_value += temp/FILTER_LENGTH;
        }

    }

    return 0;
}
