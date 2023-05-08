/****************************************

	LIMP BIOS PROGRAM
	
	by: Erick S. Oliveira

*****************************************/

/****************************************

	MEMORY SCHEME

	0x8000..0xFFFF => Code
	
	0x7000..0x7FFC => Stack
	0x4100 => Main stdout Device
	0x4104 => Main disk Device
	0x4108 => Main key Device
	0x410C => Main display Device
	0x4400..0x4800 => Interruption Vector
	0x4800..0x5480 => Display characters

*****************************************/

.adr 0x8000

/**
	CONSTANTS
*/
.define intVec 0x4400 ; The address of interruption vector
.define mdevStdout 0x4100 ; Main Stdout Device
.define mdevDisk 0x4104 ; Main Disk Device
.define mdevKey 0x4108 ; Main Key Device
.define mdevDisplay 0x410C ; Main Display Device

.define dcharsvec 0x4200 ; Vector for VGA characters showing

.define displaychars 0x4800 ; Display Characters


/**
	ENTRY EXECUTION
*/
/* Setup Stack pointer */
movi sp, 0x7FFC

/**
	INITIALIZES THE INTERRUPTION VECTOR
*/
.scope	bInitIV
	// Sets the base to interruption vector
	movi bx, intVec
	// Moving offset to hardware interruptions
	add.d bx, 0x200
	// Loading the code address of setup to be stored
	movi ax, iSetV
	// Loading counter for 128 hardware interruptions
	movi cx, 0x80
	loopstp:
		strd [bx], ax
		add bx, 4
		dec cx
		jr.onz<cx> @loopstp ; If not ended, executes again
	// Reassigning the interruption vector
	movi dx, intVec
	mvtit dx
	// Enabling interruptions
	enbi
	// Wait for all needed devices to be setup
	.scope waitMDevs
		ldmd.d ax, [mdevStdout]
		jr.oez<ax> @waitMDevs
		ldmd.d ax, [mdevDisk]
		jr.oez<ax> @waitMDevs
		ldmd.d ax, [mdevKey]
		jr.oez<ax> @waitMDevs
		ldmd.d ax, [mdevDisplay]
		jr.oez<ax> @waitMDevs
	.endscope
	jl gfxShow
.endscope


/**
	INTERRUPTION TO SETUP THE CURRENT DEVICE
*/
.scope iSetV
	// Retrieving the interruption vector to register BX
	mvfst bx
	rshf bx, 24
	// Retrieving the port wich requested interruption to register AX
	mov ax, bx
	sub ax, 0x80
	// Retrieves the port type
	.scope
		outi ax, 0x10
		_:
			inup ax
			jr.co @_
		in dx, ax
		clo
	.endscope
	// Comparates and sets respectively for each device type required
	/* STDOUT */
	cmp dx, 1
	jr.ne @ecStdout
		strd.d [mdevStdout], ax
	ecStdout:
	/* DISK */
	cmp dx, 2
	jr.ne @ecDisk
		strd.d [mdevDisk], ax
	ecDisk:
	/* KEYBOARD */
	cmp dx, 4
	jr.ne @ecKeyboard
		// Setting the vector for interruption keyboard
		strd.d [mdevKey], ax
		mov cx, bx
		mul cx, 4
		add.d cx, intVec
		movi ss, intrKey
		strd [cx], ss
	ecKeyboard:
	/* DISPLAY */
	cmp dx, 7
	jr.ne @ecDisplay
		strd.d [mdevDisplay], ax
	ecDisplay:
	iret
.endscope

/**
	BASIC INTERRUPT FOR KEYBOARD
*/
.scope intrKey
	// Retrieving the interruption vector to register BX
	mvfst bx
	rshf bx, 24
	
	// Retrieving the port wich requested interruption to register AX
	mov ax, bx
	sub ax, 0x80
	
	// Waiting for port to send message
	_:
		inup ax
		jr.co @_
	in dx, ax
	clo
	
	// Storing status to CX
	mov cx, dx
	rshf cx, 8
	and dx, 0xFF
	and cx, 0xFF
	
	// Decoding dx offsets
	mvrse e1, dx ; e1 = line
	mov e2, e1 ; e2 = row
	rshf e1, 4
	and e2, 0xF
	
	// Calculating offset in screen
	; (line*40 + row)*4 + displaychars
	mov e3, e1
	mul e3, 40
	add e3, e2
	mul e3, 4
	add.d e3, displaychars
	mvres sd, e3 ; Moving result to standard set
	
	// Retrieving and updating data
	ldmd ax, [sd]
	and.d ax, 0xFFFF
	jr.onz<cx> @down
	up:
		or.d ax, 0xFF0000
		jr @edown
	down:
		or.d ax, 0xC3F00000
	edown:
	strd [sd], ax
	
	iret
.endscope


/**
	SIMPLY DISPLAY A HELLO WORLD IN SCREEN
*/
.scope gfxShow
	// Setup vector for renderization
	movi dx, displaychars
	strd.d [dcharsvec], dx
	// Loads the port display
	ldmd.d ax, [mdevDisplay]
	// Setup characters vector to display device
	.scope
		outi ax, 0x28
		outi.d ax, dcharsvec
		_2:
			inus ax
			jr.co @_2
		clo
	.endscope
	// Puting the Display in Terminal Mode
	.scope
		outi ax, 0x23
		_:
			inus ax
			jr.co @_
		clo
	.endscope
	// Enabling render
	.scope
		outi ax, 0x20
		_:
			inus ax
			jr.co @_
		clo
	.endscope
	// Video is Ready!
	// Printing all characters
	movi ax, 0 ; Offset
	movi e1, 0 ; Line
	LineL:
		movi e2, 0 ; Reset the x offset
		RowL:
			// Calculating offset in screen
			; (line*40 + row)*4 + displaychars
			mov e3, e1
			mul e3, 40
			add e3, e2
			mul e3, 4
			add.d e3, displaychars
			mvres sd, e3 ; Moving result to standard set
			movi.d dx, 0x003F0000
			or dx, ax
			strd.d [sd], dx ; Storing character data to display
			inc ax ; Advance character index
			inc e2 ; Advance in row
			// Proceeds only if is not end of table width
			cmp e2, 16
			jr.ne @RowL
		inc e1 ; Advance in line
		// Proceeds only if is not end of table height
		cmp e1, 16
		jr.ne @LineL
	jr 0
.endscope

HelloStr: .text "Hello World! Display initialized\0"
