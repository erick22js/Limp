/**
	HELLO WORLD in Limp Assembly
*/

.predef stdout_port 0x10 /* The actual stdout port */
.define regstd_p ebx /* Register for storing the output stdout port */

/* A test with macro definition */
.macro super registro:reg, valor:amd
	local:
	ldmd registro, valor
.endmacro

_Main:
	nop
	super esd, [0x10]
	super esd, [0x20]
	/* Setting the Pheripherical (at the port 0x10) */
	movi.d regstd_p, stdout_port
	/* Setting the Stream Pointer */
	movi ess, hellostr
	/* Looping the Stream to output */
	strloop:
		ldmb eax, [ess]			; Retrieves the string byte
		jr.oez<eax> @endloop	; Jumps if is end of string
		out regstd_p, eax		; Outputs the character to peripherical
		chk: inup regstd_p		; Updates the odd flag to peripherical response
		jr.co @chk				; Do not advances while the peripherical do not return a response
		in eax, regstd_p		; Resets the input
		inc ess					; Increments the pointer in string
		jr @strloop				; Continues the loop
	endloop:
_Exit:
	jr @_Exit

hellostr: .text "Hello World!\0"
 