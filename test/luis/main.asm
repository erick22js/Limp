// Program constants setup
.predef stack_size 0x100

// Setting up the stack to start program
movi sp, endprogram+stack_size
jl _Main

/* Includes the utilities and needed code */
.include "devices.asm"

/**
	A little program for writing a Hello World to disk
*/


.scope _Main
	ba setupPorts
	movi sd, 0x10
	movi ss, hellostr
	movi cx, hellostr_end-hellostr
	bl WriteToDisk
	bl WriteToStdout
	movi sd, 0x800
	movi ss, 0x0
	movi cx, 0x40
	bl ReadFromDisk
	jr 0
.endscope

hellostr: .text "Ola Mundo!"
hellostr_end:

.align
endprogram: