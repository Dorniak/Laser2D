//---------------------------------------------------------------------------

#ifndef Control_AdvantechH
#define Control_AdvantechH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "bdaqctrl.h"
#include "compatibility.h"
#pragma hdrstop
using namespace Automation::BDaq;
//---------------------------------------------------------------------------
class Control_Advantech : public TThread
{            
private:
  InstantAoCtrl * Analog_Output;
  InstantDiCtrl * Digital_Input;
  InstantAiCtrl * Analog_Input;
  InstantDoCtrl * Digital_Output;

  Byte DI_Data;
  double  AI_Data[16];
  Byte DO_Data;
  double Valor_Set_Volante,  Valor_Set_Acelerador, Dato_AO_0, Dato_AO_1;
  bool Fin;
protected:
  void __fastcall Execute();
public:
  __fastcall Control_Advantech(bool CreateSuspended);
  void SetVolante(double voltaje);
  void SetAcelerador(double voltaje);
  void Finalizar();
  Byte Get_DI_Data();
  double Get_AI_Data(int n);
  void Set_DO_Data(Byte Valor);
};
//---------------------------------------------------------------------------
#endif
