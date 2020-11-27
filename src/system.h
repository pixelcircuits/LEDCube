//-----------------------------------------------------------------------
// System Interface Library
// summary:
//   Lists all global define values and sets useful helper functions/ core functionality.
// references:
//   https://www.pjrc.com/store/teensy32_pins.html
//-----------------------------------------------------------------------
#ifndef _system_h_
#define _system_h_

//-----------------------------------------------------------------------
// Configuration and System Constants
//-----------------------------------------------------------------------

//System states
#define STATE_OP_NORMAL      0
#define STATE_STANDBY_INDEF  1
#define STATE_STANDBY_START  2
#define STATE_STANDBY_HOLD   3
#define STATE_STANDBY_CLOSE  4

//Pin config
#define PIN_DATA_CS     10
#define PIN_DATA_CLK    13
#define PIN_DATA_MOSI   11
#define PIN_DATA_MISO   12

#define PIN_LED_RED    2
#define PIN_LED_GREEN  14
#define PIN_LED_BLUE   7
#define PIN_LED_CLK    8
#define PIN_LED_XLAT   6
#define PIN_LED_GSCLK  20
#define PIN_LED_BLANK  21
#define PIN_LED_VPRG   3
#define PIN_LED_DCPRG  4

#define PIN_LAYER_0    15
#define PIN_LAYER_1    22
#define PIN_LAYER_2    23
#define PIN_LAYER_3    9
#define PIN_LAYER_4    16
#define PIN_LAYER_5    17
#define PIN_LAYER_6    19
#define PIN_LAYER_7    18
#define PIN_LAYER_8    0
#define PIN_LAYER_9    1

//Byte layout
#define LED_PORT  PORTD_BYTE
#define BIT_LED_RED    0x01
#define BIT_LED_GREEN  0x02
#define BIT_LED_BLUE   0x04
#define BIT_LED_CLK    0x08
#define BIT_LED_XLAT   0x10
#define BIT_LED_GSCLK  0x20
#define BIT_LED_BLANK  0x40

//LED/Layer Layout
#define NUM_LAYERS            10
#define NUM_LEDS_PER_LAYER    (10*10)
#define NUM_LEDS_PER_DRIVER   (16*7)
#define NUM_DRIVER_GS_BITS    12
#define NUM_DRIVER_GS_CYCLES  4096
#define DATA_BUFFER_SIZE      (NUM_LEDS_PER_LAYER*NUM_LAYERS*3)

//Color Dot Correction
#define NUM_DRIVER_DC_BITS   6
#define DRIVER_DC_VAL_RED    16
#define DRIVER_DC_VAL_GREEN  16
#define DRIVER_DC_VAL_BLUE   14

//Meta data
#define META_DATA_NUM_BYTES   2
#define META_DATA_SYNC_BYTE   0x01
#define META_DATA_BRIGHTNESS  0x03
#define META_DATA_RESET       0x20
#define META_DATA_STANDBY     0x10


//-----------------------------------------------------------------------
// System Functions
//-----------------------------------------------------------------------
static void system_init();
static void system_delay(uint32_t value);
static uint32_t system_clock();
static void system_drawStandby(uint8_t* buffer, uint32_t clock);
static void system_drawPoint(uint8_t* buffer, uint32_t x, uint32_t y, uint32_t z, uint8_t r, uint8_t g, uint8_t b);

//-----------------------------------------------------------------------
// System Data
//-----------------------------------------------------------------------
static uint32_t system_clockTicks;

//-----------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------
static void system_init() {
	system_clockTicks = 0;
}

static void system_delay(uint32_t value) {
	volatile uint32_t i;
	for(i=0; i<value; i++);
}

static uint32_t system_clock() {
	system_clockTicks += (256000000/F_CPU);
	return system_clockTicks;
}

static void system_drawStandby(uint8_t* buffer, uint32_t clock) {
	//determine color
	uint32_t rgb[] = {0,0,0};
	uint32_t c = clock % (256*3);
	if(c<256) {
		rgb[0] = 255-c;
		rgb[1] = c;
	} else if(c<256*2) {
		rgb[1] = 255-(c-256);
		rgb[2] = c-256;
	} else if(c<256*3) {
		rgb[2] = 255-(c-256*2);
		rgb[0] = c-256*2;
	}
	
	//draw box
	uint32_t width = 6;
	uint32_t pos[] = {2,2,2};
	uint32_t x, y, z;
	for(x=0; x<width; x++) {
		system_drawPoint(buffer, pos[0]+x, pos[1]+0, pos[2]+0, rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+x, pos[1]+(width-1), pos[2]+0, rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+x, pos[1]+0, pos[2]+(width-1), rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+x, pos[1]+(width-1), pos[2]+(width-1), rgb[0], rgb[1], rgb[2]);
	}
	for(y=0; y<width; y++) {
		system_drawPoint(buffer, pos[0]+0, pos[1]+y, pos[2]+0, rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+0, pos[1]+y, pos[2]+(width-1), rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+(width-1), pos[1]+y, pos[2]+0, rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+(width-1), pos[1]+y, pos[2]+(width-1), rgb[0], rgb[1], rgb[2]);
	}
	for(z=0; z<width; z++) {
		system_drawPoint(buffer, pos[0]+0, pos[1]+0, pos[2]+z, rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+0, pos[1]+(width-1), pos[2]+z, rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+(width-1), pos[1]+0, pos[2]+z, rgb[0], rgb[1], rgb[2]);
		system_drawPoint(buffer, pos[0]+(width-1), pos[1]+(width-1), pos[2]+z, rgb[0], rgb[1], rgb[2]);
	}
}

static void system_drawPoint(uint8_t* buffer, uint32_t x, uint32_t y, uint32_t z, uint8_t r, uint8_t g, uint8_t b) {
	const uint32_t dimX = 10;
	const uint32_t dimZ = 10;
	buffer[(y*dimZ*dimX + z*dimX + x)*3 + 0] = r;
	buffer[(y*dimZ*dimX + z*dimX + x)*3 + 1] = g;
	buffer[(y*dimZ*dimX + z*dimX + x)*3 + 2] = b;
}

#endif /*_system_h_*/