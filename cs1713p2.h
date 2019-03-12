/**********************************************************************
cs1713p1.h
Purpose:
    Defines typedefs for
        Student - includes email address, full name, birthdate, gender,
                   student id, gpa, major and a character indicating 
                   whether they are an international student or not.
        Reservation - courses the student wants.
    Defines constants for
        boolean values
        error messages
        program return codes
    Prototypes
Notes:
    
**********************************************************************/

/**** typedefs ****/

// Student information 
typedef struct
{
    char        szBirthDt[11];              // Birthdate - YYYY/MM/DD
    char        szEmail[31];                // student's email address
    char        szStudentId[7];              // abc123 id number
    char        szFullName[31];             // student full name
    char        szMajor[4];                 // indicates student major
    
    char        cGender;                    // M - Male or F - Female
    char        cInternationalStudent;       // indicates whether a student
                                            // is international Y - yes N - no
    
    double      dGpa;                       // students current gpa
} Student;

// Course Request information 
typedef struct
{
    char szCourseId[12];                   // Course Identifier 
} CourseRequest;

// Course Definition
typedef struct
{
    char szCourseId[12];                    // Course Identifier
    char szRoom[15];                        // Room number of the course
    char szDays[8];                         // What days the course will meet, ex: MWF, TR, etc
    char szTimes[15];                        // Meeting Time, ex: 10:00-11:15am
    int  iAvailSeats;                       // Number of available seats in the course
    double dFee;                            // Additional fees for the course
} Course;

/**** constants ****/
#define MAX_COURSES 	100

// boolean
#define FALSE           0
#define TRUE            1

/*  Error Messages */
#define ERR_MISSING_SWITCH          "missing switch"
#define ERR_EXPECTED_SWITCH         "expected switch, found"
#define ERR_MISSING_ARGUMENT        "missing argument for"
#define ERR_STUDENT_RES_FILENAME    "invalid student registration file name"
#define ERR_STUDENT_ID_DATA         "invalid student id data"
#define ERR_STUDENT_ADDRESS_DATA    "invalid student address data"
#define ERR_RESERVATION_DATA        "invalid student registration data"

/* Errors added for Assignment 2 */
#define ERR_COURSE_FILENAME         "invalid course file name"
#define ERR_COURSE_ID_DATA          "invalid course ID"
#define ERR_COURSE_FULL			    "course is full, not adding the fees"
#define ERR_COURSE_NOT_FOUND        "course Id not found"

/* program return codes */
#define ERR_COMMAND_LINE_SYNTAX     -1      // invalid command line syntax
#define USAGE_ONLY                  -2      // show usage only
#define ERROR_PROCESSING            -3

/* prototypes */
void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);