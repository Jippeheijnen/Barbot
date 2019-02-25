//
// Created by niels on 2/25/2019.
//
#include "../include/I2CLCD/I2CIO.h"


// LCD Address

// commands
uint8_t LCD_CLEARDISPLAY = 0x01;
uint8_t LCD_RETURNHOME = 0x02;
uint8_t LCD_ENTRYMODESET = 0x04;
uint8_t LCD_DISPLAYCONTROL = 0x08;
uint8_t LCD_CURSORSHIFT = 0x10;
uint8_t LCD_FUNCTIONSET = 0x20;
uint8_t LCD_SETCGRAMADDR = 0x40;
uint8_t LCD_SETDDRAMADDR = 0x80;

// flags for display entry mode
uint8_t LCD_ENTRYRIGHT = 0x00;
uint8_t LCD_ENTRYLEFT = 0x02;
uint8_t LCD_ENTRYSHIFTINCREMENT = 0x01;
uint8_t LCD_ENTRYSHIFTDECREMENT = 0x00;

// flags for display on/off control
uint8_t LCD_DISPLAYON = 0x04;
uint8_t LCD_DISPLAYOFF = 0x00;
uint8_t LCD_CURSORON = 0x02;
uint8_t LCD_CURSOROFF = 0x00;
uint8_t LCD_BLINKON = 0x01;
uint8_t LCD_BLINKOFF = 0x00;

// flags for display/cursor shift
uint8_t LCD_DISPLAYMOVE = 0x08;
uint8_t LCD_CURSORMOVE = 0x00;
uint8_t LCD_MOVERIGHT = 0x04;
uint8_t LCD_MOVELEFT = 0x00;

// flags for function set
uint8_t LCD_8BITMODE = 0x10;
uint8_t LCD_4BITMODE = 0x00;
uint8_t LCD_2LINE = 0x08;
uint8_t LCD_1LINE = 0x00;
uint8_t LCD_5x10DOTS = 0x04;
uint8_t LCD_5x8DOTS = 0x00;

// flags for backlight control
uint8_t LCD_BACKLIGHT = 0x08;
uint8_t LCD_NOBACKLIGHT = 0x00;

uint8_t En = 0b00000100; // Enable bit
uint8_t Rw = 0b00000010; // Read/Write bit
uint8_t Rs = 0b00000001; // Register select bit

uint8_t i2c=0x3f;
uint8_t rows = 4;
uint8_t cols = 20;
I2CIO dev;

void __initlcd() {
    dev.begin("/dev/i2c-1", i2c);

}



int main() {





    lcd.begin(cols, rows);

    lcd.print("ABCDEFGH");
    lcd.setCursor(0, 1);
    lcd.print("12345678");

    if (rows > 2) {
        lcd.setCursor(0, 2);
        lcd.print("ABCDEFGH");
        lcd.setCursor(0, 3);
        lcd.print("12345678");
    }

    sleep(2);

    lcd.clear();
    lcd.write('H');
    lcd.write('e');
    lcd.write('l');
    lcd.write('l');
    lcd.write('o');
    lcd.setCursor(0, 1);
    lcd.write('W');
    lcd.write('o');
    lcd.write('r');
    lcd.write('l');
    lcd.write('d');
    lcd.write('!');

    if (rows > 2) {
        lcd.setCursor(0, 2);
        lcd.print("We say");
        lcd.setCursor(0, 3);
        lcd.print("H'ello back!");
    }

    sleep(2);
    lcd.blink();
    sleep(2);

    lcd.clear();
    lcd.cursor();
    lcd.autoscroll();
    for (uint8_t i = 33; i < 255; i++) {
        usleep(35000);
        lcd.write((char) i);
        if (i % 8 == 0)
            sleep(1);
    }
    sleep(1);
    lcd.noBlink();
    lcd.noCursor();
    sleep(1);
    lcd.clear();
}
