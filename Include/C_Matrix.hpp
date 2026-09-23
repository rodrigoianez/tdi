#ifndef _C_Matrix_H
#define _C_Matrix_H
/*----------------------------------------------------------------------------
*
*	Module: C_Matrix
*	Author:	Francisco Guindos
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

#include <C_General.hpp>
#include <C_File.hpp>
#include <C_Trace.hpp>

/*---------------------------- CONSTANTS ----------------------------------*/

// Usually defined in <math.h>
#ifndef M_PI
#define M_PI (3.1415926535897932384626433832795)
#endif

#ifndef M_SQRT2
#define M_SQRT2 (1.4142135623730950488016887242097)
#endif


// #define C_MATRIX_NAN C_DOUBLE_NAN CBuilder 3 in AMD K6-II gives arithmetic error sometimes
#define C_MATRIX_NAN C_DOUBLE_INF

/*------------------------------ TYPES ------------------------------------*/
/*----------------------------- CLASSES -----------------------------------*/

class C_Matrix
{
  public: // types
    typedef double ElementT;
    typedef long   IndexT;

    class CoordT        // just for a few funcions that return a coordinate
    {
      public:
        IndexT row, col;

        inline bool operator == (CoordT& coord2)
          { return ((row == coord2.row) && (col == coord2.col)); }


        inline bool operator < (CoordT& coord2)
          { return ((row < coord2.row) || ((row == coord2.row) && (col < coord2.col))); }
    };



//    typedef struct { IndexT row, col; } CoordT; // just for a few funcions that return a coordinate
    typedef enum
    {
      DIR_N, DIR_NE, DIR_E, DIR_SE, DIR_S, DIR_SW, DIR_W, DIR_NW,
      DIR_FIRST = DIR_N,
      DIR_LAST_4 = DIR_W, DIR_LAST_8 = DIR_NW
    } DirectionT;

  private: // data
    bool       empty;

    IndexT     firstRow, lastRow,
               firstCol, lastCol;
    IndexT     rowN,     colN;

    C_Matrix * superMat;        // If this is a matrix => NULL. Else, if this
                                //   is a submatrix => pointer to the supermatrix
    C_Matrix * supraMat;        // Pointer to the first matrix in the submatrix chain
    IndexT     firstRowSupraMat,
               firstColSupraMat;

    int        subMatN;         // Number of submatrices created from this matrix
    ElementT * body;

    bool       fail;

  public: // methods

    // Constructor: creates an empty matrix
    C_Matrix ();

    // Copy constructor (it's invoked when a matrix is used as a parameter to a function?)
    C_Matrix (C_Matrix & matrixIn);

    // Constructor: creates a matrix of a given size, initializing it
    C_Matrix (const IndexT firstRow, const IndexT lastRow,
              const IndexT firstCol, const IndexT lastCol,
	          const ElementT initValue = 0);

    // Constructor: creates a SUBmatrix of an existing matrix (supermatrix).
    // It doesn't copy the body. Instead, it creates a way to manipulate a
    // rectangular zone of the original matrix.
    // The body is the SAME (same memory address) than the original
    C_Matrix (C_Matrix & superMatrix,
              const IndexT firstRow,         const IndexT lastRow,
              const IndexT firstCol,         const IndexT lastCol,
              const IndexT firstRowSuperMat,
              const IndexT firstColSuperMat);

    // Destructor. DON'T DESTROY A MATRIX WITH SUBMATRICES DEFINED !!
    // You must destroy submatrices before it's supermatrix.
    ~C_Matrix ();

    // Frees a matrix to an empty one. Frees body memory:
    void Free (void);

    // Access to class data:
    inline bool   Empty    (void) const { return empty;    }
    inline IndexT FirstRow (void) const { return firstRow; }
    inline IndexT LastRow  (void) const { return lastRow;  }
    inline IndexT FirstCol (void) const { return firstCol; }
    inline IndexT LastCol  (void) const { return lastCol;  }
    inline IndexT RowN     (void) const { return rowN;     }
    inline IndexT ColN     (void) const { return colN;     }
    inline bool   Fail     (void) const { return fail;     }
    inline void   SetFail  (void)       { fail = true;     }

    // True if a coordinate pair is beneath the matrix limits
    bool In (const IndexT row, const IndexT col) const;

    // Resets fail status to false. Needed after an error detection.
    void Clear (void);

    // Access to a matrix element: overloading ()
    ElementT& operator () (const IndexT row, const IndexT col);

    // Access to a matrix element: overloading ()
    ElementT& operator () (IndexT row, IndexT col, bool extendBoundaries);

    // Copy of a matrix: overloading =
    // The copy is independent from the source and won't ever be a submatrix
    C_Matrix& operator = (C_Matrix& source);

