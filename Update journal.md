Assignment 4:
==============

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
----------------------------

Before we can do anything useful, we have to read in some courses. so let us edit the `getCourses` method in cs1713p4.c

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

The printCourses Method
------------------------------
It is important to be able to see what we are doing as early as possible. So we should make a function to print to the console.

the professor already has some code in cs1713p4.c, so we just have to build off of that.
He has marked where we needed to put our code inside the printCourses method. (see the cs1713p4.c skeleton code provided by the professor)

the code already in the function just prints this:

    <bla bla stuff from driver program>
    ************************************ Courses ************************************
    Course ID    Room Number     Days     Times           Seats Fees  

We are just printing this part:

    HIS1043.002  MH2.102         MWF      1:00-1:50pm     120   35.00     
    GEO1013.005  MB1.101         TR       12:30-1:45pm    5     35.00     
    MAT1214.003  MS1.02.03       TR       2:00-3:15pm     1     35.00     
    CS1713.002   NPB1.202        MWF      1:00-1:50pm     0     50.00     
    MAT3013.001  MS1.02.07       TR       2:00-3:15pm     1     35.00     
    ENG1023.001  MH2.202         MWF      10:00-10:50am   15    35.00  

So just traverse the list and print the course info from each course. 
For reference: here is how I am printing out an individual course:

    void printCourse(Course c){
        printf("%-12s %-15s %-8s %-15s %-5d %-10.2lf\n", c.szCourseId, c.szRoom, c.szDays, c.szTimes, c.iAvailSeats, c.dFee);
    }
You have to traverse and print each course.

Test 1
---------
We don't want to run hundreds of lines of code without a single test! That's begging for future punishment.

Copy this code into "cs1713p4.c":

    //This is test code. It should be deleted.
    int main(int argc, char *argv[]){
        CourseNode* head = getCourses("p4Courses.txt");
        printCourses("This is Test numero uno",head);
        
        return (0);
    }
Then compile with: `gcc -g -o test cs1713p4.c` 

run it with: `./test` 

You should get this as your output:

    This is Test numero uno
    ****************************************** Courses ******************************************
    Course ID      Room Number    Days           Times          Seats Fees  
    HIS1043.002  MH2.102         MWF      1:00-1:50pm     120   35.00     
    GEO1013.005  MB1.101         TR       12:30-1:45pm    5     35.00     
    MAT1214.003  MS1.02.03       TR       2:00-3:15pm     1     35.00     
    CS1713.002   NPB1.202        MWF      1:00-1:50pm     0     50.00     
    MAT3013.001  MS1.02.07       TR       2:00-3:15pm     1     35.00     
    ENG1023.001  MS1.02.07       MWF      10:00-10:50am   15    35.00     
    ART2113.001  AR4.01          TR       11:30-12:45pm   10    45.00     
    ART3023.001  AR4.04          MWF      12:00-1:50pm    7     35.00     

If you get the courses in a different order, that is okay, since we will sort them later anyway. 

For me, My program didn't compile, because my `getCourses` was calling `exitError`, which was undefined. I just had to copy paste those functions in.

**Remember to delete the test code you added**

The search Method
---------------------------------
Next method up on the list! Gotta make it! 

Look for the method stub in "cs1713p4.c": 
`CourseNode * search(CourseNode *pHead, char *pszMatchCourseId)` 

This is where we put our code. We just have to iterate through the linked list specified by `pHead`, check for a match with `pszMatchCourseId`, and return the corresponding `CourseNode`.

