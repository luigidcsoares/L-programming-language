sseg SEGMENT STACK		; Início seg. pilha
	byte 4000h DUP(?)	; Dimensiona pilha
sseg ENDS			; Fim seg. pilha

dseg SEGMENT PUBLIC		; Início seg. dados
	byte 4000h DUP(?)	; Temporários
	sword 1		; Const. int em 16384
	sword 3		; Const. int em 16386
	sword -5		; Const. int em 16388
	byte 67		; Const. char em 16390
dseg ENDS			; Fim seg. dados

cseg SEGMENT PUBLIC		; Início seg. código
	ASSUME CS:cseg, DS:dseg

strt:				; Início do programa
cseg ENDS			; Fim seg. código
END strs			; Fim programa
