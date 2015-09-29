//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Fichero.h"
#include <stdio.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
//Constructor de la clase que inicia un fichero de recorridos
//para grabar las posiciones. el fichero se denomina Datos.log.
//Si ya existe se añade un numero al final.
__fastcall Fichero::Fichero(AnsiString Tipo)
{
        AnsiString NombreFichero = AnsiString("Datos.")+Tipo;
        int i=1;
        while (FileExists(NombreFichero))
        {
                NombreFichero = AnsiString("Datos")+i+AnsiString(".")+Tipo;
                i++;
        }

	iFileHandle = FileCreate(NombreFichero);
        AnsiString Fecha =  DateToStr(Date());
        AnsiString Hora = TimeToStr(Time());
        AnsiString Cabecera =  Fecha + " " + Hora + "\r\n";
        FileWrite(iFileHandle,(char*)(Cabecera.c_str()), Cabecera.Length());
}
//---------------------------------------------------------------------------
//Constructor de la clase que inicia un fichero de recorridos
//para grabar las posiciones. el fichero se denomina Sesion.log.
//Si ya existe se añade un numero al final.
__fastcall Fichero::Fichero()
{
        AnsiString NombreFichero = AnsiString(".\\Log\\Sesion.log");
        int i=1;
        while (FileExists(NombreFichero))
        {
                NombreFichero = AnsiString(".\\Log\\Sesion")+i+AnsiString(".")+AnsiString("log");
                i++;
        }

        iFileHandle = FileCreate(NombreFichero);
        AnsiString Fecha =  DateToStr(Date());
        AnsiString Hora = TimeToStr(Time());
        AnsiString Cabecera =  Fecha + " " + Hora + AnsiString("\r\n");
        FileWrite(iFileHandle,(char*)(Cabecera.c_str()), Cabecera.Length());
}
//----------------------------------------------------------------------
//Constructor de la clase que crea un fichero nuevo, sobreescribiéndolo
//en caso de que ya exista con ese nombre
__fastcall Fichero::Fichero(AnsiString Nombre, AnsiString Directorio, int modo)
{
        AnsiString Direccion = Directorio+AnsiString("\\")+Nombre;
        iFileHandle = FileOpen(Direccion, modo);

}
//----------------------------------------------------------------------
//Constructor de la clase que crea un fichero nuevo, sobreescribiéndolo
//encaso de que ya exista con ese nombre
__fastcall Fichero::Fichero(AnsiString Nombre, AnsiString Directorio)
{
        AnsiString Direccion = Directorio+AnsiString("\\")+Nombre;
        iFileHandle = FileCreate(Direccion);
        
}
//----------------------------------------------------------------------
//Escribe una posicion en un fichero de tipo fichero de posiciones
void __fastcall Fichero::EscribirDato(double N, double E)
{
        AnsiString DatoPosicion = "N:"+AnsiString(N)+",E:"+AnsiString(E)+"\r\n";
        FileWrite(iFileHandle,(char*)(DatoPosicion.c_str()), DatoPosicion.Length());
}
//----------------------------------------------------------------------
//Escribe un dato de tipo AnsiString en un fichero genérico
void __fastcall Fichero::EscribirDato(AnsiString Dato)
{
        FileWrite(iFileHandle,(char*)(Dato.c_str()), Dato.Length());
}

//----------------------------------------------------------------------------
//cierra el fichero
void __fastcall Fichero::CerrarFichero()
{       
        FileClose(iFileHandle);
}

//----------------------------------------------------------------------------
//Lee una cadena de caracteres del fichero.
AnsiString __fastcall Fichero::LeerDato()
{
        char * pszBuffer;
        long iFileLength = FileSeek(iFileHandle,0,2);
        FileSeek(iFileHandle,0,0);
        pszBuffer = new char[iFileLength+1];
        for (int i=0; i<iFileLength+1;i++)
          pszBuffer[i] = '\0';
        FileRead(iFileHandle, pszBuffer, iFileLength);
        return AnsiString(pszBuffer);
}


