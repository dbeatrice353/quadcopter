#ifndef _INTERFACES_
#define _INTERFACES_

enum IMU_addresses{
    IMU_I2C_ADDR_W   = 0xD6,  // IMU I2C slave address + write bit
    IMU_I2C_ADDR_R   = 0xD7,  // IMU I2C slave address + read bit
    IMU_WHO_AM_I_REG = 0x0F   // "who am i?" register
};

// gyroscope output registers: x,y,z and upper/lower bytes
enum IMU_output_registers{
    IMU_GYRO_X_L = 0x22,
    IMU_GYRO_X_U = 0x23,
    IMU_GYRO_Y_L = 0x24,
    IMU_GYRO_Y_U = 0x25,
    IMU_GYRO_Z_L = 0x26,
    IMU_GYRO_Z_U = 0x27,
    IMU_ACC_X_L = 0x28,
    IMU_ACC_X_U = 0x29,
    IMU_ACC_Y_L = 0x2A,
    IMU_ACC_Y_U = 0x2B,
    IMU_ACC_Z_L = 0x2C,
    IMU_ACC_Z_U = 0x2D
};

// IMU control registers
enum control_registers{
    IMU_CTRL1 = 0x10,
    IMU_CTRL2 = 0x11,
    IMU_CTRL3 = 0x12,
    IMU_CTRL4 = 0x13,
    IMU_CTRL5 = 0x14,
    IMU_CTRL6 = 0x15,
    IMU_CTRL7 = 0x16
};

// accelerometer configuration bits
enum accelerometer_config{
    IMU_ACC_BANDWIDTH_100Hz   = 0x02,
    IMU_ACC_RANGE_16G         = 0x04,
    IMU_ACC_SAMPLE_RATE_416Hz = 0x60,
    IMU_ACC_BANDWIDTH_SELECT  = 0x80
};
// gyroscope configuration bits
enum gyroscope_config{
    IMU_GYRO_RANGE_2000dps     = 0x0C,
    IMU_GYRO_SAMPLE_RATE_416Hz = 0x60
};

extern void status_leds_init(void);
extern void red_status_on(void);
extern void red_status_off(void);
extern void green_status_on(void);
extern void green_status_off(void);

extern void push_button_init(void);
extern int read_push_button(void);

extern void output_init(void);
extern void write_to_output(unsigned char byte);

extern void I2C_init(void);
extern void I2C_start(void);
extern void I2C_stop(void);
extern void I2C_tx(unsigned char buffer);
extern void I2C_rx(int ack, char *buffer);

extern void IMU_init(void);

#define I2C_DATA_HIGH()\
        TRISC_buffer |= 0x01;\
        TRISC = TRISC_buffer;

#define I2C_DATA_LOW()\
        TRISC_buffer &= 0xFE;\
        TRISC = TRISC_buffer;\
        PORTC &= 0xFE;

#define I2C_CLK_HIGH()\
        TRISC_buffer |= 0x02;\
        TRISC = TRISC_buffer;

#define I2C_CLK_LOW()\
        TRISC_buffer &= 0xFD;\
        TRISC = TRISC_buffer;\
        PORTC &= 0xFD;

#define I2C_DELAY() //__delay_us(1)
#define I2C_READ_DATA() (PORTC & 0x01)
#define I2C_READ_CLK() (PORTC & 0x02)>>1

#define IMU_READ(reg, buffer)\
                I2C_start();\
                I2C_tx(IMU_I2C_ADDR_W);\
                I2C_tx(reg);\
                I2C_start();\
                I2C_tx(IMU_I2C_ADDR_R);\
                I2C_rx(0, buffer);\
                I2C_stop();

#define IMU_WRITE(reg, data)\
                 I2C_start();\
                 I2C_tx(IMU_I2C_ADDR_W);\
                 I2C_tx(reg);\
                 I2C_tx(data);\
                 I2C_stop();

#endif
