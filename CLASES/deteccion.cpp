#include "CLASES/deteccion.h"
#include <math.h>
#include <cmath>
#define PI 3.14159265
#define FACTOR_SEGURIDAD 10
using namespace std;


Deteccion::Deteccion()
{
    adelantamiento; 
    vuelta = 1;
    vel = 10;
    frenada = false;
    frenada_ant = false;
    frenada_antt = false;
    adelantando = false;
    acelerar=true;
    filasNuevas=0;
    filasViejas=0;
    angulo=0;
    tiempox=0;


}

double Deteccion::getData(int barrido,float modulo,float angulo, float tiempo,double VCOCHE,double * dir)
{
    double  result = 999;
    if (barrido == vuelta)
    {
        if(modulo > 2 && modulo < 60)
        {
            t1 = tiempo;
            puntos.push_back(new Punto(modulo,angulo));
        }
        else
        {
            descartados++;
        }
    }
    else
    {
        periodo = (tiempo - t1)/1000;
        vuelta = barrido;
        if (puntos.size() > 5){
            result = tratamiento(barrido,puntos,descartados,periodo,VCOCHE,dir);
            puntos.clear();
        }
        else {
            puntos.clear();
            return 999;
           }
    }
    return result;
}
double Deteccion::tratamiento(int barrido,std::vector <Punto*> puntos, int descartados,float periodo,double VCOCHE,double * dir)
{
    int i,indice, adelantado=-1;
    float minimo;
    vector <Obstaculo*> obstaculos;
    resolucionAngular = puntos[3]->getAngulo() - puntos[2]->getAngulo();
    abertura = (puntos.size() + descartados) * resolucionAngular;
    vel = VCOCHE;
    if (VCOCHE <1.0) VCOCHE=0;

    //printf("\n%d\n",barrido);
    if (VCOCHE > 10 && VCOCHE < 20)
    if (comprobarBloqueo(puntos))
        {
            return 0;
        }

    obtenerObstaculos(obstaculos);

    if( obstaculos.size() > 0)   //if (VCOCHE > 14  ){
    {
        for (i=0; (unsigned)i < obstaculos.size(); i++)
        {
            obstaculos[i]->prepararObstaculo();
            matrix[i][0] = *obstaculos[i];//poner obstaculo en la columna de nuevos(0)
        }
        filasNuevas = obstaculos.size();

        if (barrido > 2)
        {
            for (i=0; i < filasNuevas; i++)
            {
                minimo = 2;
                indice = -1;

                for (int j=0; j< filasViejas; j++)
                {
                    if (matrix[j][1].getVelocidad() >= 1)
                    {
                        if(fabs(matrix[i][0].getCentro()->distanciaPunto(matrix[j][1].getCentropred())) < (VCOCHE/3.6)*0.3)
                        {
                            relacionarVel(i,j,VCOCHE,resolucionAngular);
                            indice = j;
                        }
                    }
                    else if(matrix[i][0].getCentro()->distanciaPunto(matrix[j][1].getCentro()) < minimo && fabs(matrix[i][0].getYaw() - matrix[j][1].getYaw()) < 5)
                    {
                        relacionarPos(i,j,VCOCHE,resolucionAngular);
                        indice = j;
                    }
                }

                if (!frenada && (matrix[i][0].getTTC() != -1) )
                {
                    if(matrix[i][0].getTTC() < FACTOR_SEGURIDAD )
                    {
                        frenada = true;
                    }
                    else if( VCOCHE > matrix[i][0].getVelocidad() && matrix[i][0].getTTC() < (2*FACTOR_SEGURIDAD) && matrix[indice][1].getdir()->gety() > 0)
                    {
                        vel = matrix[i][0].getVelocidad();
                        adelantado = i;
                    }
                }
            }
        }

        if((frenada && frenada_ant))
        {
            acelerar=!frenada_ant;
            frenada_ant=frenada;
            frenada = false;
            filasViejas = filasNuevas;
            borrarMatriz();
            obstaculos.clear();
            return 0;
        }
             /////////////////// �
          if (!adelantando && adelantado > -1)
               {
                   adelantamiento = new Adelantamiento(matrix[adelantado][0].getAngulo(),matrix[adelantado][0].getVelocidad());
                   angulo = adelantamiento->intentar_adelantar(VCOCHE,obstaculos) ;
                   if (angulo != -1)
                   {
                       adelantando=true;
                       *dir = angulo;
                       tiempox=0;
                   }
                   else delete adelantamiento;
               }
          else
              {
              if (tiempox < 2) {
                  *dir = -60;//-60-angulo;//adelantamiento->intentar_adelantar(VCOCHE,obstaculos) ;
                   vel = vel*1.5;
                  tiempox += 0.2;
              } else if (tiempox < 4) {
                     *dir=60;
                      tiempox += 0.2;
              }
              else if (tiempox < 7)
                {
                        *dir =0;
                        tiempox += 0.2;
                }
              else if(tiempox < 9){
                     vel=vel*0.75;
                     *dir = 60;
                     tiempox += 0.2;
              }
              else if (tiempox < 11){
                     *dir=-60;
                    tiempox +=0.2;
              }
              else {
              *dir=0;
                     delete adelantamiento;
                     adelantando=false;
              }
         }


             ////////////////////////////////////

        filasViejas = filasNuevas;
        borrarMatriz();
        obstaculos.clear();
        floor( vel + 0.5);
        if (vel>45)
        {
            vel=45;
        }
            acelerar=true;
            return vel;
       }

    obstaculos.clear();
    return vel;
}
bool Deteccion::puntosCercanos(Punto *p1, Punto *p2)
{
    float s0 = 1.4;
    float s1 = sqrt(2-(2*cos(2*resolucionAngular*PI/180)));
    float r = p1->getModulo();
    if (p1->getModulo() > p2->getModulo())
        r = p2->getModulo();
    float tolererancia = s0 + (s1 * r);

    return (tolererancia > p1->distanciaPunto(p2));
}
void Deteccion::relacionarVel(int i,int j,double VCOCHE,float resolucionAngular)
{
    matrix[i][0].setDireccion(matrix[j][1].getCentro(),matrix[i][0].getCentro());
    matrix[i][0].calcCentropred();
    matrix[i][0].setVelocidad(resolucionAngular);
    matrix[i][0].calTTC(VCOCHE, matrix[j][1].getTTC());
}
void Deteccion::relacionarPos(int i,int j,double VCOCHE,float resolucionAngular)
{

    matrix[i][0].setDireccion(matrix[j][1].getCentro(),matrix[i][0].getCentro());
    matrix[i][0].calcCentropred();
    matrix[i][0].setVelocidad(resolucionAngular);

}
void Deteccion::borrarMatriz()
{
    for(int m=0; m<filasNuevas; m++)
    {
        matrix[m][1] = matrix[m][0];

    }
}
void Deteccion::obtenerObstaculos(std::vector <Obstaculo*> & obstaculos)
{
    int i=0;

    while ((unsigned) i < (puntos.size()-2))
    {
        if(puntosCercanos(puntos[i], puntos[i+1]))
        {
            obstaculos.push_back(new Obstaculo());
            obstaculos[obstaculos.size()-1]->componentes.push_back(*puntos[i]);
            obstaculos[obstaculos.size()-1]->componentes.push_back(*puntos[i+1]);
            i++;

            while (puntosCercanos(puntos[i],puntos[i+1]) && ((unsigned)i < (puntos.size()-2)))
            {
                obstaculos[obstaculos.size()-1]->componentes.push_back(*puntos[i+1]);
                i++;
            }
            if ((obstaculos[obstaculos.size()-1]->componentes.size() < 5) || (obstaculos[obstaculos.size()-1]->errorMedio() > 0.595) )
                obstaculos.pop_back();
        }
        i++;
    }
}
bool Deteccion::comprobarBloqueo(std::vector <Punto*> & puntos)
{
    int k;
    for(k=0; (unsigned) k<puntos.size(); k++)
    {
        if(puntos[k]->getAngulo()>=170 && puntos[k]->getAngulo()<=190 && puntos[k]->getModulo() < 15 )
        //if(puntos[k]->getAngulo()>=170.6 && puntos[k]->getAngulo()<=189.4 && puntos[k]->getModulo() < 6 )
        return true;
    }
    return false;
}
