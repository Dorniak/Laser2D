#ifndef mDeteccion
#define mDeteccion

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "CLASES/obstaculo.h"
#include "adelantamiento.h"

class Deteccion
{
private:
    int vuelta;
    int descartados;
    float t1;
    float resolucionAngular;
    float abertura;
    double vel;
    double angulo;
    bool frenada;
    bool frenada_ant;
    bool frenada_antt;
    bool acelerar;
    int filasViejas,filasNuevas;
    float periodo;
    Obstaculo matrix[100][2];
    double tiempox;

public:
    Deteccion();
    Adelantamiento * adelantamiento;
    bool adelantando;
    bool puntosCercanos(Punto *p1, Punto *p2);
    std::vector <Punto*> puntos;
    double tratamiento(int barrido,std::vector <Punto*> puntos, int descartados,float periodo,double VCOCHE,double * dir);
    double getData(int barrido,float modulo,float angulo, float tiempo,double VCOCHE,double * dir);
    void relacionarVel(int i,int j,double VCOCHE,float resolucionAngular);
    void relacionarPos(int i,int j,double VCOCHE,float resolucionAngular);
    void borrarMatriz();
    void obtenerObstaculos(std::vector <Obstaculo*> & obstaculos);
    bool comprobarBloqueo(std::vector <Punto*> & puntos);


};
#endif
