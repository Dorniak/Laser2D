//---------------------------------------------------------------------------
#ifndef ThreadCocheLocalGGAH
#define ThreadCocheLocalGGAH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "ControlPSerie.h"
#include "LatLong-UTMconversion.h"
//---------------------------------------------------------------------------
class ThreadLecturaGPS : public TThread
{
private:
protected:
        void __fastcall Execute();
        bool Fin;
        ControlPSerie *CPS;
        double UTM_North, UTM_East, UTM_Height;
        AnsiString time;
public:
        __fastcall ThreadLecturaGPS(bool CreateSuspended, int NPuerto, int VPuerto);
        void __fastcall Finalizar();
        bool __fastcall LongitudCorrecta(int LongObligatoria, AnsiString Trama);
        double GetUTM_North();
        double GetUTM_East();
        AnsiString GetUTM_Time();
        double GetUTM_Height();

};
//---------------------------------------------------------------------------
#endif