    // This function changes the indices of a matrix, but the body stays unchanged.
    void Reindex (const IndexT newFirstRow, const IndexT newFirstCol);

    // Resizes a matrix or submatrix.
    // Matrix: The values in the zone common to old and new matrices don't change
    // Submatrix: The position of upper-left corner in superMatrix doesn't change
    void Resize (const IndexT newFirstRow, const IndexT newLastRow,
                 const IndexT newFirstCol, const IndexT newLastCol,
                 const ElementT defValue = 0);

    // This function moves the window that a submatrix is for it's supermatrix
    //to a different place. The size isn't changed.
    void MoveSubMat (const IndexT newFirstRowSuperMat, const IndexT newFirstColSuperMat);


    // ********** UTILITY FUNCIONS **********:


    // Assign "newValue" to all the elements of the matrix
    void SetValue (const ElementT newValue);

    // Assign "newValue" to all the elements whose value is oldValue
    void SetValue (const ElementT oldValue, const ElementT newValue);

    // Assign "newValue" to all the elements whose value is beneath min and max
    void SetValue (const ElementT oldValueMin, const ElementT oldValueMax, const ElementT newValue);

    // Fills a matrix with a serie
    void Serie (const ElementT initValue,
                const ElementT rowInc, const ElementT colInc);

    // Fills a matrix with random integer numbers
    void Rand (const int min, const int max);

    // All values under min are set to min and all values over max are set to max
    void Trunc (const ElementT min, const ElementT max);

    // The histogram is modified to fetch into min-max
    void Stretch (const ElementT min, const ElementT max);

    // These functions calculate some values from a matrix (or submatrix) */
    ElementT Min  (void);
    ElementT Max  (void);
    ElementT Sum  (void);
    ElementT Mean (void);
    ElementT Mode (long int * frequency = NULL, ElementT discardValue = C_MATRIX_NAN);

    // These functions do some operations (element by element) with a matrix */
    void Abs   (void);
    void Round (void);

    // These functions do some operations (element by element) with two matrices
    //   (mat1 and mat2) ant store the result in "this" matrix
    void Add         (C_Matrix & mat1, C_Matrix & mat2);
    void Subtract    (C_Matrix & mat1, C_Matrix & mat2);
    void MultiplyElm (C_Matrix & mat1, C_Matrix & mat2);
    void DivideElm   (C_Matrix & mat1, C_Matrix & mat2);

    // These functions do some operations (element by element) with a matrix and
    //   an escalar
    void AddEscalar          (ElementT escalar);
    void SubtractEscalar     (ElementT escalar);
    void SubtractFromEscalar (ElementT escalar);
    void MultiplyEscalar     (ElementT escalar);
    void DivideEscalar       (ElementT escalar);


    void Enlarge (int factor);

    // ********** NEIGHBOURHOOD FUNCIONS **********:

    // Coordinates of neighbours. THIS DOESN'T CHECK MATRIX BOUNDARIES
    CoordT Neigh (const IndexT row, const IndexT col,
                  DirectionT direction);

    // Coordinates of neighbours. THIS DOESN'T CHECK MATRIX BOUNDARIES
    DirectionT NeighNext (DirectionT direction, int neighbourhood = 8);

    // Distance to neighbours. 1 or sqrt(2)
    double NeighDist (DirectionT direction);

    // Detects if a pixels has neighbours with different values (excluding discardvalue)
    // Return value : true / false
    bool MultipleNeighs (const IndexT row, const IndexT col,
                         int neighbourhood = 8,
                         ElementT discardValue = C_MATRIX_NAN);

    // Calculates the statistical mode in the neighbours of a pixel, excluding the pixel itself
    // return value: mode value + *frecuency
    ElementT NeighMode (const IndexT row, const IndexT col,
                        int * frequency = NULL, int neighbourhood = 8,
                        ElementT discardValue = C_MATRIX_NAN);

    // Return the neighbour of a pixel with the minimal value
    // return value: pixel coordinates
    CoordT NeighMin (const IndexT row, const IndexT col,
                     int neighbourhood = 8,
                     ElementT discardValue1 = C_MATRIX_NAN,
                     ElementT discardValue2 = C_MATRIX_NAN);


    // ********** HIGH LEVEL FUNCIONS **********:


    // Fills the matrix with the gaussian distribution values of std deviation
    void Gaussian (const float std);

    // Matrix convolution. It will convolute "matrix" with "convMatrix" and store
    //   result in "this" matrix
    void Convolution (C_Matrix & matrix, C_Matrix & convMatrix);

