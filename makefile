arb_test: arb_int.h arb_int.c arb_test.c
	gcc -std=c11 -Wall -Werror -pedantic -o arb_test arb_int.h arb_int.c arb_test.c -lcunit
default: arb_int.h arb_int.c arb_test.c
	gcc -std=c11 -Wall -Werror -pedantic -o arb_test arb_int.h arb_int.c arb_test.c -lcunit
clean: 
	rm -rf arb_test