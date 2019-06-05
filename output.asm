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
	sword 1			; Const. int em 16472
	sword 3			; Const. int em 16474
	byte 67			; Const. char em 16476
	sword -5			; Const. int em 16477
dseg ENDS			; Fim seg. dados

cseg SEGMENT PUBLIC		; Início seg. código
	ASSUME CS:cseg, DS:dseg

strt:				; Início do programa
	mov AX, dseg
	mov DS, AX

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16479
		byte "Tails e Sonic$"
	dseg ENDS

	; ============ Atrib. id ===========
	mov AX, DS:[16479]
	mov DS:[16452], AX

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16493
		byte "Lasanha eh Vida$"
	dseg ENDS

	; ============ Atrib. id ===========
	mov AX, DS:[16493]
	mov DS:[16384], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R1:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R2

	; ============ Temp. Const. ('D') ===========
	mov AX, 68
	mov DS:[4], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16445]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jne R3
	mov AX, 0
	jmp R4
R3:
	mov AX, 1
R4:
	mov DS:[5], AX

	; ============ If ===========
	mov AX, DS:[5]
	mov AH, 0
	cmp AX, 0
	je R5

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[6], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[7], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[6]
	mov BX, DS:[7]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[8], AL

	; ============ Atrib. id ===========
	mov AX, DS:[8]
	mov DS:[16445], AX

	; ============ Else ===========
	jmp R6
R5:

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
R6:

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 2
	add AX, BX
	mov DS:[16446], AX
	jmp R1
R2:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jg R7
	mov AX, 0
	jmp R8
R7:
	mov AX, 1
R8:
	mov DS:[2], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16472]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jl R9
	mov AX, 0
	jmp R10
R9:
	mov AX, 1
R10:
	mov DS:[3], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[2]
	mov BX, DS:[3]
	mov AH, 0
	mov BH, 0
	mov CX, AX
	add CX, BX
	imul BX
	sub CX, AX
	mov AX, CX
	mov DS:[4], AL

	; ============ If ===========
	mov AX, DS:[4]
	mov AH, 0
	cmp AX, 0
	je R11

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[5], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[6], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[5]
	mov BX, DS:[6]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[7], AL

	; ============ Atrib. id ===========
	mov AX, DS:[7]
	mov DS:[16445], AX

	; ============ If sem Else ===========
R11:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jg R12
	mov AX, 0
	jmp R13
R12:
	mov AX, 1
R13:
	mov DS:[2], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16472]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jge R14
	mov AX, 0
	jmp R15
R14:
	mov AX, 1
R15:
	mov DS:[3], AX

	; ============ Op. Termo ===========
	mov AX, DS:[2]
	mov BX, DS:[3]
	mov AH, 0
	mov BH, 0
	imul BX
	mov DS:[4], AL

	; ============ If ===========
	mov AX, DS:[4]
	mov AH, 0
	cmp AX, 0
	je R16

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[5], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[6], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[5]
	mov BX, DS:[6]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[7], AL

	; ============ Atrib. id ===========
	mov AX, DS:[7]
	mov DS:[16445], AX

	; ============ If sem Else ===========
R16:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jle R17
	mov AX, 0
	jmp R18
R17:
	mov AX, 1
R18:
	mov DS:[2], AX

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R19

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[3], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[4], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[3]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[5], AL

	; ============ Atrib. id ===========
	mov AX, DS:[5]
	mov DS:[16445], AX

	; ============ If sem Else ===========
R19:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[0]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jge R20
	mov AX, 0
	jmp R21
R20:
	mov AX, 1
R21:
	mov DS:[2], AX

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R22

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[3], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[4], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[3]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[5], AL

	; ============ Atrib. id ===========
	mov AX, DS:[5]
	mov DS:[16445], AX

	; ============ If sem Else ===========
R22:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R23:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R24

	; ============ Temp. Const. (12) ===========
	mov AX, 12
	mov DS:[4], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	je R25
	mov AX, 0
	jmp R26
R25:
	mov AX, 1
R26:
	mov DS:[6], AX

	; ============ If ===========
	mov AX, DS:[6]
	mov AH, 0
	cmp AX, 0
	je R27

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[7], AX

	; ============ Op. Termo ===========
	mov AX, DS:[16446]
	mov BX, DS:[7]
	cwd
	idiv BX
	mov AX, DX
	mov DS:[9], AX

	; ============ Atrib. id ===========
	mov AX, DS:[9]
	mov DS:[16446], AX

	; ============ If sem Else ===========
R27:

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 1
	add AX, BX
	mov DS:[16446], AX
	jmp R23
R24:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Temp. Const. ('M') ===========
	mov AX, 77
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[0], AX

	; ============ Temp. Const. (0x41) ===========
	mov AX, 65
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[0], AX

	; ============ Temp. Const. (0x43) ===========
	mov AX, 67
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[0], AX

	; ============ Temp. Const. (0x4F) ===========
	mov AX, 79
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[0], AX

	; ============ Temp. Const. ('N') ===========
	mov AX, 78
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (6) ===========
	mov AX, 6
	mov DS:[0], AX

	; ============ Temp. Const. ('H') ===========
	mov AX, 72
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (7) ===========
	mov AX, 7
	mov DS:[0], AX

	; ============ Temp. Const. (0x41) ===========
	mov AX, 65
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (8) ===========
	mov AX, 8
	mov DS:[0], AX

	; ============ Temp. Const. ('.') ===========
	mov AX, 46
	mov DS:[2], AX

	; ============ Atrib. id ===========
	mov AX, DS:[2]
	mov DI, DS:[0]
	add DI, 16384
	mov DS:[DI], AX

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
	mov AX, 68
	mov DS:[0], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16445]
	mov BX, DS:[0]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	je R28
	mov AX, 0
	jmp R29
R28:
	mov AX, 1
R29:
	mov DS:[1], AX
	; ============ Op. NOT ===========

	mov AX, DS:[1]
	neg AX
	add AX, 1
	mov DS:[2], AX

	; ============ If ===========
	mov AX, DS:[2]
	mov AH, 0
	cmp AX, 0
	je R30

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
R30:

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16446], AX
R31:

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16446]
	mov BX, DS:[2]
	cmp AX, BX
	jg R32

	; ============ Fim For ===========
	mov AX, DS:[16446]
	mov BX, 1
	add AX, BX
	mov DS:[16446], AX
	jmp R31
R32:

	mov ah, 4Ch		; Finalização do programa
	int 21h			; Finalização do programa
cseg ENDS			; Fim seg. código
END strt			; Fim programa
