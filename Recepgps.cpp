/******************************************************************************/
/* Funciones de comunicación con el receptor GPS */
/******************************************************************************/
/* Se van a implementar aspectos relacionados con la comunicación con el
	receptor GPS Z-12 de Ashtec */


#include <stdlib.h>
#include <time.h>
#include "UART.H"
#include "RS232C.H"
#include "ERRORES.H"
#include "RECEPGPS.H"
#include <vcl.h>

/* Funciones locales */

void reenviar_comando (UCHAR * buff, int tam, HANDLE hcom)
   /* Envía un comando por el puerto serie al receptor GPS
      Par 1: Comando a enviar
      Par 2: Tamaño del comando
      Par 3: Descriptor del puerto por el que se envía */
{
 int ind=0;

 do
	{
	 if (b_WriteRS232C(hcom,buff[ind++]) == ERR_WB_RS)
	   break;
	}
 while (ind < tam);
} /* FIN de reenviar_comando */


/* Funciones exportables */

int recibir_ack (t_uart_obj uart)
{
 UCHAR ele_rec;

 if (b_ReadRS232C(uart.hcom,&ele_rec) == ERR_RB_RS)
   return(ERR_T_REC_ACK);
 if (ele_rec == ACK)
   return(NO_ERR);
 return(ERR_ACK);
} /* FIN de recibir_ack */

int str_a_buff (char * com_str, t_uart_obj * p_uart)
{
 unsigned int i;

 for (i=0; i < strlen(com_str); i++) /* No se copia \0 */
	 {
	  if (!buff_lleno(p_uart->u_buff_emi))
		 meter_ele(&p_uart->u_buff_emi,(UCHAR) com_str[i]);
	  else return(ERR_B_EMI_LLENO);
	 }
 return(NO_ERR);
} /* FIN de str_a_buff */


void buff_a_str (t_uart_obj * p_uart, char * respuesta)
{
 int i=0;

 while (!buff_vacio(p_uart->u_buff_rec))
	 respuesta[i++]=(char) sacar_ele(&p_uart->u_buff_rec);
 respuesta[i]='\0';
} /* FIN de buff_a_str */


int es_setcommand (t_buff buff_c)
{
 return(buff_c.buff[(buff_c.pri+strlen(COMM_S)-1)%TAM_BUFF] == 'S');
} /* FIN de es_setcommand */


int recibir_datos (t_uart_obj * p_uart)
{
 UCHAR ele_rec; /* Almacena el byte recibido */
 int rec_CR=0; /* Almacena si el byte que se acaba de recibir es CR */
 int rec_LF=0; /* Almacena si el byte que se acaba de recibir es LF */

 do
   {
	if (b_ReadRS232C(p_uart->hcom,&ele_rec) == ERR_RB_RS)
	  return(ERR_T_REC_DAT);

	   if (((char) ele_rec) == CR) /* Se comprueba la recepción de CR*/
		 rec_CR=1;
	   else if (((char) ele_rec) == LF) /* Se comprueba la recepción de LF*/
			  if (rec_CR)
				rec_LF=1;
			  else rec_LF=0;
			else {
				  rec_CR=0;
				  rec_LF=0;
				 }
	   if (!buff_lleno(p_uart->u_buff_rec))
		 meter_ele(&p_uart->u_buff_rec,ele_rec);    /*
	   else return(ERR_B_REC_LLENO);
	 */
   }
 while (!rec_LF);
 /* Se quitan del buffer los caracteres CRLF
 sacar_ult(&p_uart->u_buff_rec);
 sacar_ult(&p_uart->u_buff_rec); */
 return(NO_ERR);
} /* FIN de recibir_datos */


/**
 * Envia la corrección diferencial recibida por la red al GPS
 */
void EnviarCorreccion (t_uart_obj * p_uart, unsigned char * Correccion, int Longitud)
{
   WriteRS232C(p_uart->hcom, Correccion, Longitud);
}


int enviar_comando (t_uart_obj * p_uart)
{
 UCHAR ele_env; /* Almacena el byte a enviar */
 int n_naks=0; /* Almacena el número de NAK's recibidos como respuesta a un
				  SET COMMAND */
 UCHAR * buff=NULL; /* Buffer auxiliar para posibles reenvíos */
 int tam; /* Tamaño del buffer auxiliar */
 int ind;
 int comp_ack; /* Almacena si se debe buscar o no una ACK */

 if (!buff_lleno(p_uart->u_buff_emi))
   meter_ele(&p_uart->u_buff_emi,(UCHAR) CR);
 else return(ERR_B_EMI_LLENO);
 if (!buff_lleno(p_uart->u_buff_emi))
   meter_ele(&p_uart->u_buff_emi,(UCHAR) LF);
 else return(ERR_B_EMI_LLENO);
 if (es_setcommand(p_uart->u_buff_emi)) /* Es un SET COMMAND */
   {
	comp_ack=1;
	buff=(UCHAR *) calloc((tam=num_elems(p_uart->u_buff_emi)),sizeof(UCHAR));
   }
 else comp_ack=0;
 ind=0;
 do
   {
	ele_env=sacar_ele(&p_uart->u_buff_emi);
	if (comp_ack)
	  buff[ind++]=ele_env;
	if (b_WriteRS232C(p_uart->hcom,ele_env) == ERR_WB_RS)
	  return(ERR_T_ENV_COM);
   }
 while (!buff_vacio(p_uart->u_buff_emi));
 if (comp_ack)
   {
	do
	  {
	   if (recibir_ack(*p_uart) < 0)
		 {
		  n_naks++;
		  reenviar_comando(buff,tam,p_uart->hcom);
		 }
	   else {
			 free(buff);
			 return(NO_ERR);
			}
	  }
	while (n_naks < MAX_NAK);
	free(buff);
	return(ERR_MAX_NAK);
   }
 return(NO_ERR);
} /* FIN de enviar_comando */


