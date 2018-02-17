
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

int main(void){

  Attitude attitude;

  while(1){
    update_control_variables(&attitude.roll);
    update_control_variables(&attitude.pitch);
    update_control_variables(&attitude.yaw);
  }
}
