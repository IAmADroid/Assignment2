
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p2.h"

FILE *pFileStu;               // stream Input for Student Registration data
FILE *pFileClasses;               // stream Input for Classes data

void processCommandSwitches(int argc, char *argv[], char **ppszStudentFileName, char **ppszClassFileName);
void processRegistrations(Course courseM[], int iCourseCount);
void printCourses(Course courseM[], int iCourseCount);
int getCourses(Course courseM[]);


int main(int argc, char *argv[])
{
    char *pszStudentFileName = NULL;
    char *pszClassFileName = NULL;
  
    // Process the command switches
    processCommandSwitches(argc, argv,  &pszStudentFileName, &pszClassFileName);
    
    // open the Student Registration stream data file
    if (pszStudentFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-s");
    if (pszClassFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-c");
    
    pFileStu = fopen(pszStudentFileName, "r"); // open file for reading
    pFileClasses = fopen(pszClassFileName, "r+"); // open file for reading and writing

    if (pFileStu == NULL)
        exitError(ERR_STUDENT_RES_FILENAME, pszStudentFileName);
    if (pFileClasses == NULL)
        exitError(ERR_COURSE_FILENAME, pszClassFileName);
   
    // process the Registrations
    Course courseM[MAX_COURSES];
    int numCourses = getCourses(courseM);
    
    
    printCourses(courseM, numCourses);
    processRegistrations(courseM, numCourses);
    printCourses(courseM, numCourses);

    fclose(pFileStu);
    fclose(pFileClasses);
    printf("\n");    // included so that you can put a breakpoint on this line
    return 0;
}

/* reads courses from file. Puts courses in courseM. returns the number of courses as an int.*/
int getCourses(Course courseM[]){
    char szInputBuffer[100];
    int numCourses = 0;
    while(fgets(szInputBuffer, 100, pFileClasses) != NULL){
        Course c;
        sscanf(szInputBuffer, "%s %s %s %s %d %lf", c.szCourseId, c.szRoom, c.szDays, c.szTimes, &c.iAvailSeats, &c.dFee);
        
        courseM[numCourses] = c;

        numCourses++;
    }
    return numCourses;
}
/* Prints out the courses in courseM according to the Assignment 2 specifications. */
void printCourses(Course courseM[], int iCourseCount){
    printf("************************************ Courses ************************************\n");
    printf("%-12s %-15s %-8s %-15s %-5s %-10s\n", "Course ID", "Room Number", "Days", "Times", "Seats", "Fees");
    int i = 0;
    for(; i < iCourseCount; i++){
        Course c = courseM[i];
        printf("%-12s %-15s %-8s %-15s %-5d %-10.2lf\n", c.szCourseId, c.szRoom, c.szDays, c.szTimes, c.iAvailSeats, c.dFee);
    }
}

/* Prints out the courses in courseM. */
void printCoursesData(Course courseM[], int iCourseCount){
    int i = 0;
    for(; i < iCourseCount; i++){
        Course c = courseM[i];
        printf("%s %s %s %s %d %10lf\n", c.szCourseId, c.szRoom, c.szDays, c.szTimes, c.iAvailSeats, c.dFee);
    }
}

/* returns the course corresponding to a courseID. if no course is found, NULL is returned. */
Course * findCourse(Course courseM[], int iCourseCount, char * szCourseId){
    int i = 0;
    for(; i < iCourseCount; i++){
        Course c = courseM[i];
        if(strcmp(c.szCourseId, szCourseId) == 0){
            return &(courseM[i]);
        }
    }
    return NULL;
}

/****** you need to document and code this function *****/

void processRegistrations(Course courseM[], int iCourseCount)
{
    char szInputBuffer[100];
    char szError[100];
    int iScanfCount = -1;
    int lineNumber = 0;
    int bValidEnd = FALSE;
    Student student;
    CourseRequest courseRequest;

    while(fgets(szInputBuffer, 100, pFileStu) != NULL)
    {
        printf("**************** Student Registration Request ****************\n");


        // ************** Handle student id information **************
        lineNumber++; 
        iScanfCount = sscanf(szInputBuffer, "%s %c %s %[^\n]\n", student.szStudentId
                                                                , &student.cGender
                                                                , student.szBirthDt
                                                                , student.szFullName );
        if (iScanfCount != 4)
        {
            sprintf(szError, "on line %d of student file\n", lineNumber);
            exitError(ERR_STUDENT_ID_DATA, szError);
        }
        printf("%s %s (%c %s)\n", student.szStudentId
                                , student.szFullName
                                , student.cGender
                                , student.szBirthDt);

        if (fgets(szInputBuffer, 100, pFileStu) == NULL)
        {
            sprintf(szError, "Incomplete record at end of file, line %d\n", lineNumber);
            exitError(ERR_STUDENT_ADDRESS_DATA, szError);
        }


        // ******** Handle student record information ***********
        lineNumber++; 
        iScanfCount = sscanf(szInputBuffer, "%[^,],%[^,],%lf,%c", student.szMajor
                                                                , student.szEmail
                                                                , &student.dGpa
                                                                , &student.cInternationalStudent );
        if (iScanfCount != 4)
        {
            sprintf(szError, "on line %d of student file\n", lineNumber);
            exitError(ERR_STUDENT_ADDRESS_DATA, szError);
        }
        printf("%s %s INTL:%c GPA:%4.2lf\n", student.szMajor
                                        , student.szEmail
                                        , student.cInternationalStudent
                                        , student.dGpa );
        

        double fees = 0;
        
        // ************ Handle course requests ***************
        printf("\tCourses\n");
        while(fgets(szInputBuffer, 100, pFileStu) != NULL)
        {
            lineNumber++; 
            iScanfCount = sscanf(szInputBuffer, "%[^ \n\t]", courseRequest.szCourseId);
            if (iScanfCount != 1)
            {
                sprintf(szError, "on line %d of student file\n", lineNumber);
                exitError(ERR_RESERVATION_DATA, szError);
            }
            
            if (strnlen(courseRequest.szCourseId, 15) > 12)
            {
                sprintf(szError, "on line %d '%s'\n", lineNumber, courseRequest.szCourseId);
                exitError(ERR_RESERVATION_DATA, szError);
            }
            
            if (strncmp(courseRequest.szCourseId, "END", 100) == 0)
            {
                bValidEnd = TRUE;
                break;
            }

            printf("\t%s", courseRequest.szCourseId);

            szError[0] = 0;

            Course * newCourse = findCourse(courseM, iCourseCount, courseRequest.szCourseId);
            if(newCourse == NULL){
                sprintf(szError, "%s", ERR_COURSE_NOT_FOUND);
            }
            else if((*newCourse).iAvailSeats < 1){
                sprintf(szError, "%s", ERR_COURSE_FULL);
            }


            if(szError[0] != '\0'){
                printf(" %s", szError);
                printf("\n");
                continue;
            }
            //Course was found, so now we edit it!
            (*newCourse).iAvailSeats--;
            fees += (*newCourse).dFee;
            
            printf("\n");
        }

        if (!bValidEnd)
        {
            sprintf(szError, "Missing END record at end of file, line %d\n", lineNumber);
            exitError(ERR_RESERVATION_DATA, szError);
        }
        bValidEnd = FALSE;
        
        //print fees
        printf("\ttotal fees: $%.2lf\n",fees);
    }
}


/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszStudentFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                        count of command line arguments
    I   char *argv[]                    array of command line arguments
    O   char **ppszStudentFileName     student registration file name
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszStudentFileName, char **ppszClassFileName)
{
    int i;
    
    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 's':                   // Student Registration File Name
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszStudentFileName = argv[i];
                break;
            case 'c':                   // Student Registration File Name
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszClassFileName = argv[i];
                break;
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
    }
}

/******************** exitError *****************************
    void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    Prints an error message and diagnostic to stderr.  Exits with
    ERROR_PROCESSING.
Parameters:
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
    fprintf(stderr, "Error: %s %s\n"
        , pszMessage
        , pszDiagnosticInfo);
    exit(ERROR_PROCESSING);
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    If this is an argument error (iArg >= 0), it prints a formatted message
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE_SYNTAX.

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    if (iArg >= 0)
        fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
            , iArg
            , pszMessage
            , pszDiagnosticInfo);
    fprintf(stderr, "reserve -s studentRegistrationFile -c courseListFile\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
