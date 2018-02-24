#ifdef __XC8
#include <htc.h>
#else
#include "dev_htc.h"
#endif

#include <stdint.h>
#include "interfaces.h"



unsigned char TRISA_buffer = 0xFF;
unsigned char TRISB_buffer = 0xFF;
unsigned char TRISC_buffer = 0xFF;


void status_leds_init(void){
    TRISC_buffer &= 0x3F;
    TRISC = TRISC_buffer;
    PORTC &= 0x3F;
}

void push_button_init(void){
    TRISB_buffer |= 0x20;
    TRISB = TRISB_buffer;
}



void output_init(void){
    TRISA_buffer &= 0xF0;
    TRISB_buffer &= 0xF0;
    TRISA = TRISA_buffer;
    TRISB = TRISB_buffer;
}

void write_to_output(unsigned char byte){
  PORTA = (PORTA & 0xF0) |(byte & 0x0F);
  PORTB = (PORTB & 0xF0) | byte>>4;
}


void red_status_on(void){
    PORTC |= 0x40;
}

void red_status_off(void){
    PORTC &= 0xBF;
}

void green_status_on(void){
    PORTC |= 0x80;
}

void green_status_off(void){
    PORTC &= 0xEF;
}

int read_push_button(void){
    return (PORTB & 0x20)>>5;
}

void I2C_init(void){
      I2C_DATA_HIGH();
      I2C_CLK_HIGH();
}

void I2C_start(void){
    I2C_DATA_HIGH();
    I2C_DELAY();
    I2C_CLK_HIGH();
    I2C_DELAY();
    I2C_DATA_LOW();
    I2C_DELAY();
    I2C_CLK_LOW();
    I2C_DELAY();
}

 void I2C_stop(void){
     I2C_DATA_LOW();
     I2C_DELAY();
     I2C_CLK_HIGH();
     I2C_DELAY();
     I2C_DATA_HIGH();
     I2C_DELAY();
 }

 void I2C_tx(unsigned char buffer){
     #ifdef __XC8
     static bit ack_bit;
     #else
     int ack_bit;
     #endif
     uint8_t i;

     for(i=8;i;i--){
         if(buffer&0x80){
             I2C_DATA_HIGH();
         }else{
             I2C_DATA_LOW();
         }
         I2C_CLK_HIGH();
         buffer <<= 1;
         I2C_CLK_LOW();
     }
     I2C_DATA_HIGH();
     I2C_CLK_HIGH();
     I2C_DELAY();
     ack_bit = I2C_READ_DATA();
     I2C_CLK_LOW();
 }

 void I2C_rx(int ack, char *buffer){
     uint8_t i;
     char data = 0x00;

     I2C_DATA_HIGH();
     for(i=0;i<8;i++){
        data <<= 1;
        do{
            I2C_CLK_HIGH();
        }while(I2C_READ_CLK()==0);
        I2C_DELAY();
        if(I2C_READ_DATA()){
            data |= 0x01;
        }
        I2C_CLK_LOW();
    }
    if(ack){
        I2C_DATA_LOW();
    }else{
        I2C_DATA_LOW();
    }
     I2C_CLK_HIGH();
     I2C_DELAY();
     I2C_CLK_LOW();
     I2C_DATA_HIGH();
     *buffer = data;
 }
