/******************************************************************************/
/* Definición de los errores contemplados */
/******************************************************************************/


#ifndef _ERRORES
#define _ERRORES


#define NO_ERR 1              /* No ha habido error */
#define ERR_INI_COM INVALID_HANDLE_VALUE /* Error al inicializar el puerto
                                            serie */
#define ERR_WB_RS -2          /* Error al escribir un byte en el puerto */
#define ERR_RB_RS -3          /* Error al leer un byte del puerto */
#define ERR_W_RS -4           /* Error al escribir un bloque en el puerto */
#define ERR_R_RS -5           /* Error al leer un bloque del puerto */
#define ERR_T_REC_ACK -6      /* T_out al recibir confirmación */
#define ERR_ACK -7            /* Confirmación recibida <> ACK */
#define ERR_B_EMI_LLENO -8    /* Se intenta introducir un byte en el buffer de
                                 emisión y está lleno */
#define ERR_T_REC_DAT -9     /* Sobrepasado el tiempo de espera del polling de
                                 recepción de datos */
#define ERR_B_REC_LLENO -10   /* Se intenta introducir un byte en el buffer de
                                 recepción y está lleno */
#define ERR_T_ENV_COM -11     /* Sobrepasado el tiempo de espera en envío de
                                 comando */
#define ERR_MAX_NAK -12       /* Número máximo de NAK's permitido excedido */
#define ERR_BE_POS_AC -13     /* Buffer de emisión lleno al tomar una posición
                                 en la fase de activación */
#define ERR_POS_ENV_AC -14    /* Error en el enlace en envío de activación */
#define ERR_BE_POS_DE -15     /* Buffer de emisión lleno al tomar una posición
                                 en la fase de desactivación */
#define ERR_POS_ENV_DE -16    /* Error en el enlace en envío de desactivación */
#define ERR_BR_POS_DA -17     /* Buffer de recepción lleno al recibir datos */
#define ERR_POS_REC -21       /* Error en el enlace en recepción de datos */
#define ERR_SEG_DES -22       /* Error al parar al receptor de forma
                                 obligatoria */
#define ERR_NO_COM -23        /* Error al leer del buffer de una UART un
                                 double */                                 


#endif
