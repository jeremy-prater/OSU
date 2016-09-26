TITLE Elementary Arithemic     (Project01.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 01                Date: 9/21/2016
; Description:  This program will introduce the programmer, and project name,
;               get input from user, calculate output values, print results,
;               display exit message.
;
; Write and test a MASM program to perform the following tasks:
; 1. Display your name and program title on the output screen.
; 2. Display instructions for the user.
; 3. Prompt the user to enter two numbers.
; 4. Calculate the sum, difference, product, (integer) quotient and remainder of the numbers.
; 5. Display a terminating message. 

INCLUDE Irvine32.inc

.data
messageTitle       BYTE  "                     Elementary Arithmetc            by       Jeremy Prater" ,0
messageInstruction BYTE  "Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder." ,0
messageFirstNum    BYTE  "Enter First Number: " ,0
messageSecondNum   BYTE  "Enter Second Number: " ,0
messageDivideByZ   BYTE  " -- DIVIDE BY ZERO --" ,0
messageExit        BYTE  "x86 Assembly is pretty cool, eh? Bye!" ,0

mathAdd            BYTE  " + "
mathSub            BYTE  " - "
mathMul            BYTE  " * "
mathDiv            BYTE  " / "
mathEqual          BYTE  " = "
mathRemainder      BYTE  " remainder "

inputFirstNum      DWORD ?       ; first integer entered by user
inputSecondNum     DWORD ?       ; second integer entered by user

storageAddResult   DWORD ?       ; Memory to store the add result
storageSubResult   DWORD ?       ; Memory to store the sub result
storageMulResult   DWORD ?       ; Memory to store the mul result
storageDivResult   DWORD ?       ; Memory to store the div result

.code
main PROC

;Main procedure requirements
; introduction
	mov		edx, OFFSET messageTitle
	call	WriteString
	call	CrLf
	call	CrLf

; get the data
	mov		edx, OFFSET messageInstruction
	call	WriteString
	call	CrLf

	mov		edx, OFFSET messageFirstNum
	call	WriteString

	call	ReadInt
	mov		inputFirstNum, eax

	mov		edx, OFFSET messageSecondNum
	call	WriteString

	call	ReadInt
	mov		inputSecondNum, eax


; calculate the required values
	mov		eax, inputFirstNum
	add     eax, inputSecondNum
	mov     storageAddResult, eax

	mov		eax, inputFirstNum
	sub     eax, inputSecondNum
	mov     storageSubResult, eax

	mov		eax, inputFirstNum
	mul     inputSecondNum
	mov     storageMulResult, eax

	mov		eax, inputFirstNum
	div     inputSecondNum
	mov     storageDivResult, eax
	
; display the results
	;call    WriteDec
	;call	WriteString
	;call	CrLf
	
; say goodbye 
	mov		edx, OFFSET messageExit
	call	WriteString
	call	CrLf
	call	CrLf

	exit	; exit to operating system
main ENDP

END main


