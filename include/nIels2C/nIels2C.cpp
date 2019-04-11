//
// Created by Niels on 2/25/2019.
//

#include "nIels2C.h"
#include <thread>
#include <bitset>
#include <unistd.h>
#include <fcntl.h>
#include <stropts.h>
#include <linux/i2c-dev.h>


uint8_t i2c = 0x3f;
uint8_t rows = 4;
uint8_t cols = 20;
int i = 0;

nIels2C::nIels2C(uint8_t address, uint8_t rows, uint8_t cols) : address(address), rows(rows), cols(cols) {
    _fd = open("/dev/i2c-1", O_RDWR);
    // Under0 Check

    int r = ioctl(_fd, I2C_SLAVE, address);
    if (r < 0)
        close(_fd);

    write(0x03);
    write(0x03);
    write(0x03);
    write(0x02);

    write(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE);
    write(LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    write(LCD_CLEARDISPLAY);
    write(LCD_ENTRYMODESET | LCD_ENTRYLEFT);
    sleep(200000);

}

void nIels2C::i2c_write(uint8_t data) {
    i2c_smbus_write_byte(_fd, data);
}

void nIels2C::strobe(uint8_t data) {
    i2c_write(data | En | LCD_BACKLIGHT);
    sleep(500);
    i2c_write(((data & ~En) | LCD_BACKLIGHT));
    sleep(100);
}

void nIels2C::write_four_bits(uint8_t data) {
    i2c_smbus_write_byte(_fd, data | LCD_BACKLIGHT);
    strobe(data);
}

void nIels2C::write(uint8_t cmd, uint8_t mode) {
    write_four_bits(mode | (cmd & ((uint8_t) 0xF0)));
    write_four_bits(mode | ((cmd << 4) & ((uint8_t) 0xF0)));
}

void nIels2C::display_string(std::string str, uint8_t line) {
    if (line == 1)
        write(0x80);
    if (line == 2)
        write(0xC0);
    if (line == 3)
        write(0x94);
    if (line == 4)
        write(0xD4);

    for (char c : str) {
        write((uint8_t) c, Rs);
    }
}

void nIels2C::clear() {
    write(LCD_CLEARDISPLAY);
    write(LCD_RETURNHOME);
}

void nIels2C::sleep(long us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}



