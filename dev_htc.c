#include <stdio.h>
#include <stdint.h>
#include "dev_htc.h"

uint8_t TRISA;
uint8_t TRISB;
uint8_t TRISC;

uint8_t PORTA = 0xFF;
uint8_t PORTB = 0xFF;
uint8_t PORTC = 0xFF;

void print_motor_outputs(void){
  uint8_t FL = (PORTC & 0x08) >> 3;
  uint8_t FR = (PORTC & 0x04) >> 2;
  uint8_t BL = (PORTC & 0x10) >> 4;
  uint8_t BR = (PORTC & 0x20) >> 5;
  printf("%i, %i, %i, %i\n", FL, FR, BL, BR);
}

void __delay_ms(int ms){
  printf("%i ms delay\n",ms);
}

void __delay_us(int us){
  printf("%i us delay\n",us);
}
