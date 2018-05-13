#!/usr/bin/env python3

import argparse
import math

parser = argparse.ArgumentParser()
parser.add_argument("--test", action='store_const', default=False, const=True,
                    help="Generate values for test.c")
args = parser.parse_args()

note_names = [
    'C',
    'CS',
    'D',
    'DS',
    'E',
    'F',
    'FS',
    'G',
    'GS',
    'A',
    'AS',
    'B',
]

F_CPU = 1000000

notes = []
if args.test:
    print("static octave_t octaves[8] = {")
else:
    print("PROGMEM const struct avr_octave octaves[8] = {")
for octave in range(0, 8):
    print("\t{{ /* Octave {} */".format(octave))
    for note in range(0,12):
        # Use C0 as base, 16.35Hz
        freq = 2**(note/12+octave)*16.352
        if args.test:
            print("\t\t.note_{} = {{.freq = {}}},".format(note_names[note],
                                                          round(freq, 2)))
        else:
            f_tck = F_CPU
            divisor = 1
            while True:
                ocr = f_tck / freq - 1
                if ocr < 128:
                    break
                divisor <<= 1
                # One full period == 0 -> OCR1A -> OCR1C. We use ocr for OCR1A and
                # 2*ocr for OCR1C, so count the divisor double.
                f_tck = F_CPU / (divisor*2)
            print("\t\t.note_{} = {{{}, N_{}}}, /* {}Hz */".format(note_names[note],
                                                                   round(ocr),
                                                                   divisor,
                                                                   round(freq, 2)))
    print("\t},")
print("};")

#            notes.append("0x{:02x}".format(round(skip)))
#    print(", ".join(notes))
#
#if args.sine:
#    values = []
#    for x in range(0, 4000):
#        print(math.sin(x/4000.0*2*math.pi)*128+128)
#        values.append("0x{:02X}".format(round(math.sin(x/4000.0*2*math.pi)*128.0+127)))
#    print(", ".join(values))
#
