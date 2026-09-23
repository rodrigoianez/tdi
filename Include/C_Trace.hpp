#ifndef _C_Trace_H
#define _C_Trace_H

/*------------------------- IMPORTED MODULES ------------------------------*/

//#include <vcl.h>
#include <string>

using namespace std;

/*---------------------------- CONSTANTS ----------------------------------*/
/*------------------------------ TYPES ------------------------------------*/
/*----------------------------- CLASSES -----------------------------------*/

// No need to declare C_Trace objects, because all their components are static
class C_Trace
{
  private:
    static string ident;
    static bool   console;
    static string file;
  public:
    // Set trace behaviour: trace identity text, console trace and file trace
    static void Set (const string newIdent, const bool newConsole, const string newFile);

    /* Please don't use these functions directly. They should be called through
       the macros defined below */
    static void TraceProgramCall (const int argc, char * argv[], bool resetFile);
    static void Trace (const char type, const char *c_file, const int c_line, const char * text);
    static void Trace (const char type, const char *c_file, const int c_line, const char * text,
                       const double num);
    static void Trace (const char type, const char *c_file, const int c_line, const char * text,
                       const double num1, const double num2);
    static void Trace (const char type, const char *c_file, const int c_line, const char * text,
                       const char *str );   // C-style null terminated string
    static void Trace (const char type, const char *c_file, const int c_line, const char * text,
                       const string str );  // C++ STL string
    static void Trace (const char type, const char *c_file, const int c_line, const char * text,
                       const char *address, const int byteN);

};

/*---------------------------- FUNCTIONS ----------------------------------*/


// Prints a trace of the program call in log file. It can be used only in main program
// resetFile: true: deletes previous logs. false: doesn't delete them
#define C_TraceProgramCall(resetFile)                \
{                                                    \
  C_Trace::TraceProgramCall (argc, argv, resetFile); \
}


/* Prints a message */
#define C_Print(text)                             \
{                                                 \
  C_Trace::Trace (0, __FILE__, __LINE__, text); \
}

/* Prints a trace with the file name, line number, the desired message */
#define C_Trace(text)                             \
{                                                 \
  C_Trace::Trace ('T', __FILE__, __LINE__, text); \
}

/* Displays a warning message with the file name, line number and the
   desired message */
#define C_Warning(text)                           \
{                                                 \
  C_Trace::Trace ('W', __FILE__, __LINE__, text); \
}

/* Displays a warning message with the file name, line number and the
   desired message */
#define C_IfWarning(cond,text)                      \
{                                                   \
  if (cond)                                         \
    C_Trace::Trace ('W', __FILE__, __LINE__, text); \
}

/* Displays an error message with the file name, line number and the desired
   message and DOES to_do */
#define C_Error(text,to_do)	                      \
{								                  \
  C_Trace::Trace ('E', __FILE__, __LINE__, text); \
  to_do;							              \
}

/* Displays an error message with the file name, line number and the desired
   message and DOES to_do */
#define C_IfError(cond,text,to_do)	                \
{								                    \
  if (cond)							                \
  {								                    \
    C_Trace::Trace ('E', __FILE__, __LINE__, text); \
    to_do;							                \
  }								                    \
}

/* Prints the desired message and a numeric value or variable */
#define C_PrintNum(text,num)                           \
{ 							                           \
  C_Trace::Trace (0, __FILE__, __LINE__, text, num); \
}

/* Prints a trace with the file name, line number, the desired message and
   a numeric value or variable */
#define C_TraceNum(text,num)                           \
{ 							                           \
  C_Trace::Trace ('T', __FILE__, __LINE__, text, num); \
}

/* Displays a warning message with the file name, line number, the desired
   message and an int value or variable*/
#define C_WarningNum(text,num)                         \
{								                       \
  C_Trace::Trace ('W', __FILE__, __LINE__, text, num); \
}

/* Displays a warning message with the file name, line number, the desired
   message and an int value or variable*/
#define C_IfWarningNum(cond,text,num)                    \
{								                         \
  if (cond)							                     \
    C_Trace::Trace ('W', __FILE__, __LINE__, text, num); \
}

/* Displays an error message with the file name, line number, the desired
   message and an int value or variable and DOES to_do */
#define C_ErrorNum(text,num,to_do)                     \
{								                       \
  C_Trace::Trace ('E', __FILE__, __LINE__, text, num); \
  to_do;							                   \
}

/* Displays an error message with the file name, line number, the desired
   message and an int value or variable and DOES to_do */
#define C_IfErrorNum(cond,text,num,to_do)                \
{								                         \
  if (cond)							                     \
  {								                         \
    C_Trace::Trace ('E', __FILE__, __LINE__, text, num); \
    to_do;							                     \
  }								                         \
}


