#ifndef CAN_MESSAGING_H
#define CAN_MESSAGING_H

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "stdint.h"
#include"Mcu.h"
#include"Can_43_FLEXCAN.h"
#include "CDD_Uart.h"
#include "Messaging_Types.h"
#include "UartMessaging.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

#define MASK 0x3FFFFFFF
#define CAN_HTH_HANDLE 0x00000001

typedef enum{
	ID_CAN_INVERTOR_STANGA = 	0x00000110,
	ID_CAN_INVERTOR_DREAPTA = 	0x00000111,
	ID_CAN_INVERTOARE = 		0x00000112,

	ID_CAN_BORD = 				0x00000113,

	ID_CAN_ACCELERATIE = 		0x00000330,
	ID_CAN_FRANA = 				0x00000331,

	ID_CAN_BATERIE = 			0x00000114,
	/*ID_CAN_BATERIE_TENSIUNI_CELULE nu se trimite pe CAN*/
	/*ID_CAN_BATERIE_TEMPERATURI_CELULE nu se trimite pe CAN*/
	ID_CAN_BATERIE_2 = 			0x00000117,
	ID_CAN_BATERIE_CHARGER =    0x00000119,

	ID_CAN_COMUNICATII = 		0x00000118
}idCan_t;

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define ReadDataFromAddress(xMonitoredValue_t_Address) (xMonitoredValue_t_Address)->value
#define WriteDataAtAddress(data, xMonitoredValue_t_Address) (xMonitoredValue_t_Address)->value = (data)

void CanMessaging_Init(void);
void CanMessaging_Test(void);
void CanMessaging_Update(void);
void CanMessaging_CreateBuffer(idCan_t type);
void CanMessaging_AppTest(void);

#ifdef __cplusplus
}
#endif

#endif
