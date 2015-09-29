//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Pintar.h"
#include "math.h"

//---------------------------------------------------------------------------
Pintar::Pintar()
 
{


  angulo = 0.0;
  pi = 3.141592653589;

   
}


//---------------------------------------------------------------------------

double Pintar::calcularSeno(double a)
{
double x;

x = sin(a);

return x;

}


//---------------------------------------------------------------------------

double Pintar::calcularCoseno(double a)
{

double x;

x = cos(a);

return x;
}

//---------------------------------------------------------------------------

double Pintar::convertirAngulo(double a)
{
        
        if (a!=0.0)
                angulo=a-180.0;
        else if (a==180.0)
                angulo=0.0;



        /*
	if (a>180.0)
		angulo = (a-180.0);
	else if (a<180.0)
		angulo = (180.0-a);
	else if (a==180.0)
		angulo = 0.0;
        */

        a-=90.0;

        angulo=((a*pi)/180.0);

        return angulo;
}
//---------------------------------------------------------------------------

double Pintar::calcularPosicionX(double d, double s)
{
if (s==0.0)
        return 0.0;
else
	return (d*s);
}
//---------------------------------------------------------------------------

double Pintar::calcularPosicionY(double d, double c)
{
if (c==0.0)
        return d;
else
	return (d*c);
}
//---------------------------------------------------------------------------

double Pintar::escalarPosicionX(double posX)
{
        return (/*200.0-*/(posX*6.0));
	//return (150-(posX*150.0/100.0));
}
//---------------------------------------------------------------------------

double Pintar::escalarPosicionY(double posY)
{
        return (/*250.0-*/(posY*9.0));
	//return (250-(posY*250.0/50.0));
}
//---------------------------------------------------------------------------
/*
void Pintar::pintarBola(int numGiro, double d, double a)
{

angulo = convertirAngulo(a);
seno = calcularSeno(angulo);
coseno = calcularCoseno(angulo);
posicionX= calcularPosicionX(d, seno);
posicionY= calcularPosicionY(d, coseno);
posicionXpanel= escalarPosicionX(posicionX);
posicionYpanel= escalarPosicionY(posicionY);

}

*/

//---------------------------------------------------------------------------
double Pintar::calcularPosY(double d, double a)
{
double ang, c, posY,result;

ang = convertirAngulo(a);
c= calcularCoseno(ang);

posY=calcularPosicionY(d, c);

result = escalarPosicionY(posY);
return (result);
}


//---------------------------------------------------------------------------

double Pintar::calcularPosX(double d, double a)
{
double ang, s, posX, result;

ang = convertirAngulo(a);

s= calcularSeno(ang);
posX=calcularPosicionX(d, s);

result = escalarPosicionX(posX);
return (result);

}
//---------------------------------------------------------------------------
