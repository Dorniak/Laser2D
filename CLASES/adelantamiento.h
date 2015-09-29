#include <vector>
#include "CLASES/obstaculo.h"

class Adelantamiento
{
private:
    double  angulo_adelantado;
    double vel_adelantado;
    double angulo_volante;
    double s1;
    double s2;
    double t_adelatamiento;
    double t_cambiocarril1;
    double t_cambiocarril2;
    double t_recta;
    double tiempo;

public:
    Adelantamiento(double ang,double vel);
    Adelantamiento();
    double intentar_adelantar(double vcoche,std::vector <Obstaculo*> obstaculos);
  //  double adelantar();


};


