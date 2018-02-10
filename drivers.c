#ifdef __XC8
#include <htc.h>
#else
#include "dev_htc.h"
#endif

#include <stdint.h>



void output_init(void){
    TRISA = 0xF0;
    TRISB = 0xF0;
}

void write_to_output(unsigned char byte){
  PORTA = (PORTA & 0xF0) | (byte & 0x0F);
  PORTB = (PORTB & 0xF0) | byte>>4;
}


//---------------------------------------------------------//
//                          I2C                            //
//---------------------------------------------------------//
// portions of this code were taken from here: http://www.robot-electronics.co.uk/i2c-tutorial

/*
 * The "TRISC" register is write-only, prohibiting
 * operations like "TRISC |= 0x01" that select
 * individual bits. The work around here is to set
 * and clear individual bits of a buffer (TRISC_buffer),
 * then write the whole buffer to TRISC.
 */
unsigned char TRISC_buffer = 0xFF;

 void I2C_data_high(void){
    TRISC_buffer |= 0x01;
    TRISC = TRISC_buffer;
 }

 void I2C_data_low(void){
    TRISC_buffer &= 0xFE;
    TRISC = TRISC_buffer;
    PORTC &= 0xFE;
 }

 void I2C_clk_high(void){
    TRISC_buffer |= 0x02;
    TRISC = TRISC_buffer;
 }

 void I2C_clk_low(void){
    TRISC_buffer &= 0xFD;
    TRISC = TRISC_buffer;
    PORTC &= 0xFD;
 }

 int I2C_read_data(void){
     return (PORTC & 0x01);
 }

 int I2C_read_clk(void){
     return (PORTC & 0x02)>>1;
 }

 void I2C_delay(void){
 }

void I2C_init(void){
      I2C_data_high();
      I2C_clk_high();
}

 void I2C_start(void){
     I2C_data_high();
     I2C_delay();
     I2C_clk_high();
     I2C_delay();
     I2C_data_low();
     I2C_delay();
     I2C_clk_low();
     I2C_delay();
 }

 void I2C_stop(void){
     I2C_data_low();
     I2C_delay();
     I2C_clk_high();
     I2C_delay();
     I2C_data_high();
     I2C_delay();
 }

 void I2C_tx(unsigned char buffer){
     int i;
     static bit ack_bit;
     for(i=8;i;i--){
         if(buffer&0x80){
             I2C_data_high();
         }else{
             I2C_data_low();
         }
         I2C_clk_high();
         buffer <<= 1;
         I2C_clk_low();
     }
     I2C_data_high();
     I2C_clk_high();
     I2C_delay();
     ack_bit = I2C_read_data();
     I2C_clk_low();
 }

 void I2C_rx(int ack, char *buffer){
     int i;
     char data = 0x00;

     I2C_data_high();
     for(i=0;i<8;i++){
        data <<= 1;
        do{
            I2C_clk_high();
        }while(I2C_read_clk()==0);
        I2C_delay();
        if(I2C_read_data()){
            data |= 0x01;
        }
        I2C_clk_low();
    }
    if(ack){
        I2C_data_low();
    }else{
        I2C_data_high();
    }
     I2C_clk_high();
     I2C_delay();
     I2C_clk_low();
     I2C_data_high();
     *buffer = data;
 }
 /*
int main(int argc, char** argv) {
    char buffer;

    I2C_init();
    output_init();


    while(1){

        __delay_ms(1000);
        I2C_start();
        I2C_tx(0xD6); // SAD+W
        I2C_tx(0x0F); // SUB      // "who am i?" register
        I2C_start();  // SAD+R
        I2C_tx(0xD7); // SAD+R
        I2C_rx(0,&buffer);
        I2C_stop();

        write_to_output(buffer);

    }
    return 0;
}
*/
