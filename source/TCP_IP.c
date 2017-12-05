/*
 * TCP_IP.c
 *
 *  Created on: 23 Nov 2017
 *      Author: samuel9520
 */
#include "board.h"

#include "network.h"
#include "TCP_IP.h"
#include "SLIP.h"

static uint8_t wwwport=80; // 80 is just a default value. Gets overwritten during init
static uint8_t ipaddr[4] = {194,169,55,2};;
static int16_t info_hdr_len=0;
static int16_t info_data_len=0;
static uint8_t seqnum=0xa; // my initial tcp sequence number

void init_len_info(uint8_t *buf)
{
	info_data_len=(((int16_t)buf[IP_TOTLEN_H_P])<<8)|(buf[IP_TOTLEN_L_P]&0xff);
	info_data_len-=IP_HEADER_LEN;
	info_hdr_len=(buf[TCP_HEADER_LEN_P]>>4)*4; // generate len in bytes;
	info_data_len-=info_hdr_len;
	if (info_data_len<=0){
		info_data_len=0;
	}
}

void fill_ip_hdr_checksum(uint8_t *buf)
{
	uint16_t ck;
	// clear the 2 byte checksum
	buf[IP_CHECKSUM_P]=0;
	buf[IP_CHECKSUM_P+1]=0;
	buf[IP_FLAGS_P]=0x40; // don't fragment
	buf[IP_FLAGS_P+1]=0;  // fragement offset
	buf[IP_TTL_P]=64; // ttl
	// calculate the checksum:
	ck=checksum(&buf[IP_P], IP_HEADER_LEN,0);
	buf[IP_CHECKSUM_P]=ck>>8;
	buf[IP_CHECKSUM_P+1]=ck& 0xff;
}

uint16_t checksum(uint8_t *buf, uint16_t len,uint8_t type){
	// type 0=ip
	//      1=udp
	//      2=tcp
	uint32_t sum = 0;

	//if(type==0){
	//        // do not add anything
	//}

	if(type==2){
		sum+=IP_PROTO_TCP_V;
		// the length here is the length of tcp (data+header len)
		// =length given to this function - (IP.scr+IP.dst length)
		sum+=len-8; // = real tcp len
	}
	// build the sum of 16bit words
	while(len >1){
		sum += 0xFFFF & (((uint32_t)*buf<<8)|*(buf+1));
		buf+=2;
		len-=2;
	}
	// if there is a byte left then add it (padded with zero)
	if (len){
		sum += ((uint32_t)(0xFF & *buf))<<8;
	}
	// now calculate the sum over the bytes in the sum
	// until the result is only 16bit long
	while (sum>>16){
		sum = (sum & 0xFFFF)+(sum >> 16);
	}
	// build 1's complement:
	return( (uint16_t) sum ^ 0xFFFF);
}


void make_ip(uint8_t *buf)
{
	uint8_t i=0;
	while(i<4){
		buf[IP_DST_P+i]=buf[IP_SRC_P+i];
		buf[IP_SRC_P+i]=ipaddr[i];
		i++;
	}
	fill_ip_hdr_checksum(buf);
}

uint16_t get_tcp_data_pointer(void)
{
	if (info_data_len){
		return((uint16_t)TCP_SRC_PORT_H_P+info_hdr_len);
	}else{
		return(0);
	}
}

void make_tcphead(uint8_t *buf,uint16_t rel_ack_num,uint8_t mss,uint8_t cp_seq)
{
	uint8_t i=0;
	uint8_t tseq;
	while(i<2){
		buf[TCP_DST_PORT_H_P+i]=buf[TCP_SRC_PORT_H_P+i];
		buf[TCP_SRC_PORT_H_P+i]=0; // clear source port
		i++;
	}
	// set source port  (http):
        		buf[TCP_SRC_PORT_L_P]=wwwport;
        		i=4;
        		// sequence numbers:
        		// add the rel ack num to SEQACK
        		while(i>0){
        			rel_ack_num=buf[TCP_SEQ_H_P+i-1]+rel_ack_num;
        			tseq=buf[TCP_SEQACK_H_P+i-1];
        			buf[TCP_SEQACK_H_P+i-1]=0xff&rel_ack_num;
        			if (cp_seq){
        				// copy the acknum sent to us into the sequence number
        				buf[TCP_SEQ_H_P+i-1]=tseq;
        			}else{
        				buf[TCP_SEQ_H_P+i-1]= 0; // some preset vallue
        			}
        			rel_ack_num=rel_ack_num>>8;
        			i--;
        		}
        		if (cp_seq==0){
        			// put inital seq number
        			buf[TCP_SEQ_H_P+0]= 0;
        			buf[TCP_SEQ_H_P+1]= 0;
        			// we step only the second byte, this allows us to send packts
        			// with 255 bytes or 512 (if we step the initial seqnum by 2)
        			buf[TCP_SEQ_H_P+2]= seqnum;
        			buf[TCP_SEQ_H_P+3]= 0;
        			// step the inititial seq num by something we will not use
        			// during this tcp session:
        			seqnum+=2;
        		}
        		// zero the checksum
        		buf[TCP_CHECKSUM_H_P]=0;
        		buf[TCP_CHECKSUM_L_P]=0;

        		// The tcp header length is only a 4 bit field (the upper 4 bits).
        		// It is calculated in units of 4 bytes.
        		// E.g 24 bytes: 24/4=6 => 0x60=header len field
        		//buf[TCP_HEADER_LEN_P]=(((TCP_HEADER_LEN_PLAIN+4)/4)) <<4; // 0x60
        		if (mss){
        			// the only option we set is MSS to 1408:
        			// 1408 in hex is 0x580
        			buf[TCP_OPTIONS_P]=2;
        			buf[TCP_OPTIONS_P+1]=4;
        			buf[TCP_OPTIONS_P+2]=0x05;
        			buf[TCP_OPTIONS_P+3]=0x80;
        			// 24 bytes:
        			buf[TCP_HEADER_LEN_P]=0x60;
        		}else{
        			// no options:
        			// 20 bytes:
        			buf[TCP_HEADER_LEN_P]=0x50;
        		}
}

