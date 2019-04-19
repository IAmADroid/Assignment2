All you are doing is filling in the missing functions for the driver program to run.

The driver program is the main program, and it will try to call your c code.

Try compiling
------------------

in order to see what it needs, just try compiling it.

>
>     Martin-L-MacBookPro:Assignment2 MartinLDeLaTorre$ gcc -g -o test cs1713p4Driver.c
>     Undefined symbols for architecture x86_64:
>       "_getCourses", referenced from:
>           _main in cs1713p4Driver-b83457.o
>       "_printCourses", referenced from:
>           _main in cs1713p4Driver-b83457.o
>       "_processCourseCommand", referenced from:
>           _processCommands in cs1713p4Driver-b83457.o
>       "_processStudentCommand", referenced from:
>           _processCommands in cs1713p4Driver-b83457.o
>       "_sortCourses", referenced from:
>           _main in cs1713p4Driver-b83457.o
>     ld: symbol(s) not found for architecture x86_64
>     clang: error: linker command failed with exit code 1 (use -v to see invocation)

as you can see, we just need to fill in these functions into cs1713p4.c.

I will be editing the cs1713p4.c provided by the professor and copy pasting code from my cs1713p3.c file.

Actually, since we are working on compiling, let's do it properly. Luckily, the professor gave us instructions on how to do this.

* Compile the driver using  
 gcc -g -c -o cs1713p4Driver.o cs1713p4Driver.c   
 (you can do this instead: gcc -g -c cs1713p4Driver.c causing it to automatically create the cs1713p4Driver.o)   
 
* Compile your code using  
 gcc -g -c -o cs1713p4.o cs1713p4.c   
 (you can do this instead: gcc -g -c cs1713p4.c causing it to automatically create the cs1713p4.o)   
 
* Link them together using:  
 gcc -g -o register cs1713p4Driver.o cs1713p4.o   
 
I am using the professor's compilation instructions, but I put it in a Makefile.
(See Makefile in GitHub repository)

