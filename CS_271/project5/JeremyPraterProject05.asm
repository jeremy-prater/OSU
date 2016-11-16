TITLE Random Number Generator Sorter (Project05.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 05                Date: 11/15/2016
; Description:  Write a program to ask the user for the number of random numbers to generate
;               Display the list of generated random numbers
;               Sort the list of generated random numbers
;               Display the median value
;               Display the sorted list
;

INCLUDE Irvine32.inc

.data
messageTitle        BYTE  "       Random Number Generator Sorter         by       Jeremy Prater", 0
messageEC1          BYTE  "** EC1: Align output columns." ,0
messageEC2          BYTE  "** EC2: Display more composites, but show them one page at a time.", 0

messageIntro1       BYTE  "This program generates random numbers in the range [100 .. 999],", 0
messageIntro2       BYTE  "displays the original list, sorts the list, and calculates the", 0
messageIntro3       BYTE  "median value. Finally, it displays the list sorted in descending order.", 0

messageUserGetCount BYTE  "How many numbers should be generated? [10 .. 200]: ", 0
messageUserInvalid  BYTE  "Invalid input : ", 0
messageArrayUnsort  BYTE  "The unsorted random numbers:", 0
messageMedianVal    BYTE  "The median is ", 0
messageArraySort    BYTE  "The sorted list:", 0

constantNumGenLow   EQU   10
constantNumGenHigh  EQU   200

constantRandomMin   EQU   100
constantRandomMax   EQU   999

dataNumGen          DWORD ?
dataArray           DWORD (constantNumGenHigh) DUP (?)

.code

;--------------------------------------------------------
;
; PROCEDURE : displayIntro
;             Display the introduction
;
; PARAMETERS : None
;
;--------------------------------------------------------

displayIntro PROC
; introduction
	mov		edx, OFFSET messageTitle
	call	WriteString
	call	CrLf
	call	CrLf

; Display extra credit information
	mov		edx, OFFSET messageEC1
	call	WriteString
	call	CrLf
	mov	edx, OFFSET messageEC2
	call	WriteString
	call	CrLf
	call	CrLf
	ret
displayIntro ENDP

;--------------------------------------------------------
;
; PROCEDURE : displayInstructions
;             Display the instructions for the application
;
; PARAMETERS : None
;
;--------------------------------------------------------

displayInstructions PROC
	; Display instructions

    mov     edx, OFFSET messageIntro1
	call    WriteString
	call    CrLf

    mov     edx, OFFSET messageIntro2
	call    WriteString
	call    CrLf

    mov     edx, OFFSET messageIntro3
	call    WriteString
	call    CrLf

	ret
displayInstructions ENDP

;--------------------------------------------------------
;
; PROCEDURE : getData
;             Get user input
;
; PARAMETERS : [EBP+8] (reference) dataNumGen - the number of items to generate
;
;--------------------------------------------------------

getData PROC
	push    esp      ; Save stack pointer
	mov     ebp, esp ; copy stack into base pointer

USERINPUT:
    mov     edx, OFFSET messageUserGetCount
	call    WriteString
	call    ReadInt                        ; Result is in EAX

	; Check input and return to start if it is out of range
	cmp     eax, constantNumGenLow
	jl      INPUTINVALID
	cmp     eax, constantNumGenHigh
	jg      INPUTINVALID

	; The input is valid, result is in eax
	jmp     INPUTVALID

INPUTINVALID:
	; The invalid number is in eax, print the error and return to the start of user input
	mov     edx, OFFSET messageUserInvalid
	call    WriteString
    call    WriteDec
	call    CrLf
	jmp     USERINPUT
	
INPUTVALID:

	mov ebx, [ebp + 8] ; Fetch the offset from the stack to store result in
	mov [ebx], eax     ; offset is in EBX, store value into the memory pointed at by ebx
	pop ebp            ; Restore base pointer
	ret 4              ; Discard parameters on the stack (1x DWORD)
getData ENDP

;--------------------------------------------------------
;
; PROCEDURE : fillArray
;             Fill the array with random numbers between [min .. max]
;
; PARAMETERS : [EBP + 12] (value)     dataNumGen - the number of items to generate
;              [EBP +  8] (reference) dataArray  - the memory address of the start of the array
;
;--------------------------------------------------------

fillArray PROC
	push    esp      ; Save stack pointer
	mov     ebp, esp ; copy stack into base pointer

	mov     ecx, [ebp +	12] ; The loop counter
	mov     edx, [ebp +  8] ; Array memory location
	mov     ebx, 0
	call    Randomize

FILLLOOP:
	mov     eax, (constantRandomMax - constantRandomMin)   ; Setup the max range of the random number as max-min (min will be added later)
	call    RandomRange                                    ; Get a random number
	add     eax, constantRandomMin                         ; Add the minimum random value to the result
	mov     [edx + ebx], eax                               ; Copy the random value into the array at position [ebx]
	add     ebx, 4                                         ; Move the the next array element (memory stride is 4 bytes - dword)
	loop    FILLLOOP

	pop     ebp            ; Restore base pointer
	ret     8              ; Discard parameters on the stack (2x DWORD)
fillArray ENDP

;--------------------------------------------------------
;
; PROCEDURE : displayList
;             Print the array of data
;
; PARAMETERS : [EBP + 16] (reference) dataArray  - the memory address of the start of the array
;              [EBP + 12] (value)     dataNumGen - the number of items to generate
;              [EBP +  8] (reference) tableTitle - the title of the table to print
;
;--------------------------------------------------------

displayList PROC
	push    esp      ; Save stack pointer
	mov     ebp, esp ; copy stack into base pointer

	call    CrLf
	mov     edx, [ebp + 8]
	call    WriteString
	call    CrLf
	call    CrLf

	mov     ecx, [ebp + 12]   ; number counter
	mov     ebx, 0            ; column counter
	mov     edx, 0            ; array index counter
LOOPPRINT:
	mov     eax, [ebp + 16]   ; Get the base of the array
	mov     eax, [eax + edx]  ; Get the next array data
	call    WriteDec
	mov     eax, 32           ; Get the character for ' '
	call    WriteChar
	call    WriteChar
	add     edx, 4            ; Go to the next array offset
	inc     ebx               ; Increase the column counter
	cmp     ebx, 10           ; Check for the end of the row
	jne     SKIPCRLF

	call    CrLf              ; New line
	mov     ebx, 0            ; Reset the column counter

SKIPCRLF:
	loop LOOPPRINT

	pop     ebp            ; Restore base pointer
	ret     12             ; Discard parameters on the stack (3x DWORD)
displayList ENDP

;--------------------------------------------------------
;
; PROCEDURE : sortList
;             Sort the array of data
;
; PARAMETERS : [EBP + 12] (value)     dataNumGen - the number of items to generate
;              [EBP +  8] (reference) dataArray  - the memory address of the start of the array
;
;--------------------------------------------------------
;for(a=0; a<request-1; a++) {
;	b = a;
;	for(c=a+1; c<request; c++) {
;		if(array[c] > array[b])
;		b = c;
;	}
;	exchange(array[a], array[b]);
;}
sortList PROC
	push    esp      ; Save stack pointer
	mov     ebp, esp ; copy stack into base pointer

	mov     eax, 0
OUTERLOOP:
	mov     ebx, eax

	mov     ecx, eax
	inc     ecx
INNERLOOP:

	inc     ecx             ; End of inner loop
	mov     edx, [ebp + 12] ; Set EDX to the number of random numbers
	mov     edx, [edx]
	cmp     ecx, edx
	jl      INNERLOOP

	inc     eax             ; End of outer loop
	mov     edx, [ebp + 12] ; Set EDX to the number of random numbers
	mov     edx, [edx]
	dec     edx             ; EDX Minus 1
	cmp     eax, edx
	jl      OUTERLOOP

	pop     ebp            ; Restore base pointer
	ret     8              ; Discard parameters on the stack (2x DWORD)
sortList ENDP

;--------------------------------------------------------
;
; PROCEDURE : swapData
;             Swap elements of the array
;
; PARAMETERS : [EBP + 12] (reference) dataArray1 - the first number to swap
;              [EBP +  8] (reference) dataArray2 - the second number to swap
;
;--------------------------------------------------------

swapData PROC
	push    esp      ; Save stack pointer
	mov     ebp, esp ; copy stack into base pointer

	push    eax ; Save all registers
	push    ebx
	push    ecx
	push    edx

	mov     ecx, [ebp +  8] ; Get the memory offsets of the two items to swap
	mov     edx, [ebp + 12]

	mov     eax, [ecx] ; Cache the two values to swap in eax/ebx
	mov     ebx, [edx]

	mov     [ecx], ebx ; Restore the cached values into the opposite memory addresses
	mov     [edx], eax

	pop     edx ; Restore all registers
	pop     ecx
	pop     ebx
	pop     eax

	pop     ebp            ; Restore base pointer
	ret     8              ; Discard parameters on the stack (2x DWORD)
swapData ENDP


;--------------------------------------------------------
;
; Program entry point
;
;--------------------------------------------------------

main PROC
	
	call displayIntro
	call displayInstructions

	; Get user data
	push OFFSET dataNumGen ; Parameter 1 - offset of memory to store result
	call getData

	; Fill Array
	push dataNumGen        ; Parameter 1 - number of random numbers to generate
	push OFFSET dataArray  ; Parameter 2 - offset of memory to store result (array)
	call fillArray

	; Display the unsorted array
	push OFFSET dataArray          ; Parameter 1 - offset of memory to store result (array)
	push dataNumGen                ; Parameter 2 - number of random numbers to print
	push OFFSET messageArrayUnsort ; Parameter 3 - title for the table
	call displayList

	; Display the unsorted array
	push OFFSET dataArray          ; Parameter 1 - offset of memory to store result (array)
	push dataNumGen                ; Parameter 2 - number of random numbers to sort
	call sortList
	
	
	; Display the unsorted array
	push OFFSET dataArray          ; Parameter 1 - offset of memory to store result (array)
	push dataNumGen                ; Parameter 2 - number of random numbers to print
	push OFFSET messageArraySort   ; Parameter 3 - title for the table
	call displayList


	exit	; exit to operating system
main ENDP

END main
