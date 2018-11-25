#include "melody.h"

#ifdef SLIPS_TEST
#define PROGMEM
#else
#include <avr/pgmspace.h>
#endif

DEFINE_DELAY_FUNC(delay_800, 800)
DEFINE_DELAY_FUNC(delay_1200, 1200)
DEFINE_DELAY_FUNC(delay_1800, 1800)
DEFINE_DELAY_FUNC(delay_2000, 2000)
DEFINE_DELAY_FUNC(delay_2400, 2400)
DEFINE_DELAY_FUNC(delay_3600, 3600)

/* TODO, more melodies:
 * - Goderafton
 * - Räven raskar över isen
 * - Uppå källarbacken
 * - We wish you a merry christmas (has sheet)
 */

PROGMEM const struct melody silent_night = {
	.delay_func = delay_2400,
	.notes = {
		{ .o=4, .t=G,	.d=quarter, .dots=1 },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=E,	.d=half, .dots=1 },

		{ .o=4, .t=G,	.d=quarter, .dots=1 },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=E,	.d=half, .dots=1 },

		{ .o=5, .t=D,	.d=half },
		{ .o=5, .t=D,	.d=quarter },

		{ .o=4, .t=B,	.d=half, .dots=1 },

		{ .o=5, .t=C,	.d=half },
		{ .o=5, .t=C,	.d=quarter },

		{ .o=4, .t=G,	.d=half, .dots=1 },

		{ .o=4, .t=A,	.d=half },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=5, .t=C,	.d=quarter, .dots=1 },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=4, .t=G,	.d=quarter, .dots=1 },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=E,	.d=half, .dots=1 },

		{ .o=4, .t=A,	.d=half },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=5, .t=C,	.d=quarter, .dots=1 },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=4, .t=G,	.d=quarter, .dots=1 },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=E,	.d=half, .dots=1 },

		{ .o=5, .t=D,	.d=half },
		{ .o=5, .t=D,	.d=quarter },

		{ .o=5, .t=F,	.d=quarter },
		{ .o=5, .t=D,	.d=quarter },
		{ .o=4, .t=B,	.d=quarter },

		{ .o=5, .t=C,	.d=half, .dots=1 },

		{ .o=5, .t=E,	.d=half, .dots=1 },

		{ .o=5, .t=C,	.d=quarter },
		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },

		{ .o=4, .t=G,	.d=quarter, .dots=1 },
		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=D,	.d=quarter },

		{ .o=4, .t=C,	.d=half, .dots=1 },    
		{ .o=4, .t=R,	.d=half },    

		{ .o=4, .t=End }
	},
};

PROGMEM const struct melody glans_over_sjo = {
	.delay_func = delay_2400,
	.notes = {
		{ .o=3,	.t=Bb,	.d=half },
		{ .o=4, .t=C,	.d=quarter },
		{ .o=4, .t=D,	.d=quarter },

		{ .o=4, .t=Eb,	.d=quarter, .dots=1 },
		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=G,	.d=half },

		{ .o=4, .t=G,	.d=half },
		{ .o=4, .t=Eb,	.d=quarter },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=G,	.d=half },
		{ .o=4, .t=D,	.d=half },

		{ .o=4, .t=F,	.d=half },
		{ .o=4, .t=C,	.d=quarter },
		{ .o=4, .t=C,	.d=quarter },

		{ .o=4, .t=Eb,	.d=quarter, .dots=1 },
		{ .o=4, .t=D,	.d=eighth },
		{ .o=4, .t=C,	.d=half },

		{ .o=4, .t=D,	.d=half },
		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=Gb,	.d=quarter },

		{ .o=4, .t=Gb,	.d=half },
		{ .o=4, .t=G,	.d=half },

		{ .t=End }
	},
};

