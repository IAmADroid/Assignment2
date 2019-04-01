reserve: main.o
	cp main.o reserve

main.o: cs1713p2.c cs1713p3.h
	gcc -g -o main.o cs1713p2.c

clean:
	rm reserve main.o
