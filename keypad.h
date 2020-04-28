#ifndef KEYPAD_H
#define KEYPAD_H


#include <stdbool.h>
#include "msp.h"


void init_keypad();
void enable_keypad();
void disable_keypad();
void start_print_keypad();
void stop_print_keypad();
char read_keypad();


// keypad pin config
#define KEYPAD_PORT     (P4)
#define KEYPAD_R0       (BIT0)
#define KEYPAD_R1       (BIT1)
#define KEYPAD_R2       (BIT2)
#define KEYPAD_R3       (BIT3)
#define KEYPAD_C0       (BIT4)
#define KEYPAD_C1       (BIT5)
#define KEYPAD_C2       (BIT6)
#define KEYPAD_ROW_MASK ((KEYPAD_R0) | (KEYPAD_R1) | (KEYPAD_R2) | (KEYPAD_R3))
#define KEYPAD_COL_MASK ((KEYPAD_C0) | (KEYPAD_C1) | (KEYPAD_C2))

// keypad map of key to port value
#define K1      ((KEYPAD_R0) | (KEYPAD_C0))
#define K2      ((KEYPAD_R0) | (KEYPAD_C1))
#define K3      ((KEYPAD_R0) | (KEYPAD_C2))
#define K4      ((KEYPAD_R1) | (KEYPAD_C0))
#define K5      ((KEYPAD_R1) | (KEYPAD_C1))
#define K6      ((KEYPAD_R1) | (KEYPAD_C2))
#define K7      ((KEYPAD_R2) | (KEYPAD_C0))
#define K8      ((KEYPAD_R2) | (KEYPAD_C1))
#define K9      ((KEYPAD_R2) | (KEYPAD_C2))
#define KSTAR   ((KEYPAD_R3) | (KEYPAD_C0))
#define K0      ((KEYPAD_R3) | (KEYPAD_C1))
#define KPOUND  ((KEYPAD_R3) | (KEYPAD_C2))

#endif
