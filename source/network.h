/*
 * network.h
 *
 *  Created on: 23 Nov 2017
 *      Author: samuel9520
 */

#ifndef NETWORK_H_
#define NETWORK_H_

// ******* IP *******
#define IP_HEADER_LEN	20

#define IP_SRC_P 0x0C
#define IP_DST_P 0x10
#define IP_HEADER_LEN_VER_P 0xe
#define IP_CHECKSUM_P 0x0A
#define IP_TTL_P 0x08
#define IP_FLAGS_P 0x06
#define IP_P 0x00
#define IP_TOTLEN_H_P 0x02
#define IP_TOTLEN_L_P 0x03
#define IP_PROTO_P 0x09

#define IP_PROTO_TCP_V 6


// ******* TCP *******
#define TCP_SRC_PORT_H_P 0x14
#define TCP_SRC_PORT_L_P 0x15
#define TCP_DST_PORT_H_P 0x16
#define TCP_DST_PORT_L_P 0x17
// the tcp seq number is 4 bytes 0x26-0x29
#define TCP_SEQ_H_P 0x18
#define TCP_SEQACK_H_P 0x1C
// flags: SYN=2
#define TCP_FLAGS_P 0x21

#define TCP_FLAGS_SYN_V 2
#define TCP_FLAGS_FIN_V 1
#define TCP_FLAGS_PUSH_V 8
#define TCP_FLAGS_SYNACK_V 0x12
#define TCP_FLAGS_ACK_V 0x10
#define TCP_FLAGS_PSHACK_V 0x18
//  plain len without the options:
#define TCP_HEADER_LEN_PLAIN 20

#define TCP_HEADER_LEN_P 0x20
#define TCP_CHECKSUM_H_P 0x24
#define TCP_CHECKSUM_L_P 0x25
#define TCP_OPTIONS_P 0x28

#endif /* NETWORK_H_ */
