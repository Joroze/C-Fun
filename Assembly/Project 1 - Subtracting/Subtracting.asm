; Jordan Rosenberg - roseje57

; Subtracting Three Integers
; A program that subtracts three integers using only 16 bit registers. 

INCLUDE Irvine32.inc

.data
val1 WORD 10
val2 WORD 5
val3 WORD 2
lastVal WORD ?                 

.code
main PROC

	mov ax,val1      ; val1 to ax
	sub	ax,val2      ; ax - val2   		
	sub	ax,val3      ; ax - val3          		
	mov lastVal,ax   ; ax to lastVal
	          
	call DumpRegs    ; dumps registers for proof

	invoke ExitProcess,0    ; end the program
main endp
END main