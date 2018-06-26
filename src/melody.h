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

#define _DEFINE_DELAY_FUNC(NAME, WHOLE, INTERNAL_DELAY_FUNC) \
static void NAME(uint8_t divider, uint8_t dots) { \
	switch (divider) { \
	case whole: \
		INTERNAL_DELAY_FUNC(WHOLE); \
		if (!dots--) \
			break; \
	case half: \
		INTERNAL_DELAY_FUNC(WHOLE/2); \
		if (!dots--) \
			break; \
	case quarter: \
		INTERNAL_DELAY_FUNC(WHOLE/4); \
		if (!dots--) \
			break; \
	case eighth: \
		INTERNAL_DELAY_FUNC(WHOLE/8); \
		if (!dots--) \
			break; \
	case sixteenth: \
		INTERNAL_DELAY_FUNC(WHOLE/16); \
		if (!dots--) \
			break; \
		INTERNAL_DELAY_FUNC(WHOLE/32); \
		if (!dots--) \
			break; \
		INTERNAL_DELAY_FUNC(WHOLE/64); \
	} \
}

#ifdef SLIPS_TEST
#include "portaudio.h"
#define DEFINE_DELAY_FUNC(NAME, WHOLE) _DEFINE_DELAY_FUNC(NAME, WHOLE, Pa_Sleep)
#else
#include <util/delay.h>
#define DEFINE_DELAY_FUNC(NAME, WHOLE) _DEFINE_DELAY_FUNC(NAME, WHOLE, _delay_ms)
#endif
