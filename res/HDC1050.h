#ifndef CC3200_DEVL_FIRMWARE_HDC1050_H
#define CC3200_DEVL_FIRMWARE_HDC1050_H

#include <cstdint>

class HDC1050 {
public:
    static int initialize();
    static int get_temperature(float& current_temperature);
    static int get_humidity(float& current_humidity);

    struct reading {
        uint32_t temperature;
        uint32_t humidity;
    };

    static int get_tempature_and_humidity(reading& measurement);

private:
    static int const MANUFACTURER_ID = 0x5449;
    static int const DEVICE_ID = 0x1050;
    static int const DEVICE_ADDRESS = 0b1000000;
    static int const BASE_ADDRESS = 0x0;

    enum Registers8 : uint8_t {
        temperature = 0x00,
        humidity = 0x01,
        configuration = 0x02,
        serial_id_2 = 0xFB,
        serial_id_1 = 0xFC,
        serial_id_0 = 0xFD,
        manufacturer_id = 0xFE,
        device_id = 0xFF
    };

    enum ConfigurationBitMask : uint32_t {
        RST     = 1 << 14,
        HEAT    = 1 << 12,
        MODE    = 1 << 11,
        BTST    = 1 << 10,
        TRES    = 1 << 9,
        HRES    = 3 << 7
    };

    HDC1050() = delete;
    HDC1050(HDC1050 const&) = delete;
    HDC1050(HDC1050&&) noexcept = delete;
    HDC1050& operator=(HDC1050 const&) = delete;
    HDC1050& operator=(HDC1050&&) noexcept = delete;
    ~HDC1050() = delete;
};

#endif //CC3200_DEVL_FIRMWARE_HDC1050_H
