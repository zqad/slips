/** @file paex_sine.c
  @ingroup examples_src
  @brief Play a sine wave for several seconds.
  @author Ross Bencina <rossb@audiomulch.com>
  @author Phil Burk <philburk@softsynth.com>
  */
/*
 * $Id$
 *
 * This program uses the PortAudio Portable Audio Library.
 * For more information see: http://www.portaudio.com/
 * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * The text above constitutes the entire PortAudio license; however,
 * the PortAudio community also makes the following non-binding requests:
 *
 * Any person wishing to distribute modifications to the Software is
 * requested to send the modifications to the original developer so that
 * they can be incorporated into the canonical version. It is also
 * requested that these non-binding requests be included along with the
 * license above.
 */
#include "melodies.h"
#include "melody.h"
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include "portaudio.h"
#define NUM_SECONDS   (5)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)
#ifndef M_PI
#define M_PI  (3.14159265)
#endif
typedef struct
{
	float *sine;
	float freq;
	int table_size;
	int phase;
	char message[20];
}
paTestData;

typedef struct {
	paTestData data[12];
} _octave_t;
typedef paTestData note_t;
typedef struct s_octave {
	union {
		struct {
			note_t note_C;
			note_t note_Cs;
			note_t note_D;
			union {
				note_t note_Ds;
				note_t note_Eb;
			};
			note_t note_E;
			note_t note_F;
			union {
				note_t note_Fs;
				note_t note_Gb;
			};
			note_t note_G;
			note_t note_Gs;
			note_t note_A;
			union {
				note_t note_As;
				note_t note_Bb;
			};
			note_t note_B;
		};
		note_t notes[12];
	};
} octave_t;

static octave_t octaves[8] = {
	{ /* Octave 0 */
		.note_C = {.freq = 16.35},
		.note_Cs = {.freq = 17.32},
		.note_D = {.freq = 18.35},
		.note_Ds = {.freq = 19.45},
		.note_E = {.freq = 20.6},
		.note_F = {.freq = 21.83},
		.note_Fs = {.freq = 23.13},
		.note_G = {.freq = 24.5},
		.note_Gs = {.freq = 25.96},
		.note_A = {.freq = 27.5},
		.note_As = {.freq = 29.14},
		.note_B = {.freq = 30.87},
	},
	{ /* Octave 1 */
		.note_C = {.freq = 32.7},
		.note_Cs = {.freq = 34.65},
		.note_D = {.freq = 36.71},
		.note_Ds = {.freq = 38.89},
		.note_E = {.freq = 41.2},
		.note_F = {.freq = 43.65},
		.note_Fs = {.freq = 46.25},
		.note_G = {.freq = 49.0},
		.note_Gs = {.freq = 51.91},
		.note_A = {.freq = 55.0},
		.note_As = {.freq = 58.27},
		.note_B = {.freq = 61.74},
	},
	{ /* Octave 2 */
		.note_C = {.freq = 65.41},
		.note_Cs = {.freq = 69.3},
		.note_D = {.freq = 73.42},
		.note_Ds = {.freq = 77.78},
		.note_E = {.freq = 82.41},
		.note_F = {.freq = 87.31},
		.note_Fs = {.freq = 92.5},
		.note_G = {.freq = 98.0},
		.note_Gs = {.freq = 103.83},
		.note_A = {.freq = 110.0},
		.note_As = {.freq = 116.54},
		.note_B = {.freq = 123.47},
	},
	{ /* Octave 3 */
		.note_C = {.freq = 130.82},
		.note_Cs = {.freq = 138.59},
		.note_D = {.freq = 146.84},
		.note_Ds = {.freq = 155.57},
		.note_E = {.freq = 164.82},
		.note_F = {.freq = 174.62},
		.note_Fs = {.freq = 185.0},
		.note_G = {.freq = 196.0},
		.note_Gs = {.freq = 207.66},
		.note_A = {.freq = 220.01},
		.note_As = {.freq = 233.09},
		.note_B = {.freq = 246.95},
	},
	{ /* Octave 4 */
		.note_C = {.freq = 261.63},
		.note_Cs = {.freq = 277.19},
		.note_D = {.freq = 293.67},
		.note_Ds = {.freq = 311.13},
		.note_E = {.freq = 329.64},
		.note_F = {.freq = 349.24},
		.note_Fs = {.freq = 370.0},
		.note_G = {.freq = 392.01},
		.note_Gs = {.freq = 415.31},
		.note_A = {.freq = 440.01},
		.note_As = {.freq = 466.18},
		.note_B = {.freq = 493.9},
	},
	{ /* Octave 5 */
		.note_C = {.freq = 523.26},
		.note_Cs = {.freq = 554.38},
		.note_D = {.freq = 587.34},
		.note_Ds = {.freq = 622.27},
		.note_E = {.freq = 659.27},
		.note_F = {.freq = 698.47},
		.note_Fs = {.freq = 740.01},
		.note_G = {.freq = 784.01},
		.note_Gs = {.freq = 830.63},
		.note_A = {.freq = 880.02},
		.note_As = {.freq = 932.35},
		.note_B = {.freq = 987.79},
	},
	{ /* Octave 6 */
		.note_C = {.freq = 1046.53},
		.note_Cs = {.freq = 1108.76},
		.note_D = {.freq = 1174.69},
		.note_Ds = {.freq = 1244.54},
		.note_E = {.freq = 1318.54},
		.note_F = {.freq = 1396.95},
		.note_Fs = {.freq = 1480.01},
		.note_G = {.freq = 1568.02},
		.note_Gs = {.freq = 1661.26},
		.note_A = {.freq = 1760.04},
		.note_As = {.freq = 1864.7},
		.note_B = {.freq = 1975.58},
	},

	{ /* Octave 7 */
		.note_C = {.freq = 2093.06},
		.note_Cs = {.freq = 2217.52},
		.note_D = {.freq = 2349.38},
		.note_Ds = {.freq = 2489.08},
		.note_E = {.freq = 2637.09},
		.note_F = {.freq = 2793.89},
		.note_Fs = {.freq = 2960.03},
		.note_G = {.freq = 3136.04},
		.note_Gs = {.freq = 3322.52},
		.note_A = {.freq = 3520.09},
		.note_As = {.freq = 3729.4},
		.note_B = {.freq = 3951.16},
	}, 	
};
/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */

