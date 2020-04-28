#include "keypad.h"
#include "lcd.h"


char cycle_column_high(char (*key_handler)(uint16_t), unsigned char);
void compute_key(uint16_t press_map);


static bool keypad_is_enabled = 0;

void enable_keypad() {
    keypad_is_enabled = 1;
}

void disable_keypad() {
    keypad_is_enabled = 0;
}

char decode_keymap(uint16_t press_map) {
    switch(press_map) {
        case (K0):
            return '0';

        case (K1):
            return '1';

        case (K2):
            return '2';

        case (K3):
            return '3';

        case (K4):
            return '4';

        case (K5):
            return '5';

        case (K6):
            return '6';

        case (K7):
            return '7';

        case (K8):
            return '8';

        case (K9):
            return '9';

        case (KSTAR):
            return '*';

        case (KPOUND):
            return '#';

        default:
            return '.';
    }
}

char print_key(uint16_t keymap) {
    char key = decode_keymap(keymap);

    write_char_LCD(key);

    while(KEYPAD_PORT->IN & KEYPAD_ROW_MASK) {
        /* block other keys from being pressed */
    }

    return key;
}

char read_keypad() {
    char key = cycle_column_high(decode_keymap, 1);

    while(KEYPAD_PORT->IN & KEYPAD_ROW_MASK) {
        /* block other keys from being pressed */
    }

    return key;
}

void start_print_keypad() {
    keypad_is_enabled = 1;
    cycle_column_high(print_key, 0);
}

void stop_print_keypad() {
    keypad_is_enabled = 0;
}

// cycle each column to high and execute function f on keypad detected
char cycle_column_high(char (*key_handler)(uint16_t), unsigned char doReturn) {
    unsigned char nextCol = 0;
    unsigned int newColConfig = 0;

    // essentially FSM
    while(keypad_is_enabled) {
        // this is immune to button bounce at low frequencies
        switch(nextCol) {
            case 0:
                // make sure C0 is a 1 and C1, C2 are 0 but preserve reset of port
                newColConfig = KEYPAD_PORT->OUT | KEYPAD_C0;
                newColConfig &= ~(KEYPAD_C1 | KEYPAD_C2);
                KEYPAD_PORT->OUT = newColConfig;
                nextCol = 1;
                break;

            case 1:
                // make sure C1 is a 1 and C0, C2 are 0 but preserve reset of port
                newColConfig = KEYPAD_PORT->OUT | KEYPAD_C1;
                newColConfig &= ~(KEYPAD_C0 | KEYPAD_C2);
                KEYPAD_PORT->OUT = newColConfig;
                nextCol = 2;
                break;

            case 2:
                // make sure C2 is a 1 and C0, C1 are 0 but preserve reset of port
                newColConfig = KEYPAD_PORT->OUT | KEYPAD_C2;
                newColConfig &= ~(KEYPAD_C0 | KEYPAD_C1);
                KEYPAD_PORT->OUT = newColConfig;
                nextCol = 0;
                break;
        }

        unsigned int keypress_map = 0;
        // if keypress
        if (keypress_map = (KEYPAD_PORT->IN & KEYPAD_ROW_MASK)) {
            keypress_map |= (KEYPAD_PORT->OUT & KEYPAD_COL_MASK);
            // handle the keypress
            char val = key_handler(keypress_map);

            if (doReturn) {
                return val;
            }
        }
    }

    return 0;
}

void init_keypad() {
    // all simple i/o
    KEYPAD_PORT->SEL0 &= ~(KEYPAD_ROW_MASK | KEYPAD_COL_MASK);
    KEYPAD_PORT->SEL1 &= ~(KEYPAD_ROW_MASK | KEYPAD_COL_MASK);

    // columns are output initialized to 0
    KEYPAD_PORT->DIR |= KEYPAD_COL_MASK;
    KEYPAD_PORT->OUT &= ~KEYPAD_COL_MASK;

    // rows are inputs with pull down resistors
    KEYPAD_PORT->DIR &= ~KEYPAD_ROW_MASK;
    KEYPAD_PORT->REN |= KEYPAD_ROW_MASK;
    KEYPAD_PORT->OUT &= ~KEYPAD_ROW_MASK;

    keypad_is_enabled = 1;
}
