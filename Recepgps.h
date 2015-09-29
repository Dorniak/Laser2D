/******************************************************************************/
/* Funciones de comunicación con el receptor GPS */
/******************************************************************************/
/* Se van a implementar aspectos relacionados con la comunicación con el
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
#define MAX_NAK 15 /* Número máximo de NAK's aceptados */

   /* (*) Durante la configuraci¢n se debe haber enviado $PASHS,CACK,1 */


/* Caracteres que indican el final de la llegada de datos */
#define CR 0x0d
#define LF 0x0a


/* Temporizaciones */
#define SEG_DES 5 /* Número máximo de segundos que se intentará parar al
					 receptor */


/* Transformación de la información */
#define TAM_FL_STR 11 /* Tamaño de un double en forma de string */
#define COMA_N 4 /* Número de comas tras la que se encuentra la coordenada
					Norte en $PASHR,UTM */
#define COMA_E 5 /* Número de comas tras la que se encuentra la coordenada
					Este en $PASHR,UTM */
#define COMA_A 9 /* Número de comas tras la que se encuentra la altura en
 				    $PASHR,UTM */


/* Comunicación a través de la RS232C */
#define VT CBR_19200
#define L_DAT 8
#define L_STOP ONESTOPBIT
#define MASK_PARI NOPARITY
#define T_OUT 2000 /* T_OUT en milisegundos para el polling */

   /* OJO: Si se modifican estos valores el receptor GPS debe ser configurado de
           nuevo:
              1. Pedir configuración de la UART
              2. Si configuración de la UART <> de la indicada
                    a) Inicializar el receptor
                    b) Inicializar UART
                 En otro caso Inicializar UART */


extern int recibir_ack (t_uart_obj);
   /* Recibe confirmación devuelta tras un set_command
      Par 1: UART por la que se va a recibir
      Return: Si error t_out ERR_T_ACK
              Si error <> ACK ERR_ACK
              En caso contrario NO_ERR */

extern int str_a_buff (char *, t_uart_obj *);
   /* Mete un comando almacenado como string en el buffer de emisión.
      Par 1: String que almacena el comando
      Par 2: UART que se va a utilizar
      Return: Si buffer de emisión lleno ERR_B_EMI_LLENO
              En caso contrario NO_ERR */

              
extern void buff_a_str (t_uart_obj *, char *);
   /* Convierte el contenido del buffer de recepción en string vaciando dicho
      buffer
      Par 1: UART cuyo buffer de recepción se va a tratar
      Par 2: String que se devolverá */


extern int es_setcommand (t_buff);
	/* Comprueba si el contenido del buffer de la UART es un SET COMMAND o no
       Par 1: Buffer del que se va a comprobar el contenido
       Return: Si es SET COMMAND <> 0
               En caso contrario 0 */


extern int recibir_datos (t_uart_obj *);
   /* Recibe la información enviada por el receptor GPS. Dicha información debe
      comenzar por el carácter $ (la función no hace nada hasta que no lo ha
      recibido) y terminar por los caracteres CRLF (la función no para hasta no
      haberlos recibido o hasta que se produzca un error
      Par 1: UART por la que se va a recibir (los datos recibidos se
             introducirán en el buffer de recepción
      Return: Si se intenta meter un byte en el buffer de recepción y está
                 lleno ERR_B_REC_LLENO
              Si se sobrepasa el tiempo de espera de recepción ERR_T_REC_DAT
              En caso contrario NO_ERR */


extern int enviar_comando (t_uart_obj *);
   /* Envía un comando al receptor GPS. Si es un SET COMMAND se espera el ACK
      El comando a enviar debe encontrarse en el buffer de emisión de la UART
      (con espacio (dos posiciones) para meter CR y LF
      Después de la emisión el buffer de emisión se encontrará vacío
      Par 1: UART del puerto por la que se va a enviar el comando
      Return: Si se sobrepasa el tiempo de espera en recepción de
                 datos ERR_T_REC_DAT
              Si el buffer de emisión se llena ERR_B_REC_LLENO
              Si se sobrepasa el tiempo de espera en envío de comando
                 ERR_T_ENV_COM
              Si se sobrepasa el número de NAK's permitido ERR_MAX_NAK
              En caso contrario NO_ERR */


extern int tomar_pos (t_uart_obj *);
   /* Toma una posición
      Par 1: UART a través de la que se coge la posición
      Return: Si buffer de emisión lleno al activar ERR_BE_POS_AC
              Si error en el enlace en envío de activación ERR_POS_ENV_AC
              Si buffer de emisión lleno al desactivar ERR_BE_POS_DE
              Si error en el enlace en envío de desactivación ERR_POS_ENV_DE
              Si buffer de recepción lleno al recibir los datos ERR_BR_POS_DA
              Si error en el enlace en recepción de datos (demasiado tiempo de
                 espera, datos con error, etc) ERR_POS_REC
              En caso contrario NO_ERR */


extern int desactivar (t_uart_obj *);
   /* Para al receptor conectado a la UART que se indica. Esta función sólo
      debe utilizarse en caso de errores previos ya que provoca una parada
      "brusca" del receptor. Si esta función devuelve error es muy probable que
      un error irrecuperable haya sucedido
      Al salir de esta función el buffer de emisión estrá vacío
      Par 1: UART a la que está conectado el recptor que se quiere parar
      Return: Si se sobrepasa el tiempo establecido para parar ERR_SEG_DES
              En caso contrario NO_ERR */


extern int saca_fl_buff (t_buff, int, double * );
   /* Devuelve el double que se encuentra en el buffer, que debe tener un
      comando de respuesta, tras el número de comas que se indica
      Par 1: Buffer en el que se encuentra el comadno de respuesta
      Par 2: Número de comas tras las que se encuentra el double
      Par 3: Donde se devuelve el double encontrado
      Return: Si error en el número de comas ERR_NO_COM
              En caso contrario NO_ERR */
	/* OJO: NO VACIA EL BUFFER */
	/* OJO: El float contenido en el buffer debe tener, como mucho, TAM_FL_STR
			  caracteres ASCII. Si tiene más, sólo se cogen los TAM_FL_STR
			  primeros */


extern void trat_error (int, t_uart_obj *);
   /* Rutina para el manejo de errores
      Par 1: Código del error a tratar */

extern void EnviarCorreccion (t_uart_obj * p_uart, unsigned char * Correccion, int Longitud);
        /*      Envia la un mensaje por el puerto serie */
#endif