//#include "stm32f4xx.h"
//inits

int periph_init(void);
int externalDevice_init(void);

extern uint64_t timeAfterReset;
uint64_t millis();
void delay(int ms);
int wait_for_event(short unsigned *byte_addr, short unsigned mask, char expected_value, unsigned int timeout);
