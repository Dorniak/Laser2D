

#include "CLASES/punto.h"
#include <vector>
#ifndef mObstaculo
#define mObstaculo
class Obstaculo
{
private:
    float margen;
    float angulo;
    float velocidad;
    float yaw;
    float TTC;
    Punto* centro;
    Punto* dir;
    Punto* centroPred;

public:
    Obstaculo();
    float getMargen();
    float getAngulo();
    float getYaw();
    Punto* getdir();
    float getVelocidad();
    Punto* getCentro();
    Punto* getCentropred();
    float getTTC();

    void setAngulo();
    void setMargen();
    void setDireccion(Punto *p1,Punto *p2);
    void setVelocidad(float resolucion);

    void calcCentro();
    void calcCentropred();
    void calTTC(float v,float antiguo);
    void calcEjes();

    void  prepararObstaculo();
    float errorMedio();
    std::vector <Punto> componentes;


};
#endif
