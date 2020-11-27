//-----------------------------------------------------------------------
// LED Cube Driver for Teensy 3.2
// summary:
//   Driver receives data via SPI and ouputs data to TLC5940 one layer at a time.
//   Added animation state while waiting for data.
// references:
//   https://www.pjrc.com/store/teensy32.html
//-----------------------------------------------------------------------
#include <Arduino.h>
#include "teensy_extensions.h"

extern "C" {
	#include "system.h"
	#include "led.h"
	#include "spi.h"

	//Data
	uint8_t dataBuffer[2][DATA_BUFFER_SIZE+META_DATA_NUM_BYTES];
	uint8_t* currentDataBuffer;
	uint32_t standbyTime;
	uint8_t brightness;
	uint8_t state;

	//Code Start
	int main(void)
	{
		uint32_t i;
		for(i=0;i<DATA_BUFFER_SIZE;i++) dataBuffer[0][i]=0x00;
		for(i=0;i<DATA_BUFFER_SIZE;i++) dataBuffer[1][i]=0x00;
		currentDataBuffer = dataBuffer[0];
		state = STATE_STANDBY_INDEF;
		
		//init peripherals
		system_init();
		spi_init();
		led_init();
		
		//start spi data receive
		spi_setBuffers(dataBuffer[1], dataBuffer[0], DATA_BUFFER_SIZE+META_DATA_NUM_BYTES);
		spi_start();
			
		//start with full brightness
		brightness = 4;
		led_dc(brightness);
		
		//begin program loop
		uint8_t layer = 0;
		while(1==1) {
			uint32_t clock = system_clock();
			
			//draw layer to the cube
			led_outputLayer(currentDataBuffer, layer);
			
			//check for new data when on the last layer
			if(layer == (NUM_LAYERS-1)) {
				uint8_t* newData = spi_checkData();
				if(newData) {
					currentDataBuffer = newData;
					
					//update state with the metadata
					uint8_t metaData = newData[DATA_BUFFER_SIZE];
					brightness = (metaData & META_DATA_BRIGHTNESS) + 1;
					if((metaData & META_DATA_RESET) == META_DATA_RESET) {
						for(i=0;i<DATA_BUFFER_SIZE;i++) currentDataBuffer[i]=0x00;
						state = STATE_STANDBY_INDEF;
					} else if((metaData & META_DATA_STANDBY) == META_DATA_STANDBY) {
						for(i=0;i<DATA_BUFFER_SIZE;i++) currentDataBuffer[i]=0x00;
						standbyTime = clock;
						state = STATE_STANDBY_START;
					} else {
						state = STATE_OP_NORMAL;
					}
				}
				led_dc(brightness);
				
				//transition standby state
				if(state == STATE_STANDBY_START) {
					if(clock - standbyTime > 8600) { //~2s
						state = STATE_STANDBY_HOLD;
					}
				} else if(state == STATE_STANDBY_HOLD) {
					if(spi_checkClk() == 0) {
						standbyTime = clock;
						state = STATE_STANDBY_CLOSE;
					}
				} else if(state == STATE_STANDBY_CLOSE) {
					if(clock - standbyTime > 34400) { //~8s
						for(i=0;i<DATA_BUFFER_SIZE;i++) currentDataBuffer[i]=0x00;
						state = STATE_OP_NORMAL;
					}
				}
				
				//animation
				if(state == STATE_STANDBY_INDEF || state == STATE_STANDBY_START || state == STATE_STANDBY_HOLD || state == STATE_STANDBY_CLOSE) {
					system_drawStandby(currentDataBuffer, clock/16);
				}
			}
			
			//incirment to next layer
			layer = (layer+1)%NUM_LAYERS;
			system_delay(1);
		}
		
		spi_stop();
		return 0;
	}
	
}