PROGMEM const struct melody jinglebells = {
	.delay_func = delay_800,
	.notes = {
		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=E,	.d=half },

		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=E,	.d=half },

		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=C,	.d=quarter },
		{ .o=4, .t=D,	.d=quarter },

		{ .o=4, .t=E,	.d=whole },

		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=F,	.d=quarter },

		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },

		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=D,	.d=quarter },
		{ .o=4, .t=D,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },

		{ .o=4, .t=D,	.d=half },
		{ .o=4, .t=G,	.d=quarter, .dots=1 },

		{ .t=End }
	},
};

PROGMEM const struct melody mer_jul = {
	.delay_func = delay_1800,
	.notes = {
		{ .o=5, .t=D,	.d=half },
		{ .o=5, .t=C,	.d=half },

		{ .o=4, .t=A,	.d=eighth },
		{ .o=5, .t=C,	.d=eighth },
		{ .o=5, .t=C,	.d=quarter },
		{ .o=5, .t=C,	.d=half },

		{ .o=5, .t=Ds,	.d=half },
		{ .o=5, .t=D,	.d=half, .dots=1 },
		{ .o=5, .t=D,	.d=eighth },
		{ .o=5, .t=D,	.d=quarter, .tie=1 },
		{ .o=5, .t=D,	.d=half },

		{ .o=5, .t=D,	.d=half },
		{ .o=5, .t=C,	.d=half },

		{ .o=4, .t=A,	.d=eighth },
		{ .o=5, .t=C,	.d=eighth },
		{ .o=5, .t=C,	.d=quarter },
		{ .o=5, .t=C,	.d=eighth, .dots=1 },
		{ .t=R,		.d=sixteenth },
		{ .t=R,		.d=quarter },

		{ .o=5, .t=Ds,	.d=half },
		{ .o=5, .t=D,	.d=half, .dots=1 },

		{ .t=End }
	},
};

PROGMEM const struct melody midnatt_rader = {
	.delay_func = delay_3600,
	.notes = {
		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=C,	.d=eighth },
		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=C,	.d=eighth },

		{ .o=4, .t=F,	.d=sixteenth },
		{ .o=4, .t=E,	.d=sixteenth },
		{ .o=4, .t=F,	.d=sixteenth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=F,	.d=eighth },

		{ .o=5, .t=C,	.d=eighth },
		{ .t=R,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .t=R,	.d=eighth },

		{ .o=4, .t=A,	.d=eighth },
		{ .t=R,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .t=R,	.d=eighth },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },

		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=Fs,	.d=sixteenth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=A,	.d=sixteenth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },

		{ .o=5, .t=D,	.d=quarter },
		{ .o=5, .t=C,	.d=quarter },

		{ .o=4, .t=B,	.d=quarter },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=C,	.d=eighth },
		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=C,	.d=eighth },

		{ .o=4, .t=F,	.d=sixteenth },
		{ .o=4, .t=E,	.d=sixteenth },
		{ .o=4, .t=F,	.d=sixteenth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=F,	.d=eighth },

		{ .o=5, .t=C,	.d=eighth },
		{ .t=R,	.d=eighth },
		{ .o=5, .t=C,	.d=eighth },
		{ .t=R,	.d=eighth },

		{ .o=4, .t=F,	.d=quarter },
		{ .t=R,	.d=quarter },

		{ .t=End }
	},
};

