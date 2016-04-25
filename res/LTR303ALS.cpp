#include "LTR303ALS.h"
#include "i2c_if.h"

int LTR303ALS::initialize() {
    // bring device out of standby
    uint8_t config[2] = {Registers8::ALS_CONTR, ALS_CONTR::ALS_MODE};  // see datasheet for meaning of 0x01
    I2C_IF_Write(DEVICE_ADDRESS, &config[0], 2, 1);
    return 0;
}

int LTR303ALS::get_light(LTR303ALS::light_measurement &measurement) {

    // device readings have to be taken from the registers in this order, otherwise the internal
    // sensor state machine will reset and start a new acquisition

    uint8_t ch1_lo;
    uint8_t ch1_hi;
    uint8_t ch0_lo;
    uint8_t ch0_hi;

    I2C_IF_Write(DEVICE_ADDRESS,(uint8_t*)&Registers8::ALS_DATA_CH1_0, 1, 0);
    I2C_IF_Read(DEVICE_ADDRESS, &ch1_lo, 1);

    I2C_IF_Write(DEVICE_ADDRESS, (uint8_t*)&Registers8::ALS_DATA_CH1_1, 1, 0);
    I2C_IF_Read(DEVICE_ADDRESS, &ch1_hi, 1);

    I2C_IF_Write(DEVICE_ADDRESS, (uint8_t*)&Registers8::ALS_DATA_CH0_0, 1, 0);
    I2C_IF_Read(DEVICE_ADDRESS, &ch0_lo, 1);

    I2C_IF_Write(DEVICE_ADDRESS, (uint8_t*)&Registers8::ALS_DATA_CH0_1, 1, 0);
    I2C_IF_Read(DEVICE_ADDRESS, &ch0_hi, 1);

    measurement.red = (ch1_hi << 8) | ch1_lo;
    measurement.violet = (ch0_hi << 8) | ch0_lo;

    return 0;
}


