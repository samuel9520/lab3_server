/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * \file
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/
 
#include <lab3_server.h>
#include "SMAC_Config.h"

#include "network.h"
#include "SLIP.h"
#include "TCP_IP.h"
#include "WBN_protocol.h"
#include <stdint.h>



/************************************************************************************
 *************************************************************************************
 * Private type definitions
 *************************************************************************************
 ************************************************************************************/

/************************************************************************************
 *************************************************************************************
 * Public macros
 *************************************************************************************
 ************************************************************************************/
#define SelfNotificationEvent()                         ((void)OSA_EventSet(gTaskEvent, gWMSelf_EVENT_c))

/************************************************************************************
 *************************************************************************************
 * Public memory declarations
 *************************************************************************************
 ************************************************************************************/
#if gSmacUseSecurity_c
static uint8_t gau8RxDataBuffer[gMaxSmacSDULength_c  + sizeof(rxPacket_t) + 16];                         
#else
static uint8_t gau8RxDataBuffer[gMaxSmacSDULength_c  + sizeof(rxPacket_t)];
#endif
static uint8_t gau8TxDataBuffer[gMaxSmacSDULength_c  + sizeof(txPacket_t)];                        

static txPacket_t * gAppTxPacket;
static rxPacket_t * gAppRxPacket;

osaEventId_t          gTaskEvent;
osaEventFlags_t       gTaskEventFlags;

uint8_t gu8UartData;

channels_t       testChannel;
uint8_t          testPower;
address_size_t*  pIDConfig;
address_size_t   shortSourceID;
address_size_t   shortDestinationID;
address_size_t   shortPanID;

bool_t evDataFromUART;
bool_t evTestParameters;

bool_t shortCutsEnabled;

/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/
static uint8_t mAppSer;

static bool_t bCCAFailed;
static bool_t bACKFailed;
static bool_t bTxDone;
static bool_t bRxDone;

static uint8_t packetCount = 0;
static volatile ackReceived = TRUE;

#if gSmacUseSecurity_c

