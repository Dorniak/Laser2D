//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ThreadPintar.h"

#include "Windows.h"

//---------------------------------------------------------------------------


__fastcall ThreadPintar::ThreadPintar(): TThread(true)
{

Paint * pintar = new Paint(); 


}
//---------------------------------------------------------------------------

void __fastcall ThreadPintar::Execute()
{

        while (!(fin)){

        if (tipoDatos){
                lectorDatos->leerDatos();
                //tipoDatos=false;
        }
        else{
                Cadena = conPuerto->ReadTrama();
                NuevaCadena = true;
                //Suspend();
             }
        }
}

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------



//---------------------------------------------------------------------------



//---------------------------------------------------------------------------




//---------------------------------------------------------------------------



}

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

char * Laser::LeerCadena(){
 if (NuevaCadena){
        NuevaCadena = false;
        return Cadena;
 }
 char * salida = "\0";
 return salida;
}

//---------------------------------------------------------------------------

void Laser::AcabarThread(){
        fin = true;
        Sleep(500);
       // Resume();
}


#pragma package(smart_init)