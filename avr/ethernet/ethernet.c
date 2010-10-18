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

#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>

#include <sys/select.h>
#include <sys/time.h>

#include <signal.h>

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
#include "libuart/uart.h"
#include "config.h"

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
int exiter;
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

char macAddr[] = {ETHADDR0, ETHADDR1, ETHADDR2, ETHADDR3, ETHADDR4, ETHADDR5};

struct sockaddr_ll device;

int linSock;
#define enc28j60PacketReceive(BFSZ, buffr) read(linSock, buffr, BFSZ)
#define enc28j60PacketSend(BFSZ, buffr) 	if(sendto(linSock, buffr, BFSZ, 0, (const struct sockaddr *)&device, sizeof(device)) == -1) \
														{ \
															perror("ERROR: "); \
														}
void socketInit()
{
	if((linSock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
	{
		perror("ERROR: ");
	}

	struct ifreq card;

	strcpy(card.ifr_name, "wlan0");

  if(ioctl(linSock, SIOCGIFINDEX, &card) == -1)
  {
	  perror("ERROR: ");
  }

	memset(&device, 0, sizeof(device));

	device.sll_family = AF_PACKET;
	device.sll_ifindex = card.ifr_ifindex;
	//memset(device.sll_addr, 0xFF, 6);
	memcpy(device.sll_addr, macAddr, 6);
	device.sll_halen = HTONS(6);


}
#endif


void mainUIPLoop()
{

	usart_init();


	int i;

	struct timer periodic_timer, arp_timer;

 
	#ifndef X86
	/*reset our ethernet chip*/
	writeLn("Resetting the ENC28J60...");
	DDRD = (1 << 5);
	PORTD |= (1 << 5);
	PORTD &= ~(1 << 5);
	delay_ms(10);
	PORTD |= (1 << 5);
	delay_ms(10);
	writeLn("Done!\r\n");

	clock_init();
	enc28j60Init();
	#else
	socketInit();
	#endif

	//This HAS to happen before uip_init
	preUIpInit();

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

#ifdef X86
	uip_ipaddr_t ipaddr;
	uip_ipaddr(ipaddr, 168, 192, 17, 0);
	uip_sethostaddr(ipaddr);

	uip_ipaddr(ipaddr, 168, 192, 1, 0);
	uip_setdraddr(ipaddr);

	uip_ipaddr(ipaddr, 255, 255, 0, 255);
	uip_setnetmask(ipaddr);
#else
	uip_ipaddr_t ipaddr;
	uip_ipaddr(ipaddr, 192, 168, 0, 17);
	uip_sethostaddr(ipaddr);

	uip_ipaddr(ipaddr, 192, 168, 0, 1);
	uip_setdraddr(ipaddr);

	uip_ipaddr(ipaddr, 255, 255, 255, 0);
	uip_setnetmask(ipaddr);

	enc28j60RegDump();
#endif


	web_init();
	while(1)
	{
		uip_len = enc28j60PacketReceive(UIP_BUFSIZE, uip_buf);
		if(uip_len > 0)
		{
			//ledDebug(1);
			if(BUF->type == htons(UIP_ETHTYPE_IP))
			{
				//ledDebug(2);
				uip_arp_ipin();
				uip_input();
				//	If the above function invocation resulted in data that
				//	should be sent out on the network, the global variable
				//	uip_len is set to a value > 0. 
				if(uip_len > 0)
				{
					uip_arp_out();
					enc28j60PacketSend(uip_len, uip_buf);
				}
			}
			else if(BUF->type == htons(UIP_ETHTYPE_ARP))
			{
				//ledDebug(4);
				uip_arp_arpin();
				//	If the above function invocation resulted in data that
				//	should be sent out on the network, the global variable
				//	uip_len is set to a value > 0.
				if(uip_len > 0)
				{
					enc28j60PacketSend(uip_len, uip_buf);
				}
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
					enc28j60PacketSend(uip_len, uip_buf);
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
					enc28j60PacketSend(uip_len, uip_buf);
				}
			}
#endif // UIP_UDP
      
			//Call the ARP timer function every 10 seconds.
			if(timer_expired(&arp_timer))
			{
				//This is just to see how things are going
				timer_reset(&arp_timer);
				uip_arp_timer();
			}
		}
#ifdef X86
		if(exiter) break;
#endif
	}
#ifdef X86
	printf("Closing socket...  ");
	shutdown(linSock, SHUT_RDWR);
	close(linSock);
	printf("Closed!\n");
#endif
}


#ifdef X86
void ex_program(int sig);
#endif


int main()
{
#ifdef X86
	exiter = 0;
	(void) signal(SIGINT, ex_program);
#endif

	mainUIPLoop();

	return 0;
}

#ifdef X86
void ex_program(int sig)
{
	printf("Caught signal: %d\n", sig);
	exiter = 1;
}
#endif