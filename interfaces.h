#ifndef _INTERFACES_
#define _INTERFACES_


unsigned char TRISA_buffer = 0xFF;
unsigned char TRISB_buffer = 0xFF;
unsigned char TRISC_buffer = 0xFF;

extern void status_leds_init(void);
extern void red_status_on(void);
extern void red_status_off(void);
extern void green_status_on(void);
extern void green_status_off(void);

extern void push_button_init(void);
extern int read_push_button(void);

extern void output_init(void);
extern void write_to_output(unsigned char byte);

extern void I2C_data_high(void);
extern void I2C_data_low(void);
extern void I2C_clk_high(void);
extern void I2C_clk_low(void);
extern int I2C_read_data(void);
extern int I2C_read_clk(void);
extern void I2C_delay(void);
extern void I2C_init(void);
extern void I2C_start(void);
extern void I2C_stop(void);
extern void I2C_tx(unsigned char buffer);
extern void I2C_rx(int ack, char *buffer);

#endif
