/*
 * freertos_functions.c
 *
 *  Created on: Dec 18, 2021
 *      Author: Hyun-Ho Cha
 */
#include <stdio.h>
#include "cmsis_os.h"
#include "lwip.h"
#include "socket.h"
#include "wizchip_conf.h"
#include "w5300.h"
#include "freertos_function.h"


void Unit_Side_Data_Task(void const * argument)
{

	const char* message = "Hello UDP message!\n\r";

	osDelay(1000);

	ip_addr_t PC_IPADDR;
	IP_ADDR4(&PC_IPADDR, 192, 168, 1, 50);

	struct udp_pcb* my_udp = udp_new();
	udp_connect(my_udp, &PC_IPADDR, 55151);
	struct pbuf* udp_buffer = NULL;

	for(;;)
	{
		osDelay(1000);
		/* !! PBUF_RAM is critical for correct operation !! */
		udp_buffer = pbuf_alloc(PBUF_TRANSPORT, strlen(message), PBUF_RAM);

		if (udp_buffer != NULL) {
			memcpy(udp_buffer->payload, message, strlen(message));
			udp_send(my_udp, udp_buffer);
			pbuf_free(udp_buffer);
		}
	}
}

void SCM_Side_Data_Task(void const * argument)
{
	int32_t  ret;
	uint16_t size, sentsize;
	uint8_t  destip[4];
	uint16_t destport;
	uint8_t sn;
	uint8_t* buf;
	uint16_t port;

	for(;;)
	{
		switch(getSn_SR(sn))
		{
		  case SOCK_UDP :
			 if((size = getSn_RX_RSR(sn)) > 0)
			 {
				if(size > DATA_BUF_SIZE) size = DATA_BUF_SIZE;
				ret = recvfrom(sn, buf, size, destip, (uint16_t*)&destport);
				if(ret <= 0)
				{
	#ifdef _LOOPBACK_DEBUG_
				   printf("%d: recvfrom error. %ld\r\n",sn,ret);
	#endif
				   return ret;
				}
				size = (uint16_t) ret;
				sentsize = 0;
				while(sentsize != size)
				{
				   ret = sendto(sn, buf+sentsize, size-sentsize, destip, destport);
				   if(ret < 0)
				   {
	#ifdef _LOOPBACK_DEBUG_
					  printf("%d: sendto error. %ld\r\n",sn,ret);
	#endif
					  return ret;
				   }
				   sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
				}
			 }
			 break;
		  case SOCK_CLOSED:
	#ifdef _LOOPBACK_DEBUG_
			 //printf("%d:UDP loopback start\r\n",sn);
	#endif
			 if((ret = socket(sn, Sn_MR_UDP, port, 0x00)) != sn)
				return ret;
	#ifdef _LOOPBACK_DEBUG_
			 printf("%d:Opened, UDP loopback, port [%d]\r\n", sn, port);
	#endif
			 break;
		  default :
			 break;
		}

		osDelay(1);
	}

}
