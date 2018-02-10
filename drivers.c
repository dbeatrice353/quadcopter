#ifdef __XC8
#include <htc.h>
#else
#include "dev_htc.h"
#endif


//---------------------------------------------------------//
//                          I2C                            //
//---------------------------------------------------------//



// GPIO4 = I2C clk, GPIO5 = I2C data
void I2C_init(void){
   WPU     = 0x00; // turn off weak pull-ups.
   TRISIO |= 0x30; // tri-state GPIO 4 and 5.
}

void I2C_clk_high(void){
   TRISIO |= 0x10; // tri-state GPIO4
}

void I2C_clk_low(void){
   TRISIO &= 0xEF; // set GPIO4 to output
   GP4 = 0;
}

void I2C_data_high(void){
   TRISIO |= 0x20; // tri-state GPIO5
}

void I2C_data_low(void){
   TRISIO &= 0xDF; // set GPIO5 to output
   GP5 = 0;
}

unsigned int I2C_read_clk(void){
    return GP4;
}

unsigned int I2C_read_data(void){
    return GP5;
}

void I2C_delay(void){
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

int main(int argc, char** argv) {
   char buffer;
   int sig0 = 0;
   int sig1 = 0;

   init();
   I2C_init();

   while(1){
       __delay_ms(10);

       sig1 = sig0;
       sig0 = GP2;

       if(sig0==0&&sig1==1){
           __delay_ms(50);
           I2C_start();
           I2C_tx(0x32); // SAD+W
           I2C_tx(0x0F); // SUB
           I2C_start();  // SAD+R
           I2C_tx(0x33); // SAD+R
           I2C_rx(0,&buffer);
           I2C_stop();
           __delay_ms(50);
       }
   }
   return (EXIT_SUCCESS);
}
