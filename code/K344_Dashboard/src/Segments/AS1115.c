#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "AS1115.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
//adrese pentru LPI2C0 pentru S32K344
#define LPI2C0_BASE          (0x40440000UL)									//Base Address
#define LPI2C_MCR            (*(volatile uint32_t*)(LPI2C0_BASE + 0x10))	//Control Register
#define LPI2C_MSR            (*(volatile uint32_t*)(LPI2C0_BASE + 0x14))	//Status Register
#define LPI2C_MTDR           (*(volatile uint32_t*)(LPI2C0_BASE + 0x1C))	//Transmit Data
#define LPI2C_MRDR           (*(volatile uint32_t*)(LPI2C0_BASE + 0x20))	//Receive Data

//adresa driver de trimitere
#define AS1115_I2C_ADDR      0x00

//comenzi pentru LPI2C MTDR
#define CMD_START            (0x0400U)
#define CMD_STOP             (0x0200U)
#define CMD_TRANSMIT         (0x0000U)
#define CMD_RECEIVE          (0x0100U)

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
static void LPI2C_Wait(){
	//se asteapta pana cand FIFO de transmitere a datelor are loc
	while(((*(volatile uint32_t*)(LPI2C0_BASE + 0x18)) & 0xFF) > 2);
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void AS1115_Write(AS1115Registers_t SelectedRegister, uint8_t Value){
    //START + adresa pe write
	LPI2C_Wait();
	LPI2C_MTDR = CMD_START | (AS1115_I2C_ADDR << 1);

	//trimite adresa de inregistrare
	LPI2C_Wait();
	LPI2C_MTDR = CMD_START | (uint8_t)SelectedRegister;

	//trimitere date
	LPI2C_Wait();
	LPI2C_MTDR = CMD_TRANSMIT | Value;

	//STOP
	LPI2C_Wait();
	LPI2C_MTDR = CMD_STOP;
}

uint8_t AS1115_Read(AS1115Registers_t SelectedRegister){
    uint32_t data = 0;
	//START + adresa pe write
	LPI2C_Wait();
	LPI2C_MTDR = CMD_START | (AS1115_I2C_ADDR << 1);

	//trimite adresa de inregistrare
	LPI2C_Wait();
	LPI2C_MTDR = CMD_START | (uint8_t)SelectedRegister;

	//REPEATED START + adresa pe read (bitul LSB setat pe 1)
	LPI2C_Wait();
	LPI2C_MTDR = CMD_START | (AS1115_I2C_ADDR << 1 | 0x01);

	//comanda de receive (0x00 inseamna primirea 1 octet)
	LPI2C_Wait();
	LPI2C_MTDR = CMD_RECEIVE | 0x00;

	//STOP
	LPI2C_Wait();
	LPI2C_MTDR = CMD_STOP;

	//asteapta pana cand receive FIFO are date disponibile
	//verificam registrul MSR sau MRSR
	//in LPI2C0_BASE + 0x24 avem MRSR
	while(((*(volatile uint32_t*)(LPI2C0_BASE + 0x24)) & 0xFF) == 0);

	//citirea datelor
	receivedValue = LPI2C_MRDR;

	//verificam bitul de RX Empty pentru a ne asigura ca datele sunt valide
	if (!(data & (1 << 14))) {
		return (uint8_t)(data & 0xFF);
	}

	return 0;
}

#ifdef __cplusplus
}
#endif
