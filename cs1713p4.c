/***********************************************************************************
cs1713p4.c by your name   (skeletal version)
Purpose:
    This program reads course information and a command file.   It 
    processes the commands against the course information.
    This is the driver code for the routines written by the students.
Command Parameters:
    p4 -f courseFileName -c commandFileName
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
#include "cs1713p4.h"


//Added method signatures
CourseNode* makeCourseNode(Course c);
void addLast(CourseNode** root, Course c);

void printCourse(Course c);

CourseNode* mergeSort(CourseNode* pHead);
CourseNode** split(CourseNode* pHead);
CourseNode* merge(CourseNode * pHead1, CourseNode * pHead2);


/******************** getCourses **************************************
    int getCourses(CourseNode *pHead)
Purpose: read courses and their attributes from a file.

Parameters: pszCourseFileName - The file name to read the courses from.
  
Returns: Returns list of courses with their attributes as a Linked List.
    
Notes:
    
**************************************************************************/
CourseNode *getCourses(char * pszCourseFileName)
{
    CourseNode* answer = NULL;
    
    CourseNode** courseLinked = &answer;
    
    FILE *pFileClasses;               // stream Input for Classes data
    
    pFileClasses = fopen(pszCourseFileName, "r"); // open file for reading
    if (pFileClasses == NULL)
        exitError(ERR_COURSE_FILENAME, pszCourseFileName);

    char szInputBuffer[100];
    int numCourses = 0;
    
    
    while(fgets(szInputBuffer, 100, pFileClasses) != NULL){
        //Reads a course and its details from the file and appending to the List
        Course c;
        sscanf(szInputBuffer, "%s %s %s %s %d %lf", c.szCourseId, c.szRoom, c.szDays, c.szTimes, &c.iAvailSeats, &c.dFee);
        numCourses++;
        addLast(courseLinked, c);
    }
    
    fclose(pFileClasses);
    
    return answer;

}

//Added by Martin
void addLast(CourseNode** pLL, Course c){
    CourseNode * root = *pLL;
    
    CourseNode* last = makeCourseNode(c);
    
    if(root != NULL){
        
        while(root->pNext != NULL){
            root = root->pNext;
        }
        
        root->pNext = last;
    } else {
        *pLL = last;
    }
    
}
//Added by Martin
CourseNode* makeCourseNode(Course c){
    CourseNode * node = malloc(sizeof(CourseNode));
    node->pNext = NULL;
    node->course = c;
    return node;
}
/******************** sortCourses **************************************
    void sortCourses(CourseNode *pHead)
Purpose:

Parameters:
  
Returns:
    
Notes:
    
**************************************************************************/
void sortCourses(CourseNode **ppHead)
{
    CourseNode* sorted = mergeSort(*ppHead);
    *ppHead = sorted;
}
CourseNode* mergeSort(CourseNode* pHead){
    if(pHead == NULL || pHead->pNext == NULL){
        return pHead; //Already sorted!
    }
    
    //printCourses("MergeSort", pHead);
    
    CourseNode** lists = split(pHead);
    lists[0] = mergeSort(lists[0]);
    lists[1] = mergeSort(lists[1]);
    CourseNode* sorted = merge(lists[0], lists[1]);
    free(lists);
    
    //printCourses("End MergeSort", sorted);
    return sorted;
}
CourseNode** split(CourseNode* pHead){
    
    //Make an array of linked lists of size 2;
    CourseNode** lists = malloc(sizeof(CourseNode**) * 2);
    if(pHead == NULL){
        lists[0] = NULL;
        lists[1] = NULL;
        return lists;
    }
    
    CourseNode* beginning = pHead;
    pHead = pHead->pNext;
    CourseNode* middle = pHead;
    CourseNode* premiddle = beginning;
    
    int traversals = 1;
    
    
    while(pHead != NULL){
        pHead = pHead->pNext;
        traversals++;
        
        if(traversals % 2 == 1){
            middle = middle->pNext;
            premiddle = premiddle->pNext;
        }
    }
    
    premiddle->pNext = NULL;
    
    lists[0] = beginning;
    lists[1] = middle;
    
    return lists;
}
CourseNode* merge(CourseNode * pHead1, CourseNode * pHead2){
    CourseNode* merged = NULL;
    CourseNode** lastPointer = &merged;
    
    while((pHead1 != NULL) && (pHead2 != NULL)){
        if(strcmp(pHead1->course.szCourseId, pHead2->course.szCourseId) <= 0){
            *lastPointer = pHead1;
            pHead1 = pHead1->pNext;
            
        }
        else {
            *lastPointer = pHead2;
            pHead2 = pHead2->pNext;
        }
        lastPointer = &((*lastPointer)->pNext);
    }
    
    //Add leftover elements.
    if(pHead1 != NULL){
        *lastPointer = pHead1;
        //pHead1 = pHead1->pNext;
        //lastPointer = &((*lastPointer)->pNext);
    }
    
    if(pHead2 != NULL){
        *lastPointer = pHead2;
        //pHead2 = pHead2->pNext;
        //lastPointer = &((*lastPointer)->pNext);
    }
    
    //*lastPointer = NULL;
    
    return merged;
}


