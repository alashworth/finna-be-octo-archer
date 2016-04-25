#include <cstdint>

#ifndef CC3200_DEVL_FIRMWARE_LTR303ALS_H
#define CC3200_DEVL_FIRMWARE_LTR303ALS_H

class LTR303ALS {
public:
    static int initialize();
    static int get_light(light_measurement&);
private:

    struct light_measurement {
        uint32_t violet;
        uint32_t red;
    };

    static int const DEVICE_ADDRESS = 0x29;

    enum Registers8 : uint8_t {
        ALS_CONTR = 0x80,
        ALS_MEAS_RATE = 0x85,
        PART_ID = 0x86,
        MANUFAC_ID = 0x87,
        ALS_DATA_CH1_0 = 0x88,
        ALS_DATA_CH1_1 = 0x89,
        ALS_DATA_CH0_0 = 0x8A,
        ALS_DATA_CH0_1 = 0x8B,
        ALS_STATUS = 0x8C,
        INTERRUPT = 0x8F,
        ALS_THRES_UP_0 = 0x97,
        ALS_THRES_UP_1 = 0x98,
        ALS_THRES_LOW_0 = 0x99,
        ALS_THRES_LOW_1 = 0x9A,
        INTERRUPT_PERSIST = 0x9E
    };

    enum ALS_CONTR : uint8_t {
        ALSGAIN_1X = 0b00000000,
        ALSGAIN_2X = 0b00000100,
        ALSGAIN_4X = 0b00001000,
        ALSGAIN_8X = 0b00001100,
        ALSGAIN_48X = 0b00011000,
        ALSGAIN_96X = 0b00011100,
        SW_RST = 0b00000010,
        ALS_MODE = 0b00000001  // 1 = active, 0 = standby
    };

    enum ALS_MEAS_RATE : uint8_t {
        INTEG_100MS = 0b00000000,
        INTEG_50MS = 0b00001000,
        INTEG_200MS = 0b00010000,
        INTEG_400MS = 0b00011000,
        INTEG_150MS = 0b00100000,
        INTEG_250MS = 0b00101000,
        INTEG_300MS = 0b00110000,
        INTEG_350MS = 0b00111000,
        RATE_50MS = 0b00000000,
        RATE_200MS = 0b00000001,
        RATE_500MS = 0b00000011,
        RATE_1000MS = 0b00000100,
        RATE_2000MS = 0b00000111 | 0b00000110 | 0b00000101
    };

};


#endif //CC3200_DEVL_FIRMWARE_LTR303ALS_H
