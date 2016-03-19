all:	shell

lab2: shell.o argtok.o exec.o
	gcc shell.o argtok.o exec.o -o shell

htejada_lab2.o:	shell.c argtok.h
	gcc -c shell.c

htejada_argtok.o:	argtok.c argtok.h
	gcc -c argtok.c

htejada_exec.o:	exec.c exec.h
	gcc -c exec.c

clean:
	rm *.o shell
