#ifndef _C_General_H
#define _C_General_H

/*----------------------------------------------------------------------------
*
*	Module: C_General
*	Author:	Francisco Guindos
*	Date  :
* Rev   :
*
*---------------------------- DESCRIPTION -----------------------------------
*
*  Header file with general definitions
*
*---------------------------- CONSTRAINTS -----------------------------------
*
*	Computer: INF y NAN
*	O. S.   :
*	Compiler:
*	Others  :
*
*--------------------------------------------------------------------------*/

/*------------------------- IMPORTED MODULES ------------------------------*/

/*---------------------------- CONSTANTS ----------------------------------*/

// Para los límites habría que usar  numeric_limits<T>:: pero no está implementado
// Los valores que doy podrian no funcionar en ciertas máquinas.
// Habría que definir C_FLOAT_NAN y otros de tamaño float

/* INFinite definition INF +INF -INF */
#define C_DOUBLE_INF   ( (double) *(double*) &C_double_p_inf)
#define C_DOUBLE_P_INF ( (double) *(double*) &C_double_p_inf)
#define C_DOUBLE_M_INF ( (double) *(double*) &C_double_m_inf)

/* Not-A-Number definition NAN +NAN -NAN */
#define C_DOUBLE_NAN   ( (double) *(double*) &C_double_p_nan)
#define C_DOUBLE_P_NAN ( (double) *(double*) &C_double_p_nan)
#define C_DOUBLE_M_NAN ( (double) *(double*) &C_double_m_nan)

// Implemented in C_General.cpp :
extern char C_double_p_inf [];
extern char C_double_m_inf [];
extern char C_double_p_nan [];
extern char C_double_m_nan [];

/* Computer endianness: little o big endian */
extern bool C_bigEndian;
extern bool C_littleEndian;

/*------------------------------ TYPES ------------------------------------*/

typedef enum { C_OK = 0,     C_ERROR = -1}    C_ResultT;
typedef enum { C_BIG_ENDIAN, C_LITTLE_ENDIAN} C_EndianT;

//typedef __int8  C_int8;
typedef char C_int8;
//typedef __int16 C_int16;
typedef short C_int16;
//typedef __int32 C_int32;
typedef int C_int32;
//typedef __int64 C_int64;
//typedef long C_int64;

//typedef unsigned __int8  C_uint8;
typedef unsigned char C_uint8;
//typedef unsigned __int16 C_uint16;
typedef unsigned short C_uint16;
//typedef unsigned __int32 C_uint32;
typedef unsigned int C_uint32;
//typedef unsigned __int64 C_uint64;
//typedef unsigned long C_uint64;

/*----------------------------- CLASSES -----------------------------------*/
/*---------------------------- FUNCTIONS ----------------------------------*/

#define C_Max(a,b) ( (a)>(b) ? (a) : (b) )
#define C_Min(a,b) ( (a)<(b) ? (a) : (b) )

#define C_Random(n) (n ? (rand()%(n)) : 0 )


#define C_Flag     (flagset,flag) ( (flagset) &   (flag) )
#define C_SetFlag  (flagset,flag) ( (flagset) |=  (flag) )
#define C_ResetFlag(flagset,flag) ( (flagset) &= ~(flag) )

#endif
