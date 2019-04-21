/* TEST FILE */

var integer value1, value2, value3;

const VALUE3 = 10;

value1 = 50;
value2 = 30;
value3 = value1 * value2;

value1 = value1 / 5;
value2 = value2 - value1;
value3 = value3 % value2;

write("Value3's value:", value3);
writeln("Value2's value: ", value2);

if value1 <> value2 then writeln("diferente");

for i = 2 to 5 step 2 do {
  write("OI");
  writeln("Valor: ", value1);
}
