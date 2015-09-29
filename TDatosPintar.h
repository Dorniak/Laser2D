//---------------------------------------------------------------------------
/*

Cabecera TDatosPintar.h

Clase con los métodos necesarios para convertir las matrices de datos
necesarias para la representación de la información en el panel de la aplicación.

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

        // Método que inicializa la matriz datosPintar a 0.
        void resetearArray();

        // Matriz de datos que ya contiene los datos del eje X y eje Y para representar.
        double coordenadas[2][750];

        // Método que convierte los datos obtenidos por el láser en datos para representar.
        void convertirDatos();

        // Puntero de la clase Pintar.
        Pintar *P;

};


#endif
 