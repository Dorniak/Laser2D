/******************************************************************************/
/* Definición del tipo que soportará lógicamente la programación de la UART */
/******************************************************************************/


#include "UBUFFObj.H"


#define ABIERTO 1
#define CERRADO 0


typedef struct str_uart_obj {
              HANDLE hcom; /* HANDLE del puerto serie */
              int abierto; /* Indica si la comunicación ha sido abierta */
			  t_buff u_buff_rec; /* Buffer de recepción de la UART */
			  t_buff u_buff_emi; /* Buffer de emisión de la UART */
						} t_uart_obj;

