#include "util.h"
#include "lcd.h"
#include "delay.h"


void init_LCD_pins();
void write_com(unsigned char);
void write_char_slow_LCD(unsigned char);
void write_char_LCD(unsigned char);


void clear_LCD() {
    write_com(0x01);
}

void home_LCD() {
    write_com(0x02);
}

void wakeup_LCD() {
    unsigned char key = 0x30;

    // configures I/O and initializes
    init_LCD_pins();

    write_com(key);
    // hold 100MS
    delay_us(_100_MS_IN_US, _3_MHZ);

    write_com(key);
    // hold 10MS
    delay_us(_10_MS_IN_US, _3_MHZ);

    write_com(key);
    // hold 10MS
    delay_us(_10_MS_IN_US, _3_MHZ);

    key = 0x38;
    write_com(key);

    key = 0x10;
    write_com(key);

    key = 0x0f;
    write_com(key);

    key = 0x06;
    write_com(key);

    //write_com(0x05);
}

void write_com(unsigned char data) {
    LCD_DB_PORT->OUT = data;       // put data on the bus

    LCD_RS_PORT->OUT &= ~LCD_RS;     // instruction

    LCD_RW_PORT->OUT &= ~LCD_RW;    // write

    delay_us(_2_MS_IN_US, _3_MHZ);

    LCD_E_PORT->OUT |= LCD_E;       // enable

    delay_us(_1_MS_IN_US, _3_MHZ);

    LCD_E_PORT->OUT &= ~LCD_E;      // disable
}

void write_char_LCD(unsigned char data) {
    LCD_DB_PORT->OUT = data;        // put data on the bus

    LCD_RS_PORT->OUT |= LCD_RS;     // data

    LCD_RW_PORT->OUT &= ~LCD_RW;    // write

    delay_us(_1_MS_IN_US, _3_MHZ);

    LCD_E_PORT->OUT |= LCD_E;       // enable

    delay_us(_1_MS_IN_US, _3_MHZ);

    LCD_E_PORT->OUT &= ~LCD_E;      // disable
}

void write_char_slow_LCD(unsigned char data) {
    write_char_LCD(data);

    delay_us(_100_MS_IN_US, _3_MHZ);
}

void write_string_LCD(unsigned char* string) {
    unsigned char* s = string;

    while ((*s) != '\0') {
        write_char_slow_LCD(*s);
        s++;
    }
}

void write_string_blink_LCD(unsigned char* string, uint16_t times) {
    unsigned char* s = string;
    uint32_t i = 0;

    write_com(0x0c); // disable blinking cursor;

    for(i = 0; i < times; i++) {
        while ((*s) != '\0') {
            write_char_LCD(*s);
            s++;
        }
        delay_us(_1_S_IN_US, _3_MHZ);
        clear_LCD();
        delay_us(_400_MS_IN_US, _3_MHZ);
        home_LCD();
        s = string;
    }

    write_com(0x0f); // re-enable blinking cursor;
}

void write_line_LCD(unsigned char* string, unsigned char line) {
    unsigned char* s = string;
    unsigned char i = 0;

    move_cursor(line, 0);

    while ((*s) != '\0') {
        write_char_slow_LCD(*s);
        if (i == LINE_MAX_CHARS) {
            return;
        }
        s++;
        i++;
    }
}

void move_cursor(unsigned char line, unsigned char offset) {
    if (line == 0) {
        write_com((0x80 | 0x00) + offset);
    } else {
        write_com((0x80 | 0x40) + offset);
    }
}

/**
 * set the LCD pins to their proper states
 * everything should be output with init=0x0;
 */
void init_LCD_pins() {
    // data bus is output initialized to 0x0
    LCD_DB_PORT->SEL0 = 0x00;
    LCD_DB_PORT->SEL1 = 0x00;
    LCD_DB_PORT->DIR = 0xFF;
    LCD_DB_PORT->OUT = 0x00;

    // operation_enable is output initialized to 0x0
    LCD_E_PORT->SEL0 &= ~LCD_E;
    LCD_E_PORT->SEL1 &= ~LCD_E;
    LCD_E_PORT->DIR |= LCD_E;
    LCD_E_PORT->OUT &= LCD_E;

    // read/write is output initialized to 0x0
    LCD_RW_PORT->SEL0 &= ~LCD_RW;
    LCD_RW_PORT->SEL1 &= ~LCD_RW;
    LCD_RW_PORT->DIR |= LCD_RW;
    LCD_RW_PORT->OUT &= LCD_RW;

    // register_select is output initialized to 0x0
    LCD_RS_PORT->SEL0 &= ~LCD_RS;
    LCD_RS_PORT->SEL1 &= ~LCD_RS;
    LCD_RS_PORT->DIR |= LCD_RS;
    LCD_RS_PORT->OUT &= LCD_RS;

    // contrast is output initialized to 0x0
    LCD_CNST_PORT->SEL0 &= ~LCD_CNST;
    LCD_CNST_PORT->SEL1 &= ~LCD_CNST;
    LCD_CNST_PORT->DIR |= LCD_CNST;
    LCD_CNST_PORT->OUT &= LCD_CNST;
}
