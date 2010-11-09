#include "clock-arch.h"

#ifdef X86
#include <sys/time.h>
#include <time.h>
clock_time_t clock_time(void)
{
  struct timeval tv;

  gettimeofday(&tv, NULL);

  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
#else

#include "uip-conf.h"
#include "clock.h"

#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER_PRESCALE (1<<CS11)
#define TIMER_RELOAD   (u16_t)(((F_CPU/8) / CLOCK_SECOND)-1)
#define TIMER_REAL     (F_CPU/(TIMER_RELOAD+1)/8)

clock_time_t ticks;

SIGNAL(SIG_OUTPUT_COMPARE1A) {
  /* clear counter */
  TCNT1 = 0;
  ticks++;
}

/* init timer hardware and install interrupt handler */
void clock_init(void) {
  ticks = 0;

  // make counter run
  TCCR1B = TIMER_PRESCALE; // timer1 prescaler CK/8 = 916kHz @ 7.328 Mhz

  /* 16 bit overflow = CPU_CLK/65536, at 916 kHz hz = 13.977 Hz */
  OCR1A = TIMER_RELOAD;

  // make counter generate interrupts
  TIMSK1 |= _BV(OCIE1A); // timer 1 compare a event

  sei();
}

clock_time_t
clock_time(void) {
  return ticks;
}

#endif
