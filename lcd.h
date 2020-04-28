#ifndef LCD_H
#define LCD_H


void wakeup_LCD(void);
void home_LCD(void);
void clear_LCD(void);
void write_char_LCD(unsigned char);
void write_string_LCD(unsigned char*);
void write_string_blink_LCD(unsigned char*, uint16_t);
void write_line_LCD(unsigned char*, unsigned char);
void move_cursor(unsigned char, unsigned char);


// max characters that can fit on a line
#define LINE_MAX_CHARS          20

// pins used for data bits (DB) for LCD
// note: it's REALLY convenient if we use the port as a bus
#define LCD_DB_PORT             (P2)
#define LCD_DB_7                (BIT7)
#define LCD_DB_6                (BIT6)
#define LCD_DB_5                (BIT5)
#define LCD_DB_4                (BIT4)
#define LCD_DB_3                (BIT3)
#define LCD_DB_2                (BIT2)
#define LCD_DB_1                (BIT1)
#define LCD_DB_0                (BIT0)

// operation enable for LCD
#define LCD_E_PORT              (P6)
#define LCD_E                   (BIT6)

// read/write for LCD
#define LCD_RW_PORT             (P6)
#define LCD_RW                  (BIT7)

// register select for LCD
#define LCD_RS_PORT             (P5)
#define LCD_RS                  (BIT6)

// contrast for LCD
#define LCD_CNST_PORT           (P5)
#define LCD_CNST                (BIT1)

#endif
