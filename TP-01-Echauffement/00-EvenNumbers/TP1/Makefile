compile: tp1_nombre_parfait.c
	gcc -W -Wall -std=c99 -o tp1_nombre_parfait tp1_nombre_parfait.c

test_nombre_parfait: tp1_nombre_parfait
	./tp1_nombre_parfait 500

test_factorielle_short: factorielle.c
	gcc -W -Wall -std=c99 -o factorielle_short factorielle.c
	./factorielle_short

test_factorielle_ull: factorielle.c
	gcc -W -Wall -std=c99 -o factorielle_ull -DULL_TYPE_ENTIER factorielle.c
	./factorielle_ull

