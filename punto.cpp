#pragma hdrstop

#include "punto.h"
#include <math.h>
#include <stdio.h>
#define PI 3.14159265
//#pragma once
using namespace std;
/**
    Constructor del tipo punto sin parametros.

*/
Punto::Punto()
{
    x=y=modulo=angulo=0;
}
/**
    Constructor del tipo punto con parametros.

    @param mod Modulo del punto.
    @param ang Angulo del punto.

*/

Punto::Punto(double mod, double ang)
{
    modulo = mod;
    angulo = ang;
    x = mod * sin(ang*PI/180);
    y = -mod * cos(ang*PI/180);
}
Punto::Punto(float x, float y, double ang)
{
    modulo = sqrt(pow(static_cast<double>(x),2)+pow(static_cast<double>(y),2));
    angulo = ang;
    this->x = x;
    this->y = y;
}
/**
   Devuelve el angulo del punto respecto al laser.

   @return angulo Angulo del punto.

*/
double Punto::getAngulo()
{
    return angulo;
}
/**
   Devuelve la distancia del punto respecto al laser.

   @return modulo Distancia del punto.

*/
double Punto::getModulo()
{
    return modulo;
}
/**
   Devuelve la coordenada X del punto.

   @return x Coordenada X del punto.

*/
double Punto::getx()
{
    return x;
}
/**
   Devuelve la coordenada Y del punto.

   @return x Coordenada Y del punto.

*/
double Punto::gety()
{
    return y;
}

/**
    Funcion que calcula la distancia entre dos puntos.

    @param *p2 Puntero del punto al que se va a calcular la distancia.
    @return sqrt Distancia del punto p1 al p2.
*/
float Punto::distanciaPunto(Punto *p2)
{
    //printf("mix: %f, miy: %f\nsux: %f, suy: %f\n\n",this->getx(),this->gety(),p2->getx(),p2->gety());
    return sqrt(pow (static_cast<double>(p2->getx() - this->getx()), 2.0) + pow (static_cast<double>(p2->gety() - this->gety()), 2.0));
}
void Punto::visualizar()
{
    printf("Modulo: %f\t angulo: %f\n", modulo,angulo);

}
