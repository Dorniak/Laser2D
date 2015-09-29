//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Laser.h"

#include "Windows.h"

//---------------------------------------------------------------------------


__fastcall Laser::Laser(TMemo * D, Puertos * Puerto): TThread(true)
{
  Display = D;
  fin = false;
  NuevaCadena = false;
  conPuerto = Puerto;
  FreeOnTerminate = true;
  tipoDatos = false;
  frecuencia=0;
  amplitud=0;
  eco=false;
  lectorDatos = new LectorDatos(conPuerto, "sesion.log");


}
//---------------------------------------------------------------------------

void Laser::BotonRotarClick()
{
       /* Comando TRANS_ROTATE -> Se activa el láser en el modo ROTACIÓN. El motor arranca,
		y cuando se apaga, gira a una velocidad, definida por REV. El láser se apaga. */

       /* Cuidado al introducir los comandos, porque si hay algún dato inválido, el laser se
                pone en modo inactivo*/

       conPuerto->WriteChar('\x02');
       conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
       conPuerto->WriteString("\x30\x30\x30\x34"); // Longitud
       conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
       conPuerto->WriteString("\x30\x34\x30\x33"); // Comando 0403h
       conPuerto->WriteString("\x30\x30\x30\x30"); // REV -> Frecuencia de escaneo por defecto
       conPuerto->WriteString("\x39\x31\x33\x41"); // CRC (913A)
       conPuerto->WriteChar('\x03');


       Resume();
       Sleep(3000);

       /* Comando TRANS_MEASURE -> Se activa el láser en el modo MEDIDA. El laser comienza con
		la siguiente revolución. Se puede hacer una petición a un perfil para comenzar. */


        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x30\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x34\x30\x34"); // Comando 0404h
        conPuerto->WriteString("\x32\x44\x34\x35"); // CRC (2D45)
        conPuerto->WriteChar('\x03');



        Sleep(3000);
        Resume();

}


//---------------------------------------------------------------------------

void Laser::BotonHaltClick()
{
        /* Comando DO_RESET -> El laser entra en modo de REINICIO.

         Hay diferentes acciones:
                0h: Reset (El pc se reinicializa).
                1h: Restart (El pc no se reinicializa).
                2h: Halt (Se detiene la aplicación y se pasa a estado inactivo).

         Si la acción ha sido Reset o Restart, el laser transmite la respuesta
         a este comando, antes de que entre en la secuencia de reinicio.

         Si la acción ha sido Halt, el laser transmite la respuesta despues de
         ejecutar el comando. Mientras, el laser no responde a ninguna petición
         durante el reinicio y el inicio del sistema.

        */

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x30\x34"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x34\x30\x31"); // Comando 0401h
        conPuerto->WriteString("\x30\x30\x30\x32"); // 2h -> Halt
        conPuerto->WriteString("\x42\x31\x37\x41"); // CRC (B17A)
        conPuerto->WriteChar('\x03');

        //Resume();

  //      AcabarThread();

}

//---------------------------------------------------------------------------
void Laser::BotonInicializarClick(int numP, int vel)
{
        int numPuerto;
        int velocidad;
        numPuerto = numP;
        velocidad = vel;


        /* MENSAJES DE INICIALIZACIÓN DEL LÁSER */

        conPuerto->ClosePort();
        conPuerto->AbrirPuerto(numPuerto,velocidad,NOPARITY,ONESTOPBIT,DTR_CONTROL_ENABLE,100);

        // .SRI 0.
        conPuerto->WriteString("\x02\x73\x52\x49");
        conPuerto->WriteChar('\x20');
        conPuerto->WriteChar('\x30');
        conPuerto->WriteChar('\x03');

        Resume();
        Sleep(500);

        conPuerto->ClosePort();
        conPuerto->AbrirPuerto(numPuerto,velocidad,NOPARITY,ONESTOPBIT,DTR_CONTROL_ENABLE,100);

        // ........sRI..h
        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x00');
        conPuerto->WriteChar('\x68');

        Resume();
        Sleep(500);

        conPuerto->ClosePort();
        conPuerto->AbrirPuerto(numPuerto,velocidad,NOPARITY,ONESTOPBIT,DTR_CONTROL_ENABLE,100);

        // ........sRI..h
        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x00');
        conPuerto->WriteChar('\x68');

        Resume();
        Sleep(500);

        // ........sRI..h
        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x00');
        conPuerto->WriteChar('\x68');

        Resume();
        Sleep(500);

        // ........sRI..i
        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x01');
        conPuerto->WriteChar('\x69');

        Resume();
        Sleep(500);

        // ........sRI..k

        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x03');
        conPuerto->WriteChar('\x6b');

        Resume();
        Sleep(500);

        // ........sRI..l

        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x04');
        conPuerto->WriteChar('\x6c');

        Resume()  ;
        Sleep(500);

        // ........sRI..n

        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x06');
        conPuerto->WriteChar('\x6e');

        Resume();
        Sleep(500);

        // ........sRI..j

        conPuerto->WriteString("\x02\x02\x02\x02");
        conPuerto->WriteString("\x00\x00\x00\x05");
        conPuerto->WriteString("\x73\x52\x49\x00");
        conPuerto->WriteChar('\x02');
        conPuerto->WriteChar('\x6a');


        /* FIN MENSAJES DE INICIALIZACIÓN DEL LÁSER */

        Resume();


}

