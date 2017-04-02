; Jordan Rosenberg - roseje57

; Symbolic Text Constants
; A program that defines symbolic names for several string literals (characters between quotes). 
; Use each symbolic name in a variable definition. 

INCLUDE Irvine32.inc

string1 TEXTEQU <"Whats up my man JRyder!",0> 
string2 TEXTEQU <"Mind if I call you JDog?",0>
string3 TEXTEQU <"lasagna",0> 

.data 
prompt1 BYTE string1 
prompt2 BYTE string2
prompt3 BYTE string3                

.code
main PROC

	invoke ExitProcess,0    ; end the program
main endp
END main