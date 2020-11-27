//-----------------------------------------------------------------------
// Additional Teensy Functionality
// summary:
//   Adds additional functionality for GPIO read/write per byte instead of per pin.
// references:
//   https://www.pjrc.com/teensy/K20P64M72SF1RM.pdf
//-----------------------------------------------------------------------
#ifndef _teensy_extensions_h_
#define _teensy_extensions_h_

#include <core_pins.h>

//-----------------------------------------------------------------------
// GPIO byte optimized functions
//-----------------------------------------------------------------------
#define PORTA_BYTE  0x0A
#define PORTB_BYTE  0x0B
#define PORTC_BYTE  0x0C
#define PORTD_BYTE  0x0D
#define PORTE_BYTE  0x0E

static inline void digitalByteWriteFast(uint8_t port, uint8_t val) __attribute__((always_inline, unused));
static inline void digitalByteWriteFast(uint8_t port, uint8_t val)
{
	if (port == PORTA_BYTE) {
		GPIOA_PDOR = val;
	} else if (port == PORTB_BYTE) {
		GPIOB_PDOR = val;
	} else if (port == PORTC_BYTE) {
		GPIOC_PDOR = val;
	} else if (port == PORTD_BYTE) {
		GPIOD_PDOR = val;
	}
}

static inline void digitalByteSetFast(uint8_t port, uint8_t val) __attribute__((always_inline, unused));
static inline void digitalByteSetFast(uint8_t port, uint8_t val)
{
	if (port == PORTA_BYTE) {
		GPIOA_PSOR = val;
	} else if (port == PORTB_BYTE) {
		GPIOB_PSOR = val;
	} else if (port == PORTC_BYTE) {
		GPIOC_PSOR = val;
	} else if (port == PORTD_BYTE) {
		GPIOD_PSOR = val;
	}
}

static inline void digitalByteClearFast(uint8_t port, uint8_t val) __attribute__((always_inline, unused));
static inline void digitalByteClearFast(uint8_t port, uint8_t val)
{
	if (port == PORTA_BYTE) {
		GPIOA_PCOR = val;
	} else if (port == PORTB_BYTE) {
		GPIOB_PCOR = val;
	} else if (port == PORTC_BYTE) {
		GPIOC_PCOR = val;
	} else if (port == PORTD_BYTE) {
		GPIOD_PCOR = val;
	}
}


#endif /*_teensy_extensions_h_*/