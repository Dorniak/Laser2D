//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "ThreadLecturaGPS.h"
#include "StringTokenizer.h"
#include "LatLong-UTMconversion.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ThreadCocheLocalGGA::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall ThreadLecturaGPS::ThreadLecturaGPS(bool CreateSuspended, int NPuerto, int VPuerto)
        : TThread(CreateSuspended)
{
         CPS = new ControlPSerie(NPuerto, VPuerto);
        Fin = false;
        FreeOnTerminate = true;
       // CPS->RecibirTramasGPS();

}

//----------------------------------------------------------
void __fastcall ThreadLecturaGPS::Finalizar()

{
    Fin = true;
}
//---------------------------------------------------------------------------
void __fastcall ThreadLecturaGPS::Execute()
{
        double UTMNorthing;
        double UTMEasting;
        char UTMZone[4];
        int ReferenceEllipsoid = 23;
        double Lat;
        double Long;

       // double time;
        double Latitud, lat1;
        double Longitud, lon1;
        AnsiString Dir_Longitud;
        AnsiString Trama;
        AnsiString TramaCorrecta;
       //for (int i=0; i<10;i++)
          CPS->RecibirTramaGPS();

        while (!Fin){
          try{
                Trama = AnsiString(CPS->RecibirTramaGPS());
                //Obtenemos las coordenadas GGA
                StringTokenizer *ST = new StringTokenizer(Trama, ",");
                TramaCorrecta = ST->NextToken();
                //Nos aseguramos que la trama GGA es la buena comparando la cabecera
                //Para asegurarnos mas todavia, convendria contar el numero de comas de la trama.
                // GGA Trimble --> 14 comas
                if ((AnsiString("$GPGGA")) == TramaCorrecta){
                        if (LongitudCorrecta(14,Trama)){
                                time = (ST->NextToken());//.ToDouble();
                                Latitud = (ST->NextToken()).ToDouble();
                                ST->NextToken();
                                Longitud =(ST->NextToken()).ToDouble();
                                Dir_Longitud = ST->NextToken();
                                ST->NextToken();//fix
                                ST->NextToken();//n sat
                                ST->NextToken();//DOP
                                UTM_Height = ST->NextToken().ToDouble();
                                delete ST;
                                lat1 = floor(Latitud/100);
                                Latitud = lat1+(Latitud/100-lat1)*100/60;
                                lon1 = floor(Longitud/100);
                                Longitud = lon1+(Longitud/100-lon1)*100/60;

                                //East Longitudes are positive, West longitudes are negative.
                                //North latitudes are positive, South latitudes are negative
                                if (Dir_Longitud == AnsiString("W"))
                                        LLtoUTM(ReferenceEllipsoid, Latitud, -Longitud, UTMNorthing, UTMEasting, UTMZone);
                                else
                                        LLtoUTM(ReferenceEllipsoid, Latitud, Longitud, UTMNorthing, UTMEasting, UTMZone);

                                /***************************************************************/
                                /******* Actualizo ls variables de clase  **********************/
                                /***************************************************************/
                                UTM_North = UTMNorthing;
                                UTM_East = UTMEasting;

                        }//if Longitud correcta
                }//if

          }catch(Exception &E){/*MessageBox(NULL,"Error al leer la posición","ERROR",MB_OK | MB_ICONERROR);*/
          }
        }
        CPS->CerrarPuerto();
        delete CPS;
}
//---------------------------------------------------------------------------
//Cuenta las comas de la entrada del GPS para asegurarse de que la linea es correcta
//Para ello utilizamos el método de contar el numero de comas en la entrada

bool __fastcall ThreadLecturaGPS::LongitudCorrecta(int LongObligatoria, AnsiString Trama)
{
        int CuentaComas = 0;
        int LongTrama = Trama.Length();

        for(int i=1; i<=LongTrama;i++)
        {
                if (Trama[i] == ','){
                        CuentaComas++;
                }
        }

        if (CuentaComas == LongObligatoria){
                return true;
        }
        return false;
}
//---------------------------------------------------------------------------

double ThreadLecturaGPS::GetUTM_North()
{
  return UTM_North;
}

//---------------------------------------------------------------------------

double ThreadLecturaGPS::GetUTM_East()
{
  return UTM_East;
}
//---------------------------------------------------------------------------
AnsiString ThreadLecturaGPS::GetUTM_Time()
{
  return time;
}
//---------------------------------------------------------------------------
double ThreadLecturaGPS::GetUTM_Height()
{
  return UTM_Height;
}
//---------------------------------------------------------------------------
