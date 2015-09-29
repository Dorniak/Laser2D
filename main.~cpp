//---------------------------------------------------------------------------

#include <vcl.h>
#include <mmsystem.h>
#pragma hdrstop

#include "main.h"

#include "LectorDatos.h"
#include "Pintar.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TPrincipal *Principal;



//---------------------------------------------------------------------------
__fastcall TPrincipal::TPrincipal(TComponent* Owner)
    : TForm(Owner)
{
    conPuerto = new Puertos();
    np_laser = 4;
    laserPuerto4->Checked = true;
    vp_laser = 115200;
    vLaser115200->Checked = true;
    puerto = false;
    velocidad = false;
    inicio = false;
    botonECO->Checked = false;
    ECO=false;
    resolucion = "";
    leyendo=false;
    miLaser = new Laser(textMemo, conPuerto);
    miLaser->lectorDatos->setMemo(Memo1);
    
    textMemo->SetTextBuf("Controlador Láser SICK");
    Memo1->SetTextBuf("Resultados");
    P = new Pintar();
    datosPintar = miLaser->GetDatosPintar();
    //datosPintar = new TDatosPintar();
    ConectarPuerto->Enabled = TRUE;
    botonInicializar->Enabled = FALSE;
    botonApertura->Enabled = FALSE;
    Confi60Grados->Enabled = FALSE;
    Confi180Grados->Enabled = FALSE;
    botonFrecuencia->Enabled = FALSE;
    confi10Hz->Enabled = FALSE;
    confi5Hz->Enabled = FALSE;
    botonResolucion->Enabled = FALSE;
    confi1Grado->Enabled = FALSE;
    confi05Grado->Enabled = FALSE;
    confi025Grado->Enabled = FALSE;
    confi0125Grado->Enabled = FALSE;
    Rotar->Enabled = FALSE;
    Halt->Enabled = FALSE;
    botonECO->Enabled = FALSE;
    //menuGPS->Enabled = FALSE;
    //otras->Enabled = FALSE;
    threadLectura->Enabled = FALSE;
    IniciarLecturaLaser->Enabled = FALSE;
    PararLecturaLaser->Enabled = FALSE;
    velauto=0;
    autov=false;
    autod=false;
    autof=false;
    int k;
    panel->DoubleBuffered = true;
    Principal->panel->Color = clWhite;
    for (k=0; k<750; k++)
    {

        Shape[k] = new TShape(panel);
        Shape[k]->Brush->Color=clGreen;
        Shape[k]->Pen->Color=clGreen;
        Shape[k]->Shape = stCircle;
        Shape[k]->Width=4;
        Shape[k]->Height=4;

        Shape[k]->Top= imagenPanel->Height/2.0;
        Shape[k]->Left= imagenPanel->Width/2.0;
        Shape[k]->Visible = true;

        panel->InsertControl(Shape[k]);
        //Shape[k]->Show();
    }
    CA = NULL;
    CAN_VECTOR = new CCANFunctions();
    CAN_Status = -1;

    FT = new FineTime();
    timeBeginPeriod(1);
    finDispatcher = false;
    finPintarPantalla = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrincipal::ConectarPuertoClick(TObject *Sender)
{
    nPuertoLaser->Enabled = FALSE;
    nVelocidadLaser->Enabled = FALSE;
    ConectarPuerto->Enabled = FALSE;

    if (!inicio)
    {
        botonInicializar->Enabled = TRUE;
        botonApertura->Enabled = FALSE;
        Confi60Grados->Enabled = FALSE;
        Confi180Grados->Enabled = FALSE;
    }
    else if(inicio)
    {
        botonInicializar->Enabled = FALSE;
        botonApertura->Enabled = TRUE;
        Confi60Grados->Enabled = TRUE;
        Confi180Grados->Enabled = TRUE;
    }
    puerto = false;
    velocidad = false;

    conPuerto->AbrirPuerto(np_laser,vp_laser,NOPARITY,ONESTOPBIT,DTR_CONTROL_DISABLE,100);
    textMemo->SetTextBuf("La conexión con el láser se ha establecido.");
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("La configuración que ha elegido es:");
    textMemo->Lines->Add("Número de puerto: " + AnsiString(np_laser));
    textMemo->Lines->Add("Velocidad: " + AnsiString(vp_laser));


}

//---------------------------------------------------------------------------

void __fastcall TPrincipal::laserPuerto1Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoLaser->Count; i++)
    {
        nPuertoLaser->Items[i]->Checked = false;
    }

    puerto=true;

    textMemo->SetTextBuf("Ha seleccionado el puerto número 1");

    laserPuerto1->Checked = true;
    np_laser = laserPuerto1->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;

}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::laserPuerto2Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoLaser->Count; i++)
    {
        nPuertoLaser->Items[i]->Checked = false;
    }

    puerto=true;

    textMemo->SetTextBuf("Ha seleccionado el puerto número 2");

    laserPuerto2->Checked = true;
    np_laser = laserPuerto2->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::laserPuerto3Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoLaser->Count; i++)
    {
        nPuertoLaser->Items[i]->Checked = false;
    }

    puerto=true;

    textMemo->SetTextBuf("Ha seleccionado el puerto número 3");

    laserPuerto3->Checked = true;
    np_laser = laserPuerto3->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::laserPuerto4Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoLaser->Count; i++)
    {
        nPuertoLaser->Items[i]->Checked = false;
    }

    puerto=true;

    textMemo->SetTextBuf("Ha seleccionado el puerto número 4");

    laserPuerto4->Checked = true;
    np_laser = laserPuerto4->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::laserPuerto5Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoLaser->Count; i++)
    {
        nPuertoLaser->Items[i]->Checked = false;
    }

    puerto=true;

    textMemo->SetTextBuf("Ha seleccionado el puerto número 5");

    laserPuerto5->Checked = true;
    np_laser = laserPuerto5->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::laserPuerto6Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoLaser->Count; i++)
    {
        nPuertoLaser->Items[i]->Checked = false;
    }

    puerto=true;

    textMemo->SetTextBuf("Ha seleccionado el puerto número 6");

    laserPuerto6->Checked = true;
    np_laser = laserPuerto6->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser1200Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 1200.");

    vLaser1200->Checked = true;
    vp_laser = vLaser1200->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser2400Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 2400.");

    vLaser2400->Checked = true;
    vp_laser = vLaser2400->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser4800Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 4800.");

    vLaser4800->Checked = true;
    vp_laser = vLaser4800->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser9600Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 9600.");

    vLaser9600->Checked = true;
    vp_laser = vLaser9600->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser19200Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 19200.");

    vLaser19200->Checked = true;
    vp_laser = vLaser19200->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser38400Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 38400.");

    vLaser38400->Checked = true;
    vp_laser = vLaser38400->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser57600Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 57600.");

    vLaser57600->Checked = true;
    vp_laser = vLaser57600->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vLaser115200Click(TObject *Sender)
{
    for (int i = 0; i < nVelocidadLaser->Count; i++)
    {
        nVelocidadLaser->Items[i]->Checked = false;
    }

    velocidad=true;

    textMemo->Lines->Add("Ha seleccionado una velocidad de 115200.");

    vLaser115200->Checked = true;
    vp_laser = vLaser115200->Tag;

    if (puerto && velocidad)
        ConectarPuerto->Enabled = TRUE;
}
//---------------------------------------------------------------------------


