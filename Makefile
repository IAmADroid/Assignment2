register: cs1713p4Driver.o cs1713p4.o
	gcc -g -o register cs1713p4Driver.o cs1713p4.o

cs1713p4.o: cs1713p4.c cs1713p4.h
	gcc -g -c -o cs1713p4.o cs1713p4.c

cs1713p4Driver.o: cs1713p4Driver.c
	gcc -g -c -o cs1713p4Driver.o cs1713p4Driver.c

clean:
	rm register cs1713p4Driver.o cs1713p4.o
