/**
	HELLO WORLD in Limp Assembly
	-no initial interruption-
*/

.predef stdout_port 0x10 /* The actual stdout port */
.define regstd_p bx /* Register for storing the output stdout port */

_Main:
	nop
	/* Setting the Pheripherical (at the port 0x10) */
	movi.d regstd_p, stdout_port
	/* Setting the Stream Pointer */
	movi ss, hellostr
	/* Signaling output to send multiple characters */
	outi regstd_p, 0x21
	/* Sending the size of stream */
	outi regstd_p, (endhellostr-hellostr)
	/* Waiting for signal from device */
	.scope
		_:
			inus regstd_p
			jr.co @_
		clo
	.endscope
	/* Looping the Stream to output */
	strloop:
		ldmb ax, [ss]			; Retrieves the string byte
		jr.oez<ax> @endloop		; Jumps if is end of string
		out regstd_p, ax		; Outputs the character to peripherical
		/* Waiting for signal from device */
		.scope
			_:
				inus regstd_p
				jr.co @_
			clo
		.endscope
		inc ss					; Increments the pointer in string
		jr @strloop				; Continues the loop
	endloop:
_Exit:
	jr @_Exit

hellostr: .text "Hello World!\0"
endhellostr:
 