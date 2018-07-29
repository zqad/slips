#ifndef _MELODIES_H
#define _MELODIES_H

#include <stdint.h>
#include "melody.h"

extern uint8_t NUM_MELODIES;

extern const struct melody silent_night;

extern const struct melody* melodies[];

#ifdef SLIPS_TEST
extern const struct name_melody name_melodies[];
#endif

#endif
