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

//Added Headers
CourseNode* makeCourseNode(Course c);
void insertTree(CourseNode** pTree, Course c);
void printFormattedTree(CourseNode *pRoot); // From driver program.
void printCourse(Course c);
void printCoursesHelper(CourseNode* pRoot);

/******************** getCourses **************************************
 int getCourses(CourseNode *pHead)
 Purpose: read courses and their attributes from a file.
 
 Parameters: pszCourseFileName - The file name to read the courses from.
 
 Returns: Returns list of courses with their attributes as a Linked List.
 
 Notes:
 
 **************************************************************************/
CourseNode *getCourses(char * pszCourseFileName)
{
    char szInputBuffer[100];		// input buffer for reading data
    int i = 0;                      // subscript in courseM
    int iScanfCnt;                  // returned by sscanf
    FILE *pFileClasses;             // Stream Input for Courses data.
    
    CourseNode* pTreeRoot = NULL; //change to binary tree
    
    pFileClasses = fopen(pszCourseFileName, "r"); // open file for reading
    if (pFileClasses == NULL)
        exitError(ERR_COURSE_FILENAME, pszCourseFileName);
    
    int numCourses = 0;
    
    
    while(fgets(szInputBuffer, 100, pFileClasses) != NULL){
        //Reads a course and its details from the file and appending to the List
        Course c;
        sscanf(szInputBuffer, "%s %s %s %s %d %lf", c.szCourseId, c.szRoom, c.szDays, c.szTimes, &c.iAvailSeats, &c.dFee);
        numCourses++;
        insertTree(&pTreeRoot, c); //Change to Binary Tree
    }
    
    fclose(pFileClasses);
    
    return pTreeRoot;
    
}
//Added by Martin
void insertTree(CourseNode** pTree, Course c){
    
    CourseNode * pRoot = *pTree;
    if(pRoot == NULL){
        CourseNode * pLast = makeCourseNode(c);
        *pTree = pLast;
        return;
    }
    
    if(strcmp(c.szCourseId, pRoot->course.szCourseId) < 0){
        insertTree(&pRoot->pLeft, c);
    } else if(strcmp(c.szCourseId, pRoot->course.szCourseId) > 0){
        insertTree(&pRoot->pRight, c);
    } else {
        fprintf(stderr, "Duplicate course read\n");
        return;
    }
}
//Added by Martin
CourseNode* makeCourseNode(Course c){
    CourseNode * node = malloc(sizeof(CourseNode));
    node->pLeft = NULL;
    node->pRight = NULL;
    node->course = c;
    return node;
}

/******************** printCourses **************************************
 void printCourses(char *pszHeading, CourseNode *pHead)
 Purpose: Prints the list of courses and its details
 
 Parameters:
 pszHeading - A header to print before printing the list of courses.
 pHead - the List of courses.
 
 Returns: void
 
 Notes: prints to console. It is printing an in order traversal of the tree, so the courses are sorted.
 
 **************************************************************************/
void printCourses(char *pszHeading, CourseNode *pRoot)
{
    int i;
    printf("%s\n\n", pszHeading);
    printf("****************************************** Courses ******************************************\n");
    printf("%-15s%-15s%-15s%-15s%-6s%-6s\n", "Course ID","Room Number","Days","Times","Seats","Fees");

    printCoursesHelper(pRoot);
    printf("\n");

}
/**
 * Added By Martin
 */
void printCoursesHelper(CourseNode* pRoot){
    if(pRoot == NULL){
        return;
    }
    printCoursesHelper(pRoot->pLeft);
    printCourse(pRoot->course);
    printCoursesHelper(pRoot->pRight);
}
/**
 * Added By Martin
 * Prints an individual course
 */
void printCourse(Course c){
    //Professor, what's with the weird spacing?
    printf("%-12s   %-15s%-8s       %-15s%-5d %-10.2lf\n", c.szCourseId, c.szRoom, c.szDays, c.szTimes, c.iAvailSeats, c.dFee);
}

/******************** printTree **************************************
 void printTree(CourseNode *pRoot)
 Purpose:
 prints a binary tree formatted to show structure.
 
 Parameters:
 I   CourseNode *pRoot           Root of the tree to be printed
 
 Notes:
 This function uses the printFormattedTree function from the driver program.
 **************************************************************************/