    void GradientX       (C_Matrix & matrixIn);
    void GradientY       (C_Matrix & matrixIn);
    void Gradient        (C_Matrix & matrixIn); // sqrt(Gx*Gx + Gy*Gy)
    void Pseudogradient  (C_Matrix & matrixIn); // (Gx + Gy) / 2

    // Return a matrix that is matrixIn filtered with values != 0 in the mask.
    // mode = 0 no postprocessing
    // mode = 1  regions partially covered by mask are fully present in output
    // mode = -1 regions partially covered by mask are fully removed from output
C_ResultT Mask (C_Matrix & matrixIn, C_Matrix & mask,
                const int mode = 0, const int neighbourhood = 8);

    // Returns the number of elements filled
    long FloodFill (C_Matrix & matrix,
                    const IndexT   initRow, const IndexT initCol,
                    const ElementT newValue,
                    const int      heighbourhood = 8, // may be 4 or 8
                    const ElementT intervalRadio = 0);

    // Returns the number of elements filled
    long FloodFill (C_Matrix & matrix,
                    const IndexT   initRow, const IndexT initCol,
                    const ElementT newValue,
                    const int      heighbourhood, // may be 4 or 8
                    const ElementT intervalMin,
                    const ElementT intervalMax);

    // To use the fast version, no element of the matrix can have the value "newValue"
    // No check of this requisite will be done. If you're not sure, use the normal version
    // Returns the number of elements filled
    long FloodFillFast (C_Matrix & matrix,
                        const IndexT   initRow, const IndexT initCol,
		                const ElementT newValue,
                        const int      heighbourhood = 8, // may be 4 or 8
                        const ElementT intervalRadio = 0, // If included intervalMax, then this is intervalMin
                        const ElementT intervalMax = C_MATRIX_NAN);

    void Isolines (C_Matrix & matrixIn, const ElementT interval);

    // matrixIn must be other than "this" matrix
    // regions of size less than minSize are  discarded
    long ThresholdSeg (C_Matrix & matrixIn,
                       const ElementT min, const ElementT max,
                       long minSize = 1,
                       int neighbourhood = 8,
                       bool continuePrevSeg = false);

    // the matrix (this*) must be the same size than matrixIn and
    // have the markers set (numbered each marker from 1, 2...)
    void Watersheds (C_Matrix & matrixIn,
                     const ElementT endLevel,
                     const int neighbourhood = 8);

    void WatershedTessellation (C_Matrix & geodesic,
                                const ElementT endLevel,
                                const int neighbourhood = 8);

    // ********** INPUT OUTPUT FUNCIONS **********:

    // Prints a matrix in the stadard output. Every column is colWidth width */
    void Print (int colWidth, int maxDigits);

    // Reads a matrix from text file. First line is --> rowN colN
    void Read (const char * filePath);

    // Writes a matrix to a text file. First line is --> rowN colN
    void Write (const char * filePath);

    // Writes a matrix in nexpert NXPDB format
    C_ResultT WriteCSV (const char * filePath, const char * names[], char separator = ',', char replaceSeparator = ';');

    // Writes a matrix in nexpert NXPDB format
    C_ResultT WriteNXPDB (const char * filePath, const char * names[], const int colwidth = 15);

    // Reads a matrix from raw data in a file.
    void ReadRaw (const char * filePath,
                  const long   headerSize,
                  const IndexT rowN,      const IndexT    colN,
                  const int    bitsPixel, const C_EndianT byteOrder,
                  const bool   flip = false,
                  const int    rowBoundary = 0);

    // Idem but from an open file. FILE POINTER MUST BE LOCATED AT MATRIX BEGINNING
    void ReadRaw (C_fstream    &file,
                  const IndexT rowN,      const IndexT    colN,
                  const int    bitsPixel, const C_EndianT byteOrder,
                  const bool   flip = false,
                  const int    rowBoundary = 0);

    // Writes a matrix to a file in raw format. header must be
    // filled with the data corresponding to the desired format
    void WriteRaw (const char * filePath,
                   const long   headerSize,
                   const int    bitsPixel, const C_EndianT byteOrder,
                   const bool   flip = false,
                   const int    rowBoundary = 0,
                   const int    fileboundary = 0);

    // Idem but from an open file. FILE POINTER MUST BE LOCATED AT MATRIX BEGINNING
    void WriteRaw (C_fstream    &file,
                   const int    bitsPixel, const C_EndianT byteOrder,
                   const bool   flip = false,
                   const int    rowBoundary = 0,
                   const int    fileboundary = 0);


    /*---------------------- FUNCTIONS Jose Antonio Piedra Fernandez -----------------------------*/

    //Check the matrix Edge
    //RETURN -1(center) 0(Top-Left) 1(Top-Right) 2(Bottom-Left) 3(Bottom-Right)
    //4(Top Edge) 5(Bottom Edge) 6(Left Edge) 7(Right Edge)
    int CheckEdgeMatrix (const IndexT row, const IndexT col, const IndexT sizeconvolution);

    //Copy the matrixIn in (this)matrix for the places top-left of matrix
    void AssignTopLeft(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places top-right of matrix
    void AssignTopRight(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places bottom-left of matrix
    void AssignBottomLeft(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places bottom-right of matrix
    void AssignBottomRight(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places top-edge of matrix
    void AssignTopEdge(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places top-edge of matrix
    void AssignBottomEdge(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places left-edge of matrix
    void AssignLeftEdge(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places right-edge of matrix
    void AssignRightEdge(C_Matrix &matrixIn, const IndexT row, const IndexT col);
    //Copy the matrixIn in (this)matrix for the places center of matrix
    void AssignCenter(C_Matrix &matrixIn, const IndexT row, const IndexT col);

    //Copy the matrixIn in (this)matrix after check the matrix edge
    void AssignSubMatrix (C_Matrix &matrixIn, const IndexT row, const IndexT col);

    // Calculate Convolution. It will convolute "matrix" with "convMatrix" and store
    //   result in "this" matrix
    void CalculateConvolution (C_Matrix matrix, C_Matrix convMatrix/*,const int c=1*/);

    // Calculate Convolution. It will convolute "matrix" with
    //"Gx, Gy"(The Matrix of Convolution) and store result in "this" matrix
    void CalculateConvolution2(C_Matrix matrix, C_Matrix Gx,C_Matrix Gy/*, const int c*/);

    // Calculate Convolution. It will convolute "matrix" with
    //"Gx, Gy, Gdp and Gds"(The Matrix of Convolution, Horizontal,Vertical,+45º and -45º)
    // and store result in "this" matrix
    void CalculateConvolution4(C_Matrix matrix, C_Matrix Gx,C_Matrix Gy, C_Matrix Gdp,C_Matrix Gds/*, const int c*/);

    //Sort the matrix
    void Sort();

    //Matrix median filter. It will apply median filter to "matrixIn" and store
    //result in "this" matrix
    void MedianFilter(C_Matrix & matrix, IndexT sizeConv);

    //Matrix mean filter. It will apply mean filter to "matrixIn" and store
    //result in "this" matrix
    void MeanFilter(C_Matrix & matrix, IndexT sizeConv);

    void Threshold(const ElementT low, const ElementT high,const ElementT min,const ElementT max);
    void AdaptativeThreshold(const IndexT T, const IndexT sizeLocal, const ElementT min,const ElementT max);

    void Contrast(const ElementT r1,const ElementT s1,const ElementT r2,const ElementT s2,const ElementT min, const ElementT max);

    //The negative image to scale of gray
    void Negative(const ElementT escalar);

     //Matrix Conservation filter. It will apply conservation filter to "matrixIn" and store
    //result in "this" matrix
    void ConservationFilter(C_Matrix & matrix, IndexT sizeConv);

     //Matrix Crimmins Speckel Remove. It will apply Crimmins Speckel Remove to "matrixIn" and store
    //result in "this" matrix
    void CrimminsFilter(C_Matrix & matrix, int isDark);

    //Calculate The Laplacian of Gaussian.(Parameter In -> standar desviation)
    void LoG(const ElementT desv);

    //Matrix Laplacian of Gaussian filter. It will apply LoG filter to "matrixIn" and store
    //result in "this" matrix
    void LoGFilter(C_Matrix & matrix, const ElementT desviation, const ElementT umbral, const IndexT sizeConv,const ElementT min,const ElementT max);

    //Return the convolution matrix of Low Pass
    void Lowpass(const ElementT number);

    //Return the convolution matrix of Low Pass
    void Highpass(const ElementT number);

    //Return the convolution matrix of High Boost
    void HighBoost(C_Matrix &conv,const ElementT A);

    //Logarithm Operator
    void Logarithm(const ElementT min, const ElementT max);

    //Exponential Operator
    void Exponential(const ElementT b,const ElementT min,const ElementT max);

    //Gamma Operator
    void Gamma(const ElementT g, const ElementT min, const ElementT max);

    //Uniform Operator
    void Uniform(const ElementT min, const ElementT max);

    //Calculate Histogram
    void CalculateHistogram(C_Matrix &histogram);

    //Equality of Histogram
    void EqualizeHistogram(C_Matrix &hist);

    /*---------------------- END FUNCTIONS Jose Antonio Piedra Fernandez -----------------------------*/
};



/*---------------------------- FUNCTIONS ----------------------------------*/


#endif

