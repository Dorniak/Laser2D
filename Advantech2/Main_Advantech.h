//---------------------------------------------------------------------------

#ifndef Main_AdvantechH
#define Main_AdvantechH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "bdaqctrl.h"
#include "compatibility.h"
#include "Control_Advantech.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TMemo *Memo1;
  TButton *Button1;
  TButton *Button2;
  TLabel *Label1;
  TLabel *Label2;
  TEdit *Edit1;
  TEdit *Edit2;
  TButton *Button3;
  TButton *Button4;
  TCheckBox *CheckBox1;
  TCheckBox *CheckBox2;
  TCheckBox *CheckBox3;
  TCheckBox *CheckBox4;
  TCheckBox *CheckBox5;
  TCheckBox *CheckBox6;
  TCheckBox *CheckBox7;
  TCheckBox *CheckBox8;
  TLabel *Label3;
  TTimer *Timer1;
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall Button3Click(TObject *Sender);
  void __fastcall Button4Click(TObject *Sender);
  void __fastcall CheckBox1Click(TObject *Sender);
  void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
    bool Parar;
    Control_Advantech * CA;
    Byte DO_Data;
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
