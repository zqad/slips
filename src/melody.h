#ifndef _MELODY_H
#define _MELODY_H
#include <stdint.h>

enum tone {
	C	= 0,
	Cs	= 1,
	Db	= 1,
	D	= 2,
	Ds	= 3,
	Eb 	= 3,
	E	= 4,
	F	= 5,
	Fs	= 6,
	Gb	= 6,
	G	= 7,
	Gs	= 8,
	Ab 	= 8,
	A	= 9,
	As	= 10,
	Bb	= 10,
	B	= 11,

	R	= 14, // Rest
	End	= 15,
};

enum divider {
	whole,
	half,
	quarter,
	eighth,
	sixteenth,
};

struct __attribute__((packed)) note {
	uint8_t o:3;
	enum tone t:4;
	uint8_t tie:1;
	enum divider d:3;
	uint8_t dots:2;
};

struct melody {
	void (*delay_func)(uint8_t, uint8_t);
	struct note notes[];
};

struct name_melody {
	const struct melody* melody;
	const char *name;
};

#define SUB_OR_ZERO(n, s) (((n) < (s)) ? (n) : ((n) - (s)))

#define _DEFINE_DELAY_FUNC(NAME, WHOLE, INTERNAL_DELAY_FUNC, SUB) \
static void NAME(uint8_t divider, uint8_t dots) { \
	switch (divider) { \
	case whole: \
		INTERNAL_DELAY_FUNC(SUB_OR_ZERO(WHOLE, SUB)); \
		if (!dots--) \
			break; \
	case half: \
		INTERNAL_DELAY_FUNC(SUB_OR_ZERO(WHOLE/2, SUB)); \
		if (!dots--) \
			break; \
	case quarter: \
		INTERNAL_DELAY_FUNC(SUB_OR_ZERO(WHOLE/4, SUB)); \
		if (!dots--) \
			break; \
	case eighth: \
		INTERNAL_DELAY_FUNC(SUB_OR_ZERO(WHOLE/8, SUB)); \
		if (!dots--) \
			break; \
	case sixteenth: \
		INTERNAL_DELAY_FUNC(SUB_OR_ZERO(WHOLE/16, SUB)); \
		if (!dots--) \
			break; \
		INTERNAL_DELAY_FUNC(SUB_OR_ZERO(WHOLE/32, SUB)); \
		if (!dots--) \
			break; \
		INTERNAL_DELAY_FUNC(SUB_OR_ZERO(WHOLE/64, SUB)); \
	} \
}

#ifdef SLIPS_TEST
#include "portaudio.h"
#define DEFINE_DELAY_FUNC(NAME, WHOLE) _DEFINE_DELAY_FUNC(NAME, WHOLE, Pa_Sleep, 0)
#else
#include <util/delay.h>
/* Deduct the LED flashing time from the delay */
#define DEFINE_DELAY_FUNC(NAME, WHOLE) _DEFINE_DELAY_FUNC(NAME, WHOLE, _delay_ms, 50)
#endif

#endif
