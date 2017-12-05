/*
 * SLIP.c
 *
 *  Created on: 23 Nov 2017
 *      Author: samuel9520
 */

#include "board.h"
#include "fsl_lpuart.h"

#include "SLIP.h"

#define DEMO_LPUART LPUART0
#define DEMO_LPUART_CLKSRC kCLOCK_CoreSysClk
#define DEMO_LPUART_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)

static uint8_t SLIP_PREFIX = 0xC0;
static uint8_t SLIP_POSTFIX = 0xC0;

void SLIP_Init() {

	lpuart_config_t config;
	LPUART_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx = true;
	config.enableRx = true;

	LPUART_Init(DEMO_LPUART, &config, DEMO_LPUART_CLK_FREQ);
}

void SLIP_sendPacket(uint16_t length, uint8_t* send_buffer) {

	LPUART_WriteBlocking(DEMO_LPUART, &SLIP_PREFIX, 1);
	LPUART_WriteBlocking(DEMO_LPUART, send_buffer, length);
	LPUART_WriteBlocking(DEMO_LPUART, &SLIP_POSTFIX, 1);

}

uint16_t SLIP_readPacket(uint16_t max_length, uint8_t * receive_buffer) {

	uint8_t dummy[max_length+1];
	uint8_t ch;
	uint8_t start_recording = 0;
	uint16_t counter = 0;


	while(counter < max_length) {
		//LPUART_WriteBlocking(DEMO_LPUART, "debugging", 1);

		LPUART_ReadBlocking(DEMO_LPUART, &ch, 1);

		//LPUART_WriteBlocking(DEMO_LPUART, &counter, 1);

		if (start_recording==1) {
			dummy[counter] = ch;
			counter++;
		}

		if (ch == 0xC0)
		{
			if(++start_recording == 2) {

				if(counter==1) {
					start_recording = 1;
					continue;
				}

				break;
			}
			counter = 0;
		}
	}

	counter--;
	memcpy(receive_buffer, dummy, counter*sizeof(uint8_t));
	return counter;

}


