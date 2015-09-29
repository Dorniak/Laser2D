//---------------------------------------------------------------------------

#ifndef LectorDatosH
#define LectorDatosH
//---------------------------------------------------------------------------
#include <Classes.hpp>

#include "Puertos.h"
#include "TDatosPintar.h"
#include "CLASES/deteccion.h"
#include <vcl.h>
#include <ScktComp.hpp>

//---------------------------------------------------------------------------
class LectorDatos
{
private:

  Puertos *comPuerto;
  char nombreFichero[60];

  char caracter;
  unsigned short int entrada[4];
  bool conEco, final;
  double UTMNorth, UTMEast;
  AnsiString Tiempo;
  double Velocidad;
  double vel;
  double* dir;
  Deteccion * Algoritmo_deteccion;
   TCustomWinSocket *Socketv;
   TCustomWinSocket *Socketd;
   TCustomWinSocket *Sockete;




  void LectorDatos::leerCuatro();
  int LectorDatos::hexToDec();
  void LectorDatos::cambiarTrama();
protected:

public:
        __fastcall LectorDatos(bool CreateSuspended);
        __fastcall LectorDatos(Puertos *puertoLectura,char fichero[60]);
        __fastcall ~LectorDatos(void);
        void leerDatos(bool e);
        void terminarLectura();
        void empezarLectura();
        void SetNorth(double North);
        void SetEast(double East);
        void SetVelocidad(double velocidad);
        void setMemo(TMemo *Memo);
        TDatosPintar * DatosPintar;
        void SetTiempo(AnsiString T);
        int tiempo;
         void socket_vel(TCustomWinSocket *Socketvv);
         void socket_dir(TCustomWinSocket *Socketdd);
         void socket_emg(TCustomWinSocket *Socketee);
         TMemo *Memo1;
};
//---------------------------------------------------------------------------
#endif
