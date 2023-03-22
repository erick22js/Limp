jl _Main

/** Lower Division test */
_Main:
	movi eax, 16
	movi ebx, 32
	ldiv eax, ebx
	jl @


/** Test Set on condition */
/*
_Main:
	ldmd ecx, [0x80]
	ldmd ebx, [0x84]
	steq eax, 1, ecx, ebx
	stne eax, 2, ecx, ebx
	stlt eax, 3, ecx, ebx
	stgt eax, 4, ecx, ebx
	stle eax, 5, ecx, ebx
	stge eax, 6, ecx, ebx
	stab eax, 7, ecx, ebx
	stbl eax, 8, ecx, ebx
	stae eax, 9, ecx, ebx
	stbe eax, 0xA, ecx, ebx
	jl @
*/


/** Test the Data moviments */
/*
_Main:
	loopsetup:
		movi ess, hellostr
		movi esd, 0x90
		loop:
			ldmb eax, [ess]
			strb [esd], eax
			inc ess
			inc esd
			jr.onz<eax> @loop
	exit: jr @exit
	hellostr: .text "Hello World!\0"
	.align
*/


/** Test the stack operations */
/*
_Main:
	movi.d esp, 0xc0 // Setup the stack top
	pshi 0x150
	pshi.d 0x90004FF
	movi.d eax, 0x80
	pshr eax
	popr edx
	popr ecx
	popr ebx
*/

