/* Erro Sintaxe (Tipos) linguagem L */

Var n;
nome[40];
Const MAXITER=10;

/* Programa Principal */

  write("Digite seu nome: ");
  readln(nome);
  For n=1 to MAXITER step 4 do {
    writeln("Ola ",nome);
  }