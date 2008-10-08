#ifdef X86
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <sys/socket.h>


#else
#include "global.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include "enc28j60.h"

#include <avr/eeprom.h>
#include <stdio.h>
#endif

#include <inttypes.h>
#include "uip.h"
#include "uip_arp.h"
#include "timer.h"
#include "uart.h"
#include "config.h"

#ifdef DEBUGSOCK
#include <stdio.h>
#include <stdlib.h>
#endif


//FUSES - HFUSE:99 LFUSE:EF
//FUSES - HFUSE:91 LFUSE:EF

#ifndef X86
void WDT_off(void) __attribute__((naked)) __attribute__((section(".init3")));
void WDT_off(void) 
{ 
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */ 
	MCUSR &= ~(1<<WDRF); 
	/* Write logical one to WDCE and WDE */ 
	/* Keep old prescaler setting to prevent unintentional time-out */ 
	WDTCSR |= (1<<WDCE) | (1<<WDE); 
	/* Turn off WDT */ 
	WDTCSR = 0x00; 
	sei();
}
#endif

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
#define ETHERNET_MIN_PACKET_LENGTH	0x3C
#define ETHERNET_HEADER_LENGTH		0x0E
#define IP_TCP_HEADER_LENGTH 40
#define TOTAL_HEADER_LENGTH (IP_TCP_HEADER_LENGTH+ETHERNET_HEADER_LENGTH)

#ifdef X86
void delay_ms(unsigned int ms)
{
	//This may be problematic if you wanna use this for more than one second
	usleep(1000 * ms);
}
#else
void delay_ms(unsigned int ms)
/* delay for a minimum of <ms> */
{
	// we use a calibrated macro. This is more
	// accurate and not so much compiler dependent
	// as self made code.
	while(ms)
	{
		_delay_ms(0.96);
		ms--;
	}
}
#endif