uint8_t KEY[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t  IV[16]={0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
#endif
/************************************************************************************
 *************************************************************************************
 * Private macros
 *************************************************************************************
 ************************************************************************************/
#define gUART_RX_EVENT_c         (1<<0)
#define gMcps_Cnf_EVENT_c        (1<<1)
#define gMcps_Ind_EVENT_c        (1<<2)
#define gMlme_EdCnf_EVENT_c      (1<<3)
#define gMlme_CcaCnf_EVENT_c     (1<<4)
#define gMlme_TimeoutInd_EVENT_c (1<<5)
#define gWMSelf_EVENT_c          (1<<6)
#define gTimePassed_EVENT_c      (1<<7)

#define gEventsAll_c	(gUART_RX_EVENT_c | gMcps_Cnf_EVENT_c | gMcps_Ind_EVENT_c | \
		gMlme_EdCnf_EVENT_c | gMlme_CcaCnf_EVENT_c | gMlme_TimeoutInd_EVENT_c | \
		gWMSelf_EVENT_c | gTimePassed_EVENT_c)

/************************************************************************************
 *************************************************************************************
 * Private prototypes
 *************************************************************************************
 ************************************************************************************/

void UartRxCallBack(void * param);
static void HandleEvents(int32_t evSignals);

//static bool_t stringComp(uint8_t * au8leftString, uint8_t * au8RightString, uint8_t bytesToCompare);


//static void DelayTimeElapsed();

#if gSmacUseSecurity_c

void sendRadioPacket(uint8_t board, uint8_t messageCode);
int8_t analyse_get_url(char *str);
uint16_t moved_perm(uint8_t *buf);
uint16_t print_webpage(uint8_t *buf,uint8_t on_off, uint8_t radio1_on_off, uint8_t radio2_on_off,uint8_t radio3_on_off);
#endif
/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/

uint8_t txbuff[] = "Lpuart polling example\r\nBoard will send back received characters\r\n";
uint8_t rxbuff[1500] = {0};
const char password[]="led";

/************************************************************************************
 *************************************************************************************
 * Public functions
 *************************************************************************************
 ************************************************************************************/
extern void ResetMCU(void);
/*New section added*/
void InitProject(void);
void InitSmac(void);
void Clear_CurrentLine();

/************************************************************************************
 *
 * InitProject
 *
 ************************************************************************************/
void InitProject(void)
{   
	/*Global Data init*/
	testChannel                       = gDefaultChannelNumber_c;
	testPower                         = gDefaultOutputPower_c;
	shortCutsEnabled                  = FALSE;
	evDataFromUART                    = FALSE;
	bACKFailed                        = FALSE;
	bCCAFailed                        = FALSE;
	shortSourceID                     = gNodeAddress_c;
	shortPanID                        = gDefaultPanID_c;
	shortDestinationID                = gBroadcastAddress_c;
}

/************************************************************************************
 *************************************************************************************
 * SAP functions
 *************************************************************************************
 ************************************************************************************/
//(Management) Sap handler for managing timeout indication and ED confirm
smacErrors_t smacToAppMlmeSap(smacToAppMlmeMessage_t* pMsg, instanceId_t instance)
{
	switch(pMsg->msgType)
	{
	case gMlmeEdCnf_c:
		(void)OSA_EventSet(gTaskEvent, gMlme_EdCnf_EVENT_c);
		break;
	case gMlmeCcaCnf_c:
		(void)OSA_EventSet(gTaskEvent, gMlme_CcaCnf_EVENT_c);
		break;
	case gMlmeTimeoutInd_c:
		(void)OSA_EventSet(gTaskEvent, gMlme_TimeoutInd_EVENT_c);
		break;
	default:
		break;
	}
	MEM_BufferFree(pMsg);
	return gErrorNoError_c;
}
//(Data) Sap handler for managing data confirm and data indication
smacErrors_t smacToAppMcpsSap(smacToAppDataMessage_t* pMsg, instanceId_t instance)
{
	switch(pMsg->msgType)
	{
	case gMcpsDataInd_c:
		if(pMsg->msgData.dataInd.pRxPacket->rxStatus == rxSuccessStatus_c)
		{
			(void)OSA_EventSet(gTaskEvent, gMcps_Ind_EVENT_c);
		}
		break;
	case gMcpsDataCnf_c:
		if(pMsg->msgData.dataCnf.status == gErrorChannelBusy_c)
		{
			bCCAFailed = TRUE;
		}
		if(pMsg->msgData.dataCnf.status == gErrorNoAck_c)
		{
			bACKFailed = TRUE;
		}
		(void)OSA_EventSet(gTaskEvent, gMcps_Cnf_EVENT_c);
		break;
	default:
		break;
	}

	MEM_BufferFree(pMsg);
	return gErrorNoError_c;
}
/************************************************************************************
 *
 * Performs actions based on the event flags given as param
 *
 ************************************************************************************/
static void HandleEvents(int32_t evSignals)
{
	uint16_t u16SerBytesCount = 0;

	if(evSignals & gUART_RX_EVENT_c)
	{
		if(gSerial_Success_c == Serial_GetByteFromRxBuffer(mAppSer, &gu8UartData, &u16SerBytesCount))
		{
			if(shortCutsEnabled)
			{
			}
			else
			{
				evDataFromUART = TRUE;
			}
			Serial_RxBufferByteCount(mAppSer, &u16SerBytesCount);
			if(u16SerBytesCount)
			{
				(void)OSA_EventSet(gTaskEvent, gUART_RX_EVENT_c);
			}
		}
	}
	if(evSignals & gMcps_Cnf_EVENT_c)
	{
		bTxDone = TRUE;
	}
	if(evSignals & gMcps_Ind_EVENT_c)
	{
		bRxDone = TRUE;
	}
	if(evSignals & gMlme_TimeoutInd_EVENT_c)
	{
	}
	if(evSignals & gMlme_EdCnf_EVENT_c)
	{

	}
	if(evSignals & gMlme_CcaCnf_EVENT_c)
	{

	}
	if(evSignals & gWMSelf_EVENT_c)
	{
	}
}
/*************************************************************************
 *Main Task: Application entry point*
 **************************************************************************/
void main_task(uint32_t param)
{ 
	uint16_t rlen = 0;
	uint8_t dat_p;
	int8_t cmd;

	static bool_t bIsInitialized = FALSE;

	//Initialize Memory Manager, Timer Manager and LEDs.
	if( !bIsInitialized )
	{
		hardware_init();

		MEM_Init();
		TMR_Init();
		//initialize PHY
		Phy_Init();


#if gSmacUseSecurity_c
		SecLib_Init();
#endif


		gTaskEvent = OSA_EventCreate(TRUE);
		InitApp();

		bIsInitialized = TRUE;
	}
	//initialize SLIP TCP IP
	SLIP_Init();

	LED_RED_INIT(1);
	LED_RED_ON();
	uint8_t led_status = 1;

	LED_GREEN_INIT(1);
	LED_GREEN_ON();
	uint8_t radio_led1_status = 1;
	uint8_t radio_led2_status = 1;
	uint8_t radio_led3_status = 1;


	/* sendRadioPacket(1);
	sendRadioPacket(2);
	sendRadioPacket(3);*/
	radio_led1_status = 0;
	radio_led2_status = 0;
	radio_led3_status = 0; 

	while (1)
	{

		rlen = SLIP_readPacket(1500,rxbuff);

		if(rlen==0){continue;}

		// tcp port starts

		if (rxbuff[TCP_FLAGS_P] & TCP_FLAGS_SYN_V) {
			make_tcp_synack_from_syn(rxbuff);
			continue;
		}

		if (rxbuff[TCP_FLAGS_P] & TCP_FLAGS_ACK_V) {
			init_len_info(rxbuff);

			dat_p = get_tcp_data_pointer();

			if(dat_p==0) {
				if(rxbuff[TCP_FLAGS_P] & TCP_FLAGS_FIN_V) {
					make_tcp_ack_from_any(rxbuff);
				}
				continue;
			}

			if (strncmp("GET ",(char *)&(rxbuff[dat_p]),4)!=0){

				rlen=fill_tcp_data_p(rxbuff,0,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<p>I suggest you resend your request.</p>");

				goto SENDTCP;
			}
			if (strncmp("/ ",(char *)&(rxbuff[dat_p+4]),2)==0){
				rlen=fill_tcp_data_p(rxbuff,0,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
				rlen=fill_tcp_data_p(rxbuff,rlen,"<h1>Hello World!</h1>\n");
				rlen=fill_tcp_data_p(rxbuff,rlen,"<p>This is a bare minimal HTTP/TCP/IP webserver\
  						                            running on a MKW41Z mcu over SLIP.\
  						                            NXP's SMAC stack is used for the radio.</p>\n");
				rlen=fill_tcp_data_p(rxbuff,rlen,"<h2>LED functionality: </h2>\n");
				rlen=fill_tcp_data_p(rxbuff,rlen,"<p>Go to \"194.169.55.2/led/x\" where x &#8712 {0,1,2} </p>\n");
				rlen=fill_tcp_data_p(rxbuff,rlen,"<p><font size=\"-1\">or click <a href=\"./led/\">here</a></font></p>\n");
				rlen=fill_tcp_data_p(rxbuff,rlen,"<h2>Credits: </h2>\n");
				rlen=fill_tcp_data_p(rxbuff,rlen,"<p>In my learning process, I referred to Adam Dunkel's <a href=\"http://dunkels.com/adam/miniweb/\">Miniweb</a> , \
  						                          as well as Guido Socher's <a href =\"https://tinyurl.com/2jjppf\">AVR Web Server</a>.\
  												  However, this was mostly my attempt at emmulating the http traffic to a normal website captured using tcpdump. \
  						                          The captured Ethernet/IP packtes are interpreted byte by byte based on instructions from\
  										          Kozierok's <a href=\"https://tinyurl.com/y7sy96xk\">The TCP/IP Guide</a>\
  						 	 	 	 	 	 	  and Fairhurst's <a href=\"https://tinyurl.com/8alfx\">IPv4 Packet Header</a>. </p>\n");

				goto SENDTCP;
			}

			cmd=analyse_get_url((char *)&(rxbuff[dat_p+5]));

			if (cmd==-1){
				rlen=fill_tcp_data_p(rxbuff,0,"HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<p>Not Like That<p>");
				goto SENDTCP;
			}
			if (cmd==1){
				LED_RED_ON();
				led_status = 1;
			}
			if (cmd==0){
				LED_RED_OFF();
				led_status = 0;
			}
			if (cmd==2){
				radio_led1_status = radio_led1_status? 0 : 1; // toggle
				sendRadioPacket(1, radio_led1_status);
			}
			if (cmd==3){
				radio_led2_status = radio_led2_status? 0 : 1;
				sendRadioPacket(1, radio_led2_status);
			}
			if (cmd==4){
				radio_led3_status = radio_led3_status? 0 : 1;
				sendRadioPacket(1, radio_led3_status);
			}

			if (cmd==-3){
				// redirect to add a trailing slash
				rlen=moved_perm(rxbuff);
				goto SENDTCP;
			}

			rlen=print_webpage(rxbuff,led_status,radio_led1_status, radio_led2_status, radio_led3_status);
			SENDTCP:
			make_tcp_ack_from_any(rxbuff); // send ack for http get
			make_tcp_ack_with_data(rxbuff,rlen); // send data
			continue;
		}

	}
}

/******************************************************************************
 *InitApp
 ******************************************************************************/
void InitApp()
{

	gAppTxPacket = (txPacket_t*)gau8TxDataBuffer;   //Map TX packet to buffer
	gAppRxPacket = (rxPacket_t*)gau8RxDataBuffer;   //Map Rx packet to buffer
#if gSmacUseSecurity_c
	gAppRxPacket->u8MaxDataLength = gMaxSmacSDULength_c + 16;
#else
	gAppRxPacket->u8MaxDataLength = gMaxSmacSDULength_c;
#endif


	//Initialise SMAC
	InitSmac();
	//Tell SMAC who to call when it needs to pass a message to the application thread.
	Smac_RegisterSapHandlers((SMAC_APP_MCPS_SapHandler_t)smacToAppMcpsSap,(SMAC_APP_MLME_SapHandler_t)smacToAppMlmeSap,0);

	InitProject();

	SMACFillHeader(&(gAppTxPacket->smacHeader), shortDestinationID);                   //Destination Address is set in InitProject;

	initWBN(gAppTxPacket);
	
#ifdef gPHY_802_15_4g_d
	(void)MLMESetPhyMode(gDefaultMode1_c);
#endif
	(void)MLMEPAOutputAdjust(testPower);
	(void)MLMESetChannelRequest(testChannel);

#if gSmacUseSecurity_c
	SMAC_SetIVKey(KEY, IV);
#endif
}

/***********************************************************************
 *********************Utilities Software********************************
 ************************************************************************/


void sendRadioPacket(uint8_t board, uint8_t messageCode) {
	Packet packet;
	
	packet.sourceID = 0;
	packet.destinationID = board;
	packet.packetID = packetCount;
	packet.timeToLive = 5;
	packet.payload = messageCode;
	
	if(packetCount == 127) {
		packetCount = 0;
	} else {
		packetCount = packetCount + 1;
	}
	
	uint8_t attemptCount = 0;
	do {
		ackReceived = FALSE;
   		sendViaWBN(&packet);
		attemptCount = attemptCount + 1;
		//Sets delay in milliseconds.
		OSA_TimeDelay(1000);
	} while(!ackReceived && attemptCount <= 2);

}


int8_t analyse_get_url(char *str)
{
	uint8_t loop=1;
	uint8_t i=0;
	while(loop){
		if(password[i]){
			if(*str==password[i]){
				str++;
				i++;
			}else{
				return(-1);
			}
		}else{
			// end of password
			loop=0;
		}
	}
	// is is now one char after the password
	if (*str == '/'){
		str++;
	}else{
		return(-3);
	}
	// check the first char, garbage after this is ignored (including a slash)
	if (*str < 0x3a && *str > 0x2f){
		// is a ASCII number, return it
		return(*str-0x30);
	}
	return(-2);
}


uint16_t moved_perm(uint8_t *buf)
{
	uint16_t plen;
	plen=fill_tcp_data_p(buf,0,"HTTP/1.0 301 Moved Permanently\r\nLocation: ");
	plen=fill_tcp_data_p(buf,plen,password);
	plen=fill_tcp_data_p(buf,plen,"/\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n");
	plen=fill_tcp_data_p(buf,plen,"<h1>301 Moved Permanently</h1>\n");
	plen=fill_tcp_data_p(buf,plen,"add a trailing slash to the url\n");
	return(plen);
}



// prepare the webpage by writing the data to the tcp send buffer
uint16_t print_webpage(uint8_t *buf,uint8_t on_off, uint8_t radio1_on_off, uint8_t radio2_on_off, uint8_t radio3_on_off)
{
	uint16_t plen;
	plen=fill_tcp_data_p(buf,0,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n");
	plen=fill_tcp_data_p(buf,plen,"<center><p>Onboard LED is: ");
	if (on_off){
		plen=fill_tcp_data_p(buf,plen,"<font color=\"#00FF00\"> ON</font>");
	}else{
		plen=fill_tcp_data_p(buf,plen,"OFF");
	}

	plen=fill_tcp_data_p(buf,plen,"<center><p>Remote LED1 is: ");

	if (radio1_on_off){
		plen=fill_tcp_data_p(buf,plen,"<font color=\"#00FF00\"> ON</font>");
	}else {
		plen=fill_tcp_data_p(buf,plen,"OFF");
	}

	plen=fill_tcp_data_p(buf,plen,"<center><p>Remote LED2 is: ");

	if (radio2_on_off){
		plen=fill_tcp_data_p(buf,plen,"<font color=\"#00FF00\"> ON</font>");
	}else {
		plen=fill_tcp_data_p(buf,plen,"OFF");
	}
	plen=fill_tcp_data_p(buf,plen,"<center><p>Remote LED3 is: ");

	if (radio3_on_off){
		plen=fill_tcp_data_p(buf,plen,"<font color=\"#00FF00\"> ON</font>");
	}else {
		plen=fill_tcp_data_p(buf,plen,"OFF");
	}

	if (on_off){
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./0\">Switch On Board LED off</a><p>");
	}else{
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./1\">Switch on Board LED on</a><p>");
	}

	if (radio1_on_off){
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./2\">Switch Remote LED1 off</a><p>");
	}else {
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./2\">Switch Remote LED1 on</a><p>");
	}

	if (radio2_on_off){
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./3\">Switch Remote LED2 off</a><p>");
	}else {
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./3\">Switch Remote LED2 on</a><p>");
	}


	if (radio3_on_off){
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./4\">Switch Remote LED3 off</a><p>");
	}else {
		plen=fill_tcp_data_p(buf,plen,"\n<p><a href=\"./4\">Switch Remote LED3 on</a><p>");
	}


	return(plen);
}


/***********************************************************************
 ************************************************************************/