//---------------------------------------------------------------------------

void Laser::BotonConfi60GradosClick()
{

        /* Configuración de medida para un ángulo frontal de 60º (150-210º) */


        /* SET_FUNCTION -> Se crea una función de medida. Los valores más relevantes son:
       		- Número de sector.
      		- Función del sector. Pueden ser:
     			0: No inicializado.
    			1: No medir.
   			2: Reservado.
  			3: Medición normal.
 			4: Medición de referencia.
		- Límite del sector para parar.
                - Flashflag: Los datos de configuración se almacenarán temporalmente.
        */

        fin=false;

        // SET_FUNCTION (SECTOR 0)
        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); //Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); //Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); //Cabecera
        conPuerto->WriteString("\x30\x32\x30\x41"); //Comando 020Ah
        conPuerto->WriteString("\x30\x30\x30\x30"); //Sector 0
        conPuerto->WriteString("\x30\x30\x30\x31"); //Función del sector -> No medir
        conPuerto->WriteString("\x30\x39\x35\x30"); //Limite del sector (150 minus 1)x16 = 2384 = 950h
        conPuerto->WriteString("\x30\x30\x30\x30"); //No escribir en flash
        conPuerto->WriteString("\x42\x39\x36\x34"); //CRC (B964)
        conPuerto->WriteChar('\x03');

        Resume();

        // SET_FUNCTION (SECTOR 1)
        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); //Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); //Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); //Cabecera
        conPuerto->WriteString("\x30\x32\x30\x41"); //Comando 020Ah
        conPuerto->WriteString("\x30\x30\x30\x31"); //Sector 1
        conPuerto->WriteString("\x30\x30\x30\x33"); //Función del sector -> Medida normal
        conPuerto->WriteString("\x30\x44\x31\x30"); //Limite del sector (210 minus 1)x16 = 3384 = D10h
        conPuerto->WriteString("\x30\x30\x30\x30"); //No escribir en flash
        conPuerto->WriteString("\x46\x39\x35\x35"); //CRC (F955)
        conPuerto->WriteChar('\x03');

        Resume();

        // SET_FUNCTION (SECTOR 2)
        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); //Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); //Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); //Cabecera
        conPuerto->WriteString("\x30\x32\x30\x41"); //Comando 020Ah
        conPuerto->WriteString("\x30\x30\x30\x32"); //Sector 2
        conPuerto->WriteString("\x30\x30\x30\x30"); //Función del sector -> No inicializado
        conPuerto->WriteString("\x31\x36\x37\x30"); //Limite de la zona (360 minus 1)x16 = 5744 = 1670h
        conPuerto->WriteString("\x30\x30\x30\x30"); //No escribir en flash
        conPuerto->WriteString("\x46\x44\x46\x38"); //CRC (FDF8)
        conPuerto->WriteChar('\x03');

        amplitud=60;

        Resume();

}

//---------------------------------------------------------------------------

