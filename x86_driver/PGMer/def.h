#define P_DATA	0x378
#define P_STATUS	0x379
#define P_CTRL	0x37A

#define IC_93_DELAY 1000
#define IC_24_DELAY 100

//I2C function
void reset_iic(void);
int write_byte(WORD address,BYTE data);
int read_byte(WORD address,BYTE *data);
void StartC(void);
void StopC(void);
void Send8bit(BYTE data);
BYTE Recv8bit(void);
BYTE W_ACK(void);
void S_CK(void);
void S_ACK(void);

//93C function
void reset_93(void);
void clk_93(void);
void start_93(void);
BYTE read_Byte(BYTE addr);
void write_Byte(BYTE addr,BYTE data);
void write_enable(void);
void write_disable(void);

