//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LectorDatos.h"
#include "Fichero.h"
#include "FineTime.h"
#include <math.h>
#include <string>


int numTramas,longitud,numPalabra;

#pragma package(smart_init)


__fastcall LectorDatos::LectorDatos(bool CreateSuspended)

{
}
//---------------------------------------------------------------------------

__fastcall LectorDatos::LectorDatos(Puertos *puertoLectura, char fichero[60])

{

    comPuerto = puertoLectura;
    strcpy(nombreFichero,fichero);
    entrada[0]=0;
    entrada[1]=0;
    entrada[2]=0;
    entrada[3]=0;
    //conEco = eco;
    final=true;
    UTMNorth, UTMEast, Velocidad = 0;
    DatosPintar = new TDatosPintar();
    //DatosPintar->resetearArray();
    dir = (double *) malloc(sizeof(double));
    //vel = (float *) malloc(sizeof(double));
    vel = 10.0;
    Algoritmo_deteccion = new Deteccion();


}
//---------------------------------------------------------------------------


short int asciiToInt(int numAscii)
{
    if (numAscii < 0x40)
    {
        return (numAscii-0x30);
    }
    else
    {
        if (numAscii < 0x47)
        {
            return (numAscii-0x37);
        }
        else
        {
            return(numAscii-0x57);
        }
    }
}


//---------------------------------------------------------------------------

void LectorDatos::cambiarTrama()
{
    //Leer siguiente trama
    comPuerto->ReadChar(); //CRC
    comPuerto->ReadChar(); //CRC
    comPuerto->ReadChar(); //CRC
    comPuerto->ReadChar(); //CRC
    comPuerto->ReadChar(); //03
    comPuerto->ReadChar(); //02
    comPuerto->ReadChar(); //IDs
    comPuerto->ReadChar(); //IDs
    comPuerto->ReadChar(); //IDs
    comPuerto->ReadChar(); //IDs
    entrada[0] = asciiToInt(comPuerto->ReadChar()); //Long
    entrada[1] = asciiToInt(comPuerto->ReadChar()); //Long
    entrada[2] = asciiToInt(comPuerto->ReadChar()); //Long
    entrada[3] = asciiToInt(comPuerto->ReadChar()); //Long
    longitud = hexToDec();

    entrada[0] = asciiToInt(comPuerto->ReadChar()); //NumTramas
    entrada[1] = asciiToInt(comPuerto->ReadChar()); //NumTramas
    entrada[2] = asciiToInt(comPuerto->ReadChar()); //NumTramas
    entrada[3] = asciiToInt(comPuerto->ReadChar()); //NumTramas
    numTramas = hexToDec();
    numPalabra = 1;

}

//---------------------------------------------------------------------------

void LectorDatos::leerCuatro()
{
    if (numPalabra==longitud-1)
    {
        cambiarTrama();
    }
    entrada[0] = asciiToInt(comPuerto->ReadChar());
    entrada[1] = asciiToInt(comPuerto->ReadChar());
    entrada[2] = asciiToInt(comPuerto->ReadChar());
    entrada[3] = asciiToInt(comPuerto->ReadChar());
}

//---------------------------------------------------------------------------

int LectorDatos::hexToDec()
{
    return((4096*entrada[0])+(256*entrada[1])+(16*entrada[2])+entrada[3]);
}

//---------------------------------------------------------------------------