void Laser::BotonConfi180GradosClick()
{
        /* Configuración de medida para un ángulo frontal de 180º (90-270º) */


	/* SET_FUNCTION -> Se crea una función de medida. Los valores más relevantes son:
		- Número de sector.
		- Función del sector. Pueden ser:
			0: No inicializado.
			1: No medir.
			2: Reservado.
			3: Medición normal.
			4: Medición de referencia.
		- Límite del sector para parar.
		- Flashflag: Los datos de configuración se almacenarán temporalmente.
	*/
		
	fin = false;
		
        // SET_FUNCTION (SECTOR 0)
        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); //Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); //Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); //Cabecera
        conPuerto->WriteString("\x30\x32\x30\x41"); //Comando 020Ah
        conPuerto->WriteString("\x30\x30\x30\x30"); //Sector 0
        conPuerto->WriteString("\x30\x30\x30\x31"); //Función del sector -> No medir
        conPuerto->WriteString("\x30\x35\x39\x30"); //Limite del sector (90 minus 1)x16 = 1424 = 590h
        conPuerto->WriteString("\x30\x30\x30\x30"); //No escribir en flash
        conPuerto->WriteString("\x32\x35\x34\x35"); //CRC (2545)
        conPuerto->WriteChar('\x03');

        Resume();

        // SET_FUNCTION (SECTOR 1)
        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); //Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); //Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); //Cabecera
        conPuerto->WriteString("\x30\x32\x30\x41"); //Comando 020Ah
        conPuerto->WriteString("\x30\x30\x30\x31"); //Sector 1
        conPuerto->WriteString("\x30\x30\x30\x33"); //Función del sector -> Medida normal
        conPuerto->WriteString("\x31\x30\x44\x30"); //Limite del sector (270 minus 1)x16 = 4304 = 10D0h
        conPuerto->WriteString("\x30\x30\x30\x30"); //No escribir en flash
        conPuerto->WriteString("\x35\x35\x33\x36"); //CRC (5536)
        conPuerto->WriteChar('\x03');

        Resume();

        // SET_FUNCTION (SECTOR 2)
        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); //Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); //Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); //Cabecera
        conPuerto->WriteString("\x30\x32\x30\x41"); //Comando 020Ah
        conPuerto->WriteString("\x30\x30\x30\x32"); //Sector 2
        conPuerto->WriteString("\x30\x30\x30\x30"); //Función del sector -> No inicializado
        conPuerto->WriteString("\x31\x36\x37\x30"); //Limite de la zona (360 minus 1)x16 = 5744 = 1670h
        conPuerto->WriteString("\x30\x30\x30\x30"); //No escribir en flash
        conPuerto->WriteString("\x46\x44\x46\x38"); //CRC (FDF8)
        conPuerto->WriteChar('\x03');

        amplitud=180;

        Resume();

}

//---------------------------------------------------------------------------


void Laser::BotonConfi1GradoClick()
{

/* SET_CONFIG -> Se crea una configuración que se queda almacenada.
Los valores configurables son:
        - ID de sensor.
       	- Velocidad a la que gira el motor. Entre 5 y 20 Hz
       	- Ángulo de paso. Diferencia entre dos pulsos de laser en 1/16
          grados. Tiene que ser divisible entre 5760 y mayor que 1.
*/

if (amplitud==60)
        {
        // No funciona



        }else if (amplitud==180){

                if (frecuencia==5){

        	conPuerto->WriteChar('\x02');
                conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
                conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
                conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
                conPuerto->WriteString("\x30\x32\x30\x31"); // Comando (0201h)
                conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
                conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
                conPuerto->WriteString("\x30\x30\x30\x35"); // Velocidad del motor (0005h to 0014h) -> 5h (5 Hz)
                conPuerto->WriteString("\x30\x30\x31\x30"); // Ángulo de paso -> 10h (1 grado)
                conPuerto->WriteString("\x33\x32\x39\x41"); // CRC (329A)
                conPuerto->WriteChar('\x03');


                }else if(frecuencia==10){

	        conPuerto->WriteChar('\x02');
                conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
                conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
                conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
                conPuerto->WriteString("\x30\x32\x30\x31"); // Comando
                conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
                conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
                conPuerto->WriteString("\x30\x30\x30\x41"); // Velocidad del motor (0005h to 0014h) -> Ah (10 Hz)
                conPuerto->WriteString("\x30\x30\x31\x30"); // Ángulo de paso -> 10h (1 grado)
                conPuerto->WriteString("\x43\x33\x37\x35"); // CRC (C375)
                conPuerto->WriteChar('\x03');

                }

        }
Resume();

}

//---------------------------------------------------------------------------

