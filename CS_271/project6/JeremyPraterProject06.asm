TITLE Low Level IO (Project06.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 06                Date: 11/30/2016
; Description:  
;

INCLUDE Irvine32.inc

.data
messageTitle        BYTE  "       Low-level I/O Proc and Macro      by       Jeremy Prater", 0
messageEC1          BYTE  " -- NO EC this week. Getting ready for the holidays." ,0

messageIntro1       BYTE  "Please enter 10 unsigned integers", 0
messageIntro2       BYTE  "Please enter numbers less than max uint32.", 0
messageIntro3       BYTE  "Once all numbers are entered, the sum and average will be displayed.", 0

messageUserGetCount BYTE  "Please enter a 32 bit unsigned integer : ", 0
messageUserInvalid  BYTE  "ERROR : Invalid number.", 0
messageNumberArray  BYTE  "You entered the following numbers:", 0
messageNumberSum    BYTE  "The sum of the numbers is : ", 0
messageNumberAvg    BYTE  "The avgerage of the numbers is :", 0

userString          BYTE  (32) DUP (?)
userData            DWORD (10) DUP (?)

.code

;--------------------------------------------------------
;
; MACRO : getString
;         Read a string from the user input
;
; PARAMETERS : memory address to store number
;
;--------------------------------------------------------

getString MACRO buffer
	push ecx
	push edx
	mov  edx, OFFSET buffer
	mov  ecx, (SIZEOF buffer)-1
	call ReadString
	pop  edx
	pop  ecx
ENDM

;--------------------------------------------------------
;
; MACRO : displayString
;         Write a string to the console
;
; PARAMETERS : OFFSET mem - memory address of the string to write
;              BOOL (0/1) - Print CrLf
;
;--------------------------------------------------------

displayString MACRO buffer, eol
	LOCAL NOCRLF

	push edx
	mov  edx, OFFSET buffer
	call WriteString
	push eax
	mov  eax, eol
	cmp  eax, 0
	je   NOCRLF
	call CrLf
NOCRLF:
	pop  eax
	pop  edx
ENDM

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
	displayString  messageTitle, 1
	call	CrLf

; Display extra credit information
	displayString messageEC1, 1
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
    displayString messageIntro1, 1
    displayString messageIntro2, 1
    displayString messageIntro3, 1
	ret
displayInstructions ENDP

;--------------------------------------------------------
;
; PROCEDURE : ReadVal
;             Read unsigned integer from input into register
;
; -- Uses getString Macro to get input string
; PARAMETERS : Memory address to store converted string integer
;
;--------------------------------------------------------

ReadVal PROC
START:
	displayString messageUserGetCount ,0
	getString     userString
	; EAX contains string length

	cmp    EAX, 11
	jg     INPUTFAIL

INPUTFAIL:
	displayString messageUserInvalid, 1
	jmp    START

INPUTPASS:
ReadVal ENDP

;--------------------------------------------------------
;
; PROCEDURE : WriteVal
;             Write unsigned integer from register to output
;
; -- Uses displayString Macro to output the value
; PARAMETERS : None
;
;--------------------------------------------------------

WriteVal PROC

WriteVal ENDP

;--------------------------------------------------------
;
; Program entry point
;
;--------------------------------------------------------

main PROC
	
	call displayIntro
	call displayInstructions

	exit	; exit to operating system
main ENDP

END main
