sseg SEGMENT STACK		; Início seg. pilha
	byte 4000h DUP(?)	; Dimensiona pilha
sseg ENDS			; Fim seg. pilha

dseg SEGMENT PUBLIC		; Início seg. dados
	byte 4000h DUP(?)	; Temporários
	byte 20 DUP(?)			; Var. vec. char em 16384
	byte 95			; Var. char em 16404
	sword 20 DUP(?)			; Var. vec. int em 16405
	byte 65			; Var. char em 16445
	sword 1			; Var. int em 16446
	sword ?			; Var. int em 16448
	sword 4			; Var. int em 16450
	byte 20 DUP(?)			; Var. vec. char em 16452
	byte 5 DUP(?)			; Var. vec. char em 16472
	sword 1			; Const. int em 16477
	sword 3			; Const. int em 16479
	byte 67			; Const. char em 16481
	sword -5			; Const. int em 16482
dseg ENDS			; Fim seg. dados

cseg SEGMENT PUBLIC		; Início seg. código
	ASSUME CS:cseg, DS:dseg

strt:				; Início do programa
	mov AX, dseg
	mov DS, AX

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16484
		byte "Tails e Sonic$"
	dseg ENDS

	; ============ Atrib. id ===========
	mov AL, DS:[16484]
	mov DS:[16452], AL

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16498
		byte "Lasanha eh Vida$"
	dseg ENDS

	; ============ Atrib. id ===========
	mov AL, DS:[16498]
	mov DS:[16384], AL
	mov DX, 0

	; ============ Readln String ===========
	mov AL, 20
	mov DS:[0], AL

	mov AH, 0Ah
	int 21h

	mov AH, 02h
	mov DL, 0Dh
	int 21h

	mov DL, 0Ah
	int 21h

	mov DI, 2
	mov SI, 16452
	mov AH, 0
R1:
	mov AL, DS:[DI]
	cmp AX, 0Dh
	je R2
	mov DS:[SI], AL
	add DI, 1
	add SI, 1
	jmp R1
R2:
	mov DL, 24h
	mov DS:[SI], DL

	; ============ Temp. Const. (0) ===========
	mov AX, 0
	mov DS:[23], AX

	; ============ Temp. Const. ('A') ===========
	mov AL, 65
	mov DS:[25], AL

	; ============ Atrib. id ===========
	mov AL, DS:[25]
	mov DI, DS:[23]
	add DI, 16472
	mov DS:[DI], AL

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Temp. Const. ('B') ===========
	mov AL, 66
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16472
	mov DS:[DI], AL

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[0], AX

	; ============ Temp. Const. ('C') ===========
	mov AL, 67
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16472
	mov DS:[DI], AL

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[0], AX

	; ============ Temp. Const. ('D') ===========
	mov AL, 68
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16472
	mov DS:[DI], AL

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[0], AX

	; ============ Temp. Const. ('E') ===========
	mov AL, 69
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16472
	mov DS:[DI], AL

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16514
		byte "ABCDE$"
	dseg ENDS

	; ============ Op. Exp (Vetor) ===========
	mov AX, 5
	mov BX, 5
	cmp AX, BX
	jne R3
	mov DI, 16514
	mov SI, 16472
	add AX, DI
	mov BH, 0
	mov CH, 0
R4:
	cmp DI, AX
	je R5
	mov BL, DS:[DI]
	mov CL, DS:[SI]
	cmp BX, CX
	jne R3
	add DI, 1
	add SI, 1
	jmp R4
R5:
	mov AL, 1
	jmp R6
R3:
	mov AL, 0
R6:
	mov DS:[0], AL

	; ============ If ===========
	mov AX, DS:[0]
	mov AH, 0
	cmp AX, 0
	je R7

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16520
		byte "IGUAL$"
	dseg ENDS

	; ============ Write(ln) Vetor/String ===========
	mov DX, 16520
	mov AH, 09h
	int 21h

	; ============ Writeln (End) ===========
	mov AH, 02h
	mov DL, 0Dh
	int 21h

	mov DL, 0Ah
	int 21h

	; ============ If sem Else ===========
