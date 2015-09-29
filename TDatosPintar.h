//---------------------------------------------------------------------------
/*

Cabecera TDatosPintar.h

Clase con los m�todos necesarios para convertir las matrices de datos
necesarias para la representaci�n de la informaci�n en el panel de la aplicaci�n.

*/
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef TDatosPintarH
#define TDatosPintarH

#include "Pintar.h"

//---------------------------------------------------------------------------
class TDatosPintar
{

private:

        

public:

        // Constructor de la clase.
        TDatosPintar();

        // Matriz de datos que se va actualizando en la clase LectorDatos.
        double datosPintar[3][750];

        // M�todo que inicializa la matriz datosPintar a 0.
        void resetearArray();

        // Matriz de datos que ya contiene los datos del eje X y eje Y para representar.
        double coordenadas[2][750];

        // M�todo que convierte los datos obtenidos por el l�ser en datos para representar.
        void convertirDatos();

        // Puntero de la clase Pintar.
        Pintar *P;

};


#endif
 