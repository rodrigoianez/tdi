#include <math.h>
#include <fcntl.h>

#include <time.h>

#include <C_General.hpp>
#include <C_Trace.hpp>
#include <C_File.hpp>
#include <C_Arguments.hpp>
#include <C_Matrix.hpp>
#include <C_Image.hpp>

//---------------------------------------------------------------------------

// En este fichero se incluyen ejemplos de uso de las funciones de IMtdi.
// Todas ellas pueden borrarse tranquilamente o mantenerlas como referencia.
// El contenido de la función main() se sustituirá por el código adecuado a la práctica.


void Pause();
void EjemplosMatrices();
void EjemplosSegmentacion();
void TestGeneral();
void TestTrace();
void TestFile();
void TestArguments(int argc, char ** argv);
void TestMatrix();
void TestMatrixOperators();
void Testimage();

int Test(int argc, char **argv)
{
  EjemplosMatrices();
  EjemplosSegmentacion();

  TestGeneral();
  TestTrace();
  TestFile();
  TestArguments(argc, argv);
  TestMatrix();
  TestMatrixOperators();
  Testimage();

  Pause();
  return 0;
}

void Pause()
{
  C_Print ("Press ENTER to continue.");
  getchar (); /* wait for input */
}


void EjemplosMatrices_C_Matrix_1()
{
  printf ("C_Matrix\n\n");

  C_Matrix matriz;
}

void EjemplosMatrices_C_Matrix_2()
{
  printf ("C_Matrix (1, 5, 1, 5, 9)\n\n");

  C_Matrix matriz (1, 5, 1, 5, 9);

  matriz.Print(1, 1);
}

void EjemplosMatrices_C_Matrix_3()
{
  printf ("C_Matrix\n\n");

  C_Matrix matriz (1, 5, 1, 5);
  C_Matrix submatriz (matriz, -1, 1, -1, 1, 1, 2);

  matriz.Rand(0, 9);
  matriz.Print(2, 1);
  printf ("\n\nC_Matrix submatriz (matriz, -1, 1, -1, 1, 1, 2)\n\n");
  submatriz.Print(2,1);
}

