/******************************************************************************/
/* Definici�n del tipo que soportar� l�gicamente la programaci�n de la UART */
/******************************************************************************/


#include "UBUFFObj.H"


#define ABIERTO 1
#define CERRADO 0


typedef struct str_uart_obj {
              HANDLE hcom; /* HANDLE del puerto serie */
              int abierto; /* Indica si la comunicaci�n ha sido abierta */
			  t_buff u_buff_rec; /* Buffer de recepci�n de la UART */
			  t_buff u_buff_emi; /* Buffer de emisi�n de la UART */
						} t_uart_obj;
