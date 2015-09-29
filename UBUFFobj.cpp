/******************************************************************************/
/* Implementación del TAD cola */
/******************************************************************************/


#include <conio.h>
#include "UBUFFobj.H"


void iniciar_buff (t_buff * p_buff)
{
 p_buff->pri=0;
 p_buff->ult=0;
} /* FIN de iniciar_buff */


int buff_vacio (t_buff buffer)
{
 /* VAR */
 int aux;
 /**/
 aux=(buffer.pri == buffer.ult);
 return(aux);
} /* FIN de buff_vacio */


int buff_lleno (t_buff buffer)
{
 /* VAR */
 int aux;
 /**/

 aux=((buffer.ult+1)%TAM_BUFF == buffer.pri);
 return(aux);
} /* FIN de buff_lleno */


UCHAR sacar_ele (t_buff * p_buff)
/* Debe ser modificado si se a¤ade el control de error a cada elemento del
	buffer */
{
 UCHAR ele;

 ele=p_buff->buff[p_buff->pri];
 p_buff->pri=(p_buff->pri+1)%TAM_BUFF;
 return(ele);
} /* FIN de sacar_ele */


void meter_ele (t_buff * p_buff, UCHAR ele)
{
 p_buff->buff[p_buff->ult]=ele;
 p_buff->ult=(p_buff->ult+1)%TAM_BUFF;
} /* FIN de meter_ele */


int num_elems (t_buff buffer)
{
 if (buffer.ult >= buffer.pri)
	return(buffer.ult-buffer.pri);
 else return(TAM_BUFF-buffer.pri+buffer.ult);
} /* FIN de num_elems */


void sacar_ult (t_buff * p_buff)
{
 if (!buff_vacio(*p_buff))
   if (p_buff->ult == 0)
     p_buff->ult=TAM_BUFF-1;
   else p_buff->ult-=1;
} /* FIN de sacar_ult */
