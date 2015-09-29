/******************************************************************************/
/* Rutinas para el manejo de la RS232C */
/******************************************************************************/
/* La ayuda donde aparecen las funciones utilizadas referentes al puerto serie
   están en win32.hlp */


#ifndef _RS232C
#define _RS232C


#include <vcl\vcl.h>


#define COM1 1
#define COM2 2
#define COM3 3
#define COM4 4


extern HANDLE OpenRS232C (int com,
                          DWORD BaudRate,
                          BYTE ByteSize,
                          BYTE Parity,
                          BYTE StopBits,
                          DWORD fDtrControl,
                          DWORD t_out);
   /* Configura los parámetros de funcionamiento del puerto serie
      Par 1: Número de puerto
      Par 2: Velocidad de transmisión en BPS
      Par 3: Longitud del campo datos
      Par 4: Máscara de paridad
      Par 5: Longitud del stop
      Par 7: Control de flujo
      Par 6: Time_Out en milisegundos
      Return: Si error ERR_INI_COM
              En caso contrario descriptor para acceder al puerto serie */


extern void CloseRS232C (HANDLE);
   /* Cierra el puerto
      Par 1: Puerto a cerrar */

extern void SetSizeInputBuff(HANDLE hcom, DWORD Size);
   /* Define un tamaño en bytes para el buffer de entrada de la UART.
    */

extern void SetSizeOutputBuff(HANDLE hcom, DWORD Size);
  /* Define un tamaño en bytes para el buffer de salida de la UART.
   */

extern int b_WriteRS232C (HANDLE, UCHAR);
  /* Envia un byte por el puerto
     Par 1: Puerto
     Par 2: Byte a enviar
     Return : Si error ERR_WB_RS
              En caso contrario NO_ERR */


extern int b_ReadRS232C (HANDLE, UCHAR *);
   /* Recibe un byte por el puerto
      Par 1: Puerto por el que se recibe
      Par 2: Se devuelve el byte recibido
      Return: Si error ERR_RB_RS
              En caso contrario NO_ERR */


extern int WriteRS232C (HANDLE, UCHAR *, UINT);
   /* Envia por el puerto un bloque de bytes
      Par 1: Puerto por el que se envía
      Par 2: Bytes a enviar
      Par 3: Número de bytes a enviar
      Return: Si error ERR_W_RS
              En caso contrario NO_ERR */


extern int ReadRS232C (HANDLE, UCHAR *, UINT);
   /* Recibe por el puerto un bloque de bytes
      Par 1: Puerto por el que se recibe
      Par 2: Variable donde se devuelve el bloque leído
      Par 3: Número de bytes a leer
      Return: Si error ERR_R_RS
              En caso contrario NO_ERR */


#endif
