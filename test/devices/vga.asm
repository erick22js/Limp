/**
	VGA Displaying in Limp Assembly
	-no initial interruption-
*/

.predef disk_port 0x20 /* The actual vga port */
.define regdk bx /* Register for storing the vga */

.define vga_vec 0x80 /* Vector for pointer references for vga */
.define chr_arr 0x100 /* The current array for characters to display up */

_Main:
	nop
	/* Setting the Pheripherical (at the port 0x20) */
	movi.d regdk, disk_port
	
	/* Enabling the renderer */
	outi regdk, 0x20
	.scope
		_:
			inus regdk
			jr.co @_
		clo
	.endscope
	
	/* Setting the vector */
	movi ax, chr_arr
	strd.d [vga_vec], ax
	outi regdk, 0x28
	outi regdk, vga_vec
	.scope
		_:
			inus regdk
			jr.co @_
		clo
	.endscope
	
	/* Writing hello world to vga memory space */
	movi ss, hellostr
	movi sd, chr_arr
	movi.d bx, 0x00FF0000
	loop:
		ldmb dx, [ss]
		jr.oez<dx> @endloop
		or dx, bx
		strd [sd], dx
		inc ss
		add sd, 4
		jr @loop
	endloop:
	
_Exit:
	jr @_Exit

hellostr: .text "Hello World!\0"
