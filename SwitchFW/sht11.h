// SHT11 hum/temp sensor
#define SHT11_SCL	(1<<PC2)
#define SHT11_SDA	(1<<PC3)
#define SHT11_LOWRES	0		// 0: 12/14bit (SHT11), 1: 8/12bit (SHT11+FOST02)

#define SHT11_GLUE(a, b)	a##b
#define SHT11_PORT PORTC
#define SHT11_PIN PINC
#define SHT11_DDR DDRC

#define		SHT11_UNAVAIL  -32768
#define		SHT11_CRC_FAIL -32767
#define		sht11_valid(v) ((v) > -32000)

#define SHT11_CMD_TEMP	0x03
#define SHT11_CMD_HUMID	0x05
#define SHT11_CMD_WSTAT	0x06
#define SHT11_CMD_RSTAT	0x07
#define SHT11_CMD_RESET	0x1E

static void	delay(void)	{ _delay_us(20); wdt_reset(); }

#define setBits(port,mask)	do{ (port) |=  (mask); }while(0)
#define clrBits(port,mask)	do{ (port) &= ~(mask); }while(0)
#define tstBits(port,mask)	((port) & (mask))

static void	scl_hi(void)    { setBits(SHT11_PORT, SHT11_SCL); }
static void	scl_lo(void)    { clrBits(SHT11_PORT, SHT11_SCL); }
static void	sda_hi(void)    { clrBits(SHT11_DDR, SHT11_SDA); }
static void	sda_lo(void)    { setBits(SHT11_DDR, SHT11_SDA); }
static void	scl_pulse(void) { scl_hi(); delay(); scl_lo(); }
static uint8_t	sda_val(void)   { return (SHT11_PIN & SHT11_SDA) != 0; }