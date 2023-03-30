// Program constants setup
.predef stack_size 0x100

// Setting up the stack to start program
movi esp, endprogram+stack_size
jl _Main

/* Includes the utilities and needed code */
.include "devices.asm"

/**
	A little program for writing a Hello World to disk
*/


.scope _Main
	ba setupPorts
	movi esd, 0x10
	movi ess, hellostr
	movi ecx, hellostr_end-hellostr
	bl WriteToDisk
	bl WriteToStdout
	movi esd, 0x800
	movi ess, 0x0
	movi ecx, 0x40
	bl ReadFromDisk
	jr 0
.endscope

hellostr: .text "Ola Mundo!"
hellostr_end:

.align
endprogram: