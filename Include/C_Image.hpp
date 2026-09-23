#ifndef _C_Image_H
#define _C_Image_H
/*----------------------------------------------------------------------------
*
*	Module: C_Image
*	Author:	Francisco Guindos
*	Date  :
*
*---------------------------- DESCRIPTION -----------------------------------
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

#include <C_Matrix.hpp>

/*---------------------------- CONSTANTS ----------------------------------*/
#define C_RED (3)
#define C_GREEN (2)
#define C_BLUE (1)
/*------------------------------ TYPES ------------------------------------*/

/*---------------------------- FUNCTIONS ----------------------------------*/

class C_Image : public C_Matrix
{
  public: // Data
    C_Matrix palette; // Columns: 1, 2, 3   Rows: 0 - paletteSize-1

  public: // Methods
    // Constructor: empty image
    C_Image ();

    //Constructor:
    C_Image (const IndexT firstRow, const IndexT lastRow,
             const IndexT firstCol, const IndexT lastCol,
             const ElementT initValue = 0,
             const IndexT paletteSize = 256);

    //Constructor, creates an image from a matrix (a copy of it), adding the palette
    C_Image (C_Matrix matrix, const ElementT paletteSize = 256);

    // Frees an image (matrix and palette):
    void Free (void);

    inline IndexT PaletteSize(void) const { return palette.RowN(); }
    void SetPaletteSize (const IndexT paletteSize);

    // Detects img format type upon the file extension and read or writes that format
    void Read  (const char * filePath);
    void Write (const char * filePath, const C_EndianT endianType = C_LITTLE_ENDIAN);

    void ReadBMP  (const char * filePath);
    void WriteBMP (const char * filePath);
    //***** Jose Antonio Piedra Fernandez *******
    int static BMPFileInfo(const char * filePath,
                           IndexT &rowN,IndexT &colN,IndexT &colorsN);
    //***** Jose Antonio Piedra Fernandez *******

    void ReadLAN74  (const char * filePath);
    void WriteLAN74 (const char * filePath);

    // Convert to 256 levels greyscale
    void Grey ();

};



/*
t_boolean CMATIMP_KnownType (const CFILE_T_Path filepath);

t_result CMATIMP_ReadMATLAB (const CFILE_T_Path filename, t_matrix * matrix);
t_result CMATIMP_WriteMATLAB (const CFILE_T_Path filename, const t_matrix matrix,
			      const char matrixname [], const t_endian endianness);

t_result CMATIMP_ReadLAN74 (const CFILE_T_Path filename, t_matrix * matrix);
t_result CMATIMP_WriteLAN74 (const CFILE_T_Path filename, const t_matrix matrix);
*/

#endif