static paTestData *current_data = NULL;
static int patestCallback( const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData )
{
	paTestData *data = current_data;
	float *out = (float*)outputBuffer;
	unsigned long i;
	(void) timeInfo; /* Prevent unused variable warnings. */
	(void) statusFlags;
	(void) inputBuffer;
	for( i=0; i<framesPerBuffer; i++ )
	{
		if (data == NULL) {
			*out++ = 0.0;
			*out++ = 0.0;
		}
		else {
			*out++ = data->sine[data->phase];  /* left */
			*out++ = data->sine[data->phase];  /* right */
			data->phase += 1;
			if( data->phase >= data->table_size ) data->phase = 0;
		}
	}
	return paContinue;
}
/*
 * This routine is called by portaudio when playback is done.
 */
static void StreamFinished( void* userData )
{
	printf( "Stream Completed\n");
}
/*******************************************************************/

#define play(data, duration) do { \
	_play(data, duration); \
} while (0)
void _play(paTestData *data, long duration) {
	PaStream *stream;

}

void play_melody(const struct melody *melody) {
	void (*delay_func)(uint8_t, uint8_t) = melody->delay_func;
	for (int i = 0; 1; i++) {
		struct note note = melody->notes[i];
		if (note.t == End)
			break;

		if (note.t == R)
			goto rest;

		paTestData *data = &octaves[note.o].notes[note.t];
		data->phase = 0;
		current_data = data;
rest:
		delay_func(note.d, note.dots);
		if (!note.tie)
			current_data = NULL;
		Pa_Sleep( 10 );
	}
}

int main(int argc, char *argv[])
{
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
	paTestData *data;
	/* initialise sinusoidal wavetable */
	for (int octave = 0; octave < 8; octave++) {
		for (int note = 0; note < 12; note++) {
			data = &((_octave_t *)&octaves[octave])->data[note];
			int wavelength = SAMPLE_RATE / data->freq;
			data->sine = calloc(wavelength, sizeof(float));
			data->table_size = wavelength;
			if (data->sine == NULL) {
				perror("calloc");
				goto error;
			}
			for( int i=0; i < wavelength; i++ ) {
				double pos = (double)i/(double)wavelength;
				data->sine[i] = (float)sin(pos * 2. * M_PI);
			}
			data->phase = 0;
		}
	}
	err = Pa_Initialize();
	if( err != paNoError ) goto error;
	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (outputParameters.device == paNoDevice) {
		fprintf(stderr,"Error: No default output device.\n");
		goto error;
	}
	outputParameters.channelCount = 2;       /* stereo output */
	outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(
			&stream,
			NULL, /* no input */
			&outputParameters,
			SAMPLE_RATE,
			FRAMES_PER_BUFFER,
			paClipOff,      /* we won't output out of range samples so don't bother clipping them */
			patestCallback,
			data );
	if( err != paNoError ) goto error;
	sprintf( data->message, "No Message" );
	err = Pa_SetStreamFinishedCallback( stream, &StreamFinished );
	if( err != paNoError ) goto error;
	err = Pa_StartStream( stream );
	if( err != paNoError ) goto error;

	if (argc == 1) {
		for (int i = 0; i < NUM_MELODIES; i++) {
			printf("Playing melody %ld, %s\n", i,
					name_melodies[i].name);
			play_melody(melodies[i]);
			Pa_Sleep(1000);
		}
	}
	else {
		char *endptr;
		errno = 0;
		int error = 0;
		long number = strtol(argv[1], &endptr, 10);
		if ((errno != 0 && number == 0) || *endptr != 0) {
			fprintf(stderr, "Invalid number given on command line.\n");
			error = 1;
		}
		else if (number < 0 || number >= NUM_MELODIES) {
			fprintf(stderr, "Number not corresponding to a known melody.\n");
			error = 1;
		}
		if (error) {
			printf("Known melodies:\n");
			for (int i = 0; i < NUM_MELODIES; i++) {
				printf("%3d. %s\n", i, name_melodies[i].name);
			}
		}
		else {
			printf("Playing melody %ld, %s\n", number,
					name_melodies[number].name);
			play_melody(melodies[number]);
		}
	}

	err = Pa_StopStream( stream );
	if( err != paNoError ) goto error;
	err = Pa_CloseStream( stream );
	if( err != paNoError ) goto error;
	Pa_Terminate();
	printf("Test finished.\n");
	return err;
error:
	Pa_Terminate();
	fprintf( stderr, "An error occured while using the portaudio stream\n" );
	fprintf( stderr, "Error number: %d\n", err );
	fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
	return err;
}
