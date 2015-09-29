//---------------------------------------------------------------------------
/*

Cabecera Pintar.h

Clase con los métodos necesarios para calcular la posición
en la que hay que dibujar cada punto en el eje de coordenadas.

*/
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

#ifndef PintarH
#define PintarH


//---------------------------------------------------------------------------
class Pintar
{
private:

	double angulo, pi;

        // Transforma la posición del punto en el eje X.
	double calcularPosicionX(double d, double s);

        // Transforma la posición del punto en el eje Y.
	double calcularPosicionY(double d, double c);

        // Redimensiona el punto en el eje X.
	double escalarPosicionX(double posX);

        // Redimensiona el punto en el eje Y.
	double escalarPosicionY(double posY);

        // Calcula la distancia para el eje X.
	double calcularSeno(double a);

        // Calcula la distancia para el eje Y.
	double calcularCoseno(double a); 

        // Convierte el ángulo en radianes.
	double convertirAngulo(double a);



protected:

public:

        // Constructor de la clase.
        Pintar();

        // Método que hace las operaciones necesarias para el eje X
	double calcularPosX(double d, double a);

        // Método que hace las operaciones necesarias para el eje Y.
        double calcularPosY(double d, double a);
	


};
//---------------------------------------------------------------------------
#endif