.once

/* Wait until a port sends a input value */
.macro waitPort port:Reg
	_: inus port
	jr.co @_ ; Loops until port did not send a return message
	clo ; Cleans the odd flag
.endmacro
