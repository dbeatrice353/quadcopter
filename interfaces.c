#ifdef __XC8
#include <htc.h>
#else
#include "dev_htc.h"
#endif

#include <stdint.h>


//---------------------------------------------------------//
//               tristate register buffers                 //
//---------------------------------------------------------//

unsigned char TRISA_buffer = 0xFF;
unsigned char TRISB_buffer = 0xFF;
unsigned char TRISC_buffer = 0xFF;

//---------------------------------------------------------//
//                     status LEDs                         //
//---------------------------------------------------------//

void status_leds_init(void){
    TRISC_buffer &= 0x3F;
    TRISC = TRISC_buffer;
    PORTC &= 0x3F;
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

//---------------------------------------------------------//
//                     push button                         //
//---------------------------------------------------------//

void push_button_init(void){
    TRISB_buffer |= 0x20;
    TRISB = TRISB_buffer;
}

int read_push_button(void){
   return (PORTB & 0x20)>>5;
}


 //---------------------------------------------------------//
 //                 debug-LED array output                  //
 //---------------------------------------------------------//


 void output_init(void){
     TRISA_buffer &= 0xF0;
     TRISB_buffer &= 0xF0;
     TRISA = TRISA_buffer;
     TRISB = TRISB_buffer;
 }

void write_to_output(unsigned char byte){
  PORTA = (PORTA & 0xF0) | (byte & 0x0F);
  PORTB = (PORTB & 0xF0) | byte>>4;
}


//---------------------------------------------------------//
//                          I2C                            //
//---------------------------------------------------------//

// portions of the I2C code were taken from here:
// http://www.robot-electronics.co.uk/i2c-tutorial


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
