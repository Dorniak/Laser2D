//---------------------------------------------------------------------------

#ifndef ThreadPintarH
#define ThreadPintarH


class ThreadPintar : public TThread
{


private:	// User declarations
        Puertos *conPuerto; //Puntero a la clase Puertos
        TMemo * Display;
        char *Cadena;
        bool fin, NuevaCadena;
        int amplitud;
        int frecuencia;
        LectorDatos *lectorDatos;
        bool tipoDatos;
        bool eco;
        //lectordatos

protected:
        void __fastcall Execute();

public:		// User declarations

        __fastcall ThreadPintar();

};



//---------------------------------------------------------------------------
#endif
 