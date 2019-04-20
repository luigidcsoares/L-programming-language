

var integer n1 = '1', n2 = '1';
integer temp, i;

for i = 3 to 10 do {
    temp = n1;
    n1 = n2;
    n2 = n2 + temp;
}

falhaaqui("O numero de fibonacci de 10 e", n2);