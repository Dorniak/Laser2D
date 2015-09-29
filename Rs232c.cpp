/******************************************************************************/
/* Rutinas para el manejo de la RS232C */
/******************************************************************************/

#include <conio.h>
#include <stdlib.h>
#include "RS232C.H"
#include "ERRORES.H"




HANDLE OpenRS232C (int com,
                   DWORD BaudRate,
                   BYTE ByteSize,
                   BYTE Parity,
                   BYTE StopBits,
                   DWORD fDtrControl,
                   DWORD t_out)
{
 HANDLE haux;
 DCB dcb;
 BOOL fSuccess;
 char nombre[10], num[5];
 COMMTIMEOUTS timeOut;
 if ((com != 1) && (com != 2) && (com != 3) && (com != 4))
   return(ERR_INI_COM);
 if ((BaudRate > 115200L) || (BaudRate < 1L))
   return(ERR_INI_COM);
 itoa(com,num,10);
 strcpy(nombre,"COM");
 strcat(nombre,num);
 haux=CreateFile(nombre,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING, 0, NULL);
 if (haux == INVALID_HANDLE_VALUE)
   return(ERR_INI_COM);

 fSuccess=GetCommState(haux,&dcb);
 //----------------------------------------------------
 //SetupComm(haux,90,0);
 //SetCommMask(haux,EV_RXCHAR|EV_RXFLAG);
 //----------------------------------------------------
 if (!fSuccess)
   return(ERR_INI_COM);

 dcb.BaudRate=BaudRate;
 dcb.ByteSize=ByteSize;
 dcb.Parity=Parity;
 dcb.StopBits=StopBits;
 dcb.fOutX=false;
 dcb.fInX=false;
 dcb.fDtrControl=fDtrControl;

 fSuccess=SetCommState(haux,&dcb);
 if (!fSuccess)
   return(ERR_INI_COM);

 if (!GetCommTimeouts(haux,&timeOut)){
   return(ERR_INI_COM);
  }
 timeOut.ReadIntervalTimeout=2000;
 timeOut.ReadTotalTimeoutMultiplier=2000;

 SetCommTimeouts(haux,&timeOut);
 return(haux);
} /* FIN de OpenRS232C */

//---------------------------------------------------------------------------
void CloseRS232C (HANDLE hcom)
{
 CloseHandle(hcom);
} /* FIN de CloseR232C */
//---------------------------------------------------------------------------
void SetSizeInputBuff(HANDLE hcom, DWORD Size)
{
  COMMPROP commprop;
  GetCommProperties(hcom, &commprop);
  SetupComm(hcom, Size, commprop.dwCurrentTxQueue);
}

//---------------------------------------------------------------------------
void SetSizeOutputBuff(HANDLE hcom, DWORD Size)
{
  COMMPROP commprop;
  GetCommProperties(hcom, &commprop);
  SetupComm(hcom, commprop.dwCurrentRxQueue, Size);
}

//---------------------------------------------------------------------------
int b_WriteRS232C (HANDLE hcom, UCHAR obyte)
{
 static DWORD bytesEscritos;
 static USHORT sizeofChar=sizeof(obyte);

 WriteFile(hcom,&obyte,sizeofChar,&bytesEscritos,NULL);
 if (bytesEscritos != ((unsigned) sizeofChar))
   return(ERR_WB_RS);
 return(NO_ERR);
} /* FIN de b_WriteRS232C */

//---------------------------------------------------------------------------
int b_ReadRS232C (HANDLE hcom, UCHAR * p_leido)
{
 static UCHAR ibyte;
 static USHORT sizeofChar=sizeof(ibyte);
 static DWORD bytesLeidos,dwError;
 static BOOL bResult;
 //----------------------------------------------------
 /*DWORD Evento;
 WaitCommEvent(hcom, &Evento, NULL);
 //if (Evento == EV_RXCHAR)
   bResult=ReadFile(hcom,&ibyte,sizeofChar,&bytesLeidos,NULL);
 //----------------------------------------------------
 */
  int contador =0;
 do{
 bResult=ReadFile(hcom,&ibyte,sizeofChar,&bytesLeidos,NULL);
 //contador++;
 }while ((ibyte == '\0')&&(contador<5));
 
 if (!bResult)
   {
    dwError=GetLastError();
    if (dwError == ERROR_IO_PENDING)
      {
       /* Una I/O asíncrona está todavía en ejecución */
       bResult=GetOverlappedResult(hcom,NULL,&bytesLeidos,FALSE);
       if (!bResult)
         return(ERR_RB_RS);
      }
   }
 if (!bytesLeidos)
   return(ERR_RB_RS);
 *p_leido=ibyte;
 return (NO_ERR);
} /* FIN de b_ReadRS232C */


int WriteRS232C (HANDLE hcom, UCHAR * obyte, UINT nBytes)
{
 static DWORD bytesEscritos;

 WriteFile(hcom,obyte,nBytes,&bytesEscritos,NULL);
 if (bytesEscritos != nBytes)
   return(ERR_W_RS);
 return(NO_ERR);
} /* FIN de WriteRS232C */


int ReadRS232C(HANDLE hcom, UCHAR * ibyte, UINT nBytes)
{
 static DWORD bytesLeidos;
 static DWORD dwError;
 static BOOL bResult;

 bResult=ReadFile(hcom,ibyte,nBytes,&bytesLeidos,NULL);
 if (!bResult)
   {
    dwError=GetLastError();
    if (dwError == ERROR_IO_PENDING)
      {
       /* Una I/O asíncrona está todavía en ejecución */
       bResult=GetOverlappedResult(hcom,NULL,&bytesLeidos,FALSE);
       if (!bResult)
         return(ERR_R_RS);
      }
   }
 if (!bytesLeidos)
   return(ERR_R_RS);
 return (NO_ERR);
} /* FIN de ReadRS232C */
