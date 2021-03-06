//---------------------------------------------------------------------------
#include <vcl.h>
#include <conio.h>
#include <stdlib.h>
#pragma hdrstop

#include "ControlPSerie.h"
#include "TramaGPS.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)



//---------------------------------------------------------------------------
ControlPSerie::ControlPSerie(int NPuerto,
                             DWORD BaudRate,
                             BYTE ByteSize,
                             BYTE Parity,
                             BYTE StopBits,
                             DWORD fDtrControl)
{
DCB dcb, dcbCommPort;
COMSTAT comstat;
BOOL fSuccess;
char nombre[10], num[5];
COMMTIMEOUTS timeOut;

itoa(NPuerto,num,10);
strcpy(nombre,"COM");
strcat(nombre,num);
haux=CreateFile(nombre,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING, 0, NULL);
if (haux == INVALID_HANDLE_VALUE)
    if (MessageBox(NULL,"Imposible iniciar comunicaci�n\n�Desea continuar?",
                     "ERROR",MB_YESNO | MB_ICONERROR) == IDNO)
        exit(-1);
     
// Configuraci�n para la inicializaci�n del LD-OEM 1000


GetCommState(haux, &dcbCommPort);

dcbCommPort.DCBlength=28;         // sizeof(DCB)
dcbCommPort.BaudRate=BaudRate;//115200;     // current baud rate
dcbCommPort.fBinary=1;           // binary mode, no EOF check
dcbCommPort.fParity=0;           // enable parity checking
dcbCommPort.fOutxCtsFlow=0;      // CTS output flow control
dcbCommPort.fOutxDsrFlow=0;      // DSR output flow control
dcbCommPort.fDtrControl=1;       // DTR flow control type
dcbCommPort.fDsrSensitivity=0;   // DSR sensitivity
dcbCommPort.fTXContinueOnXoff=0; // XOFF continues Tx
dcbCommPort.fOutX=0;             // XON/XOFF out flow control
dcbCommPort.fInX=0;              // XON/XOFF in flow control
dcbCommPort.fErrorChar=0;        // enable error replacement
dcbCommPort.fNull=0;             // enable null stripping
dcbCommPort.fRtsControl=1;       // RTS flow control
dcbCommPort.fAbortOnError=0;     // abort reads/writes on error
dcbCommPort.fDummy2=0;           // reserved
dcbCommPort.wReserved;           // not currently used
dcbCommPort.XonLim=2048;         // transmit XON threshold
dcbCommPort.XoffLim=512;         // transmit XOFF threshold
dcbCommPort.ByteSize=8;          // number of bits/byte, 4-8
dcbCommPort.Parity=0;            // 0-4=no,odd,even,mark,space
dcbCommPort.StopBits=0;          // 0,1,2 = 1, 1.5, 2
dcbCommPort.XonChar=17;          // Tx and Rx XON character
dcbCommPort.XoffChar=19;         // Tx and Rx XOFF character
dcbCommPort.ErrorChar=0;         // error replacement character
dcbCommPort.EofChar=0;           // end of input character
dcbCommPort.EvtChar=55;          // received event character
dcbCommPort.wReserved1;

SetCommState(haux,&dcbCommPort);

GetCommTimeouts(haux,&timeOut);
timeOut.ReadIntervalTimeout=30;
timeOut.ReadTotalTimeoutMultiplier=30;
timeOut.WriteTotalTimeoutMultiplier=0;
timeOut.WriteTotalTimeoutConstant=0;
SetCommTimeouts(haux,&timeOut);

}
//---------------------------------------------------------------------------
ControlPSerie::ControlPSerie(int NPuerto,
                             DWORD BaudRate)
{
DCB dcb, dcbCommPort;
COMSTAT comstat;
BOOL fSuccess;
char nombre[10], num[5];
COMMTIMEOUTS timeOut;

itoa(NPuerto,num,10);
strcpy(nombre,"COM");
strcat(nombre,num);
haux=CreateFile(nombre,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING, 0, NULL);
if (haux == INVALID_HANDLE_VALUE)
    if (MessageBox(NULL,"Imposible iniciar comunicaci�n\n�Desea continuar?",
                     "ERROR",MB_YESNO | MB_ICONERROR) == IDNO)
        exit(-1);

// Configuraci�n para la inicializaci�n del LD-OEM 1000


GetCommState(haux, &dcbCommPort);

 dcb.BaudRate=BaudRate;
 dcb.ByteSize=8;
 dcb.Parity=NOPARITY;
 dcb.StopBits=ONESTOPBIT;
 dcb.fOutX=false;
 dcb.fInX=false;
 dcb.fDtrControl=DTR_CONTROL_DISABLE;

 SetCommState(haux,&dcb);

GetCommTimeouts(haux,&timeOut);
timeOut.ReadIntervalTimeout=30;
timeOut.ReadTotalTimeoutMultiplier=30;
timeOut.WriteTotalTimeoutMultiplier=0;
timeOut.WriteTotalTimeoutConstant=0;
SetCommTimeouts(haux,&timeOut);

}
//---------------------------------------------------------------------------
void ControlPSerie::CerrarPuerto(){
          CloseHandle(haux);
}

