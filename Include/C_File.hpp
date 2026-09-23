#ifndef _C_File_H
#define _C_File_H

/*----------------------------------------------------------------------------
*
*	Module: C_File
*	Author:	Francisco Guindos
*	Date  :
*
*---------------------------- DESCRIPTION -----------------------------------
*
*  General file management and little/big endian read/write.
*  Reads and writes through streams
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
#include <fstream>
//#include <vcl.h>

#include <C_General.hpp>

using namespace std;

/*---------------------------- CONSTANTS ----------------------------------*/
/*------------------------------ TYPES ------------------------------------*/
/*----------------------------- CLASSES -----------------------------------*/

class C_fstream : public fstream
{
  public:
    //fail() Error check:  implemented in the standard fstream
    void SetFail(void);

    void C_WriteFloatString (const double number, const unsigned int width);

    void C_WriteIntBigEndian        (long   i, int size/*bytes*/);
    void C_WriteIntLittleEndian     (long   i, int size/*bytes*/);
    void C_WriteFloat32BigEndian    (float  f);
    void C_WriteFloat32LittleEndian (float  f);
    void C_WriteFloat64BigEndian    (double f);
    void C_WriteFloat64LittleEndian (double f);

    long   C_ReadIntBigEndian        (int size/*bytes*/);
    long   C_ReadIntLittleEndian     (int size/*bytes*/);
    float  C_ReadFloat32BigEndian    ();
    float  C_ReadFloat32LittleEndian ();
    double C_ReadFloat64BigEndian    ();
    double C_ReadFloat64LittleEndian ();
};

/*---------------------------- FUNCTIONS ----------------------------------*/

C_ResultT C_FileCopy   (const char * source, const char * dest);
bool      C_FileExists (const char * fileName);

string C_ExtractFileName (const string str);
//C_ResultT C_File_FNChangeExt (AnsiString name, AnsiString ext);



#endif
