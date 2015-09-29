//#pragma once
#ifndef mPunto
#define mPunto
class Punto
{
private:
    double modulo,angulo;
    float x,y;
public:
    Punto();
    Punto(double mod, double ang);
    Punto(float x, float y, double ang);

    double getAngulo();
    double getModulo();
    double getx();
    double gety();
    void visualizar();
    float distanciaPunto(Punto *p2);
};
#endif