void Laser::BotonConfi05GradoClick()
{

/* SET_CONFIG -> Se crea una configuración que se queda almacenada.
        Los valores configurables son:
                - ID de sensor.
		- Velocidad a la que gira el motor. Entre 5 y 20 Hz
		- Ángulo de paso. Diferencia entre dos pulsos de laser en 1/16
                        grados. Tiene que ser divisible entre 5760 y mayor que 1.
*/

if (amplitud==60){
        if (frecuencia==5){

	conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x32\x30\x31"); // Comando
        conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
        conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
        conPuerto->WriteString("\x30\x30\x30\x35"); // Velocidad del motor (0005h to 0014h) -> 5h (5 Hz)
        conPuerto->WriteString("\x30\x30\x30\x38"); // Ángulo de paso -> 8h (0.5 grado)
        conPuerto->WriteString("\x33\x32\x38\x32"); // CRC (3282)
        conPuerto->WriteChar('\x03');

        }else if(frecuencia==10){

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x32\x30\x31"); // Comando
        conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
        conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
        conPuerto->WriteString("\x30\x30\x30\x41"); // Velocidad del motor (0005h to 0014h) -> Ah (10 Hz)
        conPuerto->WriteString("\x30\x30\x30\x38"); // Ángulo de paso -> 8h (0.5 grado)
        conPuerto->WriteString("\x43\x33\x36\x44"); // CRC (C36D)
        conPuerto->WriteChar('\x03');

        }

}else if (amplitud==180){

        if (frecuencia==5){

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x32\x30\x31"); // Comando
        conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
        conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
        conPuerto->WriteString("\x30\x30\x30\x35"); // Velocidad del motor (0005h to 0014h) -> 5h (5 Hz)
        conPuerto->WriteString("\x30\x30\x30\x38"); // Ángulo de paso -> 8h (0.5 grado)
        conPuerto->WriteString("\x33\x32\x38\x32"); // CRC (3282)
        conPuerto->WriteChar('\x03');

        }else if(frecuencia==10){

                // NO SE CONTEMPLA

        }

}

Resume();
}

//---------------------------------------------------------------------------

void Laser::BotonConfi025GradoClick(){


/* SET_CONFIG -> Se crea una configuración que se queda almacenada.
        Los valores configurables son:
                - ID de sensor.
		- Velocidad a la que gira el motor. Entre 5 y 20 Hz
		- Ángulo de paso. Diferencia entre dos pulsos de laser en 1/16
                        grados. Tiene que ser divisible entre 5760 y mayor que 1.
*/

if (amplitud==60){
        if (frecuencia==5){

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x32\x30\x31"); // Comando
        conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
        conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
        conPuerto->WriteString("\x30\x30\x30\x35"); // Velocidad del motor (0005h to 0014h) -> 5h (5 Hz)
        conPuerto->WriteString("\x30\x30\x30\x34"); // Ángulo de paso -> 4h (0.25 grado)
        conPuerto->WriteString("\x33\x32\x38\x45"); // CRC (328E)
        conPuerto->WriteChar('\x03');

        }else if(frecuencia==10){

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x32\x30\x31"); // Comando
        conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
        conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
        conPuerto->WriteString("\x30\x30\x30\x41"); // Velocidad del motor (0005h to 0014h) -> Ah (10 Hz)
        conPuerto->WriteString("\x30\x30\x30\x34"); // Ángulo de paso -> 4h (0.25 grado)
        conPuerto->WriteString("\x43\x33\x36\x31"); // CRC (C361)
        conPuerto->WriteChar('\x03');

       }

}else if (amplitud==180){

        // No es compatible a 180º
        }

Resume();
}

//---------------------------------------------------------------------------

void Laser::BotonConfi0125GradoClick()
{


/* SET_CONFIG -> Se crea una configuración que se queda almacenada.
        Los valores configurables son:
                - ID de sensor.
		- Velocidad a la que gira el motor. Entre 5 y 20 Hz
		- Ángulo de paso. Diferencia entre dos pulsos de laser en 1/16
                        grados. Tiene que ser divisible entre 5760 y mayor que 1.
*/

if (amplitud==60){
        if (frecuencia==5){

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x31\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x32\x30\x31"); // Comando
        conPuerto->WriteString("\x30\x30\x31\x30"); // Comando de Configuración global
        conPuerto->WriteString("\x30\x30\x31\x30"); // ID del sensor (0000h to 00FEh) -> 10h
        conPuerto->WriteString("\x30\x30\x30\x35"); // Velocidad del motor (0005h to 0014h) -> 5h
        conPuerto->WriteString("\x30\x30\x30\x32"); // Ángulo de paso -> 2h (0.125 grado)
        conPuerto->WriteString("\x33\x32\x38\x38"); // CRC (3288)
        conPuerto->WriteChar('\x03');

        }else if(frecuencia==10){
		//NO SE CONTEMPLA
        }

}else if (amplitud==180){

        // No es compatible a 60º
}
Resume();
}


//---------------------------------------------------------------------------

void Laser::confi10HzClick()
{
frecuencia=10;
};

