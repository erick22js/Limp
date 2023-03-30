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
	ldmb.d ebx, [mport_disk]
	jr.onz<ebx> @has_disk
		restoreRegs
		ret
	has_disk:
	
	outi ebx, 0x14 ; Set the seek in disk
	waitPort ebx ; Wait the disk send a message
	
	out ebx, esd ; Sending the position in disk
	waitPort ebx ; Wait the disk send a message
	
	outi ebx, 0x1C ; Asking to disk for a writing from memory
	waitPort ebx ; Wait the disk send a message
	
	out ebx, ess ; Sending the position of stream
	waitPort ebx ; Wait the disk send a message
	
	out ebx, ecx ; Sending the size of stream
	waitPort ebx ; Waits the disk finishes
	
	waitPort ebx ; Waits the disk finishes
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
	ldmb.d ebx, [mport_disk]
	jr.onz<ebx> @has_disk
		restoreRegs
		ret
	has_disk:
	
	outi ebx, 0x14 ; Set the seek in disk
	waitPort ebx ; Wait the disk send a message
	
	out ebx, ess ; Sending the position in disk
	waitPort ebx ; Wait the disk send a message
	
	outi ebx, 0x1D ; Asking to disk for a writing from memory
	waitPort ebx ; Wait the disk send a message
	
	out ebx, esd ; Sending the position for stream
	waitPort ebx ; Wait the disk send a message
	
	out ebx, ecx ; Sending the size for stream
	waitPort ebx ; Wait the disk send a message
	
	waitPort ebx ; Waits the disk finishes
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
	ldmb.d ebx, [mport_stdout]
	jr.onz<ebx> @has_stdout
		restoreRegs
		ret
	has_stdout:
	
	outi ebx, 0x24 ; Asking to stdout for a writing from memory
	waitPort ebx ; Wait the stdout send a message
	
	out ebx, ess ; Sending the position of stream
	waitPort ebx ; Wait the stdout send a message
	
	out ebx, ecx ; Sending the size of stream
	waitPort ebx ; Waits the stdout finishes
	
	waitPort ebx ; Waits the stdout finishes
	restoreRegs
	ret
.endscope


