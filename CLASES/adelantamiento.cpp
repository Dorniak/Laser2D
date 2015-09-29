#include <math.h>
#include "CLASES/adelantamiento.h"
using namespace std;

Adelantamiento::Adelantamiento(double ang,double vel)
{
    angulo_adelantado = ang;
    vel_adelantado = vel;
    angulo_volante=0;
    s1=s2=0;
    t_adelatamiento=0;
    t_cambiocarril1=0;
    t_cambiocarril2=0;
    t_recta = 0 ;
    tiempo = 0;

}
Adelantamiento::Adelantamiento()
{

}

double Adelantamiento::intentar_adelantar(double vcoche,std::vector <Obstaculo*> obstaculos)
{
    double s2 = vcoche/2; //distancia de seguriadrad para empezar

    angulo_volante = (sqrt(9+(s2*s2)))/3;//angulo de giro
    angulo_volante=angulo_volante*17.5;

    for(int i=0; (unsigned)i<obstaculos.size(); i++)
    {
        if (obstaculos[i]->getAngulo() > angulo_adelantado && obstaculos[i]->getAngulo() < angulo_adelantado+angulo_volante)
            if (obstaculos[i]->getMargen() < 2*s2+4)
                return -1;// no se puede
    }
    //double s1 = vel_adelantado/7.2;
  //  double sh = (s1+s2+8+(angulo_volante*3));
   // double t_adelatamiento = (3.6*sh)/(vcoche-vel_adelantado);
  //  if (t_adelatamiento > 15)
        //return -1;//no aceptable

    //t_cambiocarril1 = (sqrt(9+pow(s2,2))/vcoche)+0.2;
    //t_cambiocarril2 = (sqrt(9+pow(s1,2))/vcoche)+0.2;
   // t_recta = t_adelatamiento - t_cambiocarril1 - t_cambiocarril2;
    return angulo_volante;
}
/*double Adelantamiento::adelantar()
{
    tiempo += 0.2;
    if (tiempo < t_cambiocarril1)
        return -angulo_volante;
    else if (tiempo < t_recta+t_cambiocarril1)
        return 0.0;
    else if (tiempo < t_recta+t_cambiocarril1+t_cambiocarril2)
        return angulo_volante;
    else return 999;
}   */






