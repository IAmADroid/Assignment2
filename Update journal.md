Assignment 4:
------------
------------

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

Alright. After *compiling properly*, and running the program with
>
>     ./register -c p4Command.txt -f p4Courses.txt

Then I got this output:

    Initial Courses
    ****************************************** Courses ******************************************
    Course ID      Room Number    Days           Times          Seats Fees  
    You called the sort courses method, please delete this msg.Sorted Courses
    ****************************************** Courses ******************************************
    Course ID      Room Number    Days           Times          Seats Fees  
    STUDENT BEGIN pte357 M 1986/01/01 Pete Moss
    STUDENT INFO CS,pte357@my.uni.edu,3.20,N
    STUDENT REGISTER HIS1043.002    
    You called the search method, please delete this msg.STUDENT REGISTER GEO1013.005
    You called the search method, please delete this msg.STUDENT REGISTER MAT1214.003
    You called the search method, please delete this msg.STUDENT REGISTER CS1713.002
    You called the search method, please delete this msg.STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    STUDENT BEGIN agt352 M 1957/02/02 Pop Corn
    STUDENT INFO MAT,agt352@my.uni.edu,2.8,N
    STUDENT REGISTER HIS1043.002
    You called the search method, please delete this msg.STUDENT REGISTER ENG1023.003
    You called the search method, please delete this msg.STUDENT REGISTER ART3023.001
    You called the search method, please delete this msg.STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    COURSE INCREASE MAT1214.003 15
    You called the process course command method, please delete this msg.COURSE SHOW MAT1214.003
    You called the process course command method, please delete this msg.STUDENT BEGIN geh582 F 1958/03/03 Penny Loafer
    STUDENT INFO CS,pennyl@xyz.net,3.5,N
    STUDENT REGISTER MAT1214.003
    You called the search method, please delete this msg.STUDENT REGISTER CS1713.002
    You called the search method, please delete this msg.STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    STUDENT BEGIN sen233 M 1979/04/04 Adam Sandler
    STUDENT INFO ENG,hgilmore@xyz.net,2.93,Y
    STUDENT REGISTER ENG1023.001
    You called the search method, please delete this msg.STUDENT REGISTER GEO1013.005
    You called the search method, please delete this msg.STUDENT REGISTER MAT3013.001
    You called the search method, please delete this msg.STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    COURSE SHOW MAT3013.001
    You called the process course command method, please delete this msg.STUDENT BEGIN fse234 F 1989/05/05 Melba Toast
    STUDENT INFO BIO,butter@xyz.net,2.03,N
    STUDENT REGISTER CS1713.002
    You called the search method, please delete this msg.STUDENT REGISTER ENG1023.001
    You called the search method, please delete this msg.STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    COURSE INCREASE HIS1043.004 10
    You called the process course command method, please delete this msg.COURSE SHOW HIS1043.004
    You called the process course command method, please delete this msg.COURSE SHOW CS1713.002
    You called the process course command method, please delete this msg.COURSE SHOW ART2113.001
    You called the process course command method, please delete this msg.STUDENT BEGIN bob420 M 1942/08/29 Bob Ross
    STUDENT INFO ART,happylittlecloud@yourworld.net,4.0,N
    STUDENT REGISTER ART2113.001
    You called the search method, please delete this msg.STUDENT REGISTER ART3023.001
    You called the search method, please delete this msg.STUDENT COMPLETEResulting Courses
    ****************************************** Courses ******************************************
    Course ID      Room Number    Days           Times          Seats Fees
    
As you can see, it is filled with `You called the <blabla> method, please delete this msg.`
That is where we will put our methods.

The getCourses Method
------------------

Before we can do anything useful, we have to read in some courses. so let us edit the getCourses method in cs1713p4.c

I would copy paste it verbatim from cs1713p3.c to cs1713p4.c, but since I haven't been following the professor, His code is formatted differently than mine.

Assuming you've been following the professor, you can probably copy it exactly.

Let me show you some of the problems I'm having:

My code (cs1713p3.c):
>
>     int getCourses(CourseNode** courseLinked)

Professor's code (cs1713p4.c):
>
>     CourseNode *getCourses(char * pszCourseFileName)

As you can see, my code edits the linked list through the parameters, while the professor returns the new linked list.

Mine also reads the file through a global variable, while the professor takes the file through the parameters. So I also have to open the file myself, like so:
>
>     FILE *pFileClasses;
>     pFileClasses = fopen(pszCourseFileName, "r"); // open file for reading
>     if (pFileClasses == NULL)
>         exitError(ERR_COURSE_FILENAME, pszCourseFileName);

So yeah. just a bunch of copy pasting with minor adjustments.
*Check that your copy pasted code isn't calling other functions. If it is, copy those functions over too. and don't forget the method signature at the top.*

Also throw this in the end of `getCourses`:
>
>     fclose(pFileClasses);

**Notice: I called the File `pFileClasses`. you might have called it `pFileCourses` or something else entirely.**




