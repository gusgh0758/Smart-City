#include <stdio.h>
#include "lwip.h"
#include "api.h"

uint32_t lwip_udp_test(struct netconn *conn, struct netbuf *buf)
{
	uint8_t *data;
	uint16_t len;
	uint16_t dest_port, source_port;
	ip_addr_t dest_ip, source_ip;
	uint8_t i;
	uint8_t key = 0x12;

	dest_port = 2000;

	IP4_ADDR(&dest_ip, 192, 168, 1, 50);

	while (netconn_recv(conn, &buf) == ERR_OK)
	{
		source_ip = buf->addr;
		source_port = buf->port;

		do
		{

			/******************* Encryption Section *******************/
			for (i = 0; i < buf->p->len; i++) {
				*((uint8_t*)buf->p->payload + i) = *((uint8_t*)buf->p->payload + i) ^ key;
			}
			/*******************************************************************/

			netconn_sendto(conn, buf, &dest_ip, dest_port);
		}
		while(netbuf_next(buf) >=0);

		netbuf_delete(buf);
	}

	return 0;
}