//---------------------------------------------------------------------------
void ControlPSerie::SetSizeInputBuffer(DWORD Size)
{
  COMMPROP commprop;
  GetCommProperties(haux, &commprop);
  SetupComm(haux, Size, commprop.dwCurrentTxQueue);
}

//---------------------------------------------------------------------------
void ControlPSerie::SetSizeOutputBuffer(DWORD Size)
{
  COMMPROP commprop;
  GetCommProperties(haux, &commprop);
  SetupComm(haux, commprop.dwCurrentRxQueue, Size);
}
//---------------------------------------------------------------------------
char ControlPSerie::ReadChar2()
{
  char Caracter;
  char ibyte='\0';
  USHORT sizeofChar=sizeof(ibyte);
  DWORD bytesLeidos,dwError;
  BOOL bResult;

 int parar = 0;
 do{
    //bResult=
    ReadFile(haux,&ibyte,sizeofChar,&bytesLeidos,NULL);
    parar++;
 }while ((ibyte == '\0') && (parar<20));

 if (!bytesLeidos)
   return('\0');
 return(ibyte);
}
//---------------------------------------------------------------------------
UCHAR ControlPSerie::ReadChar()
{
  UCHAR Caracter;
  UCHAR ibyte;
  USHORT sizeofChar=sizeof(ibyte);
  DWORD bytesLeidos,dwError;
  BOOL bResult;

 int parar = 0;
 do{
    //bResult=
    ReadFile(haux,&ibyte,sizeofChar,&bytesLeidos,NULL);
    parar++;
 }while ((ibyte == '\0') && (parar<20));

 if (!bytesLeidos)
   return('\0');
 return(ibyte);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ControlPSerie::WriteChar(UCHAR obyte)
{
  DWORD bytesEscritos;
  SHORT sizeofChar=sizeof(obyte);

 WriteFile(haux,&obyte,sizeofChar,&bytesEscritos,NULL);
}
//---------------------------------------------------------------------------

UCHAR* ControlPSerie::ReadString(int tamanyo)
{
  UCHAR Caracter;
  UCHAR* ibyte;
  DWORD bytesLeidos,dwError;
  BOOL bResult;

 do{
    //bResult=
    ReadFile(haux,&ibyte,tamanyo,&bytesLeidos,NULL);
 }while (ibyte == '\0');

 if (!bytesLeidos)
   return('\0');
 return(ibyte);
}
//---------------------------------------------------------------------------
void ControlPSerie::WriteString(unsigned char* str)
{
  DWORD bytesEscritos;

  WriteFile(haux,str,sizeof(str),&bytesEscritos,NULL);          
}
//---------------------------------------------------------------------------
AnsiString ControlPSerie::RecibirTramaGPS()
{
  TramaGPS *TramaGGA;
  TramaGGA = new TramaGPS();
  AnsiString Resultado;
  Resultado = TramaGGA->AddCaracter(AnsiString(ReadChar2()));
  while (Resultado.IsEmpty())
    Resultado = TramaGGA->AddCaracter(AnsiString(ReadChar2()));
  delete TramaGGA;
  return Resultado;
}
//---------------------------------------------------------------------------
