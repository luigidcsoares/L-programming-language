/* Erro Sintaxe (Ponto e virgula) linguagem L */

Var integer n
Char nome[40]
Const MAXITER=+10

/* Programa Principal */

  write("Digite seu nome: ")
  readln(nome)
  For n=1 to MAXITER step 2 do {
    writeln("Ola ",nome)
  }