void EjemplosMatrices_Free()
{
  printf ("Free()\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  // . . .
  matriz.Free();
}

void EjemplosMatrices_Empty()
{
  printf ("Empty()\n\n");

  C_Matrix matriz;

  // . . .
  if ( matriz.Empty() ) { printf("Matriz vacía\n"); }
}

void EjemplosMatrices_MatrixDataAccess()
{
  printf ("FirstRow, LastRow, FirstCol, LastCol, Fail, SetFail, Clear\n\n");
  bool fallo = true;

  C_Matrix::IndexT fila, col;
  C_Matrix matriz (1, 5, 1, 5);

  for (fila = matriz.FirstRow(); fila <= matriz.LastRow(); fila++)
    for (col = matriz.FirstCol(); col <= matriz.LastCol(); col++)
    {
      // . . .
      if ( fallo ) { matriz.SetFail(); }
      // . . .
    }

  if ( matriz.Fail() )
  {
    printf ("Se ha simulado un fallo\n");
    matriz.Clear();
  }
}

void EjemplosMatrices_ElementAccess()
{
  printf ("Acceso a elementos\n\n");
  double dato;

  C_Matrix matriz (1, 5, 1, 5);

  dato = matriz(2, 3);
  // . . .
  matriz(1, 5) = 3;

  matriz.Print(1, 1);
}

void EjemplosMatrices_OperatorEq()
{
  printf ("Operador =\n\n");

  C_Matrix A (1, 5, 1, 5, 7);
  C_Matrix B;

  // . . .
  B = A;

  B.Print(1, 1);
}

void EjemplosMatrices_Reindex()
{
  printf ("Reindex\n\n");

  C_Matrix matriz (0, 4, 0, 4);

  /* . . . */ matriz.Rand(0, 9);
  /* . . . */ matriz.Print(1, 1);
  matriz.Reindex(1, 1);

  printf ("\n\nmatriz.Reindex(1, 1)\n\n");
  matriz.Print(1, 1);
}

void EjemplosMatrices_Resize()
{
  printf ("Resize\n\n");

  C_Matrix matriz (0, 4, 0, 4);

  /* . . . */ matriz.Rand(0, 9);
  /* . . . */ matriz.Print(1, 1);
  matriz.Resize(1, 6, 1, 6, 0);

  printf ("\n\nmatriz.Resize(1, 6, 1, 6, 0)\n\n");
  matriz.Print(1, 1);
}

void EjemplosMatrices_MoveSubMat()
{
  printf ("MoveSubMat\n\n");

  C_Matrix matriz (1, 5, 1, 5);
  C_Matrix submatriz (matriz, -1, 1, -1, 1, 1, 2);

  /* . . . */ matriz.Rand(0, 9);
  /* . . . */ matriz.Print(2, 1);
  submatriz.MoveSubMat(2,3);

  printf ("\n\nsubmatriz.MoveSubMat(2,3)\n\n");
  submatriz.Print(2, 1);
}

void EjemplosMatrices_Statistic()
{
  printf ("Min, Max, Sum, Mean, Mode\n\n");

  C_Matrix matriz (1, 5, 1, 5);
  C_Matrix::ElementT min, max, sum, mean, mode;
  long int frec;

  /* . . . */ matriz.Rand(0, 9);
  min  = matriz.Min();
  max  = matriz.Max();
  sum  = matriz.Sum();
  mean = matriz.Mean();
  mode = matriz.Mode(&frec);

  matriz.Print(1, 1);
  printf ("\n");
  printf ("Min  = %3d    Max  = %3d\n", (int)min, (int)max);
  printf ("Sum  = %3d    Mean = %6.2f\n", (int)sum, mean);
  printf ("Mode = %3d    Frec = %3ld\n", (int)mode, frec);
}

void EjemplosMatrices_SetValue1()
{
  printf ("SetValue(9)\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  matriz.SetValue(9);

  matriz.Print(1, 1);
}

void EjemplosMatrices_SetValue2()
{
  printf ("SetValue\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 1);
  /* . . . */ matriz.Print(1, 1);
  matriz.SetValue(0, 9);

  printf ("\n\nSetValue(0, 9)\n\n");
  matriz.Print(1, 1);
}

void EjemplosMatrices_SetValue3()
{
  printf ("SetValue\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(1, 9);
  /* . . . */ matriz.Print(1, 1);
  matriz.SetValue(1, 5, 0);

  printf ("\n\nSetValue(1, 5, 0)\n\n");
  matriz.Print(1, 1);
}

void EjemplosMatrices_Serie()
{
  printf ("Serie(11, 10, 1)\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  matriz.Serie(11, 10, 1);

  matriz.Print(2, 2);
}

void EjemplosMatrices_Trunc()
{
  printf ("Trunc\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 30);
  /* . . . */ matriz.Print(2, 2);
  matriz.Trunc(10, 20);

  printf ("\n\nTrunc(10, 20)\n\n");
  matriz.Print(2, 2);
}

void EjemplosMatrices_Stretch()
{
  printf ("Stretch\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 30);
  /* . . . */ matriz.Print(2, 2);
  matriz.Stretch(10, 20);

  printf ("\n\nStretch(10, 20)\n\n");
  matriz.Print(4, 3);
}

void EjemplosMatrices_Abs()
{
  printf ("Abs\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(-9, 9);
  /* . . . */ matriz.Print(2, 1);
  matriz.Abs();

  printf ("\nAbs()\n\n");
  matriz.Print(2, 1);
}

void EjemplosMatrices_Add()
{
  printf ("Add\n\n");

  C_Matrix matriz1 (1, 5, 1, 5);
  C_Matrix matriz2 (1, 5, 1, 5);
  C_Matrix matriz3;

  /* . . . */ matriz1.Rand(1, 10);
  /* . . . */ matriz2.Rand(1, 10);
  /* . . . */ matriz1.Print(2, 2);
  /* . . . */ matriz2.Print(2, 2);
  matriz3.Add(matriz1, matriz2);

  printf ("Add(matriz1, matriz2)\n");
  matriz3.Print(2, 2);
}

void EjemplosMatrices_Subtract()
{
  printf ("Subtract\n\n");

  C_Matrix matriz1 (1, 5, 1, 5);
  C_Matrix matriz2 (1, 5, 1, 5);
  C_Matrix matriz3;

  /* . . . */ matriz1.Rand(1, 10);
  /* . . . */ matriz2.Rand(1, 10);
  /* . . . */ matriz1.Print(2, 2);
  /* . . . */ matriz2.Print(2, 2);
  matriz3.Subtract(matriz1, matriz2);

  printf ("Subtract(matriz1, matriz2)\n");
  matriz3.Print(2, 2);
}

void EjemplosMatrices_MultiplyElm()
{
  printf ("MultiplyElm\n\n");

  C_Matrix matriz1 (1, 5, 1, 5);
  C_Matrix matriz2 (1, 5, 1, 5);
  C_Matrix matriz3;

  /* . . . */ matriz1.Rand(1, 10);
  /* . . . */ matriz2.Rand(1, 9);
  /* . . . */ matriz1.Print(2, 2);
  /* . . . */ matriz2.Print(2, 2);
  matriz3.MultiplyElm(matriz1, matriz2);

  printf ("MultiplyElm(matriz1, matriz2)\n");
  matriz3.Print(2, 2);
}

void EjemplosMatrices_DivideElm()
{
  printf ("DivideElm\n\n");

  C_Matrix matriz1 (1, 5, 1, 5);
  C_Matrix matriz2 (1, 5, 1, 5);
  C_Matrix matriz3;

  /* . . . */ matriz1.Rand(1, 10);
  /* . . . */ matriz2.Rand(1, 10);
  /* . . . */ matriz1.Print(4, 2);
  /* . . . */ matriz2.Print(4, 2);
  matriz3.DivideElm(matriz1, matriz2);

  printf ("DivideElm(matriz1, matriz2)\n");
  matriz3.Print(4, 2);
}

void EjemplosMatrices_AddEscalar()
{
  printf ("AddEscalar\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 9);
  /* . . . */ matriz.Print(2, 2);
  matriz.AddEscalar(10);

  printf ("\n\nAddEscalar(10)\n\n");
  matriz.Print(2, 2);
}

void EjemplosMatrices_SubtractEscalar()
{
  printf ("SubtractEscalar\n\n");

  C_Matrix matriz (1, 5, 1, 5);
  

  /* . . . */ matriz.Rand(10, 19);
  /* . . . */ matriz.Print(2, 2);
  matriz.SubtractEscalar(10);

  printf ("\n\nSubtractEscalar(10)\n\n");
  matriz.Print(2, 2);
}

void EjemplosMatrices_SubtractFromEscalar()
{
  printf ("SubtractFromEscalar\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(1, 10);
  /* . . . */ matriz.Print(2, 2);
  matriz.SubtractFromEscalar(10);

  printf ("\n\nSubtractFromEscalar(10)\n\n");
  matriz.Print(2, 2);
}

void EjemplosMatrices_MultiplyEscalar()
{
  printf ("MultiplyEscalar\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 9);
  /* . . . */ matriz.Print(3, 2);
  matriz.MultiplyEscalar(10);

  printf ("\n\nMultiplyEscalar(10)\n\n");
  matriz.Print(3, 2);
}

void EjemplosMatrices_DivideEscalar()
{
  printf ("DivideEscalar\n\n");

  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 9);
  /* . . . */ matriz.Print(3, 2);
  matriz.DivideEscalar(10);

  printf ("\n\nDivideEscalar(10)\n\n");
  matriz.Print(3, 2);
}

void EjemplosMatrices_Gaussian()
{
  printf ("Gaussian()\n\n");

  C_Matrix matriz (-2, 2, -2, 2);

  matriz.Gaussian(0.5);

  matriz.Print(7, 2);
  printf("\nSuma:%f\n", matriz.Sum());
}

void EjemplosMatrices_Convolution()
{
  printf ("Convolution\n\n");

  C_Matrix matriz1 (1, 10, 1, 10);
  C_Matrix matriz2 (-1, 1, -1, 1);
  C_Matrix matriz3;

  /* . . . */ matriz1.Rand(1, 10);
  /* . . . */ matriz2.Gaussian((float)0.2);
  /* . . . */ matriz1.Print(3, 2);
  /* . . . */ matriz2.Print(7, 2);
  /* . . . */ matriz2.DivideEscalar(matriz2.Sum());
  matriz3.Convolution(matriz1, matriz2);

  printf ("\nConvolution(matriz1, matriz2)\n\n");
  matriz3.Print(3, 2);
}

void EjemplosMatrices_Print()
{
  printf ("Print\n\n");
  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 9);
  matriz.Print(3, 1);
}

void EjemplosMatrices_Write()
{
  printf ("Write\n\n");
  C_Matrix matriz (1, 5, 1, 5);

  /* . . . */ matriz.Rand(0, 9);

  matriz.Write("Matriz.txt");

  printf ("Fin\n");
}

void EjemplosMatrices_Read()
{
  printf ("Read\n\n");
  C_Matrix matriz;

  matriz.Read("Matriz.txt");

  matriz.Print(3, 1);
}


void EjemplosMatrices()
{
  EjemplosMatrices_C_Matrix_1();
  Pause();
  EjemplosMatrices_C_Matrix_2();
  Pause();
  EjemplosMatrices_C_Matrix_3();
  Pause();
  EjemplosMatrices_Free();
  Pause();
  EjemplosMatrices_Empty();
  Pause();
  EjemplosMatrices_MatrixDataAccess();
  Pause();
  EjemplosMatrices_ElementAccess();
  Pause();
  EjemplosMatrices_OperatorEq();
  Pause();
  EjemplosMatrices_Reindex();
  Pause();
  EjemplosMatrices_Resize();
  Pause();
  EjemplosMatrices_MoveSubMat();
  Pause();
  EjemplosMatrices_Statistic();
  Pause();
  EjemplosMatrices_SetValue1();
  Pause();
  EjemplosMatrices_SetValue2();
  Pause();
  EjemplosMatrices_SetValue3();
  Pause();
  EjemplosMatrices_Serie();
  Pause();
  EjemplosMatrices_Trunc();
  Pause();
  EjemplosMatrices_Stretch();
  Pause();
  EjemplosMatrices_Abs();
  Pause();
  EjemplosMatrices_Add();
  Pause();
  EjemplosMatrices_Subtract();
  Pause();
  EjemplosMatrices_MultiplyElm();
  Pause();
  EjemplosMatrices_DivideElm();
  Pause();
  EjemplosMatrices_AddEscalar();
  Pause();
  EjemplosMatrices_SubtractEscalar();
  Pause();
  EjemplosMatrices_SubtractFromEscalar();
  Pause();
  EjemplosMatrices_MultiplyEscalar();
  Pause();
  EjemplosMatrices_DivideEscalar();
  Pause();
  EjemplosMatrices_Gaussian();
  Pause();
  EjemplosMatrices_Convolution();
  Pause();
  EjemplosMatrices_Print();
  Pause();
  EjemplosMatrices_Write();
  Pause();
  EjemplosMatrices_Read();
  Pause();

}


void EjemplosSegmentacion_Gradient()
{
  printf ("Gradient\n\n");

  C_Matrix matriz1 (1, 5, 1, 5);
  C_Matrix matriz2;

  /* . . . */ matriz1.Rand(0, 9);
  /* . . . */ matriz1.Print(4, 2);
  matriz2.GradientX(matriz1);

  printf ("\n\nGradientX()\n\n");
  matriz2.Print(4, 2);
  Pause();

  matriz2.GradientY(matriz1);

  printf ("\n\nGradientY()\n\n");
  matriz2.Print(4, 2);
  Pause();


  matriz2.Gradient(matriz1);

  printf ("\n\nGradient()\n\n");
  matriz2.Print(4, 2);
  Pause();


  matriz2.Pseudogradient(matriz1);

  printf ("\n\nPseudogradient()\n\n");
  matriz2.Print(4, 2);
}


void EjemplosSegmentacion_FloodFill1()
{
  printf ("FloodFill\n\n");

  C_Image imagen1;
  C_Image imagen2;

  imagen1.ReadBMP("Hercules_Gris.bmp");

  imagen2.FloodFill(imagen1, 140, 90, 255, 4);

  imagen2.SubtractFromEscalar(255);
  imagen2.palette = imagen1.palette;
  imagen2.WriteBMP("Camiseta.bmp");
  printf ("Fin\n");
}

void EjemplosSegmentacion_FloodFill2()
{
  printf ("FloodFill\n\n");

  C_Image imagen1;
  C_Image imagen2;

  imagen1.ReadBMP("Hercules_Gris.bmp");

  imagen2.FloodFill(imagen1, 80, 100, 255, 8, 35);

  imagen2.SubtractFromEscalar(255);
  imagen2.palette = imagen1.palette;
  imagen2.WriteBMP("Cara.bmp");
  printf ("Fin\n");
}

void EjemplosSegmentacion_FloodFill3()
{
  printf ("FloodFill\n\n");

  C_Image imagen1;
  C_Image imagen2;

  imagen1.ReadBMP("Hercules_Gris.bmp");

  imagen2.FloodFill(imagen1, 80, 100, 255, 8, 0, 240);

  imagen2.SubtractFromEscalar(255);
  imagen2.palette = imagen1.palette;
  imagen2.WriteBMP("Figura.bmp");
  printf ("Fin\n");
}

void EjemplosSegmentacion_Isolines()
{
  printf ("Isolines\n\n");

  C_Image imagen1;
  C_Image imagen2;

  imagen1.ReadBMP("Aguadulce_Gris.bmp");

  imagen2.Isolines(imagen1, 1);
  printf ("Min= %d   Max= %d\n", (int)(imagen2.Min()), (int)(imagen2.Max()));

  imagen2.MultiplyEscalar(3);
  imagen2.Trunc(0, 255);
  imagen2.SubtractFromEscalar(255);
  imagen2.palette = imagen1.palette;
  imagen2.WriteBMP("AguadulceIsolines.bmp");
  printf ("Fin\n");
}

void EjemplosSegmentacion_ThresholdSeg()
{
  printf ("ThresholdSeg\n\n");

  C_Image imagen1;
  C_Image imagen2;
  long int numRegiones;

  imagen1.ReadBMP("Ajedrez_Gris.bmp");

  numRegiones = imagen2.ThresholdSeg(imagen1, 165, 255, 50);
  printf ("numRegiones= %ld\n", numRegiones);

  imagen2.palette.Read("PaletaSurtida256.txt");
  imagen2.WriteBMP("PeonesBlancos.bmp");
  printf ("Fin\n");
}


void EjemplosSegmentacion_ThresholdSeg2()
{
  printf ("ThresholdSeg 2\n\n");

  C_Image imagen1;
  C_Image imagen2;
  long int numRegiones;

  imagen1.ReadBMP("Ajedrez_Gris.bmp");

  imagen2.ThresholdSeg(imagen1, 165, 255, 5000, 8, false);
  numRegiones = imagen2.ThresholdSeg(imagen1, 0,    95, 5000, 8, true);
  printf ("numRegiones= %ld\n", numRegiones);

  imagen2.palette.Read("PaletaSurtida256.txt");
  imagen2.WriteBMP("Peones.bmp");
  printf ("Fin\n");
}


void EjemplosSegmentacion_Watershed()
{
  printf ("Watershed\n\n");

  C_Image imagen;
  C_Image gradiente;
  C_Image watershed;
  long int numRegiones;

  imagen.ReadBMP("Alumina.bmp");
  gradiente.Gradient(imagen);

  numRegiones = watershed.ThresholdSeg(gradiente, 30, gradiente.Max());
  printf ("numRegiones= %ld\n", numRegiones);

  watershed.WatershedTessellation(gradiente, gradiente.Max());

  watershed.palette.Read ("PaletaSurtida256.txt");
  watershed.WriteBMP("Alumina_Watershed.bmp");
  printf ("Fin\n");
}

void EjemplosSegmentacion()
{
  EjemplosSegmentacion_Gradient();
  Pause();
  EjemplosSegmentacion_FloodFill1();
  Pause();
  EjemplosSegmentacion_FloodFill2();
  Pause();
  EjemplosSegmentacion_FloodFill3();
  Pause();
  EjemplosSegmentacion_Isolines();
  Pause();
  EjemplosSegmentacion_ThresholdSeg();
  Pause();
  EjemplosSegmentacion_ThresholdSeg2();
  Pause();
  EjemplosSegmentacion_Watershed();
  Pause();
}

void TestGeneral()
{
  float  f4;
  double f8;

  C_Trace ("");
  C_Trace ("TEST: General");

  C_IfWarning (C_littleEndian, "Ordenador little endian");
  C_IfWarning (C_bigEndian,    "Ordenador big endian");

  f8 = C_DOUBLE_INF;
  C_TraceNum ("Infinity", f8);
  f8 = C_DOUBLE_M_INF;
  C_TraceNum ("Negative infinity", f8);
  f8 = C_DOUBLE_NAN;
  C_TraceNum ("Not a number", f8);
  f8 = C_DOUBLE_M_NAN;
  C_TraceNum ("Negative not a number", f8);

  f4 = (float)C_DOUBLE_INF;
  C_TraceNum ("Float infinity", f4);
  f4 = (float)C_DOUBLE_M_INF;
  C_TraceNum ("Float negative infinity", f4);
  f4 = (float)C_DOUBLE_NAN;
  C_TraceNum ("Float not a number", f4);
  f4 = (float)C_DOUBLE_M_NAN;
  C_TraceNum ("Float negative not a number", f4);

  Pause();
}


void TestTrace()
{
  char errStr [] = "<error string>";
  
  C_Trace ("");
  C_Trace ("TEST: Trace");

  C_Trace             ("It must count from 1 to 10");
  C_Trace             (" 1 C_Trace");
  C_Warning           (" 2 C_Warning");
  C_IfWarning (1 == 2, " * C_IfWarning");
  C_IfWarning (1 != 2, " 3 C_IfWarning");
  C_Error             (" 4 C_Error", );
  C_IfError   (1 == 2, " * C_IfError", );
  C_IfError   (1 != 2, " 5 C_IfError", );
  C_TraceNum          (" 6 C_TraceNum (Int)", 30);
  C_TraceNum          (" 7 C_TraceNum (Float)", 1.0/3);
  C_Trace2Num         (" 8 C_Trace2Num", exp (-100.0), exp(100.0));
  C_IfErrorStr(1 != 2, " 9 C_IfErrorStr", errStr, );
  C_TraceBytes        ("10 C_TraceBytes", errStr, 10);
  C_Trace ("PRESS A KEY");
  Pause();
}

void TestFile()
{
  char           i1;
  //unsigned char ui1;
  short          i2;
  long           i4;
  float          f4;
  double         f8;

  C_fstream testFile;
  //int checkFile;


  C_Trace ("");
  C_Trace ("TEST: File");

  testFile.C_WriteIntBigEndian    (0x21, 1);
  C_IfError (testFile.fail(), "Aqui debe dar un error por escribir antes de abrir el fichero",);

  testFile.clear();

  testFile.open("prueba.bin", ios::out | ios::trunc | ios::binary);
  C_IfError (testFile.fail(), "Error abriendo el fichero",);

  testFile.C_WriteIntBigEndian    (0x21, 1);
  testFile.C_WriteIntLittleEndian (0x21, 1);
  testFile.C_WriteIntBigEndian    (0xFF, 1);
  testFile.C_WriteIntLittleEndian (0xFF, 1);
  testFile.C_WriteIntBigEndian    (-0x21, 1);
  testFile.C_WriteIntLittleEndian (-0x21, 1);
  testFile.C_WriteIntBigEndian    (0x4321, 2);
  testFile.C_WriteIntLittleEndian (0x4321, 2);
  testFile.C_WriteIntBigEndian    (-0x4321, 2);
  testFile.C_WriteIntLittleEndian (-0x4321, 2);
  testFile.C_WriteIntBigEndian    (0x77654321, 4);
  testFile.C_WriteIntLittleEndian (0x77654321, 4);
  testFile.C_WriteIntBigEndian    (-0x77654321, 4);
  testFile.C_WriteIntLittleEndian (-0x77654321, 4);
  testFile.C_WriteFloat32BigEndian    (numeric_limits<float>::max());
  testFile.C_WriteFloat32LittleEndian (numeric_limits<float>::max());
  testFile.C_WriteFloat64BigEndian    (numeric_limits<double>::max());
  testFile.C_WriteFloat64LittleEndian (numeric_limits<double>::max());
  testFile.close();


  /* No disponible en Visual Studio 2010

  C_Trace ("COMPROBACION DE WriteIntBigEndian");
  C_Trace ("DEBE LEER BIEN EL QUE COINCIDA CON EL TIPO DE MAQUINA");
  checkFile = open("prueba.bin", O_RDWR | O_CREAT | O_BINARY	);

  read (checkFile, &i1, 1);
  C_TraceNum ("BigEndian    0x21", i1);
  read (checkFile, &i1, 1);
  C_TraceNum ("LittleEndian 0x21", i1);

  read (checkFile, &ui1, 1);
  C_TraceNum ("BigEndian    0xFF", ui1);
  read (checkFile, &ui1, 1);
  C_TraceNum ("LittleEndian 0xFF", ui1);

  read (checkFile, &i1, 1);
  C_TraceNum ("BigEndian    -0x21", i1);
  read (checkFile, &i1, 1);
  C_TraceNum ("LittleEndian -0x21", i1);

  read (checkFile, &i2, 2);
  C_TraceNum ("BigEndian    0x4321", i2);
  read (checkFile, &i2, 2);
  C_TraceNum ("LittleEndian 0x4321", i2);
  read (checkFile, &i2, 2);
  C_TraceNum ("BigEndian    -0x4321", i2);
  read (checkFile, &i2, 2);
  C_TraceNum ("LittleEndian -0x4321", i2);

  read (checkFile, &i4, 4);
  C_TraceNum ("BigEndian    0x77654321", i4);
  read (checkFile, &i4, 4);
  C_TraceNum ("LittleEndian 0x77654321", i4);
  read (checkFile, &i4, 4);
  C_TraceNum ("BigEndian    -0x77654321", i4);
  read (checkFile, &i4, 4);
  C_TraceNum ("LittleEndian -0x77654321", i4);

  read (checkFile, &f4, 4);
  C_Trace2Num ("BigEndian MaxFloat", numeric_limits<float>::max(), f4);
  read (checkFile, &f4, 4);
  C_Trace2Num ("LittleEndian MaxFloat", numeric_limits<float>::max(), f4);

  read (checkFile, &f8, 8);
  C_Trace2Num ("BigEndian MaxDouble", numeric_limits<double>::max(), f8);
  read (checkFile, &f8, 8);
  C_Trace2Num ("LittleEndian MaxDouble", numeric_limits<double>::max(), f8);

  close(checkFile);

  Pause();
  C_Trace ("");

  */

  C_Trace ("COMPROBACION DE WriteIntBigEndian y ReadIntBigEndian");
  C_Trace ("DEBE LEER BIEN TODOS");
  testFile.open("prueba.bin", ios::in | ios::binary);

  i1 = (char) testFile.C_ReadIntBigEndian (1);
  C_TraceNum ("BigEndian    0x21", i1);
  i1 = (char) testFile.C_ReadIntLittleEndian (1);
  C_TraceNum ("LittleEndian 0x21", i1);

  i1 = (char) testFile.C_ReadIntBigEndian (1);
  C_TraceNum ("BigEndian    0xFF", i1);
  i1 = (char) testFile.C_ReadIntLittleEndian (1);
  C_TraceNum ("LittleEndian 0xFF", i1);

  i1 = (char) testFile.C_ReadIntBigEndian (1);
  C_TraceNum ("BigEndian    -0x21", i1);
  i1 = (char) testFile.C_ReadIntLittleEndian (1);
  C_TraceNum ("LittleEndian -0x21", i1);

  i2 = (short) testFile.C_ReadIntBigEndian (2);
  C_TraceNum ("BigEndian    0x4321", i2);
  i2 = (short) testFile.C_ReadIntLittleEndian (2);
  C_TraceNum ("LittleEndian 0x4321", i2);
  i2 = (short) testFile.C_ReadIntBigEndian (2);
  C_TraceNum ("BigEndian    -0x4321", i2);
  i2 = (short) testFile.C_ReadIntLittleEndian (2);
  C_TraceNum ("LittleEndian -0x4321", i2);

  i4 = testFile.C_ReadIntBigEndian (4);
  C_TraceNum ("BigEndian    0x77654321", i4);
  i4 = testFile.C_ReadIntLittleEndian (4);
  C_TraceNum ("LittleEndian 0x77654321", i4);
  i4 = testFile.C_ReadIntBigEndian (4);
  C_TraceNum ("BigEndian    -0x77654321", i4);
  i4 = testFile.C_ReadIntLittleEndian (4);
  C_TraceNum ("LittleEndian -0x77654321", i4);

  f4 = testFile.C_ReadFloat32BigEndian();
  C_Trace2Num ("BigEndian MaxFloat", numeric_limits<float>::max(), f4);
  f4 = testFile.C_ReadFloat32LittleEndian();
  C_Trace2Num ("LittleEndian MaxFloat", numeric_limits<float>::max(), f4);

  f8 = testFile.C_ReadFloat64BigEndian();
  C_Trace2Num ("BigEndian MaxDouble", numeric_limits<double>::max(), f8);
  f8 = testFile.C_ReadFloat64LittleEndian();
  C_Trace2Num ("LittleEndian MaxDouble", numeric_limits<double>::max(), f8);

  testFile.close();


  Pause();
}


void TestArguments(int argc, char * argv[])
{
  C_Trace ("");
  C_Trace ("TEST: Arguments");

  C_Arguments arguments (argc, argv, 2, 4, "atx", false);
  if ( arguments.Fail() )
  {
    printf ("\n Uso: %s p1 p2 [p3] [p4] [/a] [/t] [/x]\n", (C_ExtractFileName(arguments.Param(0))).c_str());
    printf ("Pulsa una tecla\n");
    Pause();
  }

  arguments.Log (NULL, NULL);

  if (arguments.Option('a'))
  {
    C_Trace ("opcion ---> /a");
    if (arguments.OptionValue('a'))
      C_TraceStr ("opcion ---> a con valor", arguments.OptionValueStr('a') );
  }

  C_TraceStr ("El parametro 1 es", arguments.Param(1));


  Pause();
}


void TestMatrix()
{
  C_Matrix::IndexT row, col;

  C_Trace ("");
  C_Trace ("");
  C_Trace ("TEST: Matrix basics");
  C_Trace ("");

  C_Matrix matrixWrong (7, 0, 3, 9, 4.0/3.0);
  C_IfError (matrixWrong.Fail(), "Error creating a new matrix", printf ("Ha habido un error ESTABA PREVISTO\n"););
  matrixWrong.Clear();

  C_Trace ("Matrix creation");
  C_Matrix matrix (0, 7, 3, 9, 4.0/3.0);
  matrix.Print (5,2);

  Pause();
  
  C_Trace ("Matrix data access");
  for (row = matrix.FirstRow(); row <= matrix.LastRow(); row++)
    for (col = matrix.FirstCol(); col <= matrix.LastCol(); col++)
        matrix(row,col) = (row*10+col);
  matrix.Print (2,2);

  C_Trace ("Submatrix at (1, 4)");
  C_Matrix submatrix (matrix, 2, 5, 5, 8, 1, 4);
  submatrix.Print (2,2);

  Pause();

  C_Trace ("Submatrix of submatrix at (3, 6)");
  C_Matrix submatrix2 (submatrix, -1, 1, -1, 1, 3, 6);
  submatrix2.Print (2,2);
  printf ("\n");

  Pause();

  C_Trace ("Modification of supermatrix through submatrix");
  for (row = submatrix.FirstRow(); row <= submatrix.LastRow(); row++)
    for (col = submatrix.FirstCol(); col <= submatrix.LastCol(); col++)
        submatrix(row,col) = 0;
  matrix.Print (2,2);

  Pause();

  C_Trace ("Modification of supermatrix through submatrix of submatrix");
  for (row = submatrix2.FirstRow(); row <= submatrix2.LastRow(); row++)
    for (col = submatrix2.FirstCol(); col <= submatrix2.LastCol(); col++)
        submatrix2(row,col) = 7;
  matrix.Print (2,2);
  printf ("\n");

  Pause();

  C_Trace ("Restoring best visible values");
  for (row = matrix.FirstRow(); row <= matrix.LastRow(); row++)
    for (col = matrix.FirstCol(); col <= matrix.LastCol(); col++)
        matrix(row,col) = (row*10+col);
  matrix.Print (2,2);

  C_Trace ("Matrix copy. NEW MATRIX:");
  C_Matrix matrix2;
  matrix2 = matrix;
  matrix2.Print (2,2);

  Pause();

  C_Trace ("Matrix resize");
  matrix2.Resize (-1, 3, -1, 6, -2);
  matrix2.Print (2,2);

  Pause();

  C_Trace ("Try to resize a matrix with submatrices (There'll be ERROR):");
  matrix.Resize (-1, 3, -1, 6, -2);
  C_IfError (matrix.Fail(), "Couldn't resize.", matrix.Clear());

  Pause();

  C_Trace ("");
  C_Trace ("");
  C_Trace ("Matrix:");
  matrix.Print (2,2);
  C_Trace ("Subatrix:");
  submatrix.Print (2,2);
  submatrix2.Free();

  Pause();

  C_Trace ("Submatrix resize");
  submatrix.Resize (-2, 2, -2, 2);
  submatrix.Print (2,2);

  Pause();

  C_Trace ("Submatrix move to (2, 5)");
  submatrix.MoveSubMat (2, 5);
  submatrix.Print (2,2);


  Pause();

  submatrix2.Free();
  submatrix.Free();
}


void TestMatrixOperators()
{
  C_Matrix::IndexT row, col;

  C_Matrix mat1 (-2, 2, -4, 5, 0);
  C_Matrix mat2 (-2, 2, -4, 5, 0);
  for (row = mat1.FirstRow(); row <= mat1.LastRow(); row++)
    for (col = mat1.FirstCol(); col <= mat1.LastCol(); col++)
        mat1(row,col) = (row*10+col);

  for (row = mat2.FirstRow(); row <= mat2.LastRow(); row++)
    for (col = mat2.FirstCol(); col <= mat2.LastCol(); col++)
        mat2(row,col) = col;

  mat1.Print (3,2);

  C_TraceNum ("Minimum", mat1.Min());
  C_TraceNum ("Maximum", mat1.Max());
  C_TraceNum ("Sum    ", mat1.Sum());
  C_TraceNum ("Mean   ", mat1.Mean());

  Pause();

}


void Testimage()
{
  C_Image::IndexT row, col;
  C_Image image, image2;
  clock_t initTime;

  initTime = clock();

  C_Trace ("Reading image");
  image.ReadBMP ("Hercules.bmp");
  C_IfError (image.Fail(), "Could not read the image file", return);

  C_TraceNum ("Image to greyscale", clock() - initTime);
  image.Grey ();
  C_Trace ("Writing image");
  image.WriteBMP("Hercules_Grey.bmp");

  C_Trace ("Image to negative");
  for (row = image.FirstRow(); row <= image.LastRow(); row++)
    for (col = image.FirstCol(); col <= image.LastCol(); col++)
        image(row,col) = 255 - image(row,col);
  C_Trace ("Writing image");
  image.WriteBMP("Hercules_Negative.bmp");

  C_Trace ("Extracting t-shirt");
  image2.Free();
  image2.palette = image.palette;
  image2.palette (1, C_RED) = 255;  //(Indice 1, componente Rojo) = 255
  image2.FloodFill (image, 140, 90, 1, 4);
  C_Trace ("Writing image");
  image2.WriteBMP("Hercules_JustTheShirt.bmp");

  C_Trace ("Coloring t-shirt");
  image.FloodFill (image, 140, 90, 0, 4);
  C_Trace ("Writing image");
  image.WriteBMP("Hercules_BlackShirt.bmp");

  C_IfError (image.Fail(), "There was an error in the image process", return);
  C_IfError (image2.Fail(), "There was an error in the image process", return);
  Pause();

  C_IfError (image.Fail(), "There was an error in the image process", return);
  C_IfError (image2.Fail(), "There was an error in the image process", return);
  Pause();
}




