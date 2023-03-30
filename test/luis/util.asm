.once

/* Saves all register (Except ESP) in stack */
.macro saveRegs
	pshp eax, efp
	pshp ess, esd
.endmacro

/* Restores all registers (Except ESP) from stack */
.macro restoreRegs
	popp ess, esd
	popp eax, efp
.endmacro
