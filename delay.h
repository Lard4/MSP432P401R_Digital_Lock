#ifndef DELAY_H
#define DELAY_H

void delay_us(uint32_t, uint32_t);


#define _1_MS_IN_US         (939)
#define _2_MS_IN_US         ((_1_MS_IN_US) * 2)
#define _10_MS_IN_US        ((_1_MS_IN_US) * 10)
#define _80_MS_IN_US        ((_10_MS_IN_US) * 8)
#define _100_MS_IN_US       ((_10_MS_IN_US) * 10)
#define _400_MS_IN_US       ((_100_MS_IN_US) * 4)
#define _1_S_IN_US          ((_100_MS_IN_US) * 10)


#endif
