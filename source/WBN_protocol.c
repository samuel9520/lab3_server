#include "WBN_protocol.h"

static txPacket_t* smacPacket;

void initWBN(txPacket_t* appTxPacket) {
	smacPacket = appTxPacket;
} 

void sendViaWBN(Packet* packet) {
	smacErrors_t err = gErrorNoError_c;
	static uint8_t* pPacketPdu;

	pPacketPdu = smacPacket->smacPdu.smacPdu;

	FLib_MemSet(smacPacket->smacPdu.smacPdu, 0, gMaxSmacSDULength_c);
	
	pPacketPdu[0]=packet->sourceID;
	pPacketPdu[0]=packet->destinationID;
	pPacketPdu[0]=packet->packetID;
	pPacketPdu[0]=packet->timeToLive;
	pPacketPdu[0]=packet->payload;

	smacPacket->u8DataLength = 5;

	err = MCPSDataRequest(smacPacket);
	if(err == gErrorNoError_c); // do something
	
}
