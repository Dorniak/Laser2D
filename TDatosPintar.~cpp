//---------------------------------------------------------------------------


#pragma hdrstop

#include "TDatosPintar.h"

//---------------------------------------------------------------------------
TDatosPintar::TDatosPintar()
{
P = new Pintar();


}

//---------------------------------------------------------------------------
void TDatosPintar::resetearArray(){
  int i, j;
  for(i=0;i<3;i++)
        for(j=0;j<750;j++)
                datosPintar[i][j]=0;
}


//---------------------------------------------------------------------------
void TDatosPintar::convertirDatos(){
int i,j;
double x,y;

//for (i=0;i<2;i++)
        for(j=0;j<750;j++){
                x = P->calcularPosX(datosPintar[1][j], datosPintar[2][j]);
                coordenadas[0][j]= x;
                y = P->calcularPosY(datosPintar[1][j], datosPintar[2][j]);
                coordenadas[1][j]= y;
        }
}

//---------------------------------------------------------------------------
/*
double * double* TDatosPintar::getCoordenadas(){
        return coordenadas;
}
*/

//---------------------------------------------------------------------------
#pragma package(smart_init)
