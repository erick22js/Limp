/**
	COMPILATION Tests
*/


ja Main

.macro set reg:Reg, value:Imm
	movi reg, value
	.scope
		movi reg, value
	.endscope
.endmacro

.macro set_eax value:Imm
	set eax, value
.endmacro

.macro set_ebx value:Imm
	.macro set_reg val:Imm
		movi ebx, val
	.endmacro
	.include "ext.asm"
	set_reg value
.endmacro



.scope Main
	set_eax 0x10
	set_ebx 0x80
	.scope Main1
		set_eax 0xC0
	.endscope
	.scope Main2
		set_ebx 0x98
		set_ebx 0x18
	.endscope
.endscope

.scope Main3
	.d32 Main
.endscope

