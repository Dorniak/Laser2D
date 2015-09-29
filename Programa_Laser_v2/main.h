//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>

#include "Laser.h"
#include "LectorDatos.h"
#include "Puertos.h"
#include "Pintar.h"
#include "TDatosPintar.h"
#include "ThreadLecturaGPS.h"
#include "Advantech2/Control_Advantech.h"
#include "CAN/xlCANFunctions.h"
#include "Fichero.h"
#include "FineTime.h"

#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ScktComp.hpp>

//---------------------------------------------------------------------------
class TPrincipal : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *menuPrincipal;
        TMenuItem *menuLaser;
        TMenuItem *ConectarPuerto;
        TMemo *textMemo;
        TMenuItem *nPuertoLaser;
        TMenuItem *laserPuerto1;
        TMenuItem *laserPuerto2;
        TMenuItem *laserPuerto3;
        TMenuItem *laserPuerto4;
        TMenuItem *laserPuerto5;
        TMenuItem *laserPuerto6;
        TMenuItem *nVelocidadLaser;
        TMenuItem *vLaser1200;
        TMenuItem *vLaser2400;
        TMenuItem *vLaser4800;
        TMenuItem *vLaser9600;
        TMenuItem *vLaser19200;
        TMenuItem *vLaser38400;
        TMenuItem *vLaser57600;
        TMenuItem *vLaser115200;
        TMenuItem *botonInicializar;
        TMenuItem *botonApertura;
        TMenuItem *Confi60Grados;
        TMenuItem *Confi180Grados;
        TMenuItem *botonFrecuencia;
        TMenuItem *botonResolucion;
        TMenuItem *Rotar;
        TMenuItem *Halt;
        TMenuItem *botonECO;
        TMenuItem *confi10Hz;
        TMenuItem *confi5Hz;
        TMenuItem *confi1Grado;
        TMenuItem *confi05Grado;
        TMenuItem *confi025Grado;
        TMenuItem *confi0125Grado;
        TMenuItem *menuGPS;
        TMenuItem *conectarGPS;
        TMenuItem *nPuertoGPS;
        TMenuItem *nVelocidadGPS;
        TMenuItem *gpsPuerto1;
        TMenuItem *gpsPuerto2;
        TMenuItem *gpsPuerto3;
        TMenuItem *gpsPuerto4;
        TMenuItem *gpsPuerto5;
        TMenuItem *gpsPuerto6;
        TMenuItem *vGPS1200;
        TMenuItem *vGPS2400;
        TMenuItem *vGPS4800;
        TMenuItem *vGPS9600;
        TMenuItem *vGPS19200;
        TMenuItem *vGPS38400;
        TMenuItem *vGPS57600;
        TMenuItem *vGPS115200;
        TMenuItem *otras;
        TMenuItem *tarjetaAdquisicion;
        TMenuItem *can;
        TMenuItem *threadLectura;
        TMenuItem *IniciarLecturaLaser;
        TMenuItem *PararLecturaLaser;
        TTimer *Temporizador;
        TPanel *panel;
        TImage *imagenPanel;
        TTimer *timerPantalla;
  TTimer *TimerGPS;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TEdit *Edit1;
        TLabel *Label1;
        TEdit *Edit2;
        TEdit *Edit3;
        TLabel *Label2;
        TMenuItem *ConexionRapida1;
        TClientSocket *ClientSocket1;
        TClientSocket *ClientSocket2;
        TClientSocket *ClientSocket3;
        
        void __fastcall ConectarPuertoClick(TObject *Sender);
        void __fastcall laserPuerto1Click(TObject *Sender);
        void __fastcall laserPuerto2Click(TObject *Sender);
        void __fastcall laserPuerto3Click(TObject *Sender);
        void __fastcall laserPuerto4Click(TObject *Sender);
        void __fastcall laserPuerto5Click(TObject *Sender);
        void __fastcall laserPuerto6Click(TObject *Sender);
        void __fastcall vLaser1200Click(TObject *Sender);
        void __fastcall vLaser2400Click(TObject *Sender);
        void __fastcall vLaser4800Click(TObject *Sender);
        void __fastcall vLaser9600Click(TObject *Sender);
        void __fastcall vLaser19200Click(TObject *Sender);
        void __fastcall vLaser38400Click(TObject *Sender);
        void __fastcall vLaser57600Click(TObject *Sender);
        void __fastcall vLaser115200Click(TObject *Sender);
        void __fastcall botonInicializarClick(TObject *Sender);
        void __fastcall Confi60GradosClick(TObject *Sender);
        void __fastcall Confi180GradosClick(TObject *Sender);
        void __fastcall confi10HzClick(TObject *Sender);
        void __fastcall confi5HzClick(TObject *Sender);
        void __fastcall confi1GradoClick(TObject *Sender);
        void __fastcall confi05GradoClick(TObject *Sender);
        void __fastcall confi025GradoClick(TObject *Sender);
        void __fastcall confi0125GradoClick(TObject *Sender);
        void __fastcall RotarClick(TObject *Sender);
        void __fastcall HaltClick(TObject *Sender);
        void __fastcall conectarGPSClick(TObject *Sender);
        void __fastcall gpsPuerto1Click(TObject *Sender);
        void __fastcall gpsPuerto2Click(TObject *Sender);
        void __fastcall gpsPuerto3Click(TObject *Sender);
        void __fastcall gpsPuerto4Click(TObject *Sender);
        void __fastcall gpsPuerto5Click(TObject *Sender);
        void __fastcall gpsPuerto6Click(TObject *Sender);
        void __fastcall vGPS1200Click(TObject *Sender);
        void __fastcall vGPS2400Click(TObject *Sender);
        void __fastcall vGPS4800Click(TObject *Sender);
        void __fastcall vGPS9600Click(TObject *Sender);
        void __fastcall vGPS19200Click(TObject *Sender);
        void __fastcall vGPS38400Click(TObject *Sender);
        void __fastcall vGPS57600Click(TObject *Sender);
        void __fastcall vGPS115200Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall TemporizadorTimer(TObject *Sender);
        void __fastcall IniciarLecturaLaserClick(TObject *Sender);
        void __fastcall PararLecturaLaserClick(TObject *Sender);
        void __fastcall botonECOClick(TObject *Sender);
        void __fastcall LINEA (int P1, int P2, int P3, int P4);
        void __fastcall timerPantallaTimer(TObject *Sender);
  void __fastcall TimerGPSTimer(TObject *Sender);
  void __fastcall tarjetaAdquisicionClick(TObject *Sender);
  void __fastcall canClick(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall ConexionRapida1Click(TObject *Sender);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket2Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket3Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket2Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket3Connect(TObject *Sender,
          TCustomWinSocket *Socket);


private:	// User declarations
        Puertos *conPuerto;
//        int numPuerto_laser_menu;
        int np_laser;
        int vp_laser;
//        int numPuerto_gps_menu;
        int np_gps;
        int vp_gps;
        Laser *miLaser; //Puntero de la clase Laser.
        int ampli;
        int frecuencia;
        bool inicio, puerto, velocidad, ECO;
        String resolucion;
        bool leyendo;
        void DibujarEjes();
        TShape *Shape[750];
        Pintar *P;
        TDatosPintar *datosPintar;
        ThreadLecturaGPS *TLGPS;
        Control_Advantech * CA;
        CCANFunctions * CAN_VECTOR;
        int CAN_Status;
        Fichero *F;
        HANDLE Handle_Dispatcher;
        static DWORD WINAPI __stdcall Dispatcher(LPVOID lpParameter);
        FineTime *FT;
        bool finDispatcher;
        static DWORD WINAPI __stdcall PintarPantalla();
        static DWORD WINAPI __stdcall PintarPantalla2();
        static DWORD WINAPI __stdcall PintarPantalla3();
        bool finPintarPantalla;
        HANDLE Handle_PintarPantalla, Handle_PintarPantalla2, Handle_PintarPantalla3;
        void  Swich_DO(double AI);
        int DO_0;
        bool Rec1, Rec2;


// ATRIBUTO PARA LA CONFIGURACION DEL GPS        ThreadManejoGPS *TMGPS;


public:		// User declarations
        __fastcall TPrincipal(TComponent* Owner);



};
//---------------------------------------------------------------------------
extern PACKAGE TPrincipal *Principal;
//---------------------------------------------------------------------------
#endif
