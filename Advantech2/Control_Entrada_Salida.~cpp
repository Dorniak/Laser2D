//---------------------------------------------------------------------------


#pragma hdrstop

#include "Control_Entrada_Salida.h"
#include "Advantech/driver.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Control_Entrada_Salida::Control_Entrada_Salida()
: TThread(false)
{
 //Abrir el driver
  Status = DRV_DeviceOpen (0, &USB_4711A);

 //2a tarjeta
  Status2 = DRV_DeviceOpen (1, &USB_4711A_2);

 //Configurar todos E/S

 //Volante: AO canal 0. range: +/- 10v
 PT_AOConfig Configuracion_Canal_Vol;
 Configuracion_Canal_Vol.chan = 0;
 Configuracion_Canal_Vol.RefSrc = 0;
 Configuracion_Canal_Vol.MaxValue = 10.0;
 Configuracion_Canal_Vol.MinValue = -10.0;

 DRV_AOConfig (USB_4711A,&Configuracion_Canal_Vol);

 //Acelerador: AO canal 1. range: 0-5v
 PT_AOConfig Configuracion_Canal_Acel;
 Configuracion_Canal_Acel.chan = 1;
 Configuracion_Canal_Acel.RefSrc = 0;
 Configuracion_Canal_Acel.MaxValue = 5.0;
 Configuracion_Canal_Acel.MinValue = 0;

 DRV_AOConfig (USB_4711A,&Configuracion_Canal_Acel);

 //Velocidad: AI canal 1. range: 0-5v
 PT_AIConfig  Configuracion_Canal_Vel;
 Configuracion_Canal_Vel.DasChan = 1;
 Configuracion_Canal_Vel.DasGain = 0;

 DRV_AIConfig( USB_4711A, &Configuracion_Canal_Vel );

 //Configuro a 0 el buffer de las salidas digitales
 DO_Byte = 0x00;
 AdxDioWriteDoPorts(USB_4711A,0,1, &DO_Byte);

 //Configurar la 2a tarjeta
 /**********************************************************************/
  
 if (Status2 == SUCCESS){
  //Acelerador 100%: AO canal 0. range: 0-5v
  PT_AOConfig Configuracion_Canal_Acel_2T_P0;
  Configuracion_Canal_Acel_2T_P0.chan = 0;
  Configuracion_Canal_Acel_2T_P0.RefSrc = 0;
  Configuracion_Canal_Acel_2T_P0.MaxValue = 0;
  Configuracion_Canal_Acel_2T_P0.MinValue = 5.0;

  DRV_AOConfig (USB_4711A_2,&Configuracion_Canal_Acel_2T_P0);

  //Acelerador 50%: AO canal 1. range: 0-5v
  PT_AOConfig Configuracion_Canal_Acel_2T_P1;
  Configuracion_Canal_Acel_2T_P1.chan = 1;
  Configuracion_Canal_Acel_2T_P1.RefSrc = 0;
  Configuracion_Canal_Acel_2T_P1.MaxValue = 5.0;
  Configuracion_Canal_Acel_2T_P1.MinValue = 0;

  DRV_AOConfig (USB_4711A_2,&Configuracion_Canal_Acel_2T_P1);
 }
 /**********************************************************************/

 //activo el bucle de control
 Fin = false;
 FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
//Set voltaje volante por AnalogOutput0
void Control_Entrada_Salida::SetVolante(double voltaje){
   /*
   PT_AOVoltageOut AO_Value;
   AO_Value.chan = 0;
   AO_Value.OutputValue = voltaje;

   DRV_AOVoltageOut (USB_4711A, &AO_Value); */
   Valor_Set_Volante = voltaje;

}
//---------------------------------------------------------------------------
//Set voltaje acelerador por AnalogOutput1
void Control_Entrada_Salida::SetAcelerador(double voltaje)
{
    /*
   PT_AOVoltageOut AO_Value;
   AO_Value.chan = 1;
   AO_Value.OutputValue = voltaje;

   DRV_AOVoltageOut (USB_4711A, &AO_Value); */
   Valor_Set_Acelerador = voltaje;
}
//---------------------------------------------------------------------------
//Set voltaje por DigitalOutput0
bool Control_Entrada_Salida::Auto_Man_Volante (double valor){
   /*
   DO_Byte = DO_Byte & 0x02; //pongo a 0 el bit 0 y mantengo el bit 1
   if (valor ==1) //si valor es 1, pongo el bit 0 a 1
       DO_Byte = DO_Byte | 0x01;
   
   AdxDioWriteDoPorts(USB_4711A,0,1, &DO_Byte);*/
   Valor_Auto_Man_Volante = valor;
   bool aux;

  return aux;
}
//---------------------------------------------------------------------------
//Set voltaje por DigitalOutput1
bool Control_Entrada_Salida::Auto_Man_Acelerador (double valor){
   /*
   DO_Byte = DO_Byte & 0x01; //pongo a 0 el bit 1 y mantengo el bit 0
   if (valor ==1) //si valor es 1, pongo el bit 1 a 1
       DO_Byte = DO_Byte | 0x02;
   
   AdxDioWriteDoPorts(USB_4711A,0,1, &DO_Byte); */
   Valor_Auto_Man_Acelerador = valor;
   bool aux;
  return aux;
}
//--------------------------------------------------------------------------
//Get señal de par que le llega por AnalogInput7
double Control_Entrada_Salida::GetPar()
{
   return 0;
}
//--------------------------------------------------------------------------
//Get señal de velocidad que le llega por AnalogInput1
double Control_Entrada_Salida::GetVelocidad()
{
     float fvoltage;
     PT_AIVoltageIn AI_Value;
     AI_Value.chan = 1;
     AI_Value.gain = 0;
     AI_Value.TrigMode = 0;
     AI_Value.voltage = &fvoltage;
    DRV_AIVoltageIn (USB_4711A, &AI_Value);
    return fvoltage;
}
//--------------------------------------------------------------------------
//Get señal de velocidad que le llega por AnalogInput1
int Control_Entrada_Salida::GetStatus()
{
  return Status;
}
//--------------------------------------------------------------------------
void Control_Entrada_Salida::Finalizar()
{
        Fin = true;
}
//--------------------------------------------------------------------------
void __fastcall Control_Entrada_Salida::Execute()
{
  //Volante
   PT_AOVoltageOut AO_Value_Volante;
   AO_Value_Volante.chan = 0;

  //Acelerador
   PT_AOVoltageOut AO_Value_Acelerador;
   AO_Value_Acelerador.chan = 1;

  while (!(Fin)){
   //Volante
   AO_Value_Volante.OutputValue = Valor_Set_Volante;
   DRV_AOVoltageOut (USB_4711A, &AO_Value_Volante);

   //Acelerador
   AO_Value_Acelerador.OutputValue = Valor_Set_Acelerador;
   DRV_AOVoltageOut (USB_4711A, &AO_Value_Acelerador);
   //2a tarjeta de adquisicion
  /******************************************************************/
   if (Status2 == SUCCESS){
    AO_Value_Acelerador.chan = 0;
    DRV_AOVoltageOut (USB_4711A_2, &AO_Value_Acelerador);
    AO_Value_Acelerador.chan = 1;
    AO_Value_Acelerador.OutputValue = Valor_Set_Acelerador/2.0;
    DRV_AOVoltageOut (USB_4711A_2, &AO_Value_Acelerador);
   }
  /*******************************************************************/



   //Auto Man Volante
   DO_Byte = DO_Byte & 0x02; //pongo a 0 el bit 0 y mantengo el bit 1
   if (Valor_Auto_Man_Volante ==1) //si valor es 1, pongo el bit 0 a 1
       DO_Byte = DO_Byte | 0x01;
   AdxDioWriteDoPorts(USB_4711A,0,1, &DO_Byte);

   //Auto Man Acelerador
   DO_Byte = DO_Byte & 0x01; //pongo a 0 el bit 1 y mantengo el bit 0
   if (Valor_Auto_Man_Acelerador ==1) //si valor es 1, pongo el bit 1 a 1
       DO_Byte = DO_Byte | 0x02;
   AdxDioWriteDoPorts(USB_4711A,0,1, &DO_Byte);


   
  }

  DRV_DeviceClose ( &USB_4711A);
  if (Status2 == SUCCESS)
    DRV_DeviceClose ( &USB_4711A_2);

}
