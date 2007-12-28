/*
 * SPI2CF (c) 2006, Till Harbaum.
 * All rights reserved.
 *
 * This file is distributed under the GPL.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part SPI2CF port of the uIP TCP/IP stack.
 */

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



/*---------------------------------------------------------------------------*/
clock_time_t
clock_time(void) {
  return ticks;
}
/*---------------------------------------------------------------------------*/
