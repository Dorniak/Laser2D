#include "deteccion.h"
#include <math.h>
#define PI 3.14159265
#define FACTOR_SEGURIDAD 10
using namespace std;


Deteccion::Deteccion()
{
    // adelantamiento = new Adelantamiento();
    vuelta = 1;
    vel = 999;
    frenada = false;
    frenada_ant = false;
    adelantando = false;
    acelerar=true;
    filasNuevas=0;
    filasViejas=0;

}

float Deteccion::getData(int barrido,float modulo,float angulo, float tiempo,float VCOCHE)
{
    float  result = 999;
    if (barrido == vuelta)
    {
        if(modulo > 0 && modulo < 100)
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
        if (puntos.size() > 5)
            result = tratamiento(barrido,puntos,descartados,periodo,VCOCHE);
        else
            return 999;
        puntos.clear();
    }

    return result;
}
float Deteccion::tratamiento(int barrido,std::vector <Punto*> puntos, int descartados,float periodo,float VCOCHE)
{
    int i,indice, adelantado;
    float minimo;
    vector <Obstaculo*> obstaculos;

    resolucionAngular = puntos[3]->getAngulo() - puntos[2]->getAngulo();
    abertura = (puntos.size() + descartados) * resolucionAngular;
    if (VCOCHE <1.0) VCOCHE=0;
    vel = VCOCHE;

    printf("%d\n",barrido);

    obtenerObstaculos(obstaculos);

    if( obstaculos.size() > 0)
    {
        for (i=0; (unsigned)i < obstaculos.size(); i++)
        {
            obstaculos[i]->prepararObstaculo();
            matrix[i][0] = *obstaculos[i];//poner obstaculo en la columna de nuevos(0)
        }
        filasNuevas = obstaculos.size();

        if (comprobarBloqueo(obstaculos))
        {
            frenada_ant=frenada;
            frenada = true;
            acelerar = false;
            filasViejas = filasNuevas;
            borrarMatriz();
            obstaculos.clear();
            return 0.0;
        }

        if (barrido > 2  && !frenada)
        {
            for (i=0; i < filasNuevas; i++)
            {
                minimo = 2;
                indice = -1;

                for (int j=0; j< filasViejas; j++)
                {
                    if (matrix[j][1].getVelocidad() >= 1)
                    {
                        if(fabs(matrix[i][0].getCentro()->distanciaPunto(matrix[j][1].getCentropred())) < 4)
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

        if(frenada || frenada_ant)
        {
            acelerar=false;
            frenada_ant=frenada;
            frenada = false;
            filasViejas = filasNuevas;
            borrarMatriz();
            obstaculos.clear();
            return 0.0;
        }
        /* if (vel != 999 && vel != 0)
         {
               if (!adelantando)
               {
                   adelantamiento = new Adelantamiento(matrix[adelantado][0].getAngulo(),matrix[adelantado][0].getVelocidad());
                   if (adelantamiento->intentar_adelantar(VCOCHE,obstaculos))
                       adelantando=true;
                    else delete adelantamiento;
               }
               else
               {
                   *dir = adelantamiento->adelantar();
                   if (*dir == 999 )
                   {
                       *dir = 0;
                       delete adelantamiento;
                       adelantado = 0;
                   }
                   else return 35   ;//VELOCIDAD MAXIMA
               }

               else{
             filasViejas = filasNuevas;
             borrarMatriz();
             obstaculos.clear();
            return vel;
            }
         }   */

        filasViejas = filasNuevas;
        borrarMatriz();
        obstaculos.clear();

        if (vel>45 && vel != 999)
        {
            vel=45;
        }

        if (acelerar)
            return vel;
        else
        {
            acelerar=true;
            return 0.0;
        }
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
void Deteccion::relacionarVel(int i,int j,float VCOCHE,float resolucionAngular)
{
    matrix[i][0].setDireccion(matrix[j][1].getCentro(),matrix[i][0].getCentro());
    matrix[i][0].calcCentropred();
    matrix[i][0].setVelocidad(resolucionAngular);
    matrix[i][0].calTTC(VCOCHE, matrix[j][1].getTTC());
}
void Deteccion::relacionarPos(int i,int j,float VCOCHE,float resolucionAngular)
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
        if(puntos[i]->getAngulo()==180 && puntos[i]->getModulo() < 5)
            frenada=true;
        if(puntosCercanos(puntos[i], puntos[i+1]))
        {
            obstaculos.push_back(new Obstaculo());
            obstaculos[obstaculos.size()-1]->componentes.push_back(*puntos[i]);
            obstaculos[obstaculos.size()-1]->componentes.push_back(*puntos[i+1]);
            i++;

            if(puntos[i]->getAngulo()==180 && puntos[i]->getModulo() < 5)
                frenada=true;

            while (puntosCercanos(puntos[i],puntos[i+1]) && ((unsigned)i < (puntos.size()-2)))
            {
                obstaculos[obstaculos.size()-1]->componentes.push_back(*puntos[i+1]);
                i++;
                if(puntos[i]->getAngulo()==180 && puntos[i]->getModulo() < 5)
                    frenada=true;
            }

            if ((obstaculos[obstaculos.size()-1]->componentes.size() < 5) || (obstaculos[obstaculos.size()-1]->errorMedio() > 0.595) )
                obstaculos.pop_back();
        }
        i++;
    }
}
bool Deteccion::comprobarBloqueo(std::vector <Obstaculo*> & obstaculos)
{
    for(int k=0; k<obstaculos.size(); k++)
    {
        if (obstaculos[k]->getCentro()->getx() > -1.5 && obstaculos[k]->getCentro()->getx() < 1.5)
        {
            if (obstaculos[k]->getMargen()<5)
            {
                return true;
            }
        }
    }
    return false;
}
