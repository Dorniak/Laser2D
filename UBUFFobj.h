/******************************************************************************/
/* Implementaci�n del TAD cola */
/******************************************************************************/


#ifndef _UBUFF
#define _UBUFF


#include <vcl\vcl.h>


#define TAM_BUFF 1024


typedef struct str_buff {
			  int pri; /* Primero de los elementos del buffer */
			  int ult; /* Ultimo de los elementos del buffer */
			  UCHAR buff [TAM_BUFF]; /* Buffer de la UART */
						} t_buff;

   /* El buffer se implementa sobre un array tratado de forma circular. */



extern void iniciar_buff (t_buff *);
   /* Inicializa el buffer de la UART en el que se almacenan los bytes recibidos
      Par 1: Buffer a inicializar */


extern int buff_vacio (t_buff);
   /* Devuelve !=0 si el buffer est� vac�o y 0 en caso contrario
       Par 1: Buffer a comprobar*/


extern int buff_lleno (t_buff);
   /* Devuelve !=0 si el buffer est� lleno y 0 en caso contrario
      Par 1: Buffer a comprobar */


extern UCHAR sacar_ele (t_buff *);
   /* Extrae y devuelve el primer elemento de la cola. No comprueba que est�
	  vac�a
      Par 1: Buffer del que se va a extraer el primer elemento */


extern void meter_ele (t_buff *, UCHAR);
   /* Introduce un nuevo elemento en la cola. No comprueba que est� llena
      Par 1: Buffer en el que se va a meter el nuevo elemento
      Par 2: Elemento a introducir en el buffer */


extern int num_elems (t_buff);
   /* Devuelve el n�mero de elementos que contiene el buffer
      Par 1: Buffer del que se quiere saber el n�mero de elementos */


extern void sacar_ult (t_buff *);
   /* Quita del buffer el �ltimo elemento que se introdujo
      Si el buffer est� vac�o la funci�n no hace nada
      Par 1: Buffer del que se va a sacar el �ltimo elemento */


#endif      