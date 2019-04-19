reserve: main.o
	cp main.o reserve

main.o: cs1713p4.c cs1713p2.h
	gcc -g -o main.o cs1713p4.c

clean:
	rm reserve main.o