#ifdef X86
int linSock;
#define enc28j60PacketReceive(BFSZ, buffr) read(linSock, buffr, BFSZ)
#define enc28j60PacketSend(BFSZ, buffr) write(linSock, buffr, BFSZ)
void socketInit()
{
	if((linSock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
	{
		perror("ERROR: ");
	}
}
#endif

int main()
{
	int i;

	struct timer periodic_timer, arp_timer;

 
	#ifndef X86
	/*reset our ethernet chip*/
	DDRD = 0xFF;
	PORTD = 0x00;
	delay_ms(100);
	DDRD = 0x00;
	#endif

	#ifndef X86
	usart_init();
	#ifdef DEBUGSOCK
	char tst[15];
	sprintf(tst, "MCUSR: %d\r\n", MCUSR);
	MCUSR = 0;
	writeLn(tst);
	#endif
	clock_init();
	enc28j60Init();
	delay_ms(10);
	enc28j60RegDump();
	#else
	socketInit();
	#endif

	uip_init();

	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);

	struct uip_eth_addr eaddr;	
#ifdef X86
	eaddr.addr[0] = ETHADDR0;
	eaddr.addr[1] = ETHADDR1;
	eaddr.addr[2] = ETHADDR2;
	eaddr.addr[3] = ETHADDR3;
	eaddr.addr[4] = ETHADDR4;
	eaddr.addr[5] = ETHADDR5;
#else
	eaddr.addr[0] = '0';
	eaddr.addr[1] = 'F';
	eaddr.addr[2] = 'F';
	eaddr.addr[3] = 'I';
	eaddr.addr[4] = 'C';
	eaddr.addr[5] = 'E';
#endif

	uip_setethaddr(eaddr);

	#ifdef DEBUGSOCK
	char macData[100];
	int maci;
	for(maci = 0; maci < 6; maci ++)
	{
		sprintf(macData, "MAC%d: %X\r\n", maci, eaddr.addr[maci]);
		writeLn(macData);
	}
	#endif

	//IP address = 0-3 bytes of eeprom
	//subnet mask = 4-7 bytes of eeprom
	//default gw = 8-11 bytes of eeprom
	uint8_t eepromIP[4];
	eepromIP[0] = eeprom_read_byte((uint8_t *)0);
	eepromIP[1] = eeprom_read_byte((uint8_t *)1);
	eepromIP[2] = eeprom_read_byte((uint8_t *)2);
	eepromIP[3] = eeprom_read_byte((uint8_t *)3);

	uint8_t eepromNM[4];
	eepromNM[0] = eeprom_read_byte((uint8_t *)4);
	eepromNM[1] = eeprom_read_byte((uint8_t *)5);
	eepromNM[2] = eeprom_read_byte((uint8_t *)6);
	eepromNM[3] = eeprom_read_byte((uint8_t *)7);

	uint8_t eepromDG[4];
	eepromDG[0] = eeprom_read_byte((uint8_t *)8);
	eepromDG[1] = eeprom_read_byte((uint8_t *)9);
	eepromDG[2] = eeprom_read_byte((uint8_t *)10);
	eepromDG[3] = eeprom_read_byte((uint8_t *)11);


	char infoString[50];
	sprintf(infoString, "IP ADDRESS: %d.%d.%d.%d\r\n", eepromIP[0], eepromIP[1], eepromIP[2], eepromIP[3]);
	writeLn(infoString);
	sprintf(infoString, "SUBNET MASK: %d.%d.%d.%d\r\n", eepromNM[0], eepromNM[1], eepromNM[2], eepromNM[3]);
	writeLn(infoString);
	sprintf(infoString, "DEFAULT GW: %d.%d.%d.%d\r\n", eepromDG[0], eepromDG[1], eepromDG[2], eepromDG[3]);
	writeLn(infoString);

	uip_ipaddr_t ipaddr;
	uip_ipaddr(ipaddr, eepromIP[0], eepromIP[1], eepromIP[2], eepromIP[3]);
	uip_sethostaddr(ipaddr);

	uip_ipaddr(ipaddr, eepromDG[0], eepromDG[1], eepromDG[2], eepromDG[3]);
	uip_setdraddr(ipaddr);

	uip_ipaddr(ipaddr, eepromNM[0], eepromNM[1], eepromNM[2], eepromNM[3]);
	uip_setnetmask(ipaddr);


	//hello_world_init();
	//httpd_init();
	web_init();
	#ifdef DEBUGSOCK
	char data[100];
	#endif
	while(1)
	{
		uip_len = enc28j60PacketReceive(UIP_BUFSIZE, uip_buf);
		if(uip_len > 0)
		{
			/*test
			int tl = 0;
			printf("Packet Data: ");
			fflush(NULL);
			for(tl = 0; tl < uip_len; tl++)
			{
				printf("%X ", uip_buf[tl]);
				fflush(NULL);
			}
			printf("\n");
			fflush(NULL);
			test end*/

			#ifdef DEBUGSOCK
			sprintf(data, "Packet Length: %d\r\n", uip_len);
			writeLn(data);
			#endif
			if(BUF->type == htons(UIP_ETHTYPE_IP))
			{
				uip_arp_ipin();
				uip_input();
				//	If the above function invocation resulted in data that
				//	should be sent out on the network, the global variable
				//	uip_len is set to a value > 0. 
				if(uip_len > 0)
				{
					uip_arp_out();
					#ifdef DEBUGSOCK
					writeLn("Sending IP Packet...");
					#endif
					enc28j60PacketSend(uip_len, uip_buf);
					#ifdef DEBUGSOCK
					writeLn(" Done!\r\n");
					#endif
				}
			}
			else if(BUF->type == htons(UIP_ETHTYPE_ARP))
			{
				#ifdef DEBUGSOCK
				writeLn("ARP Packet recieved\r\n");
				#endif
				uip_arp_arpin();
				//	If the above function invocation resulted in data that
				//	should be sent out on the network, the global variable
				//	uip_len is set to a value > 0.
				if(uip_len > 0)
				{
					#ifdef DEBUGSOCK
					writeLn("Sending ARP Packet...");
					#endif
					enc28j60PacketSend(uip_len, uip_buf);
					#ifdef DEBUGSOCK
					writeLn(" Done!\r\n");
					#endif
				}
				#ifdef DEBUGSOCK
				else writeLn("uip_len is not bigger than 0\r\n");
				#endif
			}
		}
		else if(timer_expired(&periodic_timer))
		{
			timer_reset(&periodic_timer);
			for(i = 0; i < UIP_CONNS; i++)
			{
				uip_periodic(i);
				//	If the above function invocation resulted in data that
				//	should be sent out on the network, the global variable
				//	uip_len is set to a value > 0.
				if(uip_len > 0)
				{
					uip_arp_out();
					#ifdef DEBUGSOCK
					writeLn("Sending OTHER Packet...");
					#endif
					enc28j60PacketSend(uip_len, uip_buf);
					#ifdef DEBUGSOCK
					writeLn(" Done!\r\n");
					#endif
				}
			}

#if UIP_UDP
			for(i = 0; i < UIP_UDP_CONNS; i++)
			{
				uip_udp_periodic(i);
				//	If the above function invocation resulted in data that
				//	should be sent out on the network, the global variable
				//	uip_len is set to a value > 0.
				if(uip_len > 0)
				{
					uip_arp_out();
					#ifdef DEBUGSOCK
					writeLn("Sending UIPARP Packet...");
					#endif
					enc28j60PacketSend(uip_len, uip_buf);
					#ifdef DEBUGSOCK
					writeLn(" Done!\r\n");
					#endif
				}
			}
#endif // UIP_UDP
      
			//Call the ARP timer function every 10 seconds.
			if(timer_expired(&arp_timer))
			{
				//This is just to see how things are going
				//enc28j60RegDump();
				timer_reset(&arp_timer);
				uip_arp_timer();
			}
		}
	}
	

	return 0;
}
