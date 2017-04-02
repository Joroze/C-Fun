; Jordan Rosenberg - roseje57

; Symbolic Integer Constants 
; A program that defines symbolic constants for all the days of the week.

INCLUDE Irvine32.inc

.data

SUN = 0
MON = 1
TUE = 2
WED = 3
THU = 4
FRI = 5
SAT = 6

DaysArray BYTE SUN, MON, TUE, WED, THU, FRI, SAT             

.code
main PROC

mov al,DaysArray+3 ; moving 3 to al
movsx eax,al       ; moving al to eax register

call DumpRegs      ; shows 3 in eax register for some proof

	invoke ExitProcess,0    ; end the program
main endp
END main