; Jordan Rosenberg - roseje57 - 10/6/2015
; Homework - Programming Assignment #2
; Copy a String Backwards
; You can find the programming problem beginning on page 138 of your book. Complete the following program from section 4.10. 

INCLUDE Irvine32.inc

.data
	source BYTE "This is the source string",0
	target BYTE SIZEOF source-2 DUP('#'),0     

.code
main PROC

	mov esi,0	               ; ESI index counter which will be incrementing
	mov edi,SIZEOF source - 2  ; EDI index counter which will be decrementing from # of character bytes in string
	mov ecx,SIZEOF source      ; counts to size of string

SwapBackwards: 
	mov al,source[esi]         ; get character from source 
	mov target[edi],al         ; store it in target

	inc esi                    ; increment esi and move to next character
	dec edi	                   ; decrement edi and move to next character
	
	loop SwapBackwards	       ; repeat for the whole string

	; Display the data
	mov esi,OFFSET target
	mov ebx,1
	mov ecx,SIZEOF target
	call DumpMem               ; Dump memory to console

	mov edx,OFFSET target      ; Irvine's WriteString function to write a string to screen (backwards string in this case).
	call WriteString

	invoke ExitProcess,0       ; end the program
main endp
END main