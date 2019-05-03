register: cs1713p5Driver.o cs1713p5.o
	gcc -g -o register cs1713p5Driver.o cs1713p5.o

cs1713p5.o: cs1713p5.c cs1713p5.h
	gcc -g -c -o cs1713p5.o cs1713p5.c

cs1713p5Driver.o: cs1713p5Driver.c
	gcc -g -c -o cs1713p5Driver.o cs1713p5Driver.c

clean:
	rm register cs1713p4Driver.o cs1713p4.o
