/******************************************************************************/
/* Funciones de comunicaci�n con el receptor GPS */
/******************************************************************************/
/* Se van a implementar aspectos relacionados con la comunicaci�n con el
	receptor GPS Z-12 de Ashtec */

#ifndef _RECEPGPS
#define _RECECPGPS


/* Cabeceras de los comandos */
#define COMM_S "$PASHS" /* Set Command */
#define COMM_Q "$PASHQ" /* Query Command */
#define COMM_R "$PASHR" /* Response Command */


/* Comados especialmente utilizados (en forma de string) */
#define ACTIVAR "$PASHS,NME,UTM,A,ON"
#define DESACTIVAR "$PASHS,NME,UTM,A,OFF"


/* Respuestas a Set commands */
#define ACK 0x06 /* Respuesta afirmativa a un Set command (*) */
#define NAK 0x15 /* Respuesta negativa a un Set command (*) */
#define MAX_NAK 15 /* N�mero m�ximo de NAK's aceptados */

   /* (*) Durante la configuraci�n se debe haber enviado $PASHS,CACK,1 */


/* Caracteres que indican el final de la llegada de datos */
#define CR 0x0d
#define LF 0x0a


/* Temporizaciones */
#define SEG_DES 5 /* N�mero m�ximo de segundos que se intentar� parar al
					 receptor */


/* Transformaci�n de la informaci�n */
#define TAM_FL_STR 11 /* Tama�o de un double en forma de string */
#define COMA_N 4 /* N�mero de comas tras la que se encuentra la coordenada
					Norte en $PASHR,UTM */
#define COMA_E 5 /* N�mero de comas tras la que se encuentra la coordenada
					Este en $PASHR,UTM */
#define COMA_A 9 /* N�mero de comas tras la que se encuentra la altura en
 				    $PASHR,UTM */


/* Comunicaci�n a trav�s de la RS232C */
#define VT CBR_19200
#define L_DAT 8
#define L_STOP ONESTOPBIT
#define MASK_PARI NOPARITY
#define T_OUT 2000 /* T_OUT en milisegundos para el polling */

   /* OJO: Si se modifican estos valores el receptor GPS debe ser configurado de
           nuevo:
              1. Pedir configuraci�n de la UART
              2. Si configuraci�n de la UART <> de la indicada
                    a) Inicializar el receptor
                    b) Inicializar UART
                 En otro caso Inicializar UART */


extern int recibir_ack (t_uart_obj);
   /* Recibe confirmaci�n devuelta tras un set_command
      Par 1: UART por la que se va a recibir
      Return: Si error t_out ERR_T_ACK
              Si error <> ACK ERR_ACK
              En caso contrario NO_ERR */

extern int str_a_buff (char *, t_uart_obj *);
   /* Mete un comando almacenado como string en el buffer de emisi�n.
      Par 1: String que almacena el comando
      Par 2: UART que se va a utilizar
      Return: Si buffer de emisi�n lleno ERR_B_EMI_LLENO
              En caso contrario NO_ERR */

              
extern void buff_a_str (t_uart_obj *, char *);
   /* Convierte el contenido del buffer de recepci�n en string vaciando dicho
      buffer
      Par 1: UART cuyo buffer de recepci�n se va a tratar
      Par 2: String que se devolver� */


extern int es_setcommand (t_buff);
	/* Comprueba si el contenido del buffer de la UART es un SET COMMAND o no
       Par 1: Buffer del que se va a comprobar el contenido
       Return: Si es SET COMMAND <> 0
               En caso contrario 0 */


extern int recibir_datos (t_uart_obj *);
   /* Recibe la informaci�n enviada por el receptor GPS. Dicha informaci�n debe
      comenzar por el car�cter $ (la funci�n no hace nada hasta que no lo ha
      recibido) y terminar por los caracteres CRLF (la funci�n no para hasta no
      haberlos recibido o hasta que se produzca un error
      Par 1: UART por la que se va a recibir (los datos recibidos se
             introducir�n en el buffer de recepci�n
      Return: Si se intenta meter un byte en el buffer de recepci�n y est�
                 lleno ERR_B_REC_LLENO
              Si se sobrepasa el tiempo de espera de recepci�n ERR_T_REC_DAT
              En caso contrario NO_ERR */


extern int enviar_comando (t_uart_obj *);
   /* Env�a un comando al receptor GPS. Si es un SET COMMAND se espera el ACK
      El comando a enviar debe encontrarse en el buffer de emisi�n de la UART
      (con espacio (dos posiciones) para meter CR y LF
      Despu�s de la emisi�n el buffer de emisi�n se encontrar� vac�o
      Par 1: UART del puerto por la que se va a enviar el comando
      Return: Si se sobrepasa el tiempo de espera en recepci�n de
                 datos ERR_T_REC_DAT
              Si el buffer de emisi�n se llena ERR_B_REC_LLENO
              Si se sobrepasa el tiempo de espera en env�o de comando
                 ERR_T_ENV_COM
              Si se sobrepasa el n�mero de NAK's permitido ERR_MAX_NAK
              En caso contrario NO_ERR */


extern int tomar_pos (t_uart_obj *);
   /* Toma una posici�n
      Par 1: UART a trav�s de la que se coge la posici�n
      Return: Si buffer de emisi�n lleno al activar ERR_BE_POS_AC
              Si error en el enlace en env�o de activaci�n ERR_POS_ENV_AC
              Si buffer de emisi�n lleno al desactivar ERR_BE_POS_DE
              Si error en el enlace en env�o de desactivaci�n ERR_POS_ENV_DE
              Si buffer de recepci�n lleno al recibir los datos ERR_BR_POS_DA
              Si error en el enlace en recepci�n de datos (demasiado tiempo de
                 espera, datos con error, etc) ERR_POS_REC
              En caso contrario NO_ERR */


extern int desactivar (t_uart_obj *);
   /* Para al receptor conectado a la UART que se indica. Esta funci�n s�lo
      debe utilizarse en caso de errores previos ya que provoca una parada
      "brusca" del receptor. Si esta funci�n devuelve error es muy probable que
      un error irrecuperable haya sucedido
      Al salir de esta funci�n el buffer de emisi�n estr� vac�o
      Par 1: UART a la que est� conectado el recptor que se quiere parar
      Return: Si se sobrepasa el tiempo establecido para parar ERR_SEG_DES
              En caso contrario NO_ERR */


extern int saca_fl_buff (t_buff, int, double * );
   /* Devuelve el double que se encuentra en el buffer, que debe tener un
      comando de respuesta, tras el n�mero de comas que se indica
      Par 1: Buffer en el que se encuentra el comadno de respuesta
      Par 2: N�mero de comas tras las que se encuentra el double
      Par 3: Donde se devuelve el double encontrado
      Return: Si error en el n�mero de comas ERR_NO_COM
              En caso contrario NO_ERR */
	/* OJO: NO VACIA EL BUFFER */
	/* OJO: El float contenido en el buffer debe tener, como mucho, TAM_FL_STR
			  caracteres ASCII. Si tiene m�s, s�lo se cogen los TAM_FL_STR
			  primeros */


extern void trat_error (int, t_uart_obj *);
   /* Rutina para el manejo de errores
      Par 1: C�digo del error a tratar */

extern void EnviarCorreccion (t_uart_obj * p_uart, unsigned char * Correccion, int Longitud);
        /*      Envia la un mensaje por el puerto serie */
#endif