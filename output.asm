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

	dseg SEGMENT PUBLIC		; String em 16479
		byte "Tails e Sonic$"
	dseg ENDS

	dseg SEGMENT PUBLIC		; String em 16493
		byte "Lasanha eh Vida$"
	dseg ENDS

	mov AX, 1			; Temp. const.: 1
	mov DS:[0], AX

	mov AX, 10			; Temp. const.: 10
	mov DS:[2], AX

	mov AX, 68			; Temp. const.: 'D'
	mov DS:[4], AX

	mov AX, 65			; Temp. const.: 'A'
	mov DS:[5], AX

	mov AX, 66			; Temp. const.: 'B'
	mov DS:[6], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[7], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[9], AX

	mov AX, 65			; Temp. const.: 'A'
	mov DS:[11], AX

	mov AX, 66			; Temp. const.: 'B'
	mov DS:[12], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[13], AX

	mov AX, 65			; Temp. const.: 'A'
	mov DS:[15], AX

	mov AX, 66			; Temp. const.: 'B'
	mov DS:[16], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[17], AX

	mov AX, 65			; Temp. const.: 'A'
	mov DS:[19], AX

	mov AX, 66			; Temp. const.: 'B'
	mov DS:[20], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[21], AX

	mov AX, 65			; Temp. const.: 'A'
	mov DS:[23], AX

	mov AX, 66			; Temp. const.: 'B'
	mov DS:[24], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[25], AX

	mov AX, 10			; Temp. const.: 10
	mov DS:[27], AX

	mov AX, 12			; Temp. const.: 12
	mov DS:[29], AX

	mov AX, 2			; Temp. const.: 2
	mov DS:[31], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[33], AX

	mov AX, 77			; Temp. const.: 'M'
	mov DS:[35], AX

	mov AX, 2			; Temp. const.: 2
	mov DS:[36], AX

	mov AX, 65			; Temp. const.: 0x41
	mov DS:[38], AX

	mov AX, 3			; Temp. const.: 3
	mov DS:[39], AX

	mov AX, 67			; Temp. const.: 0x43
	mov DS:[41], AX

	mov AX, 4			; Temp. const.: 4
	mov DS:[42], AX

	mov AX, 79			; Temp. const.: 0x4F
	mov DS:[44], AX

	mov AX, 5			; Temp. const.: 5
	mov DS:[45], AX

	mov AX, 78			; Temp. const.: 'N'
	mov DS:[47], AX

	mov AX, 6			; Temp. const.: 6
	mov DS:[48], AX

	mov AX, 72			; Temp. const.: 'H'
	mov DS:[50], AX

	mov AX, 7			; Temp. const.: 7
	mov DS:[51], AX

	mov AX, 65			; Temp. const.: 0x41
	mov DS:[53], AX

	mov AX, 8			; Temp. const.: 8
	mov DS:[54], AX

	mov AX, 46			; Temp. const.: '.'
	mov DS:[56], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[57], AX

	mov AX, 5			; Temp. const.: 5
	mov DS:[59], AX

	mov AX, 2			; Temp. const.: 2
	mov DS:[61], AX

	mov AX, 4			; Temp. const.: 4
	mov DS:[63], AX

	mov AX, 3			; Temp. const.: 3
	mov DS:[65], AX

	mov AX, 5			; Temp. const.: 5
	mov DS:[67], AX

	mov AX, 3			; Temp. const.: 3
	mov DS:[69], AX

	mov AX, 4			; Temp. const.: 4
	mov DS:[71], AX

	mov AX, 4			; Temp. const.: 4
	mov DS:[73], AX

	mov AX, 2			; Temp. const.: 2
	mov DS:[75], AX

	mov AX, 5			; Temp. const.: 5
	mov DS:[77], AX

	mov AX, 4			; Temp. const.: 4
	mov DS:[79], AX

	mov AX, 2			; Temp. const.: 2
	mov DS:[81], AX

	mov AX, 6			; Temp. const.: 6
	mov DS:[83], AX

	mov AX, 10			; Temp. const.: 10
	mov DS:[85], AX

	mov AX, 68			; Temp. const.: 'D'
	mov DS:[87], AX

	mov AX, DS:[16445] 		; Not
	neg AX
	add AX, 1
	mov DS:[88], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[89], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[91], AX

	mov AX, DS:[91]		; Acesso a vetor
	add AX, AX
	add AX, 16405
	mov AX, DS:[AX]
	mov DS:[93], AX

	mov AX, 5			; Temp. const.: 5
	mov DS:[133], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[135], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[137], AX

	mov AX, DS:[137]		; Acesso a vetor
	add AX, AX
	add AX, 16405
	mov AX, DS:[AX]
	mov DS:[139], AX

	mov AX, 5			; Temp. const.: 5
	mov DS:[179], AX

	mov AX, 1			; Temp. const.: 1
	mov DS:[181], AX

	mov AX, 10			; Temp. const.: 10
	mov DS:[183], AX

	mov ah, 4Ch		; Finalização do programa
	int 21h			; Finalização do programa
cseg ENDS			; Fim seg. código
END strt			; Fim programa