void make_tcp_synack_from_syn(uint8_t *buf)
{
	uint16_t ck;

	// total length field in the IP header must be set:
	// 20 bytes IP + 24 bytes (20tcp+4tcp options)
	buf[IP_TOTLEN_H_P]=0;
	buf[IP_TOTLEN_L_P]=IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+4;
	make_ip(buf);
	buf[TCP_FLAGS_P]=TCP_FLAGS_SYNACK_V;
	make_tcphead(buf,1,1,0);
	// calculate the checksum, len=8 (start from ip.src) + TCP_HEADER_LEN_PLAIN + 4 (one option: mss)
	ck=checksum(&buf[IP_SRC_P], 8+TCP_HEADER_LEN_PLAIN+4,2);
	buf[TCP_CHECKSUM_H_P]=ck>>8;
	buf[TCP_CHECKSUM_L_P]=ck& 0xff;
	// add 4 for option mss:
	SLIP_sendPacket(IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+4,buf);
}

void make_tcp_ack_from_any(uint8_t *buf)
{
	uint16_t j;
	// fill the header:
	buf[TCP_FLAGS_P]=TCP_FLAGS_ACK_V;
	if (info_data_len==0){
		// if there is no data then we must still acknoledge one packet
		make_tcphead(buf,1,0,1); // no options
	}else{
		make_tcphead(buf,info_data_len,0,1); // no options
	}

	// total length field in the IP header must be set:
	// 20 bytes IP + 20 bytes tcp (when no options)
	j=IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN;
	buf[IP_TOTLEN_H_P]=j>>8;
	buf[IP_TOTLEN_L_P]=j& 0xff;
	make_ip(buf);
	// calculate the checksum, len=8 (start from ip.src) + TCP_HEADER_LEN_PLAIN + data len
	j=checksum(&buf[IP_SRC_P], 8+TCP_HEADER_LEN_PLAIN,2);
	buf[TCP_CHECKSUM_H_P]=j>>8;
	buf[TCP_CHECKSUM_L_P]=j& 0xff;
	SLIP_sendPacket(IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN,buf);
}

uint16_t fill_tcp_data_p(uint8_t *buf,uint16_t pos, const char *string)
{
	// fill in tcp data at position pos
	//
	// with no options the data starts after the checksum + 2 more bytes (urgent ptr)
	while (*string) {
		buf[TCP_CHECKSUM_L_P+3+pos]=*string;
		pos++;
		string++;
	}
	return(pos);
}


void make_tcp_ack_with_data(uint8_t *buf,uint16_t dlen)
{
	uint16_t j;
	// fill the header:
	// This code requires that we send only one data packet
	// because we keep no state information. We must therefore set
	// the fin here:
	buf[TCP_FLAGS_P]=TCP_FLAGS_ACK_V|TCP_FLAGS_PUSH_V|TCP_FLAGS_FIN_V;

	// total length field in the IP header must be set:
	// 20 bytes IP + 20 bytes tcp (when no options) + len of data
	j=IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+dlen;
	buf[IP_TOTLEN_H_P]=j>>8;
	buf[IP_TOTLEN_L_P]=j& 0xff;
	fill_ip_hdr_checksum(buf);
	// zero the checksum
	buf[TCP_CHECKSUM_H_P]=0;
	buf[TCP_CHECKSUM_L_P]=0;
	// calculate the checksum, len=8 (start from ip.src) + TCP_HEADER_LEN_PLAIN + data len
	j=checksum(&buf[IP_SRC_P], 8+TCP_HEADER_LEN_PLAIN+dlen,2);
	buf[TCP_CHECKSUM_H_P]=j>>8;
	buf[TCP_CHECKSUM_L_P]=j& 0xff;
	SLIP_sendPacket(IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+dlen,buf);
}