R7:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R8:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R9

	; ============ Temp. Const. ('D') ===========
	mov AL, 68
	mov DS:[4], AL

	; ============ Op. Exp ===========
	mov AX, DS:[16445]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jne R10
	mov AL, 0
	jmp R11
R10:
	mov AL, 1
R11:
	mov DS:[5], AL

	; ============ If ===========
	mov AX, DS:[5]
	mov AH, 0
	cmp AX, 0
	je R12

	; ============ Temp. Const. ('A') ===========
	mov AL, 65
	mov DS:[6], AL

	; ============ Temp. Const. ('B') ===========
	mov AL, 66
	mov DS:[7], AL

	; ============ Op. ExpS ===========
	mov AX, DS:[6]
	mov BX, DS:[7]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[8], AL

	; ============ Atrib. id ===========
	mov AL, DS:[8]
	mov DS:[16445], AL

	; ============ Else ===========
	jmp R13
R12:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	add AX, BX
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DS:[16446], AX

	; ============ If com Else ===========
R13:

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 2
	add AX, BX
	mov DS:[16446], AX
	jmp R8
R9:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jg R14
	mov AL, 0
	jmp R15
R14:
	mov AL, 1
R15:
	mov DS:[2], AL

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16477]
	cmp AX, BX
	jl R16
	mov AL, 0
	jmp R17
R16:
	mov AL, 1
R17:
	mov DS:[4], AL

	; ============ Op. ExpS ===========
	mov AX, DS:[2]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	mov CX, AX
	add CX, BX
	imul BX
	sub CX, AX
	mov AX, CX
	mov DS:[6], AL

	; ============ If ===========
	mov AX, DS:[6]
	mov AH, 0
	cmp AX, 0
	je R18

	; ============ Temp. Const. ('A') ===========
	mov AL, 65
	mov DS:[7], AL

	; ============ Temp. Const. ('B') ===========
	mov AL, 66
	mov DS:[8], AL

	; ============ Op. ExpS ===========
	mov AX, DS:[7]
	mov BX, DS:[8]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[9], AL

	; ============ Atrib. id ===========
	mov AL, DS:[9]
	mov DS:[16445], AL

	; ============ If sem Else ===========
R18:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jg R19
	mov AL, 0
	jmp R20
R19:
	mov AL, 1
R20:
	mov DS:[2], AL

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16477]
	cmp AX, BX
	jge R21
	mov AL, 0
	jmp R22
R21:
	mov AL, 1
R22:
	mov DS:[4], AL

	; ============ Op. Termo ===========
	mov AX, DS:[2]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	imul BX
	mov DS:[6], AL

	; ============ If ===========
	mov AX, DS:[6]
	mov AH, 0
	cmp AX, 0
	je R23

	; ============ Temp. Const. ('A') ===========
	mov AL, 65
	mov DS:[7], AL

	; ============ Temp. Const. ('B') ===========
	mov AL, 66
	mov DS:[8], AL

	; ============ Op. ExpS ===========
	mov AX, DS:[7]
	mov BX, DS:[8]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[9], AL

	; ============ Atrib. id ===========
	mov AL, DS:[9]
	mov DS:[16445], AL

	; ============ If sem Else ===========
R23:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jle R24
	mov AL, 0
	jmp R25
R24:
	mov AL, 1
R25:
	mov DS:[2], AL

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R26

	; ============ Temp. Const. ('A') ===========
	mov AL, 65
	mov DS:[4], AL

	; ============ Temp. Const. ('B') ===========
	mov AL, 66
	mov DS:[5], AL

	; ============ Op. ExpS ===========
	mov AX, DS:[4]
	mov BX, DS:[5]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[6], AL

	; ============ Atrib. id ===========
	mov AL, DS:[6]
	mov DS:[16445], AL

	; ============ If sem Else ===========
R26:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jge R27
	mov AL, 0
	jmp R28
