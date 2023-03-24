/**
	HELLO WORLD in Limp Assembly
*/

_Main:
	nop
	/* Setting the Pheripherical (at the port 0x10) */
	movi ebx, 0x10
	/* Setting the Stream Pointer */
	movi ess, hellostr
	/* Looping the Stream to output */
	strloop:
		ldmb eax, [ess]			; Retrieves the string byte
		ja.oez<eax> endloop		; Jumps if is end of string
		out ebx, eax			; Outputs the character to peripherical
		chk: inup ebx			; Updates the odd flag to peripherical response
		jr.co @chk				; Do not advances while the peripherical do not return a response
		in eax, ebx				; Resets the input
		inc ess					; Increments the pointer in string
		jl strloop				; Continues the loop
	endloop:
_Exit:
	jl _Exit

hellostr: .text "Hello World!\0"