#include "WBN_protocol.h"
#include "SMAC_Config.h"

static txPacket_t* smacPacket;

void initWBN(txPacket_t* appTxPacket) {
	smacPacket = appTxPacket;
} 

void sendViaWBN(Packet packet) {
	smacErrors_t err = gErrorNoError_c;
	static uint8_t* pPacketPdu;

	pPacketPdu = gAppTxPacket->smacPdu.smacPdu;

	FLib_MemSet(gAppTxPacket->smacPdu.smacPdu, 0, gMaxSmacSDULength_c);
	
	pPacketPdu[0]=packet->sourceID;
	pPacketPdu[0]=packet->destinationID;
	pPacketPdu[0]=packet->packetID;
	pPacketPdu[0]=packet->timeToLive;
	pPacketPdu[0]=packet->payload;

	gAppTxPacket->u8DataLength = 5;

	err = MCPSDataRequest(gAppTxPacket);
	if(err == gErrorNoError_c); // do something
	
}