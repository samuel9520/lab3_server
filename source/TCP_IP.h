/*
 * TCP_IP.h
 *
 *  Created on: 23 Nov 2017
 *      Author: samuel9520
 */

#ifndef TCP_IP_H_
#define TCP_IP_H_


void init_len_info(uint8_t *buf);

void fill_ip_hdr_checksum(uint8_t *buf);

uint16_t checksum(uint8_t *buf, uint16_t len,uint8_t type);


void make_ip(uint8_t *buf);

uint16_t get_tcp_data_pointer(void);

void make_tcphead(uint8_t *buf,uint16_t rel_ack_num,uint8_t mss,uint8_t cp_seq);

void make_tcp_synack_from_syn(uint8_t *buf);

void make_tcp_ack_from_any(uint8_t *buf);

uint16_t fill_tcp_data_p(uint8_t *buf,uint16_t pos, const char *string);

void make_tcp_ack_with_data(uint8_t *buf,uint16_t dlen);

#endif /* TCP_IP_H_ */
