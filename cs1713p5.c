/***********************************************************************************
cs1713p3.c by your name   (skeletal version)
Purpose:
    This program reads course information and a command file.   It 
    processes the commands against the course information.
    This is the driver code for the routines written by the students.
Command Parameters:
    p3 -f courseFileName -c commandFileName
Input:
    Course   Stream input file which contains many records defining courses:
                 szCourseId szRoom  szDays  szTimes     iAvailSeats dFee 
                 10s        3s      3s      5s          4d          10lf 

    Command  This is different from the previous assignment.  The file contains 
             text in the form of commands (one command per text line):  
                 STUDENT BEGIN szStudentId cGender szBirthDate szFullName 
                     specifies the beginning of student request and includes 
                     all the identification information from program 3.
                 STUDENT INFO szMajor,szEmail,dGpa,cInternationalStudent ( Y or N )
                     specifies the address for a student (separated by commas)
                 STUDENT REQUEST szCourseId
                    specifies a single course request.  Steps:
                     >	Print the course ID and requested number of seats
                     >	Lookup the course ID, If not found, print a warning (but do not terminate your program) and return.
                     >	If found, try to satisfy the request.  
                        If not enough seats,  print a warning and return.
                     >	Print the fees.
                     >	Accumulate the total fees for this student
                 STUDENT COMPLETE
                     specifies the completion of the list of course requests 
                     for a student.
                 COURSE INCREASE szCourseId
                     increase the available seats for a course by the specified quantity.
                 COURSE SHOW szCourseId    
                     requests a display of a particular course.  Show all of its information.

Results:
    Prints the Courses prior to sorting
    Prints the Course after sorting.
    Processes the commands (see above) and shows any errors.
    Prints the resulting Courses
Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information

Notes:
    p3 -?       will provide the usage information.  In some shells,
                you will have to type p3 -\?

**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p5.h"

/******************** getCourses **************************************
    int getCourses(CourseNode *pRoot)
Purpose:

Parameters:
  
Returns:
    
Notes:
    
**************************************************************************/
CourseNode *getCourses(char * pszCourseFileName)
{
    char szInputBuffer[100];		// input buffer for reading data
    int i = 0;                      // subscript in courseM
    int iScanfCnt;                  // returned by sscanf
    FILE *pFileCourse;              // Stream Input for Courses data. 
    CourseNode *pRoot = NULL;
    /* open the Courses stream data file */
    if (pszCourseFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-f");

    pFileCourse = fopen(pszCourseFileName, "r");
    if (pFileCourse == NULL)
        exitError(ERR_COURSE_FILENAME, pszCourseFileName);

    /* get course information until EOF
    ** fgets returns null when EOF is reached.
    */

    /**** your code ******/

    fclose(pFileCourse);
    return pRoot;

}

/******************** printCourses **************************************
    void printCourses(char *pszHeading, CourseNode *pRoot)
Purpose:

Parameters:
  
Returns:
    
Notes:
    
**************************************************************************/
void printCourses(char *pszHeading, CourseNode *pRoot)
{
    int i;
    printf("%s\n", pszHeading);
    printf("****************************************** Courses ******************************************\n");
    printf("%-15s%-15s%-15s%-15s%-6s%-6s\n", "Course ID","Room Number","Days","Times","Seats","Fees");

    /* Your code to print the tree here */

}

/******************** printTree **************************************
    void printTree(CourseNode *p);
Purpose:

Parameters:
  
Returns:
    
Notes:
    
**************************************************************************/
void printTree(CourseNode *p)
{
    
}

/********************processStudentCommand *****************************
    void processStudentCommand(CourseNode *pRoot
     , char *pszSubCommand, char *pszRemainingInput
     , Student *pStudent, double *pdStudentRequestTotalCost )
Purpose:
    Processes the subcommands associated with the STUDENT command:
                 STUDENT BEGIN cGender   szBirthDt   szEmailAddr    szFullName
                     specifies the beginning of student request and includes 
                     all the identification information from program 2.
                 STUDENT INFO szMajor,szEmail,dGpa,cInternationalStudent ( Y or N )
                     specifies the address for a student (separated by commas)
                 STUDENT REGISTER szCourseId
                     specifies a single course request.  Steps:
                     >	Print the course ID
                     >	Lookup the course ID. If not found, 
                        print a warning (but do not terminate your program) and return.
                     >	If found, try to satisfy the request, 
                        If not enough seats, print a warning and return.
                     >	Print the unit price and cost.
                     >	Accumulate the total cost for this student

                 STUDENT COMPLETE
                     specifies the completion of the tree of course requests 
                     for a student.
Parameters:
    I/O CourseNode *pRoot              Tree of courses
    I   char  *pszSubCommand          Should be BEGIN, INFO, REGISTER or COMPLETE
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
    I/O Student *pStudent           The BEGIN subcommand begins a new student.  The 
                                      student's Request Total Cost must be set to 0.
    I/O double   *pdStudentRequestTotalCost     The student total cost.  This changes depending
                                      on the subcommand:
                                          BEGIN - set to 0
                                          REGISTER - add the cost  (unless there is a warning) 
Notes:

**************************************************************************/
void processStudentCommand(CourseNode *pRoot
    , char *pszSubCommand, char *pszRemainingInput
    , Student *pStudent, double *pdStudentRequestTotalCost)
{
    int iScanfCnt;
    CourseRequest courseRequest;

    // Determine what to do based on the subCommand
    if (strcmp(pszSubCommand, "BEGIN") == 0)
    {
        // get the Student Identification Information
        // your code

        if (iScanfCnt < 4)
            exitError(ERR_STUDENT_ID_DATA, pszRemainingInput);

    }
    else if (strcmp(pszSubCommand, "INFO") == 0)
    {
        // get the student information
        // your code 

  
    }
    else if (strcmp(pszSubCommand, "COMPLETE") == 0)
    {
        // print the student's total cost
        // your code 

    }
    else if (strcmp(pszSubCommand, "REGISTER") == 0)
    {
        CourseNode * pFound;
        // get a course request
        // your code 


        // find the course in the array
        pFound = search(pRoot, courseRequest.szCourseId);

        // your code

  
    }
    else printf("   *** %s %s\n", ERR_STUDENT_SUB_COMMAND, pszSubCommand);
}
/********************processCourseCommand *****************************
    void processCourseCommand(CourseNode *pRoot
         , char *pszSubCommand, char *pszRemainingInput)
Purpose:
    Processes the subcommands associated with the COURSE command:
        COURSE INCREASE szCourseId iQuantity
               increase the available seats for a course by the specified quantity.
        COURSE SHOW szCourseId    
               requests a display of a particular course.  Show all of its information.
Parameters:
    I/O CourseNode *pRoot              Tree of courses
    I   int   iCourseCnt              Number of elments in pRoot
    I   char  *pszSubCommand          Should be INCREASE or SHOW
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
Notes:

**************************************************************************/
void processCourseCommand(CourseNode *pRoot
                             , char *pszSubCommand, char *pszRemainingInput)
{
    Course course;
    int iQuantity;      // quantity of seats 
    int iScanfCnt;
    int i;

    // Determine what to do based on the subCommand
    // your code

}
/******************** search *****************************
    CourseNode * search(CourseNode *pRoot, char *pszMatchCourseId)
Purpose:
    
Parameters:
    I   CourseNode *pRoot              Tree of courses
    I   char *pszMatchCourseId         Course Id to find in the tree
Returns:
    CourseNode*     pointer to course node
    NULL            not found
Notes:

**************************************************************************/
CourseNode * search(CourseNode *pRoot, char *pszMatchCourseId)
{
    // your code


}