PROGMEM const struct melody natten_gar_tunga = {
	.delay_func = delay_2400,
	.notes = {
		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=G,	.d=quarter, .dots=1 },
		{ .o=5, .t=C,	.d=eighth },

		{ .o=5, .t=C,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=B,	.d=half },

		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=F,	.d=quarter, .dots=1 },
		{ .o=4, .t=A,	.d=eighth },

		{ .o=4, .t=A,	.d=quarter },
		{ .o=4, .t=G,	.d=half },

		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=A,	.d=quarter, .dots=1 },
		{ .o=4, .t=G,	.d=eighth },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=Fs,	.d=eighth },
		{ .o=4, .t=F,	.d=half },

		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=E,	.d=quarter },
		{ .o=4, .t=D,	.d=quarter },

		{ .o=4, .t=A,	.d=quarter },
		{ .o=4, .t=G,	.d=half },

		{ .o=5, .t=E,	.d=quarter },
		{ .o=5, .t=D,	.d=quarter },
		{ .o=5, .t=C,	.d=quarter },

		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=5, .t=D,	.d=half },

		{ .o=5, .t=D,	.d=quarter },
		{ .o=5, .t=C,	.d=quarter },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=4, .t=Fs,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=5, .t=C,	.d=half },

		{ .o=5, .t=E,	.d=eighth },
		{ .o=5, .t=C,	.d=eighth },
		{ .o=5, .t=C,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=E,	.d=eighth },

		{ .o=4, .t=F,	.d=eighth },
		{ .o=5, .t=D,	.d=eighth },
		{ .o=5, .t=D,	.d=half },

		{ .o=5, .t=D,	.d=quarter },
		{ .o=4, .t=A,	.d=quarter, .dots=1 },
		{ .o=4, .t=B,	.d=eighth },

		{ .o=5, .t=D,	.d=quarter },
		{ .o=5, .t=C,	.d=half },

		{ .t=End }
	},
};

PROGMEM const struct melody staffan = {
	.delay_func = delay_2000,
	.notes = {
		{ .o=4, .t=D,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },

		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=5, .t=D,	.d=quarter },

		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth, .dots=1 },
		{ .o=4, .t=D,	.d=sixteenth },

		{ .o=4, .t=D,	.d=eighth },
		{ .o=4, .t=E,	.d=sixteenth },
		{ .o=4, .t=F,	.d=sixteenth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },

		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=5, .t=D,	.d=quarter },

		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=4, .t=A,	.d=eighth, .dots=1 },
		{ .o=4, .t=A,	.d=sixteenth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },

		{ .o=5, .t=C,	.d=eighth },
		{ .o=5, .t=C,	.d=sixteenth },
		{ .o=5, .t=C,	.d=sixteenth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },

		{ .o=4, .t=A,	.d=eighth, .dots=1 },
		{ .o=4, .t=A,	.d=sixteenth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },

		{ .o=5, .t=C,	.d=sixteenth },
		{ .o=5, .t=E,	.d=sixteenth },
		{ .o=5, .t=D,	.d=sixteenth },
		{ .o=5, .t=C,	.d=sixteenth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=5, .t=D,	.d=eighth },
		{ .o=5, .t=D,	.d=eighth },

		{ .o=5, .t=E,	.d=eighth },
		{ .o=5, .t=E,	.d=eighth },
		{ .o=5, .t=D,	.d=eighth, .dots=1 },
		{ .o=5, .t=C,	.d=sixteenth },

		{ .o=4, .t=B,	.d=eighth },
		{ .o=5, .t=C,	.d=sixteenth },
		{ .o=4, .t=B,	.d=sixteenth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },

		{ .o=4, .t=G,	.d=quarter },

		{ .t=End }
	},
};

PROGMEM const struct melody rudolf = {
	.delay_func = delay_1800,
	.notes = {
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth, .dots=1 },
		{ .t=R,		.d=sixteenth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=E,	.d=quarter },
		{ .o=5, .t=C,	.d=quarter },

		{ .o=4, .t=A,	.d=quarter },
		{ .o=4, .t=G,	.d=quarter },
		{ .t=R,		.d=half },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },
		{ .o=5, .t=C,	.d=quarter },

		{ .o=4, .t=B,	.d=half },
		{ .t=R,		.d=half },

		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth, .dots=1 },
		{ .t=R,		.d=sixteenth },
		{ .o=4, .t=F,	.d=eighth },
		{ .o=4, .t=D,	.d=quarter },
		{ .o=4, .t=B,	.d=quarter },

		{ .o=4, .t=A,	.d=quarter },
		{ .o=4, .t=G,	.d=half },
		{ .t=R,		.d=quarter },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=4, .t=E,	.d=quarter, .dots=1 },

		{ .t=End }
	},
};