void __fastcall TPrincipal::botonInicializarClick(TObject *Sender)
{

    ConectarPuerto->Enabled = FALSE;
    botonApertura->Enabled = TRUE;
    Confi60Grados->Enabled = TRUE;
    Confi180Grados->Enabled = TRUE;
    botonInicializar->Enabled = FALSE;
    botonECO->Enabled = TRUE;
    Halt->Enabled = TRUE;

    inicio = true;
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("El láser se está inicializando, espere unos segundos.");
    miLaser->BotonInicializarClick(np_laser, vp_laser);
    textMemo->SetTextBuf("El láser ha sido inicializado.");
    Temporizador->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Confi60GradosClick(TObject *Sender)
{
    ConectarPuerto->Enabled = FALSE;
    nPuertoLaser->Enabled = FALSE;
    nVelocidadLaser->Enabled = FALSE;
    botonInicializar->Enabled = FALSE;
    botonFrecuencia->Enabled = TRUE;
    confi10Hz->Enabled = TRUE;
    confi5Hz->Enabled = TRUE;
    ampli=60;
    Confi60Grados->Checked = True;
    Confi180Grados->Checked = False;


    miLaser->BotonConfi60GradosClick();
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("Ha elegido una amplitud de 60°");
    Temporizador->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Confi180GradosClick(TObject *Sender)
{
    ConectarPuerto->Enabled = FALSE;
    nPuertoLaser->Enabled = FALSE;
    nVelocidadLaser->Enabled = FALSE;
    botonInicializar->Enabled = FALSE;
    botonFrecuencia->Enabled = TRUE;
    confi10Hz->Enabled = TRUE;
    confi5Hz->Enabled = TRUE;
    ampli=180;

    miLaser->BotonConfi180GradosClick();
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("Ha elegido una amplitud de 180°");
    Temporizador->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::confi10HzClick(TObject *Sender)
{
    for (int i = 0; i < botonFrecuencia->Count; i++)
    {
        botonFrecuencia->Items[i]->Checked = false;
    }

    frecuencia=10;

    botonResolucion->Enabled = TRUE;
    if(!ECO)
    {
        if (ampli==60)
        {
            confi1Grado->Enabled = FALSE;
            confi05Grado->Enabled = TRUE;
            confi025Grado->Enabled = TRUE;
            confi0125Grado->Enabled = FALSE;
        }
        else if (ampli==180)
        {
            confi1Grado->Enabled = TRUE;
            confi05Grado->Enabled = FALSE;
            confi025Grado->Enabled = FALSE;
            confi0125Grado->Enabled = FALSE;
        }

    }
    else if(ECO)
    {
        if (ampli==60)
        {
            confi1Grado->Enabled = TRUE;
            confi05Grado->Enabled = TRUE;
            confi025Grado->Enabled = FALSE;
            confi0125Grado->Enabled = FALSE;
        }
        else if (ampli==180)
        {
            confi1Grado->Enabled = FALSE;
            confi05Grado->Enabled = FALSE;
            confi025Grado->Enabled = FALSE;
            confi0125Grado->Enabled = FALSE;
        }
    }

    miLaser->confi10HzClick();

    textMemo->Lines->Add("El láser va a girar a una frecuencia de 10Hz.");
    confi10Hz->Checked = true;


}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::confi5HzClick(TObject *Sender)
{
    for (int i = 0; i < botonFrecuencia->Count; i++)
    {
        botonFrecuencia->Items[i]->Checked = false;
    }

    frecuencia=5;

    botonResolucion->Enabled = TRUE;

    if(!ECO)
    {
        if (ampli==60)
        {
            confi1Grado->Enabled = FALSE;
            confi05Grado->Enabled = TRUE;
            confi025Grado->Enabled = TRUE;
            confi0125Grado->Enabled = TRUE;
        }
        else if (ampli==180)
        {
            confi1Grado->Enabled = TRUE;
            confi05Grado->Enabled = TRUE;
            confi025Grado->Enabled = FALSE;
            confi0125Grado->Enabled = FALSE;
        }
    }
    else if(ECO)
    {
        if (ampli==60)
        {
            confi1Grado->Enabled = TRUE;
            confi05Grado->Enabled = TRUE;
            confi025Grado->Enabled = TRUE;
            confi0125Grado->Enabled = FALSE;
        }
        else if (ampli==180)
        {
            confi1Grado->Enabled = TRUE;
            confi05Grado->Enabled = FALSE;
            confi025Grado->Enabled = FALSE;
            confi0125Grado->Enabled = FALSE;
        }
    }


    miLaser->confi5HzClick();

    textMemo->Lines->Add("El láser va a girar a una frecuencia de 5Hz.");
    confi5Hz->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::confi1GradoClick(TObject *Sender)
{
    Rotar->Enabled = TRUE;
    resolucion = "1°";

    miLaser->BotonConfi1GradoClick();
    textMemo->Lines->Add("Se ha configurado para medir pulsos de 1°");
    Temporizador->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::confi05GradoClick(TObject *Sender)
{
    Rotar->Enabled = TRUE;
    resolucion = "0.5°";

    miLaser->BotonConfi05GradoClick();
    textMemo->Lines->Add("Se ha configurado para medir pulsos de 0.5°");
    Temporizador->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::confi025GradoClick(TObject *Sender)
{
    Rotar->Enabled = TRUE;
    resolucion = "0.25°";

    miLaser->BotonConfi025GradoClick();
    textMemo->Lines->Add("Se ha configurado para medir pulsos de 0.25°");
    Temporizador->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::confi0125GradoClick(TObject *Sender)
{
    Rotar->Enabled = TRUE;
    resolucion = "0.125°";

    miLaser->BotonConfi0125GradoClick();
    textMemo->Lines->Add("Se ha configurado para medir pulsos de 0.125°");
    Temporizador->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::RotarClick(TObject *Sender)
{
    botonApertura->Enabled = FALSE;
    Confi60Grados->Checked = FALSE;
    Confi180Grados->Checked = FALSE;
    botonFrecuencia->Enabled = FALSE;
    botonResolucion->Enabled = FALSE;
    threadLectura->Enabled = TRUE;
    IniciarLecturaLaser->Enabled = TRUE;
    Halt->Enabled = TRUE;
    botonECO->Enabled=FALSE;


    textMemo->SetTextBuf("El láser está rotando con esta configuración:");
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("Ampitud: " + AnsiString(ampli)+"°");
    textMemo->Lines->Add("Frecuencia: " + AnsiString(frecuencia) +"Hz");
    textMemo->Lines->Add("Resolución: " + resolucion);
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("Espere unos segundos, por favor.");
    miLaser->BotonRotarClick();
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("Ya puede continuar");


    Temporizador->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::HaltClick(TObject *Sender)
{
    nPuertoLaser->Enabled = TRUE;
    nVelocidadLaser->Enabled = TRUE;
    botonApertura->Enabled = TRUE;
    threadLectura->Enabled = FALSE;
    IniciarLecturaLaser->Enabled = FALSE;
    PararLecturaLaser->Enabled = FALSE;
    Halt->Enabled = FALSE;
    botonECO->Enabled=TRUE;

    // Temporizador->Enabled = false;


    miLaser->BotonHaltClick();
    Principal->textMemo->SetTextBuf("Se ha parado el láser.");



    //miLaser->AcabarThread();


}
//---------------------------------------------------------------------------



// METODO PARA CONECTAR EL GPS

void __fastcall TPrincipal::conectarGPSClick(TObject *Sender)
{

    if (conectarGPS->Checked == true)
    {
        //TimerGPS->Enabled = false;
        conectarGPS->Checked = false;
        conectarGPS->Caption = "Conectar GPS";
        textMemo->Lines->Add(AnsiString("GPS Detenido"));
        TLGPS->Finalizar();
        CheckBox2->Checked = false;
    }
    else
    {
        conectarGPS->Checked = true;
        TLGPS = new ThreadLecturaGPS(false, np_gps,vp_gps);
        conectarGPS->Caption = "Parar GPS";
        textMemo->Lines->Add(AnsiString("GPS Iniciado"));
        CheckBox2->Checked = true;
        // TimerGPS->Enabled = true;
    }
}

//---------------------------------------------------------------------------

/*

METODO PARA LA CONFIGURACION DEL GPS

void __fastcall TPrincipal::COM_GPSComm(TObject *Sender)
{
  TMGPS->Resume();
}   */


//---------------------------------------------------------------------------

void __fastcall TPrincipal::gpsPuerto1Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    gpsPuerto1->Checked = true;
    np_gps = gpsPuerto1->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::gpsPuerto2Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    gpsPuerto2->Checked = true;
    np_gps = gpsPuerto2->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::gpsPuerto3Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    gpsPuerto3->Checked = true;
    np_gps = gpsPuerto3->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::gpsPuerto4Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    gpsPuerto4->Checked = true;
    np_gps = gpsPuerto4->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::gpsPuerto5Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    gpsPuerto5->Checked = true;
    np_gps = gpsPuerto5->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::gpsPuerto6Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    gpsPuerto6->Checked = true;
    np_gps = gpsPuerto6->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vGPS1200Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS1200->Checked = true;
    vp_gps = vGPS1200->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vGPS2400Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS2400->Checked = true;
    vp_gps = vGPS2400->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vGPS4800Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS4800->Checked = true;
    vp_gps = vGPS4800->Tag;
}
//---------------------------------------------------------------------------






void __fastcall TPrincipal::vGPS9600Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS9600->Checked = true;
    vp_gps = vGPS9600->Tag;
}
//---------------------------------------------------------------------------


void __fastcall TPrincipal::vGPS19200Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS19200->Checked = true;
    vp_gps = vGPS19200->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vGPS38400Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS38400->Checked = true;
    vp_gps = vGPS38400->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vGPS57600Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS57600->Checked = true;
    vp_gps = vGPS57600->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::vGPS115200Click(TObject *Sender)
{
    for (int i = 0; i < nPuertoGPS->Count; i++)
    {
        nPuertoGPS->Items[i]->Checked = false;
    }

    vGPS115200->Checked = true;
    vp_gps = vGPS115200->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::FormClose(TObject *Sender,
                                      TCloseAction &Action)
{
    miLaser->AcabarThread();
    if (CA != NULL)
        CA->Finalizar();
    //delete miLaser;
    if (CAN_Status>0)
    {
        CAN_VECTOR->CANGoOffBus();
        delete CAN_VECTOR;
    }
    CheckBox1->Checked = false;
    delete FT;
    miLaser->BotonPararLecturaClick();
    finDispatcher = true;
    Sleep(500);
    CloseHandle(Handle_Dispatcher);
    if (IniciarLecturaLaser->Enabled)
        F->CerrarFichero();
    delete F;
    miLaser->BotonHaltClick();
    ClientSocket1->Close();
    ClientSocket2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TemporizadorTimer(TObject *Sender)
{

//int i=0;
    AnsiString salidalaser = AnsiString(miLaser->LeerCadena());
    while (salidalaser.Length()==0)
        salidalaser = AnsiString(miLaser->LeerCadena());

//if (salidalaser[10] == '0')
    /*
    if (salidalaser[1] == '0')
           textMemo->Lines->Add("ERROR");
    else
           textMemo->Lines->Add(salidalaser);
    */

    Temporizador->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TPrincipal::IniciarLecturaLaserClick(TObject *Sender)
{


    Rotar->Enabled = FALSE;
    PararLecturaLaser->Enabled = TRUE;

    if (ECO)
        miLaser->BotonLecturaConECOClick(ECO);
    else if (!ECO) miLaser->BotonLecturaClick(ECO);


    Temporizador->Enabled = true;



    textMemo->SetTextBuf("Iniciando lectura...");
    textMemo->Lines->Add("");
    textMemo->Lines->Add("Se están almacenando datos en el fichero.");
    textMemo->Lines->Add("Pare de leer cuando lo desee...");

    leyendo=true;
    DibujarEjes();

    //timerPantalla->Enabled= true;


    Temporizador->Enabled = true;
    F = new Fichero();
    // F->EscribirDato(AnsiString("Time, North, East, Heigh, Steering, Speed, Throttle, Brake, AI0, AI1 \r\n"));
    // TimerGPS->Enabled = true;
    finDispatcher = false;
    DWORD myThreadID;
    Handle_Dispatcher = CreateThread(0, 0, (LPTHREAD_START_ROUTINE ) Dispatcher, textMemo, 0, &myThreadID);
    SetThreadPriority(Handle_Dispatcher,  REALTIME_PRIORITY_CLASS);

    //Sleep(1000);
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::PararLecturaLaserClick(TObject *Sender)
{

    //leyendo=false;

    timerPantalla->Enabled = False;

    Halt->Enabled = TRUE;
    IniciarLecturaLaser->Enabled = TRUE;

    //  miLaser->Terminate();


    miLaser->BotonPararLecturaClick();
    //textMemo->SetTextBuf("Ha parado de leer datos.");
    //TimerGPS->Enabled = false;
    finDispatcher = true;
    Sleep(500);
    CloseHandle(Handle_Dispatcher);
    F->CerrarFichero();
    delete F;
    textMemo->SetTextBuf("Ha parado de leer datos.");



}
//---------------------------------------------------------------------------


void __fastcall TPrincipal::botonECOClick(TObject *Sender)
{
    if (ECO)
    {
        ECO = false;
        botonECO->Checked = False;
        textMemo->SetTextBuf("Ha elegido la opción sin Eco.");

    }
    else if (!ECO)
    {
        ECO = true;
        botonECO->Checked = True;
        textMemo->SetTextBuf("Ha elegido la opción con Eco");
    }
    botonApertura->Enabled = TRUE;
    Confi60Grados->Enabled = TRUE;
    Confi180Grados->Enabled = TRUE;
    botonFrecuencia->Enabled = FALSE;
    botonResolucion->Enabled = FALSE;

}
//---------------------------------------------------------------------------


void __fastcall TPrincipal::LINEA (int P1, int P2, int P3, int P4)

{
    imagenPanel->Canvas->MoveTo(P1,P2);
    imagenPanel->Canvas->LineTo(P3,P4);

}

//---------------------------------------------------------------------------

void __fastcall TPrincipal::timerPantallaTimer(TObject *Sender)
{
    int i, j;
    double posX, posY;
    double auxX, auxY;


//while (leyendo)
//{
    //DatosPintar->convertirDatos();

    // for(i=0;i<2;i++) //750
    for(j=0; j<750; j++)
    {


        posX = datosPintar->coordenadas[0][j];
        posY = datosPintar->coordenadas[1][j];

        Shape[j]->Top = 200 -posX;
        Shape[j]->Left = 250 - posY;
        Shape[j]->Visible = true;
        Shape[j]->Show();


    }

//}


//timerPantalla->Enabled = False;
}
//---------------------------------------------------------------------------


void TPrincipal::DibujarEjes()
{
    int i,j,k;


    imagenPanel->Canvas->Pen->Style=psDot;//psSolid
    imagenPanel->Canvas->Pen->Color=clLtGray;



    LINEA(imagenPanel->Width/2.0, 0, imagenPanel->Width/2.0, imagenPanel->Height);
    LINEA(0, imagenPanel->Height/2.0, imagenPanel->Width, imagenPanel->Height/2.0);

}



void __fastcall TPrincipal::TimerGPSTimer(TObject *Sender)
{
    if (CheckBox2->Checked)
        miLaser->SetTiempo(TLGPS->GetUTM_Time());
    AnsiString AI;
    if (CheckBox3->Checked)
        for (int i=0; i<16; i++)
            AI+=AnsiString(CA->Get_AI_Data(i))+AnsiString(" ");

    AnsiString DatosSalida;
    if (CheckBox2->Checked)
        DatosSalida = AnsiString(miLaser->lectorDatos->tiempo)+AnsiString("  ")+AnsiString(TLGPS->GetUTM_North())+AnsiString("  ")+AnsiString(TLGPS->GetUTM_East())+AnsiString("  ")+AnsiString(TLGPS->GetUTM_Height())+AnsiString("  ")+AnsiString(CAN_VECTOR->Steering_Angle)+AnsiString("  ")+AnsiString(CAN_VECTOR->Speed)+AnsiString("  ")+AnsiString(CAN_VECTOR->Throttle)+AnsiString("  ")+AnsiString(CAN_VECTOR->Brake)+AnsiString("  ")+AI;
    else
        DatosSalida = AnsiString((int)(miLaser->lectorDatos->tiempo))+AnsiString("  ")+AnsiString(0)+AnsiString("  ")+AnsiString(0)+AnsiString("  ")+AnsiString(0)+AnsiString("  ")+AnsiString(CAN_VECTOR->Steering_Angle)+AnsiString("  ")+AnsiString(CAN_VECTOR->Speed)+AnsiString("  ")+AnsiString(CAN_VECTOR->Throttle)+AnsiString("  ")+AnsiString(CAN_VECTOR->Brake)+AnsiString("  ")+AI;
    //textMemo->Lines->Add(DatosSalida);
    F->EscribirDato(DatosSalida+AnsiString("\r\n"));
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::tarjetaAdquisicionClick(TObject *Sender)
{
    CA = new Control_Advantech(false);
    textMemo->Lines->Add(AnsiString("Tarjeta de adquisición Advantech Inicializada"));
    CheckBox3->Checked = true;
    Principal->DO_0 = 0;
    Rec1 = false;
    Rec2 = false;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::canClick(TObject *Sender)
{
    CAN_Status=CAN_VECTOR->CANInit();
    CAN_VECTOR->CANSetFilter(1,2);
    CAN_VECTOR->CANGoOnBus(500000, 250000);
    textMemo->Lines->Add(AnsiString("Tarjeta CAN Vector Inicializada"));
    CheckBox4->Checked = true;

}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::CheckBox1Click(TObject *Sender)
{
    // timerPantalla->Enabled = CheckBox1->Checked;
    HANDLE Array_Of_Thread_Handles[3];
    if (CheckBox1->Checked)
    {
        finPintarPantalla = false;
        DWORD myThreadID;
        Handle_PintarPantalla = CreateThread(0, 0, (LPTHREAD_START_ROUTINE ) PintarPantalla, NULL, 0, &myThreadID);
        Handle_PintarPantalla2 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE ) PintarPantalla2, NULL, 0, &myThreadID);
        Handle_PintarPantalla3 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE ) PintarPantalla3, NULL, 0, &myThreadID);
        Array_Of_Thread_Handles[0] = Handle_PintarPantalla;
        Array_Of_Thread_Handles[1] = Handle_PintarPantalla2;
        Array_Of_Thread_Handles[2] = Handle_PintarPantalla3;
        // SetThreadPriority(Handle_PintarPantalla,  REALTIME_PRIORITY_CLASS);
        //SetThreadPriority(Handle_PintarPantalla2,  REALTIME_PRIORITY_CLASS);
        // SetThreadPriority(Handle_PintarPantalla3,  REALTIME_PRIORITY_CLASS);
        textMemo->Lines->Add("Entra en el thread");
    }
    else
    {
        finPintarPantalla = true;
        // Wait until all threads have terminated.
        //                     3_thread                       wait_all  time_miliseconds  (INFINITE)
        if ((WaitForMultipleObjects( 3, Array_Of_Thread_Handles, TRUE, 2000))==WAIT_TIMEOUT	)
        {
            DWORD dwExitCode;
            TerminateThread( Handle_PintarPantalla, dwExitCode);
        }
        textMemo->Lines->Add("Sale del WaitForMultipleObjects");
        CloseHandle(Handle_PintarPantalla);
        CloseHandle(Handle_PintarPantalla2);
        CloseHandle(Handle_PintarPantalla3);
    }
}
//---------------------------------------------------------------------------
DWORD WINAPI __stdcall TPrincipal::Dispatcher(LPVOID lpParameter)
{
    /*
    int freq = (Principal->Edit1->Text).ToInt();
    double Periodo = 1/(double)freq;
    int contador = 0;
    double frecuencia;

    FineTime *LLC = new FineTime();
    double tiempo_ejecucion =  LLC->GetFineTime();
    double tiempo_actual = LLC->GetFineTime();
    bool finlocal = false;
    //double frecuencia;
    while (!(Principal->finDispatcher)&&!(finlocal)){
    if (((tiempo_ejecucion+Periodo)-tiempo_actual) < 0.000001) {

       AnsiString AI;
       if (Principal->CheckBox3->Checked)
           for (int i=0; i<2; i++)
               AI+=AnsiString(Principal->CA->Get_AI_Data(i))+AnsiString(" ");
       /******** control de sensor de ultrasonidos activo******
       if (Principal->DO_0 == 0)
               Principal->Swich_DO(Principal->CA->Get_AI_Data(0));
       else
               Principal->Swich_DO(Principal->CA->Get_AI_Data(1));
       /******************************************************


       AnsiString DatosSalida = AnsiString((int)(Principal->miLaser->lectorDatos->tiempo))+AnsiString("  ")+AnsiString(0)+AnsiString("  ")+AnsiString(0)+AnsiString("  ")+AnsiString(0)+AnsiString("  ")+AnsiString(Principal->CAN_VECTOR->Steering_Angle)+AnsiString("  ")+AnsiString(Principal->CAN_VECTOR->Speed)+AnsiString("  ")+AnsiString(Principal->CAN_VECTOR->Throttle)+AnsiString("  ")+AnsiString(Principal->CAN_VECTOR->Brake)+AnsiString("  ")+AI+AnsiString(" ")+AnsiString(Principal->DO_0);
       Principal->textMemo->Lines->Add(AI+AnsiString(" ")+AnsiString(Principal->DO_0));
       Principal->F->EscribirDato(DatosSalida+AnsiString("\r\n"));

       frecuencia = 1/(tiempo_actual-tiempo_ejecucion);
       tiempo_ejecucion += Periodo;
       tiempo_actual = LLC->GetFineTime();
    }else{
     tiempo_actual = LLC->GetFineTime();
     //Aqui hay que poner un sleep timeBeginPeriod
     Sleep(1);
    }
    }
    delete LLC;
       */
    return 0;
}
//---------------------------------------------------------------------------
DWORD WINAPI __stdcall TPrincipal::PintarPantalla()
{

    int i, j;
    double posX, posY;
    double auxX, auxY;

    while (!(Principal->finPintarPantalla))
    {
        j = 0;
        // for(j=0;j<750;j++){
        while ((j<250)&&(!(Principal->finPintarPantalla)))
        {

            posX = Principal->datosPintar->coordenadas[0][j];
            posY = Principal->datosPintar->coordenadas[1][j];
            //posX = random(200);
            //posY = random(200);

            Principal->Shape[j]->Invalidate();
            Principal->Shape[j]->Top = 200 -posX;
            Principal->Shape[j]->Left = 250 - posY;

            //Principal->Shape[j]->Invalidate();
            //Principal->Shape[j]->Visible = true;
            //Principal->Shape[j]->Show();
            j++;
        }
        Principal->panel->Invalidate();

        //for (int i=0; i<750;i++)
        // Principal->Shape[i]->Visible = true;
        Principal->panel->Update();
        //Principal->panel->Color = clBlack;
        Sleep(1);
        //Principal->textMemo->Lines->Add("Vuelta 1");
        Principal->Edit2->Text = "1";
    }
    Principal->textMemo->Lines->Add("Sale del thread 1");
    return 0;
}
//---------------------------------------------------------------------------
DWORD WINAPI __stdcall TPrincipal::PintarPantalla2()
{

    int i, j;
    double posX, posY;
    double auxX, auxY;

    while (!(Principal->finPintarPantalla))
    {
        j = 250;
        // for(j=0;j<750;j++){
        while ((j<500)&&(!(Principal->finPintarPantalla)))
        {

            posX = Principal->datosPintar->coordenadas[0][j];
            posY = Principal->datosPintar->coordenadas[1][j];
            //posX = random(200);
            //posY = random(200);

            Principal->Shape[j]->Invalidate();
            Principal->Shape[j]->Top = 200 -posX;
            Principal->Shape[j]->Left = 250 - posY;

            //Principal->Shape[j]->Invalidate();
            //Principal->Shape[j]->Visible = true;
            //Principal->Shape[j]->Show();
            j++;
        }
        Principal->panel->Invalidate();

        //for (int i=0; i<750;i++)
        // Principal->Shape[i]->Visible = true;

        Principal->panel->Update();
       // Principal->panel->Color = clBlack;
        Sleep(1);
        //Principal->textMemo->Lines->Add("Vuelta 2");
        Principal->Edit2->Text = "2";
    }
    Principal->textMemo->Lines->Add("Sale del thread 2");
    return 0;
}
//---------------------------------------------------------------------------
DWORD WINAPI __stdcall TPrincipal::PintarPantalla3()
{

    int i, j;
    double posX, posY;
    double auxX, auxY;

    while (!(Principal->finPintarPantalla))
    {
        j = 500;
        // for(j=0;j<750;j++){
        while ((j<750)&&(!(Principal->finPintarPantalla)))
        {

            posX = Principal->datosPintar->coordenadas[0][j];
            posY = Principal->datosPintar->coordenadas[1][j];
            //posX = random(200);
            //posY = random(200);

            Principal->Shape[j]->Invalidate();
            Principal->Shape[j]->Top = 200 -posX;
            Principal->Shape[j]->Left = 250 - posY;
            //Principal->Shape[j]->Invalidate();
            //Principal->Shape[j]->Visible = true;
            //Principal->Shape[j]->Show();
            j++;
        }
        Principal->panel->Invalidate();

        //for (int i=0; i<750;i++)
        // Principal->Shape[i]->Visible = true;

        Principal->panel->Update();
        // Principal->panel->Color = clBlack;

        Sleep(1);
        //Principal->textMemo->Lines->Add("Vuelta 3");
        Principal->Edit2->Text = "3";
    }
    Principal->textMemo->Lines->Add("Sale del thread 3");
    return 0;
}
//---------------------------------------------------------------------------
void  TPrincipal::Swich_DO(double AI)
{
    double d_reconocimiento = Edit3->Text.ToDouble();
    if (DO_0 == 0)
    {
        if (AI < d_reconocimiento)
        {
            if (!(Rec1))
                Rec1 = true;
            else if (!(Rec2))
                Rec2 = true;
            else
            {
                Rec1 = false;
                Rec2 = false;
                CA->Set_DO_Data((Byte) 2);
                DO_0 = 1;
            }
        }
        else
        {
            Rec1 = false;
            Rec2 = false;
        }
    }
    else
    {
        if (AI > d_reconocimiento)
        {
            if (!(Rec1))
                Rec1 = true;
            else if (!(Rec2))
                Rec2 = true;
            else
            {
                Rec1 = false;
                Rec2 = false;
                CA->Set_DO_Data((Byte) 1);
                DO_0 = 0;
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ConexionRapida1Click(TObject *Sender)
{

    textMemo->Lines->Add("Iniciando configuración rapida...\n");
    laserPuerto4->Checked = true;
    np_laser = laserPuerto4->Tag;
    vLaser115200->Checked = true;
    vp_laser = vLaser115200->Tag;
    conPuerto->AbrirPuerto(np_laser,vp_laser,NOPARITY,ONESTOPBIT,DTR_CONTROL_DISABLE,100);
    textMemo->Lines->Add("La conexión con el láser se ha establecido...");
    textMemo->Lines->Add("Número de puerto: " + AnsiString(np_laser));
    textMemo->Lines->Add("Velocidad: " + AnsiString(vp_laser));
    miLaser->BotonInicializarClick(np_laser, vp_laser);
    textMemo->Lines->Add("\nEl láser ha sido inicializado...");
    textMemo->Lines->Add("");
    textMemo->Lines->Add("Parámetros:");
    Confi60Grados->Checked = True;
    Confi180Grados->Checked = False;
    miLaser->BotonConfi60GradosClick();
    textMemo->Lines->Add("Amplitud:\t60°");
    Temporizador->Enabled = true;
    miLaser->confi5HzClick();
    textMemo->Lines->Add("Frecuencia:\t5Hz.");
    confi5Hz->Checked = true;
    Rotar->Enabled = TRUE;
    resolucion = "0.125°";
    miLaser->BotonConfi0125GradoClick();
    textMemo->Lines->Add("Resolución:\t0.125°");
    botonApertura->Enabled = FALSE;
    Confi60Grados->Checked = FALSE;
    Confi180Grados->Checked = FALSE;
    botonFrecuencia->Enabled = FALSE;
    botonResolucion->Enabled = FALSE;
    threadLectura->Enabled = TRUE;
    IniciarLecturaLaser->Enabled = TRUE;
    Halt->Enabled = TRUE;
    botonECO->Enabled=FALSE;
    textMemo->Lines->Add("");
    textMemo->Lines->Add("El láser está rotando...");
    textMemo->Lines->Add("Espere unos segundos, por favor.");
    miLaser->BotonRotarClick();
    textMemo->Lines->Add(" ");
    textMemo->Lines->Add("Ya puede continuar");
}
//---------------------------------------------------------------------------
void __fastcall TPrincipal::ClientSocket1Error(TObject *Sender,
        TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    ClientSocket1->Active=false;
    ClientSocket1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ClientSocket2Error(TObject *Sender,
        TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    ClientSocket2->Active=false;
    ClientSocket2->Close();
}
//---------------------------------------------------------------------------
void __fastcall TPrincipal::ClientSocket3Error(TObject *Sender,
        TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    ClientSocket3->Active=false;
    ClientSocket3->Close();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TPrincipal::ClientSocket1Connect(TObject *Sender,
        TCustomWinSocket *Socket)
{
    miLaser->lectorDatos->socket_dir(Socket);
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ClientSocket2Connect(TObject *Sender,
        TCustomWinSocket *Socket)
{
    miLaser->lectorDatos->socket_vel(Socket);
}
//---------------------------------------------------------------------------
void __fastcall TPrincipal::ClientSocket3Connect(TObject *Sender,
        TCustomWinSocket *Socket)
{
    miLaser->lectorDatos->socket_emg(Socket);
}
//---------------------------------------------------------------------------




void __fastcall TPrincipal::Button1Click(TObject *Sender)
{
        autov=!autov;
        if (autov){
        double configvel = 6.0;
        ClientSocket3->Socket->SendBuf(&configvel, sizeof(double));
        }
        else  {
        double configvel = 7.0;
        ClientSocket3->Socket->SendBuf(&configvel, sizeof(double));
        }
}
void __fastcall TPrincipal::Button2Click(TObject *Sender)
{
        autod=!autod;
        if (autod){
        double configVol = 4.0;
        ClientSocket3->Socket->SendBuf(&configVol, sizeof(double));
        }
        else  {
        double configVol = 5.0;
        ClientSocket3->Socket->SendBuf(&configVol, sizeof(double));
        }
}
void __fastcall TPrincipal::Button3Click(TObject *Sender)
{
        autof=!autof;
        if (autof){
        double configFreno = 8.0;
        ClientSocket3->Socket->SendBuf(&configFreno, sizeof(double));
        }
        else  {
        double configFreno = 9.0;
        ClientSocket3->Socket->SendBuf(&configFreno, sizeof(double));
        }
}
//---------------------------------------------------------------------------

