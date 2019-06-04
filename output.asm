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

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[2], AX

	; ============ Temp. Const. ('D') ===========
	mov AX, 68
	mov DS:[4], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16445]
	mov BX, DS:[4]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jne R1
	mov AX, 0
	jmp R2
	R1:
		mov AX, 1
	R2:
		mov DS:[5], AX

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

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[9], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[16446]
	mov BX, DS:[9]
	add AX, BX
	mov DS:[11], AX

	; ============ Atrib. id ===========
	mov AX, DS:[11]
	mov DS:[16446], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[13], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[13]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jg R3
	mov AX, 0
	jmp R4
	R3:
		mov AX, 1
	R4:
		mov DS:[15], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16472]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jl R5
	mov AX, 0
	jmp R6
	R5:
		mov AX, 1
	R6:
		mov DS:[16], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[15]
	mov BX, DS:[16]
	mov AH, 0
	mov BH, 0
	mov CX, AX
	add CX, BX
	imul BX
	sub CX, AX
	mov AX, CX
	mov DS:[17], AL

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[18], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[19], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[18]
	mov BX, DS:[19]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[20], AL

	; ============ Atrib. id ===========
	mov AX, DS:[20]
	mov DS:[16445], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[21], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[21]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jg R7
	mov AX, 0
	jmp R8
	R7:
		mov AX, 1
	R8:
		mov DS:[23], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[16472]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jge R9
	mov AX, 0
	jmp R10
	R9:
		mov AX, 1
	R10:
		mov DS:[24], AX

	; ============ Op. Termo ===========
	mov AX, DS:[23]
	mov BX, DS:[24]
	mov AH, 0
	mov BH, 0
	imul BX
	mov DS:[25], AL

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[26], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[27], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[26]
	mov BX, DS:[27]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[28], AL

	; ============ Atrib. id ===========
	mov AX, DS:[28]
	mov DS:[16445], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[29], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[29]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jle R11
	mov AX, 0
	jmp R12
	R11:
		mov AX, 1
	R12:
		mov DS:[31], AX

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[32], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[33], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[32]
	mov BX, DS:[33]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[34], AL

	; ============ Atrib. id ===========
	mov AX, DS:[34]
	mov DS:[16445], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[35], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[35]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	jge R13
	mov AX, 0
	jmp R14
	R13:
		mov AX, 1
	R14:
		mov DS:[37], AX

	; ============ Temp. Const. ('A') ===========
	mov AX, 65
	mov DS:[38], AX

	; ============ Temp. Const. ('B') ===========
	mov AX, 66
	mov DS:[39], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[38]
	mov BX, DS:[39]
	mov AH, 0
	mov BH, 0
	add AX, BX
	mov DS:[40], AL

	; ============ Atrib. id ===========
	mov AX, DS:[40]
	mov DS:[16445], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[41], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[43], AX

	; ============ Temp. Const. (12) ===========
	mov AX, 12
	mov DS:[45], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16446]
	mov BX, DS:[45]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	je R15
	mov AX, 0
	jmp R16
	R15:
		mov AX, 1
	R16:
		mov DS:[47], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[48], AX

	; ============ Op. Termo ===========
	mov AX, DS:[16446]
	mov BX, DS:[48]
	cwd
	idiv BX
	mov AX, DX
	mov DS:[50], AX

	; ============ Atrib. id ===========
	mov AX, DS:[50]
	mov DS:[16446], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[52], AX

	; ============ Temp. Const. ('M') ===========
	mov AX, 77
	mov DS:[54], AX

	; ============ Atrib. id ===========
	mov AX, DS:[54]
	mov DI, DS:[52]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[55], AX

	; ============ Temp. Const. (0x41) ===========
	mov AX, 65
	mov DS:[57], AX

	; ============ Atrib. id ===========
	mov AX, DS:[57]
	mov DI, DS:[55]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[58], AX

	; ============ Temp. Const. (0x43) ===========
	mov AX, 67
	mov DS:[60], AX

	; ============ Atrib. id ===========
	mov AX, DS:[60]
	mov DI, DS:[58]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[61], AX

	; ============ Temp. Const. (0x4F) ===========
	mov AX, 79
	mov DS:[63], AX

	; ============ Atrib. id ===========
	mov AX, DS:[63]
	mov DI, DS:[61]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[64], AX

	; ============ Temp. Const. ('N') ===========
	mov AX, 78
	mov DS:[66], AX

	; ============ Atrib. id ===========
	mov AX, DS:[66]
	mov DI, DS:[64]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (6) ===========
	mov AX, 6
	mov DS:[67], AX

	; ============ Temp. Const. ('H') ===========
	mov AX, 72
	mov DS:[69], AX

	; ============ Atrib. id ===========
	mov AX, DS:[69]
	mov DI, DS:[67]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (7) ===========
	mov AX, 7
	mov DS:[70], AX

	; ============ Temp. Const. (0x41) ===========
	mov AX, 65
	mov DS:[72], AX

	; ============ Atrib. id ===========
	mov AX, DS:[72]
	mov DI, DS:[70]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (8) ===========
	mov AX, 8
	mov DS:[73], AX

	; ============ Temp. Const. ('.') ===========
	mov AX, 46
	mov DS:[75], AX

	; ============ Atrib. id ===========
	mov AX, DS:[75]
	mov DI, DS:[73]
	add DI, 16384
	mov DS:[DI], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[76], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[78], AX

	; ============ Atrib. id ===========
	mov AX, DS:[78]
	mov DI, DS:[76]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[80], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[82], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[82]
	neg AX
	mov DS:[82], AX

	; ============ Atrib. id ===========
	mov AX, DS:[82]
	mov DI, DS:[80]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[84], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[86], AX

	; ============ Temp. Const. (3) ===========
	mov AX, 3
	mov DS:[88], AX

	; ============ Op. ExpS ===========
	mov AX, DS:[86]
	mov BX, DS:[88]
	add AX, BX
	mov DS:[90], AX

	; ============ Atrib. id ===========
	mov AX, DS:[90]
	mov DI, DS:[84]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[92], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[94], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[96], AX

	; ============ Op. Termo ===========
	mov AX, DS:[94]
	mov BX, DS:[96]
	cwd
	idiv BX
	mov DS:[98], AX

	; ============ Atrib. id ===========
	mov AX, DS:[98]
	mov DI, DS:[92]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[100], AX

	; ============ Temp. Const. (4) ===========
	mov AX, 4
	mov DS:[102], AX

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[104], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[104]
	neg AX
	mov DS:[104], AX

	; ============ Op. Termo ===========
	mov AX, DS:[102]
	mov BX, DS:[104]
	imul BX
	mov DS:[106], AX

	; ============ Atrib. id ===========
	mov AX, DS:[106]
	mov DI, DS:[100]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. (6) ===========
	mov AX, 6
	mov DS:[108], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[110], AX

	; ============ Neg. Termo ===========
	mov AX, DS:[110]
	neg AX
	mov DS:[110], AX

	; ============ Atrib. id ===========
	mov AX, DS:[110]
	mov DI, DS:[108]
	add DI, DI
	add DI, 16405
	mov DS:[DI], AX

	; ============ Temp. Const. ('D') ===========
	mov AX, 68
	mov DS:[112], AX

	; ============ Op. Exp ===========
	mov AX, DS:[16445]
	mov BX, DS:[112]
	mov AH, 0
	mov BH, 0
	cmp AX, BX
	je R17
	mov AX, 0
	jmp R18
	R17:
		mov AX, 1
	R18:
		mov DS:[113], AX
	; ============ Op. NOT ===========

	mov AX, DS:[113]
	neg AX
	add AX, 1
	mov DS:[114], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[115], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[117], AX

	; ============ Acesso a vetor ===========
	mov DI, DS:[117]
	add DI, DI
	add DI, 16405
	mov AX, DS:[DI]
	mov DS:[119], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[159], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[161], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[163], AX

	; ============ Acesso a vetor ===========
	mov DI, DS:[163]
	add DI, DI
	add DI, 16405
	mov AX, DS:[DI]
	mov DS:[165], AX

	; ============ Temp. Const. (5) ===========
	mov AX, 5
	mov DS:[205], AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[207], AX

	; ============ Temp. Const. (10) ===========
	mov AX, 10
	mov DS:[209], AX

	mov ah, 4Ch		; Finalização do programa
	int 21h			; Finalização do programa
cseg ENDS			; Fim seg. código
END strt			; Fim programa
