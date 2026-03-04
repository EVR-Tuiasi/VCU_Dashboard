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
#define DRIVER_SLAVE_ADDRESS 0x00

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
I2c_RequestType  writeRequest;
I2c_RequestType readRequest;

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
    I2c_RequestType request = {0};
    request.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    request.BitsSlaveAddressSize = false;
    request.HighSpeedMode = false;
    request.ExpectNack = false;
    request.RepeatedStart = false;
    request.BufferSize = 2;
    request.DataDirection = I2C_SEND_DATA;
    request.DataBuffer = buffer;

    I2c_SyncTransmit(0, &request); //cerere pe canalul 0
}

uint8_t AS1115_Read(AS1115Registers_t SelectedRegister){
    // ---!!!--- S-a incercat introducerea unei referinte la SelectedRegister in writeRequest.DataBuffer = &(registru);
	// ---S-au facut 3 erori la compile, rezolvarea a constat in revenirea la varianta anterioara

	uint8_t value = 0;
    uint8_t registru = (uint8_t) SelectedRegister;

    //scriem registrul dorit
    writeRequest.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    writeRequest.BitsSlaveAddressSize = false;
    writeRequest.HighSpeedMode = false;
    writeRequest.ExpectNack = false;
    writeRequest.RepeatedStart = false;
    writeRequest.BufferSize = 1;
    writeRequest.DataDirection = I2C_SEND_DATA;
    writeRequest.DataBuffer = &(registru);

    I2c_SyncTransmit(0, &writeRequest);

    //citim valoarea
    readRequest.SlaveAddress = DRIVER_SLAVE_ADDRESS;
    readRequest.BitsSlaveAddressSize = false;
    readRequest.HighSpeedMode = false;
    readRequest.ExpectNack = false;
    readRequest.RepeatedStart = false;
    readRequest.BufferSize = 1;
    readRequest.DataDirection = I2C_RECEIVE_DATA;
    readRequest.DataBuffer = &value;

    I2c_SyncTransmit(0, &readRequest);

    return value;
}

#ifdef __cplusplus
}
#endif
