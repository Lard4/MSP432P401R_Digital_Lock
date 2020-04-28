#include "msp.h"
#include "util.h"
#include "keypad.h"
#include "lcd.h"
#include "delay.h"


#define KEY             (('1'<<24)|('3'<<16)|('5'<<8)|('3'))
#define KEY_LENGTH      4
#define CLEAR_CHAR      '*'


void check_key(void);


/**
 * main.c
 */
void main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    init_keypad();
    wakeup_LCD();
	clear_LCD();

    check_key();
}

void check_key() {
    uint32_t keyBuilder = 0;
    char c = 0;
    int i = 1;

    write_string_LCD("LOCKED");
    write_line_LCD("ENTER KEY: ", 1);

    while(c = read_keypad()) {
        if (c == CLEAR_CHAR) {
            clear_LCD();
            home_LCD();
            check_key();
        }

        write_char_LCD(c);
        keyBuilder |= c << (8 * (KEY_LENGTH - i));

        if (i == KEY_LENGTH) {
            // delay to let the user see the char on the screen
            delay_us(_100_MS_IN_US, _3_MHZ);

            if (keyBuilder == KEY) {
                home_LCD();
                clear_LCD();
                write_line_LCD("UNLOCKED!", 0);
            } else {
                clear_LCD();
                home_LCD();
                write_string_blink_LCD("WRONG!!!", 3);
                check_key();
            }
        }

        i++;
    }
}
