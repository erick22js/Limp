/**
	DISK Writting in Limp Assembly
	-no initial interruption-
*/

.predef disk_port 0x12 /* The actual disk port */
.define regdk bx /* Register for storing the disk */

_Main:
	nop
	/* Setting the Pheripherical (at the port 0x12) */
	movi.d regdk, disk_port
	
	/* Seeking in the disk */
	outi regdk, 0x14
	outi regdk, 1 ; Pointer (in 1KB) of stream
	/* Waiting for disk end execution */
	.scope
		_:
			inus regdk
			jr.co @_
		clo
	.endscope
	
	/* Signaling output to write to disk */
	outi regdk, 0x18
	outi regdk, 0 ; Pointer (in 1KB) of stream
	outi regdk, 33 ; Size (in 1KB) of stream
	
	/* Waiting for disk end execution */
	.scope
		_:
			inus regdk
			jr.co @_
		clo
	.endscope
_Exit:
	jr @_Exit

.text "Some Random data just to fit inside disk storage, but nothing so badly!\0"
 