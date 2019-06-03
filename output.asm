sseg SEGMENT STACK		; Início seg. pilha
	byte 4000h DUP(?)	; Dimensiona pilha
sseg ENDS			; Fim seg. pilha

dseg SEGMENT PUBLIC		; Início seg. dados
	byte 4000h DUP(?)	; Temporários
dseg ENDS			; Fim seg. dados

cseg SEGMENT PUBLIC		; Início seg. código
	ASSUME CS:cseg, DS:dseg

strt:				; Início do programa
