.once

.include "system.asm"

/*
	Write to disk
	args:
		esd => dest
		ess => src
		ecx => size
*/
.scope WriteToDisk
	saveRegs
	// First, check if any disk is available
	ldmb.d bx, [mport_disk]
	jr.onz<bx> @has_disk
		restoreRegs
		ret
	has_disk:
	
	outi bx, 0x14 ; Set the seek in disk
	waitPort bx ; Wait the disk send a message
	
	out bx, sd ; Sending the position in disk
	waitPort bx ; Wait the disk send a message
	
	outi bx, 0x1C ; Asking to disk for a writing from memory
	waitPort bx ; Wait the disk send a message
	
	out bx, ss ; Sending the position of stream
	waitPort bx ; Wait the disk send a message
	
	out bx, cx ; Sending the size of stream
	waitPort bx ; Waits the disk finishes
	
	waitPort bx ; Waits the disk finishes
	restoreRegs
	ret
.endscope

/*
	Read from disk
	args:
		esd => dest
		ess => src
		ecx => size
*/
.scope ReadFromDisk
	saveRegs
	// First, check if any disk is available
	ldmb.d bx, [mport_disk]
	jr.onz<bx> @has_disk
		restoreRegs
		ret
	has_disk:
	
	outi bx, 0x14 ; Set the seek in disk
	waitPort bx ; Wait the disk send a message
	
	out bx, ss ; Sending the position in disk
	waitPort bx ; Wait the disk send a message
	
	outi bx, 0x1D ; Asking to disk for a writing from memory
	waitPort bx ; Wait the disk send a message
	
	out bx, sd ; Sending the position for stream
	waitPort bx ; Wait the disk send a message
	
	out bx, cx ; Sending the size for stream
	waitPort bx ; Wait the disk send a message
	
	waitPort bx ; Waits the disk finishes
	restoreRegs
	ret
.endscope


/*
	Write to stdout
	args:
		ess => src
		ecx => size
*/
.scope WriteToStdout
	saveRegs
	// First, check if stdout is available
	ldmb.d bx, [mport_stdout]
	jr.onz<bx> @has_stdout
		restoreRegs
		ret
	has_stdout:
	
	outi bx, 0x24 ; Asking to stdout for a writing from memory
	waitPort bx ; Wait the stdout send a message
	
	out bx, ss ; Sending the position of stream
	waitPort bx ; Wait the stdout send a message
	
	out bx, cx ; Sending the size of stream
	waitPort bx ; Waits the stdout finishes
	
	waitPort bx ; Waits the stdout finishes
	restoreRegs
	ret
.endscope


