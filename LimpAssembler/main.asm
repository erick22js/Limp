
/*
movi ebx, second

label:
add eax, [ebx-4]

second:
add edx, [ebx-4]
add ecx, [ebx-4]
jl label
*/

.once "@Main"

.include "other.asm"
.include "main.asm"

.scope
	.const teste2 32
	movi eax, 12
	.scope
		movi edx, teste
	.endscope
.endscope

;.include "main.asm"

movi ecx, teste2
mov ebx, eax
jl longe

.d8 50, 24, 12
//.align
.text "PROGRAM By Erick"

longe:
add ess, eax

