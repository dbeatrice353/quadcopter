#ifndef DEV_HTC
#define DEV_HTC

#include <stdint.h>
#include <stdio.h>

extern uint8_t TRISA;
extern uint8_t TRISB;
extern uint8_t TRISC;

extern uint8_t PORTA;
extern uint8_t PORTB;
extern uint8_t PORTC;

#define FRONT_LEFT_HIGH() PORTC |= 0x08
#define FRONT_RIGHT_HIGH() PORTC |= 0x04
#define BACK_LEFT_HIGH() PORTC |= 0x20
#define BACK_RIGHT_HIGH() PORTC |= 0x10

void print_motor_outputs(void);

void __delay_ms(int ms);
void __delay_us(int us);

#endif
