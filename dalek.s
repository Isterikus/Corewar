.name "Dalek"
.comment "EXTERMINATE!!!! EXTERMINATE!!!! Where is the DOCTOR??? EXTERMINATE!!!!"

protector:
	zjmp	%:start

start:
	ld	%4285464576, r2
	sti	r2, %:protector, %1

start2:
	st	r1, 6
	live	%0
	lfork	%2000
	st	r1, 6
	live	%0
	fork	%:start3
	st	r1, 6
	live	%0
	fork	%:start2
	ld		%0, r3
	zjmp	%:start2

start3:
	st	r1, 6
	live	%0
	ld		%0, r2
	zjmp	%:start3
