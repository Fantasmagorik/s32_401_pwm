

int i2c1_init(void);
int i2c1_sendAddress(char ADDRESS);
int i2c1_sendByte(char BYTE);
int i2c1_sendData(int DATA_COUNT, char *DATA_ADDR);
int i2c1_stop(void);
int i2c1_reset(void);
