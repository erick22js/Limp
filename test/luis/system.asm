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
	movi eax, setupExtIntr
	movi ess, 0x80
	loop_set_vectors:
		dec ess
		// Calculating the address
		movi ebx, intr_table
		mov ecx, ess
		add ecx, 0x80
		mul ecx, 4
		add ebx, ecx
		// Storing the program offset for interruption
		strd [ebx], eax
		jr.onz<ess> @loop_set_vectors
	// Attribute the interrupt table address
	movi edx, intr_table
	mvtit edx
	// Enable and expects for interruptions
	enbi
	// Executes a loop waiting for ports to connect
	movi ecx, 0x1000
	loop_waiti:
		dec ecx
		jr.onz<ecx> @loop_waiti
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
	getPort eax
	// Register in ports vector
	.scope
		outi eax, 0x10
		waitPort eax
		in edx, eax
		mov ebx, eax
		mul ebx, 4
		add.d ebx, ports_d
		strd.d [ebx], edx
	.endscope
	// Setup the main ports
	.scope
		movi ecx, 0
		// Comparate is a stdout device
		movi ess, mport_stdout
		cmp edx, 1
		mv.eq ecx, ess
		// Comparate is a disk device
		movi ess, mport_disk
		cmp edx, 2
		mv.eq ecx, ess
		// Stores the main port
		jr.oez<ecx> @not_mport
			strb [ecx], eax
		not_mport:
	.endscope
	restoreRegs
	iret
.endscope

