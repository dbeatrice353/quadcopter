
#ifdef __XC8
    #include <htc.h>
    #include <pic16f57.h>

    #pragma config OSC = XT   // Oscillator selection bits
    #pragma config WDT = OFF  // Watchdog timer enable bit (WDT disabled)
    #pragma config CP = OFF   // Code protection bit (Code protection off)

    #ifndef _XTAL_FREQ
    #define _XTAL_FREQ 4000000 // 4MHz
    #endif //_XTAL_FREQ
#endif //__XC8

#include <stdint.h>
#include "quadcopter.h"
#include "interfaces.h"

#define N 10

int main(void) {
    char buffer;
    int8_t gyro[N];
    int8_t mean;
    uint8_t i;

    __delay_ms(100);

    I2C_init();
    status_leds_init();
    push_button_init();
    output_init();

    //IMU_init();

    buffer = 0x01;
    write_to_output(buffer);

    red_status_off();
    green_status_on();

    //OPTION = 0x07;
    while(1){
        mean = 0;
        for(i=0;i<N;i++){
            __delay_ms(1);
            IMU_READ(IMU_GYRO_X_U,&gyro[i]);
            mean += gyro[i]/N;
        }
        write_to_output(mean);
    }

    return 0;
}
