all: build 
build: main.c othello.c othello.h othello_archivos.c othello_archivos.h
	gcc -o ../main main.c othello_archivos.c othello.c -Wall -Wextra -Wpedantic -Wformat=2 -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -O2
test: test.c othello.c othello.h othello_archivos.c othello_archivos.h
	gcc -o ../test test.c othello.c othello_archivos.c
run:
	../main
