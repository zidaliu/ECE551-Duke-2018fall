myProgram:test-power.o power.o
	gcc -o myProgram test-power.o power.o
test_power.o:test-power.c
	gcc -std=gnu99 -Wall -pedantic -Werror -c test-power.c 
power.o:power.c
	gcc -std=gnu99 -Wall -pedantic -Werror -c power.c