/******************** printCourses **************************************
    void printCourses(char *pszHeading, CourseNode *pHead)
Purpose: Prints the list of courses and its details

Parameters:
 pszHeading - A header to print before printing the list of courses.
 pHead - the List of courses.
  
Returns: void
    
Notes: prints to console.
    
**************************************************************************/
void printCourses(char *pszHeading, CourseNode *pHead)
{
    int i;
    printf("%s\n\n", pszHeading);
    printf("****************************************** Courses ******************************************\n");
    printf("%-12s %-15s %-8s %-15s %-5s %-10s\n", "Course ID","Room Number","Days","Times","Seats","Fees");

    while(pHead != NULL){
        Course c = pHead->course;
        printCourse(c);
        
        pHead = pHead->pNext;
    }

    printf("\n");
}
/**
 * Added By Martin
 * Prints an individual course
 */
void printCourse(Course c){
    printf("%-12s %-15s %-8s %-15s %-5d %-10.2lf\n", c.szCourseId, c.szRoom, c.szDays, c.szTimes, c.iAvailSeats, c.dFee);
}

/********************processStudentCommand *****************************
    void processStudentCommand(CourseNode *pHead
     , char *pszSubCommand, char *pszRemainingInput
     , Student *pStudent, double *pdStudentRequestTotalCost )
Purpose:
    Processes the subcommands associated with the STUDENT command:
                 STUDENT BEGIN cGender   szBirthDt   szEmailAddr    szFullName
                     specifies the beginning of student request and includes 
                     all the identification information from program 2.
                 STUDENT INFO szStreetAddress,szCity,szStateCd,szZipCd
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
                     specifies the completion of the list of course requests 
                     for a student.
Parameters:
    I/O CourseNode *pHead              List of courses
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
    void processCourseCommand(CourseNode *pHead
         , char *pszSubCommand, char *pszRemainingInput)
Purpose:
    Processes the subcommands associated with the COURSE command:
        COURSE INCREASE szCourseId iQuantity
               increase the available seats for a course by the specified quantity.
        COURSE SHOW szCourseId    
               requests a display of a particular course.  Show all of its information.
Parameters:
    I/O CourseNode *pHead              List of courses
    I   int   iCourseCnt              Number of elments in pHead
    I   char  *pszSubCommand          Should be INCREASE or SHOW
    I   char  *pzRemainingInput       Points to the remaining characters in the input
                                      line (i.e., the characters that following the
                                      subcommand).
Notes:

**************************************************************************/
void processCourseCommand(CourseNode *pHead
                             , char *pszSubCommand, char *pszRemainingInput)
{
    Course course;
    int iQuantity;      // quantity of seats 
    int iScanfCnt;
    int i;
    char szCourseId[12];
    CourseNode * pFound = NULL;

    if (strcmp(pszSubCommand, "SHOW") == 0){
        //Process show subcommand
        sscanf(pszRemainingInput, "%s", szCourseId);
        
        pFound = search(pHead, szCourseId);
        
        if(pFound == NULL){
            printf("   *** %s %s\n", ERR_COURSE_NOT_FOUND, szCourseId);
            return;
        }
        
        printCourse(pFound->course);
    }
    else if (strcmp(pszSubCommand, "INCREASE") == 0)
    {
        //Process increase subcommand
        sscanf(pszRemainingInput, "%s %d", szCourseId, &iQuantity);
        
        pFound = search(pHead, szCourseId);
        
        if(pFound == NULL){
            printf("   *** %s %s\n", ERR_COURSE_NOT_FOUND, szCourseId);
            return;
        }
        
        pFound->course.iAvailSeats = pFound->course.iAvailSeats + iQuantity;
    }
    //If command type was not found, print an error
    else printf("   *** %s %s\n", ERR_COURSE_SUB_COMMAND, pszSubCommand);

}
/******************** search *****************************
    int search(CourseNode *pHead, char *pszMatchCourseId)
Purpose:
    
Parameters:
    I   CourseNode *pHead               List of courses
    I   int   iCourseCnt               Number of elments in pHead
    I   char *pszMatchCourseId         Course Id to find in the array
Returns:
    >= 0   subscript of where the match value was found
    -1     not found
Notes:

**************************************************************************/
CourseNode * search(CourseNode *pHead, char *pszMatchCourseId)
{
    while(pHead != NULL){
        if(strcmp(pHead->course.szCourseId,pszMatchCourseId) == 0)
            return pHead;
        
        pHead = pHead->pNext;
    }
    return NULL;
}