void LectorDatos::leerDatos(bool e)  //lectura de datos sin thread.
{

    Fichero *ficheroSalida = new Fichero();
    empezarLectura();
    AnsiString salida = AnsiString();
    int numSectores, sectorActual, resAngular, numPuntos/*, tiempo*/, direccion, metros, numScan, varEco;
    double centimetros;
    conEco= e;
    int i=0;
    double resultado_deteccion;
    numScan = 0;
    ////////4-5///////////////////6-7/////////8-9
    double configdir = 5.0,configvel = 7.0,configfreno = 8.0;
    Sockete->SendBuf(&configdir, sizeof(double));
    Sockete->SendBuf(&configvel, sizeof(double));
    Sockete->SendBuf(&configfreno, sizeof(double));
    do  //BUCLE PRINCIPAL
    {

        //Leemos hasta comienzo de trama
        while (comPuerto->ReadChar()!= '\x02') {}


        //INFORMACION DE TRAMA  COMIENZO
        //Leemos los siguientes cuatro caracteres
        leerCuatro(); // Ids
        leerCuatro(); // Longitud
        longitud = hexToDec();
        leerCuatro(); //FFFF
        if (hexToDec()==65535)  //Si es una trama de datos entramos
        {

            numScan++;
            numPalabra = 1; //Mirar si la FFFF cuenta
            leerCuatro(); // Número de tramas
            numPalabra++;
            numTramas = hexToDec();
            leerCuatro(); // Nombre del mens.
            numPalabra++;

            //INFORMACION DE SCAN  COMIENZO
            leerCuatro(); // PROFILEFORMAT
            numPalabra++;
            leerCuatro(); // PROFILEINFO
            numPalabra++;
            numSectores = entrada[3];
            leerCuatro(); // PROFILESENT
            numPalabra++;
            leerCuatro(); // PROFILECOUNT
            numPalabra++;

            //INFORMACION DE LAYER  COMIENZO
            leerCuatro(); // LAYERNUM
            numPalabra++;

            //INFORMACION DE SECTOR  COMIENZO
            do
            {
                leerCuatro(); // SECTORNUM
                numPalabra++;
                sectorActual = hexToDec();
                leerCuatro(); // DIRSTEP
                numPalabra++;
                resAngular = ((16*entrada[2])+entrada[3]); //Resolucion angular en (/16)
                leerCuatro(); // POINTNUM
                numPalabra++;
                numPuntos = hexToDec();
                leerCuatro(); // TSTART
                numPalabra++;
                tiempo = hexToDec();
                leerCuatro(); // STARDIR
                numPalabra++;
                direccion = hexToDec();

                //INFORMACION DE DISTANCIAS COMIENZO
                while (numPuntos>0)
                {
                    leerCuatro(); //Distancias
                    numPalabra++;
                    metros =(16*entrada[0]+entrada[1]);
                    //centimetros = (16*(double)entrada[2]+(double)entrada[3])/256;
                    centimetros = (16*entrada[2]+entrada[3])/256.0;

                    /*   if ((metros+centimetros)>1000){
                               if (metros>150) metros = 0;
                               if (centimetros>150) centimetros = 0;
                       }   */
                    int numScanviejo;
                    if (conEco)
                    {
                        leerCuatro(); //ECO
                        numPalabra++;
                        varEco = hexToDec();
                        //Aqui se escriben lo datos a fichero con eco
                        //salida.sprintf("%i\t%f\t%i\t%f\t%i\t%f\t%f\t%f\r\n",numScan,((double)metros+centimetros),varEco,(double)direccion/16,tiempo, UTMNorth, UTMEast, Velocidad);
                        salida.sprintf("%i\t%f\t%i\t%f\t%i\t%s\r\n",numScan,((double)metros+centimetros),varEco,(double)direccion/16,tiempo, Tiempo.c_str());
                        ficheroSalida->EscribirDato(salida);
                    }
                    else
                    {
                        //Aqui se escriben lo datos a fichero sin eco
                        //salida.sprintf("%i\t%f\t%f\t%i\t%f\t%f\t%s\r\n",numScan,((double)metros+centimetros),(double)direccion/16,tiempo,UTMNorth, UTMEast, Velocidad);

                        resultado_deteccion = Algoritmo_deteccion->getData(numScan,((float)metros+centimetros),(float)direccion/16.0,tiempo, vel,dir);

                        if (resultado_deteccion!=999){
                            salida.sprintf("%i\t%f\t%f\t%i\t%s\t%f\r\n",numScan,((double)metros+centimetros),(double)direccion/16,tiempo,Tiempo.c_str(), resultado_deteccion);
                            vel=resultado_deteccion;
                        }

                        //ficheroSalida->EscribirDato(salida);
                    }

                    //  if ((metros+centimetros)>100)
                    //  int ll=0;

                    DatosPintar->datosPintar[1][i]=((double)(metros+centimetros));
                    DatosPintar->datosPintar[2][i]=((double)(direccion/16));
                    i++;

                    if (i==750)
                    {
                        DatosPintar->convertirDatos();
                        //DatosPintar->resetearArray();
                        i=0;

                    }
                    numPuntos--;
                    direccion += resAngular; //Actualizar la direccion
                } //while fin

                //INFORMACION DE DISTANCIAS FIN

                leerCuatro(); // TEND
                numPalabra++;
                leerCuatro(); // ENDDIR
                numPalabra++;
            }
            while(sectorActual<numSectores-1);
               /* vel=10;
               dir=20;                  */
                Memo1->Lines->Add(vel);
                ficheroSalida->EscribirDato(salida);

                Socketd->SendBuf(dir, sizeof(double));
                Socketv->SendBuf(&vel, sizeof(double));

                Socketd->ReceiveBuf(dir, sizeof(double));
                Socketv->ReceiveBuf(&vel, sizeof(double));
            //INFORMACION DE SECTOR FIN

            leerCuatro(); // SENSTAT
            leerCuatro(); // SENSTAI
            leerCuatro(); //CRC
            comPuerto->ReadChar(); //FINALIZACION DE TRAMA
            //INFORMACION DE SCAN FIN

        }
        else
        {
            while (comPuerto->ReadChar()!='\x03') {}

        }
    }
    while(!final);  // BUCLE PRINCIPAL

    terminarLectura();
    ficheroSalida->CerrarFichero();
}


//---------------------------------------------------------------------------

void LectorDatos::terminarLectura()
{
    final=true;
}
//---------------------------------------------------------------------------

void LectorDatos::empezarLectura()
{
    final=false;
}

//---------------------------------------------------------------------------

__fastcall LectorDatos::~LectorDatos(void)
{
    delete Algoritmo_deteccion;
}
//---------------------------------------------------------------------------
void LectorDatos::SetNorth(double North)
{
    UTMNorth = North;
}
//---------------------------------------------------------------------------
void LectorDatos::SetEast(double East)
{
    UTMEast = East;
}
//---------------------------------------------------------------------------
void LectorDatos::SetVelocidad(double velocidad)
{
    Velocidad = velocidad;
}
//---------------------------------------------------------------------------
void LectorDatos::SetTiempo(AnsiString T)
{
    Tiempo  = T;
}
//---------------------------------------------------------------------------

void LectorDatos::socket_vel(TCustomWinSocket *Socketvv)
{
    Socketv = Socketvv;
}
void LectorDatos::socket_dir(TCustomWinSocket *Socketdd)
{
    Socketd = Socketdd;
}
void LectorDatos::socket_emg(TCustomWinSocket *Socketee)
{
    Sockete = Socketee;
}
void LectorDatos::setMemo(TMemo *Memo){
      Memo1 = Memo;
}