int tomar_pos (t_uart_obj * p_uart)
{
 int rec_dat; /* Para comprobación de error en recepción de datos */

 /* Permitir recepción */
 if (str_a_buff(ACTIVAR,p_uart) == ERR_B_EMI_LLENO)
   return(ERR_BE_POS_AC);
 if (enviar_comando(p_uart) < 0) /* ERR_T_REC_DAT, ERR_B_REC_LLENO,
                                    ERR_T_ENV_COM o ERR_MAX_NAK */
   return(ERR_POS_ENV_AC);
 /* Recibir datos */
 rec_dat=recibir_datos(p_uart);
 /* Prohibir envío */
 if (str_a_buff(DESACTIVAR,p_uart) == ERR_B_EMI_LLENO)
   return(ERR_BE_POS_DE);
 if (enviar_comando(p_uart) < 0) /* ERR_T_REC_DAT, ERR_B_REC_LLENO,
                                    ERR_T_ENV_COM o ERR_MAX_NAK */
   return(ERR_POS_ENV_DE);
 if (rec_dat < 0)
   if (rec_dat == ERR_B_REC_LLENO)
	 return(ERR_BR_POS_DA);
	else return(ERR_POS_REC); /* ERR_T_REC_DAT */
 return(NO_ERR);
} /* FIN de tomar_pos */


int desactivar (t_uart_obj * p_uart)
{
 time_t t_ini;

 while (str_a_buff(DESACTIVAR,p_uart) == ERR_B_EMI_LLENO)
	iniciar_buff(&p_uart->u_buff_emi);
 t_ini=time(NULL);
 while (enviar_comando(p_uart) < 0)
	{
	 if ((t_ini+SEG_DES) < time(NULL))
	   return(ERR_SEG_DES);
	 while (str_a_buff(DESACTIVAR,p_uart) == ERR_B_EMI_LLENO)
		iniciar_buff(&p_uart->u_buff_emi);
	}
 return(NO_ERR);
} /* FIN de desactivar */


int saca_fl_buff (t_buff buffer, int num_com, double * fl)
{
 char str[TAM_FL_STR+1]; /* +1 para meter '\0' */
 int ind_com;
 int ind_str;
 int comas=0;
 int hay_dat;

 /* Se busca el número de coma */
 ind_com=buffer.pri;
 while ((comas != num_com) && (ind_com != buffer.ult))
	{
	 if (',' == ((char) buffer.buff[ind_com]))
	    comas++;
	 ind_com=(ind_com+1)%TAM_BUFF;
	}
 if (ind_com == buffer.ult)
   return(ERR_NO_COM);
 /* Se hace un string entre esta coma y la siguiente */
 ind_str=0;
 hay_dat=0;
 while ((ind_com != buffer.ult) && (ind_str < TAM_FL_STR))
	if (',' == ((char) buffer.buff[ind_com]))
	  {
	   ind_str++;
	   break;
	  }
	else {
		  hay_dat=1;
		  str[ind_str]=(char) buffer.buff[ind_com];
		  ind_com=(ind_com+1)%TAM_BUFF;
		  ind_str++;
		 }
 if (hay_dat)
   {
	/* Se pasa a float */
	str[ind_str]='\0';
	*fl=atof(str);
	return(NO_ERR);
   }
 else if (ind_com == buffer.ult)
		return(ERR_NO_COM);
 return(NO_ERR);
} /* FIN de saca_fl_buff */


void trat_error (int error, t_uart_obj * p_uart)
{
 switch (error)
    {
     case ERR_BE_POS_AC:
        MessageBox(NULL,
           "Comando de activación no pudo ser enviado\nBuffer de emisión lleno",
           "ERROR",MB_OK | MB_ICONERROR);
        iniciar_buff(&p_uart->u_buff_emi);
        break;
     case ERR_POS_ENV_AC:
        MessageBox(NULL,"No se recibe ACK de activación","ERROR",
                   MB_OK | MB_ICONERROR);

        if (desactivar(p_uart) == ERR_SEG_DES)
          exit(0);
        break;
     case ERR_BE_POS_DE:
        MessageBox(NULL,
        "Comando de desactivación no pudo ser enviado\nBuffer de emisión lleno",
           "ERROR",MB_OK | MB_ICONERROR);
        iniciar_buff(&p_uart->u_buff_emi);
        if (desactivar(p_uart) == ERR_SEG_DES)
          exit(0);
        break;
     case ERR_POS_ENV_DE:
        MessageBox(NULL,"No se recibe ACK de desactivación","ERROR",
                   MB_OK | MB_ICONERROR);
        if (desactivar(p_uart) == ERR_SEG_DES)
          exit(0);
        iniciar_buff(&p_uart->u_buff_rec);
        break;
     case ERR_BR_POS_DA:
        MessageBox(NULL,"Buffer de recepción lleno al recibir datos",
                   "ERROR",MB_OK | MB_ICONERROR);
        iniciar_buff(&p_uart->u_buff_rec);
        break;
     case ERR_POS_REC:
        MessageBox(NULL,"Datos erroneos por fallo de línea o t_out excedido",
                   "ERROR",MB_OK | MB_ICONERROR);
        iniciar_buff(&p_uart->u_buff_rec);
        break;
    } /* fin del switch */
} /* FIN de trat_error */

