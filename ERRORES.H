/******************************************************************************/
/* Definici�n de los errores contemplados */
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
#define ERR_T_REC_ACK -6      /* T_out al recibir confirmaci�n */
#define ERR_ACK -7            /* Confirmaci�n recibida <> ACK */
#define ERR_B_EMI_LLENO -8    /* Se intenta introducir un byte en el buffer de
                                 emisi�n y est� lleno */
#define ERR_T_REC_DAT -9     /* Sobrepasado el tiempo de espera del polling de
                                 recepci�n de datos */
#define ERR_B_REC_LLENO -10   /* Se intenta introducir un byte en el buffer de
                                 recepci�n y est� lleno */
#define ERR_T_ENV_COM -11     /* Sobrepasado el tiempo de espera en env�o de
                                 comando */
#define ERR_MAX_NAK -12       /* N�mero m�ximo de NAK's permitido excedido */
#define ERR_BE_POS_AC -13     /* Buffer de emisi�n lleno al tomar una posici�n
                                 en la fase de activaci�n */
#define ERR_POS_ENV_AC -14    /* Error en el enlace en env�o de activaci�n */
#define ERR_BE_POS_DE -15     /* Buffer de emisi�n lleno al tomar una posici�n
                                 en la fase de desactivaci�n */
#define ERR_POS_ENV_DE -16    /* Error en el enlace en env�o de desactivaci�n */
#define ERR_BR_POS_DA -17     /* Buffer de recepci�n lleno al recibir datos */
#define ERR_POS_REC -21       /* Error en el enlace en recepci�n de datos */
#define ERR_SEG_DES -22       /* Error al parar al receptor de forma
                                 obligatoria */
#define ERR_NO_COM -23        /* Error al leer del buffer de una UART un
                                 double */                                 


#endif
