#include "HDC1050.h"

#include "i2c_if.h"
#include "rom_map.h"
#include "utils.h"

int HDC1050::initialize() {
    // no initialization necessary. default reset configuration is ok
    return 0;
}

int HDC1050::get_temperature(float &current_temperature) {
    current_temperature = 0;  // not implemented, use combined function
    return 0;
}

int HDC1050::get_humidity(float &current_humidity) {
    current_humidity = 0;  // not implemented, use combined function
    return 0;
}

int HDC1050::get_tempature_and_humidity(HDC1050::reading &measurement) {
    // execute pointer write transaction at 0x00
    int rc = I2C_IF_Write(DEVICE_ADDRESS,0 /* device address*/, 1 /* bytes to read */, 0 /*no stop bit */);

    // wait at least 6.5 milliseconds - every 1000 ticks is 12.5 us
    MAP_UtilsDelay(10000000);

    static uint8_t temperature[2];
    static uint8_t humidity[2];

    uint32_t temp = 0;
    uint32_t hum = 0;

    // read
    I2C_IF_Read(DEVICE_ADDRESS + Registers8::temperature, &temperature[0], 2);
    I2C_IF_Read(DEVICE_ADDRESS + Registers8::humidity , &humidity[0], 2);

    // process readings
    temp = temperature[1];
    temp = temp << 4;
    temp += temperature[0];

    temp = temp * 165 - 40;
    temp = temp << 16;

    measurement.temperature = temp;  // celsius

    hum = humidity[1];
    hum *= 100;
    hum = hum << 16;

    measurement.humidity = hum;  // relative humidty as percentage

    // todo: check for nack
    return 0;
}


