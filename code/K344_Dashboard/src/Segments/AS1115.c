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
#include "CDD_I2c.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
//adresa slave a driverului
#define DRIVER_SLAVE_ADDRESS 0x00
//canalul folosit
#define I2C_USED_CHANNEL 0
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
//cerere globala
I2c_RequestType request;
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void AS1115_Write(AS1115Registers_t SelectedRegister, uint8_t Value){
    //structura bufferului
	uint8_t buffer[2] = {
    		(uint8_t)SelectedRegister,
			Value
    };

    //pregatire cerere
    request.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    request.BitsSlaveAddressSize = false;
    request.HighSpeedMode = false;
    request.ExpectNack = false;
    request.RepeatedStart = false;
    request.BufferSize = 2;
    request.DataDirection = I2C_SEND_DATA;
    request.DataBuffer = buffer;

    I2c_SyncTransmit(I2C_USED_CHANNEL, &request); //cerere pe canalul 0
}

uint8_t AS1115_Read(AS1115Registers_t SelectedRegister){
    // ---!!!--- S-a incercat introducerea unei referinte la SelectedRegister in writeRequest.DataBuffer = &(registru);
	// ---S-au facut 3 erori la compile, rezolvarea a constat in revenirea la varianta anterioara

	uint8_t value = 0;

    //scriem registrul dorit
    request.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    request.BitsSlaveAddressSize = false;
    request.HighSpeedMode = false;
    request.ExpectNack = false;
    request.RepeatedStart = false;
    request.BufferSize = 1;
    request.DataDirection = I2C_SEND_DATA;
    request.DataBuffer = (uint8_t*)&SelectedRegister;

    I2c_SyncTransmit(I2C_USED_CHANNEL, &request);

    //citim valoarea
    request.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    request.BitsSlaveAddressSize = false;
    request.HighSpeedMode = false;
    request.ExpectNack = false;
    request.RepeatedStart = false;
    request.BufferSize = 1;
    request.DataDirection = I2C_RECEIVE_DATA;
    request.DataBuffer = &value;

    I2c_SyncTransmit(I2C_USED_CHANNEL, &request);

    return value;
}

#ifdef __cplusplus
}
#endif
