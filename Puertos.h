/*******************************************************************************
* Header of Puertos.lib
* Generical library for Input Output data through serial ports
*
* Jos� Eugenio Naranjo
*
*******************************************************************************/
#ifndef PuertosH
#define PuertosH


#include "ControlPSerie.h"



class Puertos
{

private:
 ControlPSerie *CPS;
public:

int AbrirPuerto (int NPuerto,
            DWORD BaudRate,
            BYTE ByteSize,
            BYTE Parity,
            BYTE StopBits,
            DWORD fDtrControl
            );
            
 /* Configura los par�metros de funcionamiento del puerto serie
      NPuerto: Number of the curren serial port
              Possibles values: 1, 2, 3, 4

      BaudRate: Specifies the baud rate at which the communications
                device operates. This member can be an actual baud
                rate value, or one of the following baud rate indexes:
                  CBR_110 	CBR_19200
                  CBR_300 	CBR_38400
                  CBR_600 	CBR_56000
                  CBR_1200	CBR_57600
                  CBR_2400	CBR_115200
                  CBR_4800	CBR_128000
                  CBR_9600	CBR_256000
                  CBR_14400

      ByteSize: Specifies the number of bits in the bytes transmitted and received.

      Parity: Specifies the parity scheme to be used. This member can be one of the following values:
                  Value	      Meaning
                  EVENPARITY	Even
                  MARKPARITY	Mark
                  NOPARITY	No parity
                  ODDPARITY	Odd

      StopBits: Specifies the number of stop bits to be used. This member can be one of the following values:
                  Value	      Meaning
                  ONESTOPBIT	1 stop bit
                  ONE5STOPBITS	1.5 stop bits
                  TWOSTOPBITS	2 stop bits

      fDtrControl: Specifies the DTR (data-terminal-ready) flow control.
                  This member can be one of the following values:
                  Value	      Meaning
                  DTR_CONTROL_DISABLE	  Disables the DTR line when the device
                                        is opened and leaves it disabled.
                  DTR_CONTROL_ENABLE	  Enables the DTR line when the device is
                                        opened and leaves it on.
                  DTR_CONTROL_HANDSHAKE	Enables DTR handshaking. If handshaking
                                        is enabled, it is an error for the application to adjust the line by using the EscapeCommFunction function.

      Par 6: Time_Out in milisegundos
 */

 void ClosePort();
 /* Close the current Serial port */

 void Puertos::SetSizeInputBuffer(DWORD Size);
 /* Specifies the recommended size, in bytes, of the device's internal
  input buffer.
 */

 void Puertos::SetSizeOutputBuffer(DWORD Size);
 /* Specifies the recommended size, in bytes, of the device's internal
 output buffer.
 */

 UCHAR Puertos::ReadChar();
 /* Reads a character from the inicialized serial port
 */

 void Puertos::WriteChar(UCHAR obyte);
 /* Writes a character to the inicialized serial port
 */

 char* Puertos::ReadString();
 /* Reads a string from the incialized serial port
 */

  char* Puertos::ReadString(int longCadena);
 /* Reads a string from the incialized serial port
 */

 char* Puertos::ReadTrama();
 /* Reads a trama from the incialized serial port
 */

 void Puertos::WriteString(unsigned char* str);
 /* Writes a string to the inicialized serial port
 */

};


#endif
