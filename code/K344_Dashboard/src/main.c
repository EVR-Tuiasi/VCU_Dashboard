
#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Port.h"
#include "Det.h"
#include "Dem.h"
#include "Spi.h"
#include "Platform.h"
#include "Mcu.h"
#include "Dio.h"
#include "Mcl.h"
#include "CDD_I2c.h"
#include "Can_GeneralTypes.h"
#include "Can_43_FLEXCAN.h"
#include "CanIf.h"
#include "SchM_Can_43_FLEXCAN.h"

#include "display_old.h"
#include "FT81_misc.h"
#include "FT81_display.h"
#include "FT81_sound.h"
#include "FT81_touch.h"
#include "7-segment-display.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


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
/**
* @brief        Main function of the example
* @details      Initialize the used drivers and uses the Icu
*               and Dio drivers to toggle a LED on a push button
*/
int main(void)
{
    Mcu_Init(NULL_PTR);
    Mcu_InitClock(McuClockSettingConfig_0);
    while(MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
    	;
    }
    Mcu_DistributePllClock();
    Mcu_SetMode(McuModeSettingConf_0);
    Platform_Init(NULL_PTR);
    Port_Init(NULL_PTR);
    Mcl_Init(NULL_PTR);
    Spi_Init(NULL_PTR);
    I2c_Init(NULL_PTR);
	Can_43_FLEXCAN_Init(NULL_PTR);
	CanIf_Init(NULL_PTR);


    SevenSegmentInit();
    //SevenSegmentTest();
	DisplayInit();
	//DisplayTest();
	//DashboardTest();
	//SoundTest();

	wr8(REG_VOL_SOUND,0xFF);
	wr32(REG_GPIOX_DIR, 0x00008004);
	wr32(REG_GPIOX, 0x00008000); // disable amp
	wr8(REG_PLAY, 0);
	wr16(REG_SOUND, 0x0);
	wr8(REG_PLAY, 1);

	//sound
	wr32(REG_GPIOX, 0x00008004); // enable amp
	wr16(REG_SOUND, (0x34<< 8) | 0x41);
	wr8(REG_PLAY, 1);
	volatile int dellei = 10000000;
	while(dellei--);
	wr8(REG_PLAY, 1);
	dellei = 10000000;
	while(dellei--);
	wr8(REG_PLAY, 1);
	dellei = 10000000;
	while(dellei--);

	wr32(REG_GPIOX, 0x00008000); // disable amp
	wr8(REG_PLAY, 0);
	wr16(REG_SOUND, 0x0);
	wr8(REG_PLAY, 1);

	volatile uint32 frana = 0, acceleratie = 0, rpm = 0, tensiune = 0, curent = 0, tempController = 0, tempMotor = 0, putere = 0, procentaj = 0, tempMaxim = 0, viteza = 0;
	while(1){
		//citire valori senzori frana
		//frana = PedalsGetBrakePercent();
		//acceleratie = PedalsGetAccelerationPercent();

		//citire date de la invertor
        //rpm = InverterGetRpm(0);
        //curent = InverterGetCurrent(0);//curent returnat cu o virgula
        //tensiune = InverterGetVoltage(0);//tensiune returnata cu o virgula
        //tempController = InverterGetControllerTemperature(0);
        //tempMotor = InverterGetMotorTemperature(0);
        //throttle = InverterGetThrottle(0);

        //calcul putere instantanee
        if(curent != 0 && tensiune != 0){
            putere = (((uint64)curent) * ((uint64)tensiune))/100U;
        }
        else{
        	putere = 0U;
        }

		//actualizare afisaje segmente
        //calcul procentaj baterie
        if(tensiune < 600U){
            procentaj = 0;
        }
        else if(tensiune > 1000U){
        	procentaj = 1000U;//procentaj calculat cu o virgula
        }
        else{
        	procentaj = (uint16)(tensiune - 600U) * 5U / 2U;//procentaj calculat cu o virgula
        }
        if(procentaj < 1000U){
            SevenSegmentDisplayDecimalValue(2, procentaj, 1);
        }
        else{
            SevenSegmentDisplayDecimalValue(2, procentaj/10U, 0);
        }
        tempMaxim = 0;
        if(tempController > tempMotor){
        	tempMaxim = tempController;
        }
        else{
        	tempMaxim = tempMotor;
        }
        SevenSegmentDisplayDecimalValue(0, tempMaxim, 0);
        viteza = 0;
        if(rpm != 0){
        	viteza = (rpm * 84807U) / 312500U;
        }
        if(viteza < 1000U){
            SevenSegmentDisplayDecimalValue(1, viteza, 1);
        }
        else{
            SevenSegmentDisplayDecimalValue(1, viteza/10U, 0);
        }
		//actualizare interfata display
		//TODO martori de bord
        DashboardUpdate(viteza, putere, tensiune/10U, procentaj/10U, tempMotor, tempController, frana, acceleratie, false);
	}

	while(1);


}


#ifdef __cplusplus
}
#endif

/** @} */
