#ifndef DEV_HTC
#define DEV_HTC

#include <stdint.h>
#include <stdio.h>

#define __delay_ms(x) printf("%i ms delay",x)
#define __delay_us(x) printf("%i us delay",x)

uint8_t TRISA;
uint8_t TRISB;
uint8_t TRISC;

uint8_t PORTA;
uint8_t PORTB;
uint8_t PORTC;

#endif