PROGMEM const struct melody nej_se = {
	.delay_func = delay_1800,
	.notes = {
		{ .o=4, .t=C,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth, .dots=1 },
		{ .o=4, .t=G,	.d=sixteenth },

		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=F,	.d=eighth },
		{ .t=R,		.d=sixteenth },
		{ .o=4, .t=C,	.d=sixteenth },
		{ .o=4, .t=A,	.d=eighth, .dots=1 },
		{ .o=4, .t=G,	.d=sixteenth },

		{ .o=4, .t=F,	.d=quarter },
		{ .o=4, .t=F,	.d=eighth, .dots=1 },
		{ .o=4, .t=F,	.d=sixteenth },
		{ .o=4, .t=E,	.d=eighth, .dots=1 },
		{ .o=4, .t=F,	.d=sixteenth },

		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=G,	.d=quarter },

		{ .o=4, .t=G,	.d=quarter },
		{ .t=R,		.d=eighth, .dots=1 },
		{ .o=4, .t=C,	.d=sixteenth },
		{ .o=4, .t=Bb,	.d=eighth, .dots=1 },
		{ .o=4, .t=A,	.d=sixteenth },

		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=G,	.d=eighth },
		{ .t=R,		.d=sixteenth },
		{ .o=4, .t=C,	.d=sixteenth },
		{ .o=4, .t=Bb,	.d=eighth, .dots=1 },
		{ .o=4, .t=A,	.d=sixteenth },

		{ .o=4, .t=G,	.d=quarter },
		{ .o=4, .t=G,	.d=eighth, .dots=1 },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=F,	.d=eighth, .dots=1 },
		{ .o=4, .t=G,	.d=sixteenth },

		{ .o=4, .t=A,	.d=quarter },
		{ .o=4, .t=A,	.d=quarter },
		{ .o=4, .t=A,	.d=quarter },

		{ .o=4, .t=A,	.d=quarter },

		{ .t=End }
	},
};

PROGMEM const struct melody jul_igen = {
	.delay_func = delay_1800,
	.notes = {
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },
		{ .o=3, .t=B,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },
		{ .o=3, .t=B,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=Fs,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=5, .t=C,	.d=eighth },

		{ .o=5, .t=D,	.d=quarter },
		{ .o=5, .t=D,	.d=quarter },
		{ .t=R,		.d=quarter },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },
		{ .o=3, .t=B,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=sixteenth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },
		{ .o=3, .t=B,	.d=eighth },
		{ .o=4, .t=D,	.d=eighth },

		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=Fs,	.d=eighth },
		{ .o=4, .t=G,	.d=eighth },
		{ .o=4, .t=A,	.d=eighth },
		{ .o=4, .t=B,	.d=eighth },
		{ .o=5, .t=C,	.d=eighth },

		{ .o=5, .t=D,	.d=quarter },
		{ .o=5, .t=D,	.d=quarter },

		{ .t=End }
	},
};

#define MELODIES \
	MEL(silent_night) \
	MEL(glans_over_sjo) \
	MEL(jinglebells) \
	MEL(mer_jul) \
	MEL(midnatt_rader) \
	MEL(natten_gar_tunga) \
	MEL(staffan) \
	MEL(rudolf) \
	MEL(nej_se) \
	MEL(jul_igen)

#define MEL(x) &x,
const struct melody* melodies[] = {
	MELODIES
};

#ifdef SLIPS_TEST
#undef MEL
#define MEL(x) { &x, #x },
const struct name_melody name_melodies[] = {
	MELODIES
};
#endif

const uint8_t NUM_MELODIES = sizeof(melodies)/sizeof(struct melody *);
