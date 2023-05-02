/****************************************

	LIMP BIOS PROGRAM
	
	by: Erick S. Oliveira

*****************************************/

/****************************************

	MEMORY SCHEME

	0x0000..0x1FFF => Code
	0x2000..0x20FF => Stack
	0x2100 => Main stdout Device
	0x2104 => Main disk Device
	0x2108 => Main key Device
	0x210C => Main display Device
	0x2400..0x2800 => Interruption Vector
	0x2800..0x3480 => Display characters

*****************************************/

/**
	CONSTANTS
*/
.define intVec 0x2400 ; The address of interruption vector
.define mdevStdout 0x2100 ; Main Stdout Device
.define mdevDisk 0x2104 ; Main Disk Device
.define mdevKey 0x2108 ; Main Key Device
.define mdevDisplay 0x210C ; Main Display Device

.define dcharsvec 0x2200 ; Vector for VGA characters showing

.define displaychars 0x2800 ; Display Characters


/**
	ENTRY EXECUTION
*/
/* Setup Stack pointer */
movi sp, 0x20FC

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
		_1:
			inus ax
			jr.co @_1
		clo
		outi.d ax, dcharsvec
		_2:
			inus ax
			jr.co @_2
		clo
	.endscope
	// Puting the Display in Video Mode
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
	// Printing a little string
	movi sd, displaychars
	movi ss, HelloStr
	cprint:
		ldmb dx, [ss]
		jr.oez<dx> @ecprint
		or.d dx, 0x003F0000
		strd.d [sd], dx
		add sd, 4
		inc ss
		jr @cprint
	ecprint:
	jr 0
.endscope

HelloStr: .text "Hello World! Display initialized\0"
