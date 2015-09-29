//---------------------------------------------------------------------------
/*

Cabecera Laser.h

Clase con los métodos necesarios para establacer comunicación con
el láser y poder enviar mensajes para realizar todas las acciones
necesarias para su funcionamiento.

*/
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef LaserH
#define LaserH

#include "Puertos.h"
#include "LectorDatos.h"
#include "TDatosPintar.h"
#include <vcl.h>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------


class Laser : public TThread
{


private:	// User declarations
        Puertos *conPuerto; //Puntero a la clase Puertos
        TMemo * Display;
        char *Cadena;
        bool fin, NuevaCadena;
        int amplitud;
        int frecuencia;
        //LectorDatos *lectorDatos;
        bool tipoDatos;
        bool eco;

        //lectordatos

protected:
        void __fastcall Execute();

public:		// User declarations

        // Constructor de la clase Láser
        __fastcall Laser(TMemo * D, Puertos * Puerto);

        // Método para enviar al láser los comandos para Rotar.
        void BotonRotarClick();

        // Método para enviar al láser los comandos para pararlo.
        void BotonHaltClick();

        // Método que envía los mensajes para iniciar el láser.
        void BotonInicializarClick(int numP, int vel);

        // Método para señalar al láser el sector de medida frontal.
        void BotonConfi60GradosClick();

        // Método para señalar al láser el sector de medida delantero.
        void BotonConfi180GradosClick();

        // Métodos para configurar el paso de medida.
        void BotonConfi1GradoClick();
        void BotonConfi05GradoClick();
        void BotonConfi025GradoClick();
        void BotonConfi0125GradoClick();

        // Métodos para configurar la velocidad de giro del motor del láser.
        void confi10HzClick();
        void confi5HzClick();

        // Métodos de inicio de lectura.
        void BotonLecturaClick(bool v_eco);
        void BotonLecturaConECOClick(bool v_eco);

        // Método de final de lectura.
        void BotonPararLecturaClick();

        // Método que lee una cadena de datos.
        char * LeerCadena();

        // Método que finaliza el thread.
        void AcabarThread();

        // Devuelve la matriz de datos para pintar en la clase principal.
        TDatosPintar *GetDatosPintar();
        void SetTiempo(AnsiString T);
         void setdir(double d);
         void setvel(double v);
        
        LectorDatos *lectorDatos;
};



//---------------------------------------------------------------------------
#endif
