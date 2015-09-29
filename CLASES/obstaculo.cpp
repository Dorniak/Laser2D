#include "CLASES/obstaculo.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

using namespace std;
/**
    Constructor de la clase obstaculo.
    tamano: Numero de puntos que componen el array.
    margen: Distancia minima del laser al obstaculo.
    angulo: Angulo estimado al que se encuentra el obstaculo.
    inicio: Indice del punto inicial.
    fin: Indice del punto  final.
    centro: Punto central estimado del obstaculo.
*/
Obstaculo::Obstaculo()
{
    margen = 999;
    angulo = 0;
    velocidad = -1;
    TTC = -1;
}
/**
    Devuelve el margen del obstaculo al laser.

    @return margen El margen del obstaculo al laser.
*/
float Obstaculo::getMargen()
{
    return margen;
}
/**
    Devuelve el angulo entre el bstaculo y el  laser.

    @return angulo El angulo entre el bstaculo y el  laser.
*/
float Obstaculo::getAngulo()
{
    return  angulo;
}

float Obstaculo::getYaw()
{
    return yaw;
}
Punto* Obstaculo::getdir()
{
    return dir;
}
/**
    Devuelve la velocidad del bstaculo.

    @return velocidad La velocidad del obstaculo.
*/
float Obstaculo::getVelocidad()
{
    return velocidad;
}
Punto* Obstaculo::getCentro()
{
    return centro;
}
Punto* Obstaculo::getCentropred()
{
    return centroPred;
}
float Obstaculo::getTTC()
{
    return TTC;
}
/**
    Guarda el angulo estimado donde se encuentra el obstaculo.

    @param n El angulo estimado.
*/
void Obstaculo::setAngulo()
{
    angulo = (componentes[componentes.size()-1].getAngulo() + componentes[0].getAngulo()) /2 ;
}
/**
    Guarda el margen del obstaculo al laser.

    @param n El margen del obstaculo al laser.
*/
void Obstaculo::setMargen()
{
    float min=9999;
    for(int i=0; (unsigned)i< componentes.size(); i++)
    {
        if (componentes[i].getModulo() < min)
            min = componentes[i].getModulo();
    }
    margen = min;
}
void Obstaculo::setDireccion(Punto *p1,Punto *p2)
{
    float x = p2->getx()-p1->getx();
    float y = (p2->gety()-p1->gety());
    dir = new Punto(x,y,0);
}
/**
    Funcion que asigna una velocidad al obstaculo.
*/
void Obstaculo::setVelocidad(float resolucion)
{
    velocidad=((sqrt(pow(static_cast<double>(dir->getx()),2)+pow(static_cast<double>(dir->gety()),2)))/resolucion)*3.6;
    if (velocidad < 1)
        velocidad = 0;
}
/**
    Funcion que calcula el centro del obstaculo.
*/
void Obstaculo::calcCentro()
{
    float y21 = (componentes[componentes.size()-1].gety()+componentes[0].gety())/2;
    float x21 = (componentes[componentes.size()-1].getx()+componentes[0].getx())/2;
    centro = new Punto(x21,y21,angulo);
}
void Obstaculo::calcCentropred()
{
    float x = centro->getx()+(dir->getx());
    float y = centro->gety()+(dir->gety());
    centroPred = new Punto(x,y,angulo);
}
void Obstaculo::calTTC(float v, float antiguo)
{   float m ;
    float b;
     if(dir->getx()==0)
      m =  0;
     else
      m = dir->gety()/dir->getx();
    if(dir->getx()==0 || m==0) b = centro->gety();
    else
     b = centro->gety()/(m*centro->getx());
    Punto* corte = new Punto(0.0,b,90);

    if (b>0 && velocidad > 0 && v>0)
    {
        float tobstaculo = (centro->distanciaPunto(corte))/(velocidad/3.6);
        Punto* coche = new Punto(0,0,90);
        float tcoche = (coche->distanciaPunto(corte))/(v/3.6);
        if (fabs(tobstaculo-tcoche) > 10)
            TTC = -1;
        else
        {
            if (antiguo!=-1)
                TTC = (tobstaculo + antiguo)/2;
            else TTC = tobstaculo;
            if(TTC-antiguo<0.1)
                TTC=-1;
        }
    }
    else TTC = -1;
}
void Obstaculo::calcEjes()
{
    float y,x,m;
    for(int i=0; (unsigned)i<componentes.size(); i++)
    {
        if (componentes[i].getModulo()==margen)
        {
            y=fabs(componentes[i].gety()-componentes[0].gety());
            x=fabs(componentes[i].getx()-componentes[0].getx());
            if(x!=0)    {
            m=y/x;
            yaw = fabs(atan(m) * 57.295);
            break;   }
            else {yaw = 0;break;}
        }
    }
}
/**
    Funcion que calcula la recta de regresión de los puntos y obtiene el error medio.
    Con un error alto se descarta el obstaculo (Nube de puntos).

    @return error Error medio de todos los puntos.
*/
float Obstaculo::errorMedio()
{
    float y21 = componentes[componentes.size()-1].gety()-componentes[0].gety();
    float x21 = componentes[componentes.size()-1].getx()-componentes[0].getx();
    float pendiente = 0;
    if(x21 !=0) pendiente = y21/x21;
    float error = 0;
    float b = componentes[0].gety()-(pendiente*componentes[0].getx());
    for(int i = 0; (unsigned)i <= componentes.size()-1; i++)
    {
        int yEst = ((pendiente*componentes[i].getx())+b);
        error+=fabs(yEst-componentes[i].gety());
    }
    error /= componentes.size();
    return error;
}
void Obstaculo::prepararObstaculo()
{
    setMargen();
    setAngulo();
    calcCentro();
    calcEjes();
}
