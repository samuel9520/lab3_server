#ifndef WBN_procotol_H_
#define WBN_procotol_H_


struct Packet {
   uint8_t sourceID;
   uint8_t destinationID;
   uint8_t packetID;
   uint8_t timeToLive;
   uint8_t payload;
};  

//Preprocessing gets done before entering these
void initWBN(txPacket_t* appTxPacket);

void sendViaWBN(Packet packet);

void receiveViaWBN(Packet packet);


#endif /* WBN_procotol_H_ */