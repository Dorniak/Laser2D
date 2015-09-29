//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FineTime.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
FineTime::FineTime()
{
  LARGE_INTEGER frec;

  QueryPerformanceFrequency(&frec);
  frecuencia = frec.QuadPart;
}

//---------------------------------------------------------------------------
double FineTime::GetResolution()
{
  return 1/frecuencia;
}

//---------------------------------------------------------------------------
double FineTime::GetFineTime()
{
  static LARGE_INTEGER contador;

  QueryPerformanceCounter(&contador);
  return (double)contador.QuadPart/frecuencia;
}
