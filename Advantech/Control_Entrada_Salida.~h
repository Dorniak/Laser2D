/*  Nota de Prefuncionamiento del Advantech USB-4711A
Para poder configurar el canal de cada dispositivo, el valor del rango...
y resto de parámetros Primero hay que seleccinar el dispositivo (DeviceNumber).
En nuestro caso channelNow->0 (Volante) y channelNow->1 (Acelerador)  
*/
//---------------------------------------------------------------------------

#ifndef Control_Entrada_SalidaH
#define Control_Entrada_SalidaH
#include <vcl.h>   /*
#include "AdvAILib_OCX.h"
#include "AdvAOLib_OCX.h"
#include "AdvDIOLib_OCX.h"
#include "AdvDIOLib_TLB.h"  */
//#include "driver.h"
//---------------------------------------------------------------------------

class Control_Entrada_Salida: public TThread{

private:
        int Status, Status2;
        long USB_4711A;
        long USB_4711A_2;
        unsigned char DO_Byte;
        double Valor_Set_Volante, Valor_Set_Acelerador, Valor_Auto_Man_Volante, Valor_Auto_Man_Acelerador;
        bool Fin;

protected:
  void __fastcall Execute();

public:
        Control_Entrada_Salida();
        void Finalizar();
        void SetVolante(double voltaje);
        void SetAcelerador(double voltaje);
        bool Auto_Man_Volante (double valor);
        bool Auto_Man_Acelerador (double valor);
        double GetPar();
        double GetVelocidad();
        int GetStatus();

};





#endif
 