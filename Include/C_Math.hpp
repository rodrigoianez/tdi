//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#ifndef _C_Math_H
#define _C_Math_H
/*----------------------------------------------------------------------------
*
*	Module: CMath
*	Author:	Jose Antonio Piedra Fernández
*	Date  :
*
*---------------------------- DESCRIPTION -----------------------------------
*---------------------------- CONSTRAINTS -----------------------------------
*
*	Computer:
*	O. S.   :
*	Compiler:
*	Others  :
*
*--------------------------------------------------------------------------*/

/*------------------------- IMPORTED MODULES ------------------------------*/


#include <math.h>
#include <C_Matrix.hpp>

/*---------------------------- CONSTANTS ----------------------------------*/

/*----------------------------- FUNCTION -----------------------------------*/

    void Truncation(C_Matrix::ElementT &value);

    int CheckOperation(C_Matrix::ElementT &value);

    //int matherr (struct exception *a);

    //Control Exception by 'pow'
    //C_Matrix::ElementT power(C_Matrix::ElementT base, C_Matrix::ElementT exp);
    int power(C_Matrix::ElementT base, C_Matrix::ElementT exp,C_Matrix::ElementT &value);

    //Control Exception by 'sqrt'
    int calsqrt(C_Matrix::ElementT dato,C_Matrix::ElementT &value);

    //Control Exception by 'division'
    //C_Matrix::ElementT division(C_Matrix::ElementT numerador, C_Matrix::ElementT denominador);
    int division(C_Matrix::ElementT numerador, C_Matrix::ElementT denominador, C_Matrix::ElementT &value);

    //Control Product
    //C_Matrix::ElementT producto(C_Matrix::ElementT oper1, C_Matrix::ElementT oper2);
    int producto(C_Matrix::ElementT oper1, C_Matrix::ElementT oper2, C_Matrix::ElementT & value);

#endif