/* Prints the desired message and two int value or variable */
#define C_Print2Num(text,num1,num2)                           \
{				                                          \
  C_Trace::Trace (0, __FILE__, __LINE__, text, num1, num2); \
}

/* Prints a trace with the file name, line number, the desired message and
   two int value or variable */
#define C_Trace2Num(text,num1,num2)                           \
{ 					                                          \
  C_Trace::Trace ('T', __FILE__, __LINE__, text, num1, num2); \
}

/* Displays a warning message with the file name, line number, the desired
   message and two int value or variable*/
#define C_Warning2Num(text,num1,num2)                         \
{ 							                                  \
  C_Trace::Trace ('W', __FILE__, __LINE__, text, num1, num2); \
}

/* Displays a warning message with the file name, line number, the desired
   message and two int value or variable*/
#define C_IfWarning2Num(cond,text,num1,num2)                    \
{								                                \
  if (cond)							                            \
    C_Trace::Trace ('W', __FILE__, __LINE__, text, num1, num2); \
}

/* Displays an error message with the file name, line number, the desired
   message and two int value or variable and DOES to_do */
#define C_Error2Num(text,num1,num2,to_do)                     \
{								                              \
  C_Trace::Trace ('E', __FILE__, __LINE__, text, num1, num2); \
  to_do;							                          \
}

/* Displays an error message with the file name, line number, the desired
   message and two int value or variable and DOES to_do */
#define C_IfError2Num(cond,text,num1,num2,to_do)                \
{								                                \
  if (cond)							                            \
  {								                                \
    C_Trace::Trace ('E', __FILE__, __LINE__, text, num1, num2); \
    to_do;							                            \
  }								                                \
}


/* Prints the desired message and a string constant or variable */
#define C_PrintStr(text,str)                           \
{								                       \
  C_Trace::Trace (0, __FILE__, __LINE__, text, str); \
}

/* Prints a trace with the file name, line number, the desired message and
   a string constant or variable */
#define C_TraceStr(text,str)                           \
{								                       \
  C_Trace::Trace ('T', __FILE__, __LINE__, text, str); \
}

/* Displays a warning message with the file name, line number, the desired
   message and a string constant or variable */
#define C_WarningStr(text,str)                          \
{								                                        \
  C_Trace::Trace ('W', __FILE__, __LINE__, text, str); \
}

/* Displays a warning message with the file name, line number, the desired
   message and a string constant or variable */
#define C_IfWarningStr(cond,text,str)                     \
{								                                          \
  if (cond)							                                  \
    C_Trace::Trace ('W', __FILE__, __LINE__, text, str); \
}

/* Displays an error message with the file name, line number, the desired
   message and a string constant or variable and DOES to_do */
#define C_ErrorStr(text,str,to_do)                      \
{								                                        \
  C_Trace::Trace ('E', __FILE__, __LINE__, text, str); \
  to_do;							                                  \
}

/* Displays an error message with the file name, line number, the desired
   message and a string constant or variable and DOES to_do */
#define C_IfErrorStr(cond,text,str,to_do)	                \
{								                                          \
  if (cond)							                                  \
  {								                                        \
    C_Trace::Trace ('E', __FILE__, __LINE__, text, str); \
    to_do;							                                  \
  }								                                        \
}


/* Prints a trace with the file name, line number, the desired message and
   a series of bytes starting in addres and len length */
#define C_TraceBytes(text,address,len)             	             \
{								                                                 \
  C_Trace::Trace ('T', __FILE__, __LINE__, text, address, len); \
}

/* Displays a warning message with the file name, line number, the desired
   message and a series of bytes starting in addres and len length */
#define C_WarningBytes(text,address,len)                         \
{ 							                                                 \
  C_Trace::Trace ('W', __FILE__, __LINE__, text, address, len); \
}

/* Displays a warning message with the file name, line number, the desired
   message and a series of bytes starting in addres and len length */
#define C_IfWarningBytes(cond,text,address,len)                    \
{								                                                   \
  if (cond)							                                           \
    C_Trace::Trace ('W', __FILE__, __LINE__, text, address, len); \
}

/* Displays an error message with the file name, line number, the desired
   message and a series of bytes starting in addres and len length and
   DOES to_do*/
#define C_ErrorBytes(text,address,len,to_do)                     \
{								                                                 \
  C_Trace::Trace ('E', __FILE__, __LINE__, text, address, len); \
  to_do;							                                           \
}

/* Displays an error message with the file name, line number, the desired
   message and a series of bytes starting in addres and len length and
   DOES to_do*/
#define C_IfErrorBytes(cond,text,address,len,to_do)                \
{								                                                   \
  if (cond)							                                           \
  {								                                                 \
    C_Trace::Trace ('E', __FILE__, __LINE__, text, address, len); \
    to_do;							                                           \
  }								                                                 \
}


#endif
