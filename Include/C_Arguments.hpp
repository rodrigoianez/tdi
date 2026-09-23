#ifndef _C_Arguments_H
#define _C_Arguments_H
/*----------------------------------------------------------------------------
*
*	Module: C_Arguments
*	Author:	Francisco Guindos
*	Date  :
*
*---------------------------- DESCRIPTION -----------------------------------
*
*  Program arguments dealing
*
*---------------------------- CONSTRAINTS -----------------------------------
*
*	Computer:
*	O. S.   :
*	Compiler:
*	Others  :
*
*--------------------------------------------------------------------------*/

/*------------------------- IMPORTED MODULES ------------------------------*/

#include <string>
#include <vector>

using namespace std;

/*---------------------------- CONSTANTS ----------------------------------*/

/*------------------------------ TYPES ------------------------------------*/

/*---------------------------- FUNCTIONS ----------------------------------*/

class C_Arguments
{
  private:
    bool   fail;
    int    paramCount;
    vector <string> param;
    bool   caseSensitive;
    bool   option [256];
    bool   optionValue [256];
    vector <string> optionValueStr;

  public:        // Creator: it will interpret the arguments in the program call
                 // minParam, maxparam = min and max of parameters allowed
                 // options: array with the defined options
                 // caseSens = case sesibility of options
                 C_Arguments (const int argc, char * argv[],
                              const int minParam, const int maxParam,
                              const char options[], bool caseSens);
    bool         Fail           ();
    int          ParamCount     ();
    const char * Param          (int index);
    bool         Option         (unsigned char opt);
    bool         OptionValue    (unsigned char opt);
    const char * OptionValueStr (unsigned char opt);
                 // Writes a log to <fileLogged>.log. default = log to screen
                 // If included prevFileLogged, the file <prevFileLogged>.log will
                 //   be copied at log header.
    void         Log            (const char * fileLogged     = NULL,
                                 const char * prevFileLogged = NULL);
};

/*
It interprets argv (parameters and options) in the program call and separates
options and parameters:
Example:   DIR /P /W   DOS
               options parameter

Options must be preceded by / (each one or a group of them)
*/

#endif