//---------------------------------------------------------------------------
void Laser::confi5HzClick()
{
frecuencia=5;
};
//---------------------------------------------------------------------------


void  Laser::BotonLecturaClick(bool v_eco)
{
        /* Comando GET_PROFILE -> Hace uso de un perfil que ha sido
        previamente definido.

        En el caso de que el número de perfil sea 0, el laser envía
        perfiles continuamente, hasta que el usuario manda un mensaje
        de CANCEL_PROFILE.

        La respuesta contiene básicamente los datos solicitados en perfileFormat.
        Si el comando de solicitud no es válido, el comando es ignorado y
        exactamente una respuesta, que no contiene parámetros, se envía.
        No se envia perfiles. Si un punto de medida no es válido, la distancia
        pone a 0000h.
        */

        tipoDatos=true;
        fin=false;
        eco=v_eco;

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x30\x38"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x33\x30\x31"); // Comando 0301h
        conPuerto->WriteString("\x30\x30\x30\x30"); // Número de perfil -> 0
        conPuerto->WriteString("\x33\x39\x46\x46"); // Formato del perfil usado (39FF)
        conPuerto->WriteString("\x45\x38\x31\x41"); // CRC (E81A)  45 38 31 41
        conPuerto->WriteChar('\x03');

        //lectorDatos = new LectorDatos(conPuerto, "sesion.log", eco);

        //lectorDatos->leerDatos(eco);
        

        Resume();

}



//---------------------------------------------------------------------------


void  Laser::BotonLecturaConECOClick(bool v_eco){

        /* Comando GET_PROFILE -> Hace uso de un perfil que ha sido
        previamente definido.

        En el caso de que el número de perfil sea 0, el laser envía
        perfiles continuamente, hasta que el usuario manda un mensaje
        de CANCEL_PROFILE.

        La respuesta contiene básicamente los datos solicitados en perfileFormat.
        Si el comando de solicitud no es válido, el comando es ignorado y
        exactamente una respuesta, que no contiene parámetros, se envía.
        No se envia perfiles. Si un punto de medida no es válido, la distancia
        pone a 0000h.
        */

        tipoDatos=true;
        fin=false;
        eco=v_eco;

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x30\x38"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x33\x30\x31"); // Comando 0301h
        conPuerto->WriteString("\x30\x30\x30\x30"); // Número de perfil -> 0
        conPuerto->WriteString("\x33\x44\x46\x46"); // Formato del perfil usado (3DFF)
        conPuerto->WriteString("\x45\x43\x31\x41"); // CRC (EC1A)  45 43 31 41
        conPuerto->WriteChar('\x03');

        //lectorDatos = new LectorDatos(conPuerto, "sesion.log", eco);

        //lectorDatos->leerDatos(eco);

        Resume();

}

//---------------------------------------------------------------------------

void  Laser::BotonPararLecturaClick()
{
        /* Comando CANCEL_PROFILE -> El perfil que se está usando queda
        cancelado una vez que haya finalizado. Nunca se cancelará mientras
        se esté ejecutando alguna función.
        */

        tipoDatos=false;
        //fin=true;
        lectorDatos->terminarLectura();

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x30\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x33\x30\x32"); // Comando 0302h
        conPuerto->WriteString("\x32\x41\x34\x33"); // CRC (2A43)
        conPuerto->WriteChar('\x03');

        //Resume();

}


//---------------------------------------------------------------------------


void __fastcall Laser::Execute()
{

        while (!(fin)){

        if (tipoDatos){
                lectorDatos->leerDatos(eco);
                //tipoDatos=false;
        }
        else{
                Cadena = conPuerto->ReadTrama();
                NuevaCadena = true;
                //Suspend();
             }
        }
      /*  lectorDatos->terminarLectura();

        conPuerto->WriteChar('\x02');
        conPuerto->WriteString("\x31\x34\x31\x30"); // Identificadores
        conPuerto->WriteString("\x30\x30\x30\x30"); // Longitud
        conPuerto->WriteString("\x30\x30\x30\x30"); // Cabecera
        conPuerto->WriteString("\x30\x33\x30\x32"); // Comando 0302h
        conPuerto->WriteString("\x32\x41\x34\x33"); // CRC (2A43)
        conPuerto->WriteChar('\x03');   */
}
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
//---------------------------------------------------------------------------

TDatosPintar * Laser::GetDatosPintar( )
{

return (lectorDatos->DatosPintar);



}

void Laser::SetTiempo(AnsiString T)
{
 lectorDatos->SetTiempo(T);
}


 
#pragma package(smart_init)
 