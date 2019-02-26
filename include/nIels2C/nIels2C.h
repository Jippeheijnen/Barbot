//
// Created by Niels on 2/25/2019.
//

#ifndef BARBOT_NIELS2C_H
#define BARBOT_NIELS2C_H

#include <cstdint>
#include <iostream>

const uint8_t LCD_CLEARDISPLAY = 0x01;
const uint8_t LCD_RETURNHOME = 0x02;
const uint8_t LCD_ENTRYMODESET = 0x04;
const uint8_t LCD_DISPLAYCONTROL = 0x08;
const uint8_t LCD_CURSORSHIFT = 0x10;
const uint8_t LCD_FUNCTIONSET = 0x20;
const uint8_t LCD_SETCGRAMADDR = 0x40;
const uint8_t LCD_SETDDRAMADDR = 0x80;

// flags for display entry mode
const uint8_t LCD_ENTRYRIGHT = 0x00;
const uint8_t LCD_ENTRYLEFT = 0x02;
const uint8_t LCD_ENTRYSHIFTINCREMENT = 0x01;
const uint8_t LCD_ENTRYSHIFTDECREMENT = 0x00;

// flags for display on/off control
const uint8_t LCD_DISPLAYON = 0x04;
const uint8_t LCD_DISPLAYOFF = 0x00;
const uint8_t LCD_CURSORON = 0x02;
const uint8_t LCD_CURSOROFF = 0x00;
const uint8_t LCD_BLINKON = 0x01;
const uint8_t LCD_BLINKOFF = 0x00;

// flags for display/cursor shift
const uint8_t LCD_DISPLAYMOVE = 0x08;
const uint8_t LCD_CURSORMOVE = 0x00;
const uint8_t LCD_MOVERIGHT = 0x04;
const uint8_t LCD_MOVELEFT = 0x00;

// flags for function set
const uint8_t LCD_8BITMODE = 0x10;
const uint8_t LCD_4BITMODE = 0x00;
const uint8_t LCD_2LINE = 0x08;
const uint8_t LCD_1LINE = 0x00;
const uint8_t LCD_5x10DOTS = 0x04;
const uint8_t LCD_5x8DOTS = 0x00;

// flags for backlight control
const uint8_t LCD_BACKLIGHT = 0x08;
const uint8_t LCD_NOBACKLIGHT = 0x00;

const uint8_t En = 0b00000100; // Enable bit
const uint8_t Rw = 0b00000010; // Read/Write bit
const uint8_t Rs = 0b00000001; // Register select bit



class nIels2C {
private:
    uint8_t address, rows,cols;
    int _fd;
    void sleep(long us);

public:
    nIels2C();

    nIels2C(uint8_t address, uint8_t rows, uint8_t cols);

    void strobe(uint8_t data);
    void write_four_bits(uint8_t data);
    void write(uint8_t cmd, uint8_t mode = 0);
    void display_string(std::string str, uint8_t line);
    void clear();
    void i2c_write(uint8_t data);
};


#endif //BARBOT_NIELS2C_H
