/**
	KEY Input intersection in Limp Assembly
	-no initial interruption-
*/

.predef disk_port 0x18 /* The actual keyboard port */
.define regdk bx /* Register for storing the keyboard */

/* Setting up the stack */
movi sp, 0x80

/* Setting up the interruption vector */
movi.d bx, (0x0 + 0x80 + disk_port)*4
movi.d dx, intrr
strd.d [bx], dx

/* Enabling interruptions */
enbi

_Exit:
	inc ss
	jr @_Exit

/* The interruption by itself */
.scope intrr
	inc ax
	iret
.endscope
