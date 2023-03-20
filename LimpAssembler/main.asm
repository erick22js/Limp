/*
movi ebx, second

label:
add eax, [ebx-4]

second:
add edx, [ebx-4]
add ecx, [ebx-4]
jl label
*/

.include "other.asm"

movi eax, teste2

