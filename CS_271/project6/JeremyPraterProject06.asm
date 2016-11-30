INCLUDE Irvine32.inc

.data

.code

rcrsn PROC
   push ebp
   mov ebp,esp
   mov eax,[ebp + 12]
   mov ebx,[ebp + 8]
   cmp eax,ebx
   jl recurse
   jmp quit
recurse:
   inc eax
   push eax
   push ebx
   call rcrsn
   mov eax,[ebp + 12]
   call WriteDec
   ;Space 2
   call CrLf
quit:
   pop ebp
   ret 8
rcrsn ENDP

main PROC
   push 4
   push 10
   call rcrsn
   exit
main ENDP

END main