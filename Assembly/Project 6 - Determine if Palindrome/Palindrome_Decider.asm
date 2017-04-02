; Jordan Rosenberg - roseje57 - 10/6/2015
; Homework - Programming Assignment #2
; Decide if a string is a palindrome or not.

INCLUDE Irvine32.inc

Str_ucase PROTO,
	pString:PTR BYTE

.data

	memoryPointer DWORD $                    ; for debugging purposes, helps locate program's data in memory

	WhiteTextOnBlue = white + (blue * 16)    ; white fg text on blue bg 
	;WhiteTextOnBlue = white + (blue SHL 4)  ; also works (shift bg left by 4 bytes)
	DefaultColor = lightGray + (black * 16)  ; default color of lightGray fg text on black bg

	promptInput BYTE "Enter a palindrome, up to 42 characters: ",0
	promptError BYTE "ERROR: Your string must contain more than 2 letters!",0
	promptRetry BYTE "Would you like to try another string? (Y/y): ",0
	promptQuitting BYTE "You have chosen to end the program. Goodbye!",0dh,0ah,0ah,0
	sayOriginalStr BYTE "Original String: ",0
	sayReversedStr BYTE "Reversed String: ",0
	promptDenied BYTE "--> This is NOT a palindrome!",0dh,0ah,0ah,0
	promptAccepted BYTE "--> This string is a palindrome! :)",0dh,0ah,0ah,0

	buffer BYTE 42 DUP('0')                       ; input buffer of up to 42 bytes
	reversedBuffer BYTE SIZEOF buffer DUP(' '),0  ; stores the reversed order of buffer string
	byteCount DWORD ?                             ; holds counter
	
	source BYTE SIZEOF buffer-1 DUP('#'),0        ; stores the squeezed input string (without spaces/punctuation)
	target BYTE SIZEOF buffer-1 DUP('@'),0        ; stores the reversed squeezed source string (without spaces/punctuation)

	wordLength DWORD ?                            ; variable to store the length of characters that the source string has
	inputChar BYTE ?                              ; stores the input of one character (when program asks user to try again)

.code
main PROC


; Set colors of console to White text and blue background colors

	mov eax,WhiteTextOnBlue
	call SetTextColor              ; Irvine's SetTextColor function to set the FG and BG colors

	mov eax,memoryPointer          ; for debugging purposes, helps developer locate the program's data in memory


; Beginnning of program where it asks the user for a string

Start:

	call Clrscr                    ; Irvine's ClrScr function to clear the screen

	mov edx,OFFSET promptInput     ; Irvine's WriteString function to write a string to screen
	call WriteString

	mov edx,OFFSET buffer	       ; point to the buffer
	mov ecx,SIZEOF buffer          ; specify max characters
	call ReadString                ; Irvine's ReadString function to store a user input string
	mov byteCount,eax              ; store number of characters (bytes) from eax to byteCount


; Checks to see if the user input an empty string, and jumps back to start if so

	cmp byteCount,0                ; if byteCount == 0 (string is empty),
	je Start                       ; restart loop to input again
	
; Core procedures to be called

	call SwapBackwardsOriginalStr  ; procedure to reverse the original input string (buffer string reversed)
    call SqueezeString             ; procedure to squeeze input string's ASCII punctuation/space out
	call SwapAndCompare            ; procedure to swap the input string backwards and then compare to original string


; Prompt and ask user to input another string or not. If yes, jump to Start label. Otherwise, say "farewell" and exit.

	mov edx,OFFSET promptRetry   
	call WriteString

	call ReadChar                  ; input char into al register
	mov inputChar,al               ; store char into inputChar

	cmp inputChar,'y'		       ; compare if inputChar == 'y' ASCII
	je Start                       ; jump to Start label to input another string
	cmp inputChar,'Y'		       ; compare if inputChar == 'Y' ASCII
	je Start                       ; jump to Start label to input another string

	call Clrscr

	mov edx,OFFSET promptQuitting  ; The farewell message
	call WriteString


; Set the console colors back to the default values

	call WaitMsg
	mov eax,DefaultColor           ; set to default FG and BG colors
	call SetTextColor
	call Clrscr

	exit
main ENDP

;-----------------------------------------------------------------------------
; Swap Original String Backwards Procedure
; This procedure copies the whole original user input string from the buffer,
; and moves it to the target string reversed
;------------------------------------------------------------------------------
SwapBackwardsOriginalStr PROC

	call Clrscr

	mov edx,OFFSET sayOriginalStr  ; output original input string
	call WriteString
	mov edx,OFFSET buffer          
	call WriteString

	call Crlf

	mov eax,byteCount
	mov wordLength,eax             ; put byteCount into wordLength

	mov ecx,wordLength             ; move wordLength into loop counter

	sub wordLength,1               ; subtract 1 from wordLength to store wordLength-1 into ESI register
	mov esi,wordLength             ; move wordLength-1 into index pointer, which decrements

	mov edi,0
	mov esi,wordLength             ; basically wordLength-1