R27:
	mov AL, 1
R28:
	mov DS:[2], AL

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R29

	; ============ Temp. Const. ('A') ===========
	mov AL, 65
	mov DS:[4], AL

	; ============ Temp. Const. ('B') ===========
	mov AL, 66
	mov DS:[5], AL

	; ============ Op. ExpS ===========
	mov AX, DS:[4]
	mov BX, DS:[5]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[6], AL

	; ============ Atrib. id ===========
	mov AL, DS:[6]
	mov DS:[16445], AL

	; ============ If sem Else ===========
R29:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R30:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R31

	; ============ Temp. Const. (12) ===========
	mov AX, 12
	mov DS:[4], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[4]
	cmp AX, BX
	je R32
	mov AL, 0
	jmp R33
R32:
	mov AL, 1
R33:
	mov DS:[6], AL

	; ============ If ===========
	mov AX, DS:[6]
	mov AH, 0
	cmp AX, 0
	je R34

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[8], AX

	; ============ Op. Termo ===========
	mov AX, DS:[16446]
	mov BX, DS:[8]
	cwd
	idiv BX
	mov AX, DX
	mov DS:[10], AX

	; ============ Atrib. id ===========
	mov AX, DS:[10]
	mov DS:[16446], AX

	; ============ If sem Else ===========
R34:

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16526
		byte "valor: $"
	dseg ENDS

	; ============ Write(ln) Vetor/String ===========
	mov DX, 16526
	mov AH, 09h
	int 21h

	; ============ Write(ln) Int ===========
	mov AX, DS:[16446]
	mov DI, 0
	mov CX, 0
	cmp AX, 0
	jge R35
	mov BL, 2Dh
	mov DS:[DI], BL
	add DI, 1
	neg AX
R35:
	mov BX, 10
R36:
	add CX, 1
	mov DX, 0
	idiv BX
	push DX
	cmp AX, 0
	jne R36
R37:
	pop DX
	add DX, 48
	mov DS:[DI], DL
	add DI, 1
	add CX, -1
	cmp CX, 0
	jne R37
	mov DL, 024h
	mov DS:[DI], DL

	mov DX, 0
	mov AH, 09h
	int 21h

	; ============ Writeln (End) ===========
	mov AH, 02h
	mov DL, 0Dh
	int 21h

	mov DL, 0Ah
	int 21h

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 1
	add AX, BX
	mov DS:[16446], AX
	jmp R30
R31:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Temp. Const. ('M') ===========
	mov AL, 77
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[0], AX

	; ============ Temp. Const. (0x41) ===========
	mov AL, 65
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[0], AX

	; ============ Temp. Const. (0x43) ===========
	mov AL, 67
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[0], AX

	; ============ Temp. Const. (0x4F) ===========
	mov AL, 79
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[0], AX

	; ============ Temp. Const. ('N') ===========
	mov AL, 78
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (6) ===========
	mov AX, 6
	mov DS:[0], AX

	; ============ Temp. Const. ('H') ===========
	mov AL, 72
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (7) ===========
	mov AX, 7
	mov DS:[0], AX

	; ============ Temp. Const. (0x41) ===========
	mov AL, 65
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (8) ===========
	mov AX, 8
	mov DS:[0], AX

	; ============ Temp. Const. ('.') ===========
	mov AL, 46
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AL

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[0], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[2], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[2]
	neg AX
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[0], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[2], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[4], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[2]
	mov BX, DS:[4]
	add AX, BX
	mov DS:[6], AX

	; ============ Atrib. id ===========
	mov AX, DS:[6]
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[0], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[2], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[4], AX

	; ============ Op. Termo ===========
	mov AX, DS:[2]
	mov BX, DS:[4]
	cwd
	idiv BX
	mov DS:[6], AX

	; ============ Atrib. id ===========
	mov AX, DS:[6]
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[0], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[2], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[4], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[4]
	neg AX
	mov DS:[4], AX

	; ============ Op. Termo ===========
	mov AX, DS:[2]
	mov BX, DS:[4]
	imul BX
	mov DS:[6], AX

	; ============ Atrib. id ===========
	mov AX, DS:[6]
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (6) ===========
	mov AX, 6
	mov DS:[0], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[2]
	neg AX
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. ('D') ===========
	mov AL, 68
	mov DS:[0], AL

	; ============ Op. Exp ===========
	mov AX, DS:[16445]
	mov BX, DS:[0]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	je R38
	mov AL, 0
	jmp R39
