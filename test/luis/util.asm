.once

/* Saves all register (Except ESP) in stack */
.macro saveRegs
	pshr ax
	pshr dx
	pshr cx
	pshr bx
	pshr fp
	pshr ss
	pshr sd
.endmacro

/* Restores all registers (Except ESP) from stack */
.macro restoreRegs
	popr sd
	popr ss
	popr fp
	popr bx
	popr cx
	popr dx
	popr ax
.endmacro
