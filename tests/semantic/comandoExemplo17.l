/* Exemplo de Programa na linguagem L */

Var integer a = -2;
Var integer b = -2;
Var integer n;
Var Char k[8];
Const o = 2;

/*Programa Principal*/

for n = a to 3 step 1 do{
	if(a < 5) then{
		a = 2;
	}else
		a = 5;
	
}
writeln(o+a, 5+4, "banana", k); /*nao aceita concatenacao de string e nem de char*/

/*Erro esperado: nenhum erro*/
