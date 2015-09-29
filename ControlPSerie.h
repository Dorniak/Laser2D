//---------------------------------------------------------------------------
/*

Cabecera ControlPSerie.h

Clase con los m�todos necesarios establecer conexi�n y control con el Puerto Serie.

*/
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
#ifndef ControlPSerieH
#define ControlPSerieH

/* Includes de la aplicaci�n */
#include <stdio.h>
#include <stdlib.h>
#include <vcl\vcl.h>

#include "ERRORES.H"
#include "UART.H"
#include "RS232C.H"
#include "RECEPGPS.H"

class ControlPSerie {

private:
  HANDLE haux;

public:
   ControlPSerie(int NPuerto,
                DWORD BaudRate,
                BYTE ByteSize,
                BYTE Parity,
                BYTE StopBits,
                DWORD fDtrControl
   );
   /* Configura los par�metros de funcionamiento del puerto serie
      Par 1: N�mero de puerto
      Par 2: Velocidad de transmisi�n en BPS
      Par 3: Longitud del campo datos
      Par 4: M�scara de paridad
      Par 5: Longitud del stop
      Par 7: Control de flujo
   */
  ControlPSerie(int NPuerto,
                DWORD BaudRate
   );

   void CerrarPuerto();
   /* Cierra el puerto de comunciaciones abierto*/

  void SetSizeInputBuffer(DWORD Size);
  /* Define un tama�o en bytes para el buffer de entrada de la UART.
    */

  void SetSizeOutputBuffer(DWORD Size);
   /* Define un tama�o en bytes para el buffer de salida de la UART.
   */

  UCHAR ReadChar();
  /* Lee un caracter del puerto serie y lo devuelve */

   char ReadChar2();
  /* Lee un caracter del puerto serie y lo devuelve */

  void WriteChar(UCHAR obyte);
  /*Escribe el caracter que se le pasa como par�metro al puerto serie*/

  UCHAR* ReadString(int tamanyo);
  /* Lee una cadena de caracteres acabada en CRLF por el puerto serie y la devuelve */

  void WriteString(unsigned char* str);
  /* Escribe una cadena de caracteres por el puerto serie */

  AnsiString RecibirTramaGPS();
  /* Devuelve una trama GPS GGA completa */

};

//---------------------------------------------------------------------------
#endif
