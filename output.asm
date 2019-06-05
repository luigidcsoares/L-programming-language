sseg SEGMENT STACK		; Início seg. pilha
	byte 4000h DUP(?)	; Dimensiona pilha
sseg ENDS			; Fim seg. pilha

dseg SEGMENT PUBLIC		; Início seg. dados
	byte 4000h DUP(?)	; Temporários
	byte 65			; Var. char em 16384
	sword ?			; Var. int em 16385
dseg ENDS			; Fim seg. dados

cseg SEGMENT PUBLIC		; Início seg. código
	ASSUME CS:cseg, DS:dseg

strt:				; Início do programa
	mov AX, dseg
	mov DS, AX

	; ============ Temp. Const. (1) ===========
	mov AX, 1
	mov DS:[0], AX

	; ============ Inicio For ===========
	mov AX, DS:[0]
	mov DS:[16385], AX
R1:

	; ============ Temp. Const. (2) ===========
	mov AX, 2
	mov DS:[2], AX

	; ============ Teste For ===========
	mov AX, DS:[16385]
	mov BX, DS:[2]
	cmp AX, BX
	jg R2

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
	mov DS:[16384], AL

	; ============ Fim For ===========
	mov AX, DS:[16385]
	mov BX, 1
	add AX, BX
	mov DS:[16385], AX
	jmp R1
R2:

	mov ah, 4Ch		; Finalização do programa
	int 21h			; Finalização do programa
cseg ENDS			; Fim seg. código
END strt			; Fim programa
