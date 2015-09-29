//---------------------------------------------------------------------------
#include <vcl.h>
/*
#include <stdio.h>
#include <iostream.h>
#include <dstring.h>
*/
#pragma hdrstop
USEUNIT("UBUFFobj.cpp");
USEUNIT("Recepgps.cpp");
USEUNIT("Rs232c.cpp");
USEUNIT("ControlPSerie.cpp");
//---------------------------------------------------------------------------
#define Library

#include "Puertos.h"
ControlPSerie *CPS;
//---------------------------------------------------------------------------
int Puertos::AbrirPuerto (int NPuerto,
        DWORD BaudRate,
        BYTE ByteSize,
        BYTE Parity,
        BYTE StopBits,
        DWORD fDtrControl)

{
  CPS = new ControlPSerie(NPuerto, BaudRate, ByteSize, Parity, StopBits, fDtrControl);
  if (CPS== NULL)
    return false;
  return true;
}

//---------------------------------------------------------------------------
void Puertos::ClosePort()
{
  CPS->CerrarPuerto();
  delete (CPS);
}

//---------------------------------------------------------------------------
void Puertos::SetSizeInputBuffer(DWORD Size)
{
  CPS->SetSizeInputBuffer(Size);
}
//---------------------------------------------------------------------------
void Puertos::SetSizeOutputBuffer(DWORD Size)
{
  CPS->SetSizeOutputBuffer(Size);
}

//---------------------------------------------------------------------------
UCHAR Puertos::ReadChar()
{
  return CPS->ReadChar();
}

//---------------------------------------------------------------------------
void Puertos::WriteChar(UCHAR obyte)
{
  CPS->WriteChar(obyte);
}

//---------------------------------------------------------------------------

char* Puertos::ReadString()
{
return CPS->ReadString(12);
}
//---------------------------------------------------------------------------
char* Puertos::ReadString(int longCadena)
{
return CPS->ReadString(longCadena);
}

//---------------------------------------------------------------------------
char* Puertos::ReadTrama()
{
  UCHAR caracter;
  AnsiString trama = AnsiString();
  int intentos = 0;
        do {
          caracter = CPS->ReadChar();
          trama.cat_sprintf("%xc ", caracter);
          intentos++;
        }while ((caracter!='\x03')&&(intentos<50));

return trama.c_str();
}

//---------------------------------------------------------------------------

void Puertos::WriteString(unsigned char* str)
{
  CPS->WriteString(str);
}
//---------------------------------------------------------------------------

