//---------------------------------------------------------------------------
#ifndef FicheroH
#define FicheroH
//---------------------------------------------------------------------------
//Clase para el aceso a ficheros genéricos
//Permite acceso a ficheros para la esritura de recorridos
//y escritura de mapas.
//Modificado 23-2-00
//Autor José Eugenio Naranjo
#include <io.h>
#include <vcl.h>
class Fichero
{
private:
        int iFileHandle; //Handle del fichero
public:
        __fastcall Fichero(AnsiString Tipo); //Constructor de la clase
        __fastcall Fichero();//Construye un Sesion.log
        __fastcall Fichero(AnsiString Nombre, AnsiString Directorio, int modo);
        __fastcall Fichero(AnsiString Nombre, AnsiString Directorio);
        void __fastcall EscribirDato(double N, double E);   //Escribe un dato de tipo posicion en el fichero
        void __fastcall EscribirDato(AnsiString Dato); //Escribe un dato de tipo AnsiString en el fichero
        void __fastcall CerrarFichero(); //Cierra el fichero
        AnsiString __fastcall LeerDato(); // Lee un dato del fichero.
};


#endif