void printTree(CourseNode *p)
{
    printFormattedTree(p); // Method from Driver Program.
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
void processStudentCommand(CourseNode *pHead
    , char *pszSubCommand, char *pszRemainingInput
    , Student *pStudent, double *pdStudentRequestTotalCost)
{
    int iScanfCnt;
    CourseRequest courseRequest;

    // Determine what to do based on the subCommand
    if (strcmp(pszSubCommand, "BEGIN") == 0)
    {
        // get the Student Identification Information
        Student joe;
        //initialize to 0
        memset(&joe, 0, sizeof(Student));
        *pStudent = joe;
        *pdStudentRequestTotalCost = 0;
        
        sscanf(pszRemainingInput, "%s %c %s %s", pStudent->szStudentId, &pStudent->cGender, pStudent->szBirthDt,pStudent->szFullName);
        
        
        
        // remember to validate the data
        
    }
    else if (strcmp(pszSubCommand, "INFO") == 0)
    {
        // get the student information
        sscanf(pszRemainingInput, "%s,%s,%lf,%c", pStudent->szMajor, pStudent->szEmail, &pStudent->dGpa,&pStudent->cInternationalStudent);
        
        
    }
    else if (strcmp(pszSubCommand, "COMPLETE") == 0 || strcmp(pszSubCommand, "COMPLETE\r") == 0)
    {
        // print the student's total cost
        printf("Total Fees: $%.2lf\n", *pdStudentRequestTotalCost);
        
        return;
        
        //TODO: save student to a list somewhere.
    }
    else if (strcmp(pszSubCommand, "REGISTER") == 0)
    {
        CourseNode * pFound;
        // get a course request
        sscanf(pszRemainingInput, "%s", courseRequest.szCourseId);
        
        // find the course in the array
        pFound = search(pHead, courseRequest.szCourseId);
        
        //Check if course was not found then print error.
        if(pFound == NULL){
            printf("   *** %s %s\n", ERR_COURSE_NOT_FOUND, courseRequest.szCourseId);
            return;
        }
        //Check if course has no open seats then print error.
        else if(pFound->course.iAvailSeats < 1){
            printf("   *** %s %s\n", ERR_TOO_FEW_SEATS, courseRequest.szCourseId);
            return;
        }
        
        //Course was found, and has seats, so now we edit it!
        *pdStudentRequestTotalCost += pFound->course.dFee;
        pFound->course.iAvailSeats--;
        
    }
    //Student sub command was not recognized; print error.
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
        COURSE TPRINT
               This prints the binary tree in a structured format. The code for this
               print is provided in the driver, this code will simply call printFormattedTree
               through the printTree method.
Parameters:
    I/O CourseNode *pRoot              Tree of courses
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
    char szCourseId[12];
    CourseNode * pFound = NULL;
    
    if (strcmp(pszSubCommand, "SHOW") == 0){
        //Process show subcommand
        //printf("SHOW not yet implemented. needs SEARCH\n");
        
        
        sscanf(pszRemainingInput, "%s", szCourseId);
        
        pFound = search(pRoot, szCourseId);
        
        if(pFound == NULL){
            printf("   *** %s %s\n", ERR_COURSE_NOT_FOUND, szCourseId);
            return;
        }
        
        printCourse(pFound->course);
        
    }
    else if (strcmp(pszSubCommand, "INCREASE") == 0)
    {
        //Process increase subcommand
        //printf("Increase not yet implemented. needs SEARCH\n");
        
        sscanf(pszRemainingInput, "%s %d", szCourseId, &iQuantity);
        
        pFound = search(pRoot, szCourseId);
        
        if(pFound == NULL){
            printf("   *** %s %s\n", ERR_COURSE_NOT_FOUND, szCourseId);
            return;
        }
        
        pFound->course.iAvailSeats = pFound->course.iAvailSeats + iQuantity;
    }
    else if (strcmp(pszSubCommand, "TPRINT") == 0 || strcmp(pszSubCommand, "TPRINT\r") == 0)
    {
        printTree(pRoot);
    }
    //If command type was not found, print an error
    else printf("   *** %s %s\n", ERR_COURSE_SUB_COMMAND, pszSubCommand);
}
/******************** search *****************************
    CourseNode * search(CourseNode *pRoot, char *pszMatchCourseId)
Purpose: searches the binary tree for a course that matches pszMatchCourseId.
    
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
    if(pRoot == NULL){
        return NULL; //Course not found
    }
    if(strcmp(pszMatchCourseId, pRoot->course.szCourseId) < 0){
        return search(pRoot->pLeft, pszMatchCourseId);
    }
    if(strcmp(pszMatchCourseId, pRoot->course.szCourseId) > 0){
        return search(pRoot->pRight, pszMatchCourseId);
    }
    if(strcmp(pszMatchCourseId, pRoot->course.szCourseId) == 0){
        return pRoot; //We found it!
    }
    fprintf(stderr, "This part is unreachable, how did you get here?\n");
    return NULL;
}
