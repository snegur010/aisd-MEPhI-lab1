all:
	gcc -c main.c -o main.o -ftrapv -g -Wall -Wextra -Werror 
	gcc -c lib.c -o lib.o -ftrapv -g -Wall -Wextra -Werror 
	gcc main.o lib.o -o bin -Wall -Wextra -Werror -ftrapv -g 
