/*
 * SLIP.h
 *
 *  Created on: 23 Nov 2017
 *      Author: samuel9520
 */

#ifndef SLIP_H_
#define SLIP_H_

void SLIP_Init();
void SLIP_sendPacket(uint16_t length, uint8_t* send_buffer);
uint16_t SLIP_readPacket(uint16_t max_length, uint8_t* receive_buffer);


#endif /* SLIP_H_ */
