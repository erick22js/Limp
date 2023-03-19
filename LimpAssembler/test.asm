/*
movi ebx, second

label:
add eax, [ebx-4]

second:
add edx, [ebx-4]
add ecx, [ebx-4]
jl label
*/

movi eax, 10
inicio:
dec.d eax

jr.onz<eax> @inicio