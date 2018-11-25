#define F_CPU 1000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "melody.h"
#include "melodies.h"

#define adc_disable()  (ADCSRA &= ~(1<<ADEN))

#define	N_1	(_BV(CS10))
#define	N_2	(_BV(CS11))
#define	N_4	(_BV(CS11)|_BV(CS10))
#define	N_8	(_BV(CS12))
#define	N_16	(_BV(CS12)|_BV(CS10))
#define	N_32	(_BV(CS12)|_BV(CS11))
#define	N_64	(_BV(CS12)|_BV(CS11)|_BV(CS10))
#define	N_128	(_BV(CS13))
#define	N_256	(_BV(CS13)|_BV(CS10))
#define	N_512	(_BV(CS13)|_BV(CS11))

void adc_init()
{
	/* Use Vcc as Aref */
	ADMUX = 0;

	/* Set the prescaler to 8, this will give us ~125kHZ @ 1MHz,
	 * meaning 8us per sample => 8.2ms to traverse all the way from 0 to
	 * 1024 */
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

static inline uint16_t adc_read(uint8_t n)
{
	uint16_t result;

	/* ADC number must be 0-7 */
	ADMUX |= n & 0x7;

	/* Start single conversion */
	ADCSRA|=(1<<ADSC);

	/* Wait for conversion to complete */
	while(!(ADCSRA & (1<<ADIF)));

	/* Get the result */
	result = ADC;

	/* Clear the ADIF bit */
	ADCSRA|=(1<<ADIF);

	return result;
}

struct avr_note {
	uint8_t OCRxn; // 0..255
	uint8_t N;
};

struct avr_octave {
	union {
		struct {
			struct avr_note note_C;
			struct avr_note note_Cs;
			struct avr_note note_D;
			union {
				struct avr_note note_Ds;
				struct avr_note note_Eb;
			};
			struct avr_note note_E;
			struct avr_note note_F;
			union {
				struct avr_note note_Fs;
				struct avr_note note_Gb;
			};
			struct avr_note note_G;
			struct avr_note note_Gs;
			struct avr_note note_A;
			union {
				struct avr_note note_As;
				struct avr_note note_Bb;
			};
			struct avr_note note_B;
		};
		struct avr_note notes[12];
	};
};

/* All calculations below are done using note-calc.py */
PROGMEM const struct avr_octave octaves[8] = {
	{ /* Octave 0 */
		.note_C  = {118, N_256}, /*  16.35Hz */
		.note_Cs = {112, N_256}, /*  17.32Hz */
		.note_D  = {105, N_256}, /*  18.35Hz */
		.note_Ds = { 99, N_256}, /*  19.45Hz */
		.note_E  = { 94, N_256}, /*  20.60Hz */
		.note_F  = { 88, N_256}, /*  21.83Hz */
		.note_Fs = { 83, N_256}, /*  23.13Hz */
		.note_G  = { 79, N_256}, /*  24.50Hz */
		.note_Gs = { 74, N_256}, /*  25.96Hz */
		.note_A  = { 70, N_256}, /*  27.50Hz */
		.note_As = { 66, N_256}, /*  29.14Hz */
		.note_B  = {126, N_128}, /*  30.87Hz */
	},
	{ /* Octave 1 */
		.note_C  = {118, N_128}, /*  32.70Hz */
		.note_Cs = {112, N_128}, /*  34.65Hz */
		.note_D  = {105, N_128}, /*  36.71Hz */
		.note_Ds = { 99, N_128}, /*  38.89Hz */
		.note_E  = { 94, N_128}, /*  41.20Hz */
		.note_F  = { 88, N_128}, /*  43.65Hz */
		.note_Fs = { 83, N_128}, /*  46.25Hz */
		.note_G  = { 79, N_128}, /*  49.00Hz */
		.note_Gs = { 74, N_128}, /*  51.91Hz */
		.note_A  = { 70, N_128}, /*  55.00Hz */
		.note_As = { 66, N_128}, /*  58.27Hz */
		.note_B  = {126, N_64 }, /*  61.74Hz */
	},
	{ /* Octave 2 */
		.note_C  = {118, N_64 }, /*  65.41Hz */
		.note_Cs = {112, N_64 }, /*  69.30Hz */
		.note_D  = {105, N_64 }, /*  73.42Hz */
		.note_Ds = { 99, N_64 }, /*  77.78Hz */
		.note_E  = { 94, N_64 }, /*  82.41Hz */
		.note_F  = { 88, N_64 }, /*  87.31Hz */
		.note_Fs = { 83, N_64 }, /*  92.50Hz */
		.note_G  = { 79, N_64 }, /*  98.00Hz */
		.note_Gs = { 74, N_64 }, /* 103.83Hz */
		.note_A  = { 70, N_64 }, /* 110.00Hz */
		.note_As = { 66, N_64 }, /* 116.54Hz */
		.note_B  = {126, N_32 }, /* 123.47Hz */
	},
	{ /* Octave 3 */
		.note_C  = {118, N_32 }, /* 130.82Hz */
		.note_Cs = {112, N_32 }, /* 138.59Hz */
		.note_D  = {105, N_32 }, /* 146.84Hz */
		.note_Ds = { 99, N_32 }, /* 155.57Hz */
		.note_E  = { 94, N_32 }, /* 164.82Hz */
		.note_F  = { 88, N_32 }, /* 174.62Hz */
		.note_Fs = { 83, N_32 }, /* 185.00Hz */
		.note_G  = { 79, N_32 }, /* 196.00Hz */
		.note_Gs = { 74, N_32 }, /* 207.66Hz */
		.note_A  = { 70, N_32 }, /* 220.01Hz */
		.note_As = { 66, N_32 }, /* 233.09Hz */
		.note_B  = {126, N_16 }, /* 246.95Hz */
	},
	{ /* Octave 4 */
		.note_C  = {118, N_16 }, /* 261.63Hz */
		.note_Cs = {112, N_16 }, /* 277.19Hz */
		.note_D  = {105, N_16 }, /* 293.67Hz */
		.note_Ds = { 99, N_16 }, /* 311.13Hz */
		.note_E  = { 94, N_16 }, /* 329.64Hz */
		.note_F  = { 88, N_16 }, /* 349.24Hz */
		.note_Fs = { 83, N_16 }, /* 370.00Hz */
		.note_G  = { 79, N_16 }, /* 392.01Hz */
		.note_Gs = { 74, N_16 }, /* 415.31Hz */
		.note_A  = { 70, N_16 }, /* 440.01Hz */
		.note_As = { 66, N_16 }, /* 466.18Hz */
		.note_B  = {126, N_8  }, /* 493.90Hz */
	},
	{ /* Octave 5 */
		.note_C  = {118, N_8  }, /* 523.26Hz */
		.note_Cs = {112, N_8  }, /* 554.38Hz */
		.note_D  = {105, N_8  }, /* 587.34Hz */
		.note_Ds = { 99, N_8  }, /* 622.27Hz */
		.note_E  = { 94, N_8  }, /* 659.27Hz */
		.note_F  = { 88, N_8  }, /* 698.47Hz */
		.note_Fs = { 83, N_8  }, /* 740.01Hz */
		.note_G  = { 79, N_8  }, /* 784.01Hz */
		.note_Gs = { 74, N_8  }, /* 830.63Hz */
		.note_A  = { 70, N_8  }, /* 880.02Hz */
		.note_As = { 66, N_8  }, /* 932.35Hz */
		.note_B  = {126, N_4  }, /* 987.79Hz */
	},
	{ /* Octave 6 */
		.note_C  = {118, N_4  }, /* 1046.53Hz */
		.note_Cs = {112, N_4  }, /* 1108.76Hz */
		.note_D  = {105, N_4  }, /* 1174.69Hz */
		.note_Ds = { 99, N_4  }, /* 1244.54Hz */
		.note_E  = { 94, N_4  }, /* 1318.54Hz */
		.note_F  = { 88, N_4  }, /* 1396.95Hz */
		.note_Fs = { 83, N_4  }, /* 1480.01Hz */
		.note_G  = { 79, N_4  }, /* 1568.02Hz */
		.note_Gs = { 74, N_4  }, /* 1661.26Hz */
		.note_A  = { 70, N_4  }, /* 1760.04Hz */
		.note_As = { 66, N_4  }, /* 1864.70Hz */
		.note_B  = {126, N_2  }, /* 1975.58Hz */
	},
	{ /* Octave 7 */
		.note_C  = {118, N_2  }, /* 2093.06Hz */
		.note_Cs = {112, N_2  }, /* 2217.52Hz */
		.note_D  = {105, N_2  }, /* 2349.38Hz */
		.note_Ds = { 99, N_2  }, /* 2489.08Hz */
		.note_E  = { 94, N_2  }, /* 2637.09Hz */
		.note_F  = { 88, N_2  }, /* 2793.89Hz */
		.note_Fs = { 83, N_2  }, /* 2960.03Hz */
		.note_G  = { 79, N_2  }, /* 3136.04Hz */
		.note_Gs = { 74, N_2  }, /* 3322.52Hz */
		.note_A  = { 70, N_2  }, /* 3520.09Hz */
		.note_As = { 66, N_2  }, /* 3729.40Hz */
		.note_B  = { 62, N_2  }, /* 3951.16Hz */
	},
};

#define LED_ON() PORTB &= ~(1<<PB3) // 60ms
#define LED_OFF() PORTB |= 1<<PB3

static void play(const struct melody *melody_pgm) {
	/* Get the delay function */
	uint16_t _delay_func = pgm_read_word_near(&melody_pgm->delay_func);
	void (*delay_func)(uint8_t, uint8_t) = (void (*)(uint8_t, uint8_t))_delay_func;

	uint8_t last_had_tie = 0;
	for (uint8_t i = 0; 1; i++) {
		/* Read the note from the melody */
		uint16_t _note = pgm_read_word_near(&melody_pgm->notes[i]);
		struct note *note = (struct note *)&_note;

		/* Is it an end? */
		if (note->t == End)
			break;

		/* Is it a rest? */
		if (note->t == R)
			goto rest;

		/* Light LED unless this note is part of a tie */
		if (!last_had_tie)
			LED_ON();
		last_had_tie = note->tie;

		/* Read the values needed to configure the PWM */
		uint16_t _avr_note = pgm_read_word_near(&octaves[note->o].notes[note->t]);
		struct avr_note *avr_note = (struct avr_note *)&_avr_note;

		/* Setup the prescaler */
		TCCR1 = (TCCR1 & ~((1<<CS13)|(1<<CS12)|(1<<CS11)|(1<<CS10))) | avr_note->N;

		/* Set OCR1A for the "on" trigger, and OCR1C for the "off"
		 * trigger */
		OCR1A = avr_note->OCRxn - 1;
		OCR1C = avr_note->OCRxn * 2;

rest:
		/* Let the LED shine for a bit */
		_delay_ms(50);
		LED_OFF();

		/* Play the note (or rest) */
		delay_func(note->d, note->dots);

		/* Terminate the note unless there is a tie marker */
		if (!note->tie) {
			/* Stop the timer */
			TCCR1 &= ~((1<<CS13)|(1<<CS12)|(1<<CS11)|(1<<CS10));
		}

		/* Wait for the instrument to die out / fill out so that the
		 * notes are the same length */
		_delay_ms(10);

	}
	/* Switch off the LED */
	LED_OFF();

	/* Stop the timer */
	TCCR1 &= ~((1<<CS13)|(1<<CS12)|(1<<CS11)|(1<<CS10));
}

uint8_t rng_a = 42;
uint8_t rng_b = 18;
uint8_t rng_c = 36;
uint8_t rng_x = 230;
static uint8_t rng_get() {
	rng_x++;
	rng_a = (rng_a^rng_c^rng_x);
	rng_b = (rng_b+rng_a);
	rng_c = (rng_c+((rng_b>>1)^rng_a));
	return rng_c;
}
static void rng_init(uint8_t s1, uint8_t s2, uint8_t s3) {
	rng_a ^=s1;
	rng_b ^=s2;
	rng_c ^=s3;
	(void)rng_get();
} 

int main(void)
{
 	/*                       ______
 	 *           Reset PB5 *|      |* Vcc
 	 *            LED0 PB3 *|      |* PB2 ADC1 for RNG
 	 *            SPK0 PB4 *|      |* PB1 SPK1 (PWM)
 	 *                 GND *|______|* PB0 LED1
	 */

	// Enable 64 MHz PLL and use as source for Timer1
	//PLLCSR = 1<<PCKE | 1<<PLLE;  

	/* setup */
	/* Output on all connected I/Os except ADC1 */
	DDRB = 1<<PB4 | 1<<PB3 | 1<<PB0 | 1<<PB1;

	/* Lower all pins except the LED pins */
	PORTB = 1<<PB3 | 1<<PB0;

	/* Get random seed */
	adc_init();
	uint16_t seed = adc_read(1);

	/* Initialize the random seed */
	rng_init(seed, seed >> 8, (uint8_t)((seed >> 4) + 189));

	/* Init the PWM */
	TIMSK = 0;                              // Timer interrupts OFF
	TCCR1 = 1<<CTC1 | 1<<PWM1A | 1<<COM1A1 | 1<<COM1A0; // clear counter on match, PWM A enabled, raise on match
	OCR1A = 0;

	/* Set up sleep mode */
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	/* Only raise the LED pins */
	PORTB = 1<<PB3 | 1<<PB0;

	uint8_t r;
	/* Get random number while removing bias towards lower numbers */
	while ((r = rng_get()) > (255 - (256 % NUM_MELODIES)));
	r %= NUM_MELODIES;

#ifdef DEBUG_PLAY_ALL
	/* Play all melodies */
	for (uint8_t i = 0; i < NUM_MELODIES; i++) {
		play(melodies[i]);
		_delay_ms(1000);
	}
#else
	/* Play a random melody */
	play(melodies[r]);
#endif

	/* Put everything to sleep (~1uA) */
	PORTB = 0;
	adc_disable();
	sleep_enable();
	sleep_cpu();

}
