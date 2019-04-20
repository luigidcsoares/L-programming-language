/** /Exemplo de Programa na linguagem L */

Var integer n;
Char nome[40];
Const MAXITER=10;

/* Programa Principal */
  write("Digite seu nome: ");
  readln(nome);
  For n=1 to MAXITER do {
    writeln("Ola' ",nome);
  }
