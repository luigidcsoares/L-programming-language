/* TEST FILE */
	
Var integer value1;
    integer value2;
    integer value3;
    char    value4,
            value5,
            value6;

value1 = 5;
value2 = 10;
value3 = value1 And value2;
value1 = value3 or value2;
value2 = Not value3;

if value1 = value2 and value2 = 2 then {
    value3 = 5;
} else if value1 < value2 then {
    value3 = 10;
} else {
    value3 = 15;
}

if value3 <= 5 Then
    write("Low value of 'value3': ", value3);
else if value3 >= 6 then
    writeln("Intermediate value of 'value3': ", value3);
else
    writeln("High value of 'value3': ", valu3);

value4 = 0xAF;
value5 = 'c';
value6 = value4 + value5;