R38:
	mov AL, 1
R39:
	mov DS:[1], AL
	; ============ Op. NOT ===========

	mov AX, DS:[1]
	neg AX
	add AX, 1
	mov DS:[2], AX

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R40
	mov DX, 3

	; ============ Readln Int ===========
	mov AL, 255
	mov DS:[3], AL

	mov AH, 0Ah
	int 21h

	mov AH, 02h
	mov DL, 0Dh
	int 21h

	mov DL, 0Ah
	int 21h

	mov DI, 5
	mov AX, 0
	mov CX, 10
	mov DX, 1
	mov DH, 0
	mov BL, DS:[DI]
	cmp BX, 2Dh
	jne R41
	mov DX, -1
	add DI, 1
	mov BL, DS:[DI]
R41:
	push DX
	mov DX, 0
R42:
	cmp BX, 0Dh
	je R43
	imul CX
	add BX, -48
	add AX, BX
	add DI, 1
	mov BH, 0
	mov BL, DS:[DI]
	jmp R42
R43:
	pop CX
	imul CX
	mov DS:[16446], AX
	mov DX, 9

	; ============ Readln Char ===========
	mov AL, 3
	mov DS:[9], AL

	mov AH, 0Ah
	int 21h

	mov AH, 02h
	mov DL, 0Dh
	int 21h

	mov DL, 0Ah
	int 21h

	mov DL, 024h
	mov DS:[12], DL
	mov DI, 11
	mov AL, DS:[DI]
	mov DS:[16445], AL

	; ============ Write(ln) Int ===========
	mov AX, DS:[16446]
	mov DI, 12
	mov CX, 0
	cmp AX, 0
	jge R44
	mov BL, 2Dh
	mov DS:[DI], BL
	add DI, 1
	neg AX
R44:
	mov BX, 10
R45:
	add CX, 1
	mov DX, 0
	idiv BX
	push DX
	cmp AX, 0
	jne R45
R46:
	pop DX
	add DX, 48
	mov DS:[DI], DL
	add DI, 1
	add CX, -1
	cmp CX, 0
	jne R46
	mov DL, 024h
	mov DS:[DI], DL

	mov DX, 12
	mov AH, 09h
	int 21h

	; ============ Temp. Const. (' ') ===========
	mov AL, 32
	mov DS:[14], AL

	; ============ Write(ln) Char ===========
	mov DX, 15
	mov AL, DS:[14]
	mov DS:[15], AL
	mov DI, 16
	mov DL, 024h
	mov DS:[DI], DL

	mov DX, 15
	mov AH, 09h
	int 21h

	; ============ Write(ln) Char ===========
	mov DX, 16
	mov AL, DS:[16445]
	mov DS:[16], AL
	mov DI, 17
	mov DL, 024h
	mov DS:[DI], DL

	mov DX, 16
	mov AH, 09h
	int 21h

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16534
		byte "CHUPA$"
	dseg ENDS

	; ============ Write(ln) Vetor/String ===========
	mov DX, 16534
	mov AH, 09h
	int 21h

	; ============ Writeln (End) ===========
	mov AH, 02h
	mov DL, 0Dh
	int 21h

	mov DL, 0Ah
	int 21h

	; ============ If sem Else ===========
R40:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R47:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R48

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 1
	add AX, BX
	mov DS:[16446], AX
	jmp R47
R48:

	mov ah, 4Ch		; Finalização do programa
	int 21h			; Finalização do programa
cseg ENDS			; Fim seg. código
END strt			; Fim programa
