# L

## Definição da Linguagem

A linguagem "L" é uma linguagem imperativa simplificada, com características do
C e Pascal. A linguagem oferece tratamento para 2 tipos básicos explícitos:
char e integer, além do tipo lógico que é implícito. O tipo char é um escalar
que varia de 0 a 255, podendo ser escrito em formato alfanumérico ou
hexadecimal. Constantes em formato hexadecimal são da forma 0xDD, onde DD é um
número hexadecimal. Constantes em formato alfanumérico são da forma ‘c’ onde
c é um caractere imprimível. O tipo integer é um escalar que varia de –32768
a 32767, ocupando 2 bytes. Além dos tipos básicos a linguagem permite
a definição de vetores unidimensionais de caracteres e inteiros, com até
4 kB. Um string é um vetor de caracteres que quando armazenado em memória,
tem seu conteúdo útil finalizado pelo caracter '\$'. Constantes que representam
strings são delimitadas por aspas e não devem conter aspas, quebra de linha ou
\$. Entretanto, esses caracteres são permitidos nos vetores de caracteres.
Dessa forma, vetores e strings são compatíveis entre si, ficando a cargo do
programador o controle dos seus conteúdos e tamanhos. tipo lógico assume
valores 0 (falso) e 1 (verdadeiro), ocupando um byte de memória.

Os caracteres permitidos em um arquivo fonte são as letras, dígitos, espaço,
sublinhado, ponto, vírgula, ponto-e-vírgula, e_comercial, dois-pontos,
parênteses, colchetes, chaves, mais, menos, aspas, apóstrofo, barra,
porcentagem, circunflexo, arroba, exclamação, interrogação, maior, menor
e igual, além da quebra de linha (bytes 0Dh e 0Ah). Qualquer outro caractere
é considerado inválido. Os identificadores de constantes e variáveis são
compostos de letras, dígitos, sublinhado e ponto, não podem começar com
dígitos, nem conter apenas sublinhados ou pontos, e têm no máximo 255
caracteres. Maiúsculas e minúsculas não são diferenciadas.

As seguintes palavras e suas variações com maiúsculas e minúsculas são reservadas:


|       |         |         |        |        |       |
|:-----:|:-------:|:-------:|:------:|:------:|:-----:|
| const | var     | integer | char   | for    | if    | 
| else  | and     | or      |  not   |  =     | to    |
| (     | )       | <       | >      | <>     | >=    | 
| <=    | ,       | +       | -      | *      | /     | 
| ;     |  {      | }       | then   | readln | step  | 
| write | writeln | %       | [      | ]      | do    |

Os comandos existentes em "L" permitem atribuição a variáveis através do
operador =, entrada de valores pelo teclado e saída de valores para a tela,
estruturas de repetição (repita para), estruturas de teste (se \- então \-
senão), expressões aritméticas com inteiros e caracteres, expressões lógicas
e relacionais, manipulação de vetores, além de atribuição e comparação de
igualdade entre strings. A ordem de precedência nas expressões é:

1. Parênteses;
1. Negação lógica (not);
1. Multiplicação aritmética (\*) e lógica (and), quociente da divisão (/)
   e resto da divisão (%);
1. Subtração (-), adição aritmética (+) e lógica ( or );
1. Comparação aritmética (=, <>, <, >, <=, >=) e entre strings (=).

Comentários são delimitados por /\* \*/. A quebra de linha e o espaço podem ser
usados livremente como delimitadores de lexemas.

A estrutura básica de um programa fonte é da forma:

<center> 

**Declaraçoes Bloco_de_Comandos Fim_Arquivo**

</center>

## Descrição da Linguagem

1. Declaração de variáveis: inicia-se pela palavra reservada _Var_, à qual
   seguem-se uma ou mais listas de declarações da forma: _tipo lista-de-ids;_
   , onde _tipo_ pode ser _integer_ ou _char_ e _lista-de-ids_ é uma série de 1 ou mais
   identificadores de escalares ou vetores, separados por vírgulas. Variáveis
   escalares podem ser opcionalmente inicializadas na forma: _id = valor_, onde
   _id_ é um identificador. Para inteiros, _valor_ é uma constante decimal
   precedida ou não de sinal negativo; Para caractere, uma constante
   hexadecimal ou alfanumérica. Declarações de vetores são da forma _id[tam]_,
   onde _tam_ é uma constante inteira maior que 0. O tamanho em bytes de um vetor
   não pode ultrapassar 4 kB. Vetores não podem ser inicializados na
   declaração.

1. Declaração de constantes escalares: é da forma: _const id = valor;_ , onde _id_
   é um identificador e valor uma constante numérica, precedida ou não de sinal
   negativo, hexadecimal ou caractere alfanumérico.

1. Comando de atribuição: é da forma _id = expressão;_ ou _id[expressão]
   = expressão_;

1. Comando de repetição: pode assumir duas formas: 

    _For id = expressão to expressão step constante do comando_ \
    _For id = expressão to expressão step constante do { comandos }_

    onde _expressão_ e _constante_ são do tipo inteiro e _comandos_ é uma lista de
    zero ou mais comandos da linguagem. A definição de step é opcional, sendo
    1 se não estiver especificada.

1. Comando de teste: pode assumir as formas, onde _expressão_ é do tipo lógico:

   _if expressão then comando1_ \
   _if expressão then comando1 else comando2_

   _comando1_ e/ou _comando2_ podem ser independentemente substituídos por blocos
   da forma: 

   _if expressão then { lista_comandos1 } else { lista_comandos2 }_ 

   onde as listas são sequências de comandos.

1. Comando nulo: é da forma ; . Nada é executado neste comando.

1. Comando de leitura: é da forma _readln(id)_; , onde _id_ é um identificador de
   variável inteira, caractere alfanumérico ou string. Caracteres e strings são
   lidos da mesma maneira, sem que o usuário precise colocá-los entre aspas ou
   apóstrofos. Números inteiros podem ter sinal negativo.

1. Comandos de escrita: são da forma _write(lista_expressões)_; ou _writeln(
   lista_expressões)_;, onde _lista_expressões_ é uma lista de uma ou mais
   expressões inteiras, caracteres ou strings, separadas por vírgulas. A última
   forma, quando executada, causa a quebra de linha após a impressão.
