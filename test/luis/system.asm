.once

.include "util.asm"
.include "sysutil.asm"

/**
	Setup the ports
*/

// Memory mapping data
// Descriptor tables
.predef intr_table 0x1000
.predef ports_d 0x1400
// Main ports handdlers
.predef mport_stdout 0x1801
.predef mport_disk 0x1802

.scope setupPorts
	// Setup all the interruption vector
	movi ax, setupExtIntr
	movi ss, 0x80
	loop_set_vectors:
		dec ss
		// Calculating the address
		movi bx, intr_table
		mov cx, ss
		add cx, 0x80
		mul cx, 4
		add bx, cx
		// Storing the program offset for interruption
		strd [bx], ax
		jr.onz<ss> @loop_set_vectors
	// Attribute the interrupt table address
	movi dx, intr_table
	mvtit dx
	// Enable and expects for interruptions
	enbi
	// Executes a loop waiting for ports to connect
	movi cx, 0x1000
	loop_waiti:
		dec cx
		jr.onz<cx> @loop_waiti
	ret
.endscope

.scope setupExtIntr
	.macro getPort reg:Reg
		mvfst reg
		rshf reg, 24
		sub reg, 0x80
	.endmacro
	saveRegs
	// Getting info of actual port
	getPort ax
	// Register in ports vector
	.scope
		outi ax, 0x10
		waitPort ax
		in dx, ax
		mov bx, ax
		mul bx, 4
		add.d bx, ports_d
		strd.d [bx], dx
	.endscope
	// Setup the main ports
	.scope
		movi cx, 0
		// Comparate is a stdout device
		movi ss, mport_stdout
		cmp dx, 1
		mv.eq cx, ss
		// Comparate is a disk device
		movi ss, mport_disk
		cmp dx, 2
		mv.eq cx, ss
		// Stores the main port
		jr.oez<cx> @not_mport
			strb [cx], ax
		not_mport:
	.endscope
	restoreRegs
	iret
.endscope