SwapInputBackwardsLoop:            ; Take from source string and input it backwards into target string
	mov al,buffer[edi]             ; get character from source 
	mov reversedBuffer[esi],al     ; store it in target

	inc edi                        ; increment esi and move to next character
	dec esi	                       ; decrement edi and move to next character

	loop SwapInputBackwardsLoop	   ; repeat for the whole string

	mov reversedBuffer[edi],0

	mov edx,OFFSET sayReversedStr  ; output original input string
	call WriteString
	mov edx,OFFSET reversedBuffer         
	call WriteString
	call Crlf

SwapBackwardsOriginalStr ENDP

;--------------------------------------------------------------------------------------------------
; The Squeeze String Procedure
; This procedure copies only uppercase/lowercase alphabetical letters from the
; input string buffer, and moves it to the "source" string. Thus, a string without punctuation/spaces.
;--------------------------------------------------------------------------------------------------
SqueezeString PROC

	mov esi,0	                 ; ESI index counter which will be incrementing
	mov edi,0                    ; EDI index counter which will only be incrementing if ESI points
	                             ; to an index location of the buffer that contains an alphabetical letter

	mov ecx,byteCount            ; counts to size of string

SqueezeStringLoop:	             ; Beginning of the SqueezeString loop
	cmp buffer[esi],'A'		     ; compare if buffer[esi] < 'A' ASCII
	jl SkipContent
		; if not, proceed
	cmp buffer[esi],'z'		     ; compare if buffer[esi] > 'z' ASCII
	jg SkipContent
		; if not, proceed
	cmp buffer[esi],'Z'          ; compare if buffer[esi] > 'Z' ASCII
	jg bufferGreater_Cap_Z
		; if not, proceed
	jmp Proceed_Me

bufferGreater_Cap_Z:             ; This step then checks to see if buffer[esi] > 'a' && buffer[esi] < 'a'

	cmp buffer[esi],'a'          ; compare if buffer[esi] < 'a' ASCII
	jl SkipContent
		; if not, proceed
	jmp Proceed_Me

SkipContent:
	inc esi

	loop SqueezeStringLoop
	ret

Proceed_Me:
	mov al,buffer[esi]
	mov source[edi],al
	inc esi                       ; increment ESI and move to next character
	inc edi                       ; increment EDI and move to next character

	loop SqueezeStringLoop
	ret

SqueezeString ENDP

;--------------------------------------------------------------------------------
; The Swap Backwards and Compare Procedure:
; Copies the string backwards into the target string (overwriting the data), 
; then compares the original to the swapped version to see if they're identicle. 
; If so, the string that the user originally put in is a palindrome.
;--------------------------------------------------------------------------------
SwapAndCompare PROC

	cmp edi,2                     ; compare if edi <= 2 (because it's pointless to have an input of 2 or less characters)
	jle ErrorInput                ; go to ErrorInput label to display error message and then return
	jmp GoodInput                 ; if the input is good (more than 3 alphabetical letters)

ErrorInput:
	call Clrscr
	mov edx,OFFSET promptError
	call WriteString

	call Crlf
	call Crlf

	call WaitMsg

	call Clrscr
	ret

GoodInput:

    mov source[edi],0              ; Trim the string by putting a null terminator at end of source string
	mov target[edi],0              ; Trim the string by putting a null terminator at end of target string

    INVOKE Str_ucase,ADDR source   ; capitalizes the entire string

	mov wordLength,edi
	mov ecx,wordLength             ; move wordLength into loop counter

	sub wordLength,1               ; subtract 1 from wordLength to store wordLength-1 into ESI register
	mov esi,wordLength             ; move wordLength-1 into index pointer, which decrements
	mov edi,0                      ; start edi at 0, which increments

SwapBackwardsLoop:                 ; Take from source string and input it backwards into target string
	mov al,source[edi]             ; get character from source 
	mov target[esi],al             ; store it in target

	inc edi                        ; increment esi and move to next character
	dec esi	                       ; decrement edi and move to next character
	
	loop SwapBackwardsLoop	       ; repeat for the whole string


; --- Now compare the strings ---

	mov esi,0
	mov ecx,wordLength		       

CompareStrings:                    ; compares the original and reversed string, letter by letter, to see if they're equal
	
	mov al,source[esi]
	mov bl,target[esi]

	cmp al,bl                      ; compare if source[esi] != target[esi]
	jne NotEqualStrings			   ; jump to NotEqualStrings and exit the loop

	inc esi                        ; increment ESI

	loop CompareStrings

	jmp EqualStrings               ; jump to EqualStrings label if the strings are equal to eachother (letter by letter)

NotEqualStrings:
	mov edx,OFFSET promptDenied
	call WriteString
	ret                            

EqualStrings:
	mov edx,OFFSET promptAccepted
	call WriteString
	ret

SwapAndCompare ENDP
END main

