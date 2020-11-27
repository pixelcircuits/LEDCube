//-----------------------------------------------------------------------
// SPI Interface Library
// summary:
//   SPI data is received in the SPI peripheral buffer and is read periodically via a timer interrupt.
//   DMA is not an option since the LED data outputting uses up the full peripheral data bus (to be as fast as possible).
// references:
//   https://www.pjrc.com/teensy/K20P64M72SF1RM.pdf
//-----------------------------------------------------------------------
#ifndef _spi_h_
#define _spi_h_

#include "system.h"

//-----------------------------------------------------------------------
// SPI Interface Functions
//-----------------------------------------------------------------------
static void spi_init();
static void spi_setBuffers(uint8_t* buffer0, uint8_t* buffer1, uint32_t size);
static void spi_start();
static void spi_stop();
static void spi_reset();
static uint8_t* spi_checkData();
static uint8_t spi_checkClk();

//-----------------------------------------------------------------------
// SPI Defines
//-----------------------------------------------------------------------
#define SPI_POLL_US 15
#define SPI_TIMEOUT_US 2000

//-----------------------------------------------------------------------
// SPI Data
//-----------------------------------------------------------------------
static uint8_t* spi_writeBuffer;
static uint8_t* spi_readyBuffer;
static uint32_t spi_bufferSize;
static uint8_t spi_dataReadyFlag;
static uint32_t spi_writeIndex;
static uint32_t spi_timoutCounter;
IntervalTimer spi_timer;

//-----------------------------------------------------------------------
// SPI PIT Interrupt Routine
//-----------------------------------------------------------------------
void spi_timer_isr(void) {
	uint8_t rxCount = (SPI0_SR >> 4) & 0x0f;
	if(rxCount > 0) {
		spi_timoutCounter = 0;
		for(;rxCount > 0; rxCount--) {
			uint8_t data = SPI0_POPR;
			if(spi_writeIndex < spi_bufferSize) spi_writeBuffer[spi_writeIndex] = data;
			spi_writeIndex++;
		}
		
		//check buffer filled
		if(spi_writeIndex == spi_bufferSize) {
			if(spi_writeBuffer[spi_bufferSize-1] == META_DATA_SYNC_BYTE) {
				spi_dataReadyFlag = 1;
				uint8_t* temp = spi_writeBuffer;
				spi_writeBuffer = spi_readyBuffer;
				spi_readyBuffer = temp;
			}
			spi_reset();
		}
		
	} else {
		spi_timoutCounter += SPI_POLL_US;
		
		//check timeout
		if(spi_timoutCounter >= SPI_TIMEOUT_US) {
			spi_timoutCounter = 0;
			spi_reset();
		}
	}
}

//-----------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------
static void spi_init() {
	//data
	spi_writeBuffer = 0;
	spi_readyBuffer = 0;
	spi_bufferSize = 0;
	spi_dataReadyFlag = 0;
	spi_writeIndex = 0;
	spi_timoutCounter = 0;

	//enable peripheral clocks for SPI
	SIM_SCGC6 |= SIM_SCGC6_SPI0;
	
	//set pin modes
	CORE_PIN10_CONFIG = PORT_PCR_MUX(2); //SPI CS
	CORE_PIN13_CONFIG = PORT_PCR_MUX(2); //SPI CLK
	CORE_PIN12_CONFIG = PORT_PCR_MUX(2); //SPI DIN
	pinMode(PIN_DATA_MOSI, OUTPUT);
	digitalWriteFast(PIN_DATA_MOSI, LOW);
	
	//setup SPI
	SPI0_MCR = SPI_MCR_PCSIS(0x1F) | SPI_MCR_HALT; //slave mode, set all inactive states high (cs), halt
	SPI0_CTAR0_SLAVE = SPI_CTAR_FMSZ(7); //clock and transfer attributes, 8 bits per frame (value + 1)
}

static void spi_setBuffers(uint8_t* buffer0, uint8_t* buffer1, uint32_t size) {
	spi_writeBuffer = buffer0;
	spi_readyBuffer = buffer1;
	spi_bufferSize = size;
}

static void spi_start() {
	if(spi_writeBuffer != 0 && spi_bufferSize > 0) {
		//start and reset SPI
		SPI0_MCR = SPI_MCR_PCSIS(0x1F);//slave mode, set all inactive states high (cs), no halt
		spi_reset();
		
		//start timer
		spi_timer.begin(spi_timer_isr, SPI_POLL_US);
	}
}

static void spi_stop() {
	//halt SPI peripheral
	SPI0_MCR = SPI_MCR_HALT;
	
	//end timer
	spi_timer.end();
}

static void spi_reset() {
	//clear SPI fifos
	SPI0_MCR |= SPI_MCR_CLR_TXF | SPI_MCR_CLR_RXF;
	
	//pulse the CS line to clear frames
	digitalWriteFast(PIN_DATA_MOSI, HIGH);
	system_delay(1);
	digitalWriteFast(PIN_DATA_MOSI, LOW);
	system_delay(1);
	digitalWriteFast(PIN_DATA_MOSI, HIGH);
	system_delay(1);
	digitalWriteFast(PIN_DATA_MOSI, LOW);
	
	//reset write index
	spi_writeIndex = 0;
}

static uint8_t* spi_checkData() {
	if(spi_dataReadyFlag) {
		spi_dataReadyFlag = 0;
		return spi_readyBuffer;
	}
	return 0;
}

static uint8_t spi_checkClk() {
	//read clk pin
	pinMode(PIN_DATA_CLK, INPUT);
	system_delay(1000);
	uint8_t val = digitalReadFast(PIN_DATA_CLK);
	
	//switch pin mode back
	CORE_PIN13_CONFIG = PORT_PCR_MUX(2); //SPI CLK
	
	return val;	
}

#endif /*_spi_h_*/