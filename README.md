Background
==========
I bought a cheap christmas tie, but I thought that it was a shame that it only
played the same medley of traditional North American christmas songs. So when
it ran out of batteries, I did a a quick design to replace it with a ATTiny85
and a CR2032, using the same LED and speaker.

Design notes
============
The simplest way of designing this was to have a pushbutton (open by default)
that pulls down the !RES pin of the ATTiny, effectively restarting it. Upon
boot, it will read its ADC1 pin, which is floating, to get a random number.
This will be used to seed the minimalistic pseudo-random number generator,
which will be used to select a song. After the song is played using the PWM
hardware (square waves) on the speaker, the ATTiny will enter a sleep state
where almost all internal functions are shut down.

Hardware
========
I built this using an ATTiny85, a battery (CR2032), a pushbutton for reset, a
small speaker, a LED and a resistor for the LED. A simple sketch of the wiring
from the ATTiny view is available in `src/main.c`.
