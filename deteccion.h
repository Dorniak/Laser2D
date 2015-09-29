#ifndef mDeteccion
#define mDeteccion

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "obstaculo.h"
//#include "adelantamiento.h"

class Deteccion
{
private:
    int vuelta;
    int descartados;
    float t1;
    float resolucionAngular;
    float abertura;
    float vel;
    bool frenada;
    bool frenada_ant;
    bool acelerar;
    int filasViejas,filasNuevas;
    float periodo;
    Obstaculo matrix[100][2];

public:
    Deteccion();
//    Adelantamiento * adelantamiento;
    bool adelantando;
    bool puntosCercanos(Punto *p1, Punto *p2);
    std::vector <Punto*> puntos;
    float tratamiento(int barrido,std::vector <Punto*> puntos, int descartados,float periodo,float VCOCHE);
    float getData(int barrido,float modulo,float angulo, float tiempo,float VCOCHE);
    void relacionarVel(int i,int j,float VCOCHE,float resolucionAngular);
    void relacionarPos(int i,int j,float VCOCHE,float resolucionAngular);
    void borrarMatriz();
    void obtenerObstaculos(std::vector <Obstaculo*> & obstaculos);
    bool comprobarBloqueo(std::vector <Obstaculo*> & obstaculos);


};
#endif
