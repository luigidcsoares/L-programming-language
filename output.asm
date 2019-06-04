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

	; ============ Decl. de String ===========
	dseg SEGMENT PUBLIC		; String em 16493
		byte "Lasanha eh Vida$"
	dseg ENDS

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Temp. Const. ('D') ===========
	mov AX, 68
	mov DS:[4], AX

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[5], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[6], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[7], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[9], AX

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[11], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[12], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[13], AX

	; ============ Op. Termo ===========
	mov AX, DS:[16446]
	mov BX, DS:[16446]
	mov AH, 0
	mov BH, 0
	imul BX
	mov DS:[15], AL

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[16], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[17], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[18], AX

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[20], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[21], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[22], AX

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[24], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[25], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[26], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[28], AX

	; ============ Temp. Const. (12) ===========
	mov AX, 12
	mov DS:[30], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[32], AX

	; ============ Op. Termo ===========
	mov AX, DS:[16446]
	mov BX, DS:[32]
	cwd
	idiv BX
mov AX, DX
	mov DS:[34], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[36], AX

	; ============ Temp. Const. ('M') ===========
	mov AX, 77
	mov DS:[38], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[39], AX

	; ============ Temp. Const. (0x41) ===========
	mov AX, 65
	mov DS:[41], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[42], AX

	; ============ Temp. Const. (0x43) ===========
	mov AX, 67
	mov DS:[44], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[45], AX

	; ============ Temp. Const. (0x4F) ===========
	mov AX, 79
	mov DS:[47], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[48], AX

	; ============ Temp. Const. ('N') ===========
	mov AX, 78
	mov DS:[50], AX

	; ============ Temp. Const. (6) ===========
	mov AX, 6
	mov DS:[51], AX

	; ============ Temp. Const. ('H') ===========
	mov AX, 72
	mov DS:[53], AX

	; ============ Temp. Const. (7) ===========
	mov AX, 7
	mov DS:[54], AX

	; ============ Temp. Const. (0x41) ===========
	mov AX, 65
	mov DS:[56], AX

	; ============ Temp. Const. (8) ===========
	mov AX, 8
	mov DS:[57], AX

	; ============ Temp. Const. ('.') ===========
	mov AX, 46
	mov DS:[59], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[60], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[62], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[64], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[66], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[66]
	neg AX
	mov DS:[66], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[68], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[70], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[72], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[74], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[76], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[78], AX

	; ============ Op. Termo ===========
	mov AX, DS:[76]
	mov BX, DS:[78]
	cwd
	idiv BX
	mov DS:[80], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[82], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[84], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[86], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[86]
	neg AX
	mov DS:[86], AX

	; ============ Op. Termo ===========
	mov AX, DS:[84]
	mov BX, DS:[86]
	imul BX
	mov DS:[88], AX

	; ============ Temp. Const. (6) ===========
	mov AX, 6
	mov DS:[90], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[92], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[92]
	neg AX
	mov DS:[92], AX

	; ============ Temp. Const. ('D') ===========
	mov AX, 68
	mov DS:[94], AX
	; ============ Op. NOT ===========

	mov AX, DS:[16445]
	neg AX
	add AX, 1
	mov DS:[95], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[96], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[98], AX

	; ============ Acesso a vetor ===========
	mov DI, DS:[98
	add DI, DI
	add DI, 16405
	mov AX, DS:[DI]
	mov DS:[100], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[140], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[142], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[144], AX

	; ============ Acesso a vetor ===========
	mov DI, DS:[144
	add DI, DI
	add DI, 16405
	mov AX, DS:[DI]
	mov DS:[146], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[186], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[188], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[190], AX

	mov ah, 4Ch		; Finalização do programa
	int 21h			; Finalização do programa
cseg ENDS			; Fim seg. código
END strt			; Fim programa
