/* Exemplo de Programa na linguagem L */

Var integer n[3], max;

/* Programa Principal */

  For I=0 to 2 do {
    write("Digite um numero: ");
    readln(n[i]);
  }
  If n[0] > n[1] then {
    If n[0] > n[2] then max=n[0]; else max=n[2];
  } else If n[1] > n[2] then max=n[1]; else max=n[2];
  writeln("O maior numero e' ",max);
  
