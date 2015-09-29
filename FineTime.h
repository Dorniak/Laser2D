//---------------------------------------------------------------------------
// Clase FineTime
// Con ella se consigue medir tiempos con gran resolucion
//---------------------------------------------------------------------------

#ifndef FineTimeH
#define FineTimeH

class FineTime
{
  private:
    double frecuencia;
  public:
    FineTime();

    // Devuelve la resolucion del reloj en segundos (unidad de tiempo minima)
    double GetResolution();

    // Devuelve el tiempo en segundos desde el arranque de la máquina
    double GetFineTime();
};

#endif