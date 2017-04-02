; Jordan Rosenberg - roseje57

; Data Definitions
; A program that contains a definition of each data type [listed in table 3-2 (P. 78 edition 6, P. 74 edition 7)]

INCLUDE Irvine32.inc

.data
                                      ; Each digit in a hexadecimal represents 2 bits

myByte BYTE 24h                       ; 8-bit unsigned integer
mySByte SBYTE -24h                    ; 8-bit signed integer
myWord WORD 1234h                     ; 16-bit unsigned integer
mySWord SWORD -1234h                  ; 16-bit signed integer
myDWord DWORD 12345678h               ; 32-bit unsigned integer
mySDWord SDWORD -12345678h            ; 32-bit signed integer
myFWord FWORD 12345678912Ah           ; 48-bit integer
myQWord QWORD 1234567891234567h       ; 64-bit integer. Q stands for quad
myTByte TBYTE 1211354215123456789Ah   ; 80-bit (10 byte) integer. T stands for Ten-byte
myReal4 REAL4 -1.2                    ; 32-bit (4 byte) IEEE short real
myReal8 REAL8 1.2E-260                ; 64-bit (8 byte) IEEE long real
myReal10 REAL10 1.0E+4096             ; 80-bit (10 byte) IEEE extended real

.code

main PROC


	invoke ExitProcess,0    ; end the program
main endp
END main