Now when we compile and run, we should get: (See section titled "Try compiling" for instructions on compiling and running.)

    Initial Courses
    ****************************************** Courses ******************************************
    Course ID      Room Number    Days           Times          Seats Fees  
    HIS1043.002  MH2.102         MWF      1:00-1:50pm     120   35.00     
    GEO1013.005  MB1.101         TR       12:30-1:45pm    5     35.00     
    MAT1214.003  MS1.02.03       TR       2:00-3:15pm     1     35.00     
    CS1713.002   NPB1.202        MWF      1:00-1:50pm     0     50.00     
    MAT3013.001  MS1.02.07       TR       2:00-3:15pm     1     35.00     
    ENG1023.001  MS1.02.07       MWF      10:00-10:50am   15    35.00     
    ART2113.001  AR4.01          TR       11:30-12:45pm   10    45.00     
    ART3023.001  AR4.04          MWF      12:00-1:50pm    7     35.00     
    You called the sort courses method, please delete this msg.Sorted Courses
    ****************************************** Courses ******************************************
    Course ID      Room Number    Days           Times          Seats Fees  
    HIS1043.002  MH2.102         MWF      1:00-1:50pm     120   35.00     
    GEO1013.005  MB1.101         TR       12:30-1:45pm    5     35.00     
    MAT1214.003  MS1.02.03       TR       2:00-3:15pm     1     35.00     
    CS1713.002   NPB1.202        MWF      1:00-1:50pm     0     50.00     
    MAT3013.001  MS1.02.07       TR       2:00-3:15pm     1     35.00     
    ENG1023.001  MS1.02.07       MWF      10:00-10:50am   15    35.00     
    ART2113.001  AR4.01          TR       11:30-12:45pm   10    45.00     
    ART3023.001  AR4.04          MWF      12:00-1:50pm    7     35.00     
    STUDENT BEGIN pte357 M 1986/01/01 Pete Moss
    STUDENT INFO CS,pte357@my.uni.edu,3.20,N
    STUDENT REGISTER HIS1043.002    
    STUDENT REGISTER GEO1013.005
    STUDENT REGISTER MAT1214.003
    STUDENT REGISTER CS1713.002
    STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    STUDENT BEGIN agt352 M 1957/02/02 Pop Corn
    STUDENT INFO MAT,agt352@my.uni.edu,2.8,N
    STUDENT REGISTER HIS1043.002
    STUDENT REGISTER ENG1023.003
    STUDENT REGISTER ART3023.001
    STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    COURSE INCREASE MAT1214.003 15
    You called the process course command method, please delete this msg.COURSE SHOW MAT1214.003
    You called the process course command method, please delete this msg.STUDENT BEGIN geh582 F 1958/03/03 Penny Loafer
    STUDENT INFO CS,pennyl@xyz.net,3.5,N
    STUDENT REGISTER MAT1214.003
    STUDENT REGISTER CS1713.002
    STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    STUDENT BEGIN sen233 M 1979/04/04 Adam Sandler
    STUDENT INFO ENG,hgilmore@xyz.net,2.93,Y
    STUDENT REGISTER ENG1023.001
    STUDENT REGISTER GEO1013.005
    STUDENT REGISTER MAT3013.001
    STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    COURSE SHOW MAT3013.001
    You called the process course command method, please delete this msg.STUDENT BEGIN fse234 F 1989/05/05 Melba Toast
    STUDENT INFO BIO,butter@xyz.net,2.03,N
    STUDENT REGISTER CS1713.002
    STUDENT REGISTER ENG1023.001
    STUDENT COMPLETE
       *** invalid STUDENT subcommand  COMPLETE
    COURSE INCREASE HIS1043.004 10
    You called the process course command method, please delete this msg.COURSE SHOW HIS1043.004
    You called the process course command method, please delete this msg.COURSE SHOW CS1713.002
    You called the process course command method, please delete this msg.COURSE SHOW ART2113.001
    You called the process course command method, please delete this msg.STUDENT BEGIN bob420 M 1942/08/29 Bob Ross
    STUDENT INFO ART,happylittlecloud@yourworld.net,4.0,N
    STUDENT REGISTER ART2113.001
    STUDENT REGISTER ART3023.001
    STUDENT COMPLETEResulting Courses
    ****************************************** Courses ******************************************
    Course ID      Room Number    Days           Times          Seats Fees  
    HIS1043.002  MH2.102         MWF      1:00-1:50pm     120   35.00     
    GEO1013.005  MB1.101         TR       12:30-1:45pm    5     35.00     
    MAT1214.003  MS1.02.03       TR       2:00-3:15pm     1     35.00     
    CS1713.002   NPB1.202        MWF      1:00-1:50pm     0     50.00     
    MAT3013.001  MS1.02.07       TR       2:00-3:15pm     1     35.00     
    ENG1023.001  MS1.02.07       MWF      10:00-10:50am   15    35.00     
    ART2113.001  AR4.01          TR       11:30-12:45pm   10    45.00     
    ART3023.001  AR4.04          MWF      12:00-1:50pm    7     35.00 
    
Notice how we have less complaints than we did at the beggining? (The stuff formatted like `You called the <blabla> method, please delete this msg.`) 
    
My program actually got stuck here, I found out I had forgotten to traverse in my `search` method.



