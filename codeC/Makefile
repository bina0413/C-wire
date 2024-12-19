all: main
	./main ../tmp/data_tmp2.csv
main: fonction.o main.o
	gcc -o main fonction.o main.o

fonction: fonction.c include.h
	gcc -o fonction.o -c fonction.c -W -Wall -Werror -Wextra -pedantic -std=c99

main.o: main.c include.h
	gcc -o main.o -c main.c -W -Wall -Werror -Wextra -pedantic -std=c99

# ajouter cible clean