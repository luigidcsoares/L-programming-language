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

	; ============ Temp. Const. (0) ===========
	mov AX, 0
	mov DS:[0], AX

	; ============ Temp. Const. ('A') ===========
	mov AL, 65
	mov DS:[2], AL

	; ============ Atrib. id ===========
	mov AL, DS:[2]
	mov DI, DS:[0]
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

	; ============ Op. Exp ===========
	mov AX, 5
	mov BX, 5
	cmp AX, BX
	jne R1
	mov DI, 16514
	mov SI, 16472
	add AX, DI
	mov BH, 0
	mov CH, 0
R2:
	cmp DI, AX
	je R3
	mov BL, DS:[DI]
	mov CL, DS:[SI]
	cmp BX, CX
	jne R1
	add DI, 1
	add SI, 1
	jmp R2
R3:
	mov AL, 1
	jmp R4
R1:
	mov AL, 0
R4:
	mov DS:[0], AL

	; ============ If ===========
	mov AX, DS:[0]
	mov AH, 0
	cmp AX, 0
	je R5

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16520
		byte "IGUAL$"
	dseg ENDS

	; ============ If sem Else ===========
R5:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R6:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R7

	; ============ Temp. Const. ('D') ===========
	mov AL, 68
	mov DS:[4], AL

	; ============ Op. Exp ===========
	mov AX, DS:[16445]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jne R8
	mov AL, 0
	jmp R9
R8:
	mov AL, 1
R9:
	mov DS:[5], AL

	; ============ If ===========
	mov AX, DS:[5]
	mov AH, 0
	cmp AX, 0
	je R10

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
	jmp R11
R10:

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
R11:

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 2
	add AX, BX
	mov DS:[16446], AX
	jmp R6
R7:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jg R12
	mov AL, 0
	jmp R13
R12:
	mov AL, 1
R13:
	mov DS:[2], AL

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16477]
	cmp AX, BX
	jl R14
	mov AL, 0
	jmp R15
R14:
	mov AL, 1
R15:
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
	je R16

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
R16:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jg R17
	mov AL, 0
	jmp R18
R17:
	mov AL, 1
R18:
	mov DS:[2], AL

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16477]
	cmp AX, BX
	jge R19
	mov AL, 0
	jmp R20
R19:
	mov AL, 1
R20:
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
	je R21

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
R21:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jle R22
	mov AL, 0
	jmp R23
R22:
	mov AL, 1
R23:
	mov DS:[2], AL

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R24

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
R24:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	cmp AX, BX
	jge R25
	mov AL, 0
	jmp R26
R25:
	mov AL, 1
R26:
	mov DS:[2], AL

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R27

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
R27:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R28:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R29

	; ============ Temp. Const. (12) ===========
	mov AX, 12
	mov DS:[4], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[4]
	cmp AX, BX
	je R30
	mov AL, 0
	jmp R31
R30:
	mov AL, 1
R31:
	mov DS:[6], AL

	; ============ If ===========
	mov AX, DS:[6]
	mov AH, 0
	cmp AX, 0
	je R32

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
R32:

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 1
	add AX, BX
	mov DS:[16446], AX
	jmp R28
R29:

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
	je R33
	mov AL, 0
	jmp R34
R33:
	mov AL, 1
R34:
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
	je R35

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[3], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Acesso a vetor ===========
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov AX, DS:[DI]
	mov DS:[2], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[0], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Acesso a vetor ===========
	mov DI, DS:[0]
	add DI, DI
	add DI, 16405
	mov AX, DS:[DI]
	mov DS:[2], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[0], AX

	; ============ If sem Else ===========
R35:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R36:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R37

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 1
	add AX, BX
	mov DS:[16446], AX
	jmp R36
R37:

	mov ah, 4Ch		; Finalização do programa
	int 21h			; Finalização do programa
cseg ENDS			; Fim seg. código
END strt			; Fim programa
