reserve: main.o
	cp main.o reserve

main.o: cs1713p1.c cs1713p2.h
	cc -o main.o cs1713p1.c

clean:
	rm reserve main.o
