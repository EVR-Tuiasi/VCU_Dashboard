#ifdef __cplusplus
extern "C" {
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Dio.h"
#include "Port.h"
#include "Gpt.h"
#include "CDD_I2c.h"
#include "AS1115.h"
#include "SevenSegments.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define SCL_PIN_PCR                     71U
#define SCL_PIN_IDX				2U
#define GPT_RECOVER_CHANNEL  			0U
#define GPT_RECOVER_CLOCKS   			4000U
#define MESSAGES_UNTIL_FORCED_REINIT    500U
#define RECOVER_CLK_COUNT               20U
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
static const SegmentsGroups_t SegmentsGroups = {
	{//DigitGroup_Speed
		DIGIT_6,
		DIGIT_3,
		DIGIT_0
	},
	{//DigitGroup_Battery
		DIGIT_7,
		DIGIT_5,
		DIGIT_1
	},
	{//DigitGroup_Temperature
		DIGIT_4,
		DIGIT_2
	}
};

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
// -- SPEED_KMH pentru digiti 0-2
// -- BATTERY_PERCENTAGE pentru digiti 3-5
// -- TEMPERATURE pentru digiti 6-7
static uint8_t displayBuffer[8] = {0};

// -- STAREA CURENTA
static SegmentsState_t i2c_system_state = INITIALIZING;

// index pentru monitorizarea operatiilor atomice de READ/WRITE din fiecare stare
static uint8_t index = 0;
// tot index dar mai junior in care se monitorizeaza scrierea in buffer
static uint8_t indexDigits = 0;

// -- Variabile de flag pentru state machine
// flag de eroare
static volatile bool i2c_error_flag = false;
// pentru a face cele 9 clock uri la mana
static uint8_t recover_clk_count = 0;
static uint32_t messages_sent_since_init = 0U;
/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void Segments_State_Update(void);


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
void I2c_Callback(uint8 Event, uint8 Channel){
	if (Channel == I2C_USED_CHANNEL){
		Gpt_StopTimer(GPT_TIMEOUT_CHANNEL);
		if (
				Event == I2C_MASTER_EVENT_NACK || Event == I2C_MASTER_EVENT_ARBITRATION_LOST ||
				Event == I2C_MASTER_EVENT_ERROR_FIFO || Event == I2C_MASTER_EVENT_PIN_LOW_TIMEOUT ||
				Event == I2C_MASTER_EVENT_DMA_TRANSFER_ERROR
		){
			i2c_error_flag = true;
		} else if (Event == I2C_MASTER_EVENT_END_TRANSFER) {
			i2c_error_flag = false;
		} else {
			//orice alt eveniment neasteptat => eroare, ca sa nu ramana in busy niciodata
			i2c_error_flag = true;
		}
	}
}
void I2c_ErrorCallback(uint8 Event, uint8 Channel){
	if (Channel == I2C_USED_CHANNEL){
		Gpt_StopTimer(GPT_TIMEOUT_CHANNEL);
		if (
				Event == I2C_MASTER_EVENT_NACK || Event == I2C_MASTER_EVENT_ARBITRATION_LOST ||
				Event == I2C_MASTER_EVENT_ERROR_FIFO || Event == I2C_MASTER_EVENT_PIN_LOW_TIMEOUT ||
				Event == I2C_MASTER_EVENT_DMA_TRANSFER_ERROR
		){
			i2c_error_flag = true;
		} else if (Event == I2C_MASTER_EVENT_END_TRANSFER) {
			i2c_error_flag = false;
		} else {
			i2c_error_flag = true;
		}
	}
}
void I2c_timer_timeout(void){
	i2c_error_flag = true;
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

void Segments_Init(void){
	AS1115_Init();
	Gpt_EnableNotification(GPT_TIMEOUT_CHANNEL);
}

void Segments_Test(void){
	//variabila de test pentru simularea vitezei
	static uint16_t test_speed = 0;
	//variabila de test pentru simularea bateriei
	static uint16_t test_battery = 110;
	//variabila de test pentru simularea temperaturii
	static uint16_t test_temperature = 0;
	//counter pentru controlul refresh
	static uint32_t loop_counter = 0;

	while(1){
		// -- Actualizam valorile de test
		test_speed = (test_speed + 1) % 10000; //viteza urca pana la 999 km/h
		test_temperature = (loop_counter % 1000); //temperatura variaza intre 20-60 grade

		// -- La fiecare 10 cicluri, consumam o unitate din baterie
		if(loop_counter % 10 == 0){
			if(test_battery > 0){
				test_battery -= 1;
			} else {
				test_battery = 1000;
			}
		}

		// -- Mapam pe grupurile de digituri valorile de test
		Segments_Set(SPEED_KMH, test_speed);
		Segments_Set(BATTERY_PERCENTAGE, test_battery);
		Segments_Set(TEMPERATURE, test_temperature);


		// -- Trimitem tot bufferul catre driverul AS1115 prin I2C
		Segments_Update();

		// -- Controlul vitezei de refresh
		for(volatile uint32_t delay = 0; delay < 50000UL; delay++);
	    loop_counter++;
	}
}

void Segments_Set(SegmentsMonitoredValue_t SelectedMonitor, uint16_t Value){
	// -- SPEED_KMH pentru digiti 0-2
	// -- BATTERY_PERCENTAGE pentru digiti 3-5
	// -- TEMPERATURE pentru digiti 6-7

	switch(SelectedMonitor) {
		case SPEED_KMH:
			//limite de 0-999 kmh
			if(Value > 9999) Value = 9999;

			//valoarea va iesi de forma XYZ
			displayBuffer[SegmentsGroups.DigitGroup_Speed[0]] = (uint8_t)((Value / 10) % 10);
			displayBuffer[SegmentsGroups.DigitGroup_Speed[1]] = (uint8_t)((Value / 100) % 10);
			displayBuffer[SegmentsGroups.DigitGroup_Speed[2]] = (uint8_t)((Value / 1000) % 10);

			//stingem secventa de digituri din fata egale cu 0
			if(((uint8_t)((Value / 1000) % 10)) == 0){
				displayBuffer[SegmentsGroups.DigitGroup_Speed[2]] |= 0x0F;
				if(((uint8_t)((Value / 100) % 10)) == 0){
					displayBuffer[SegmentsGroups.DigitGroup_Speed[1]] |= 0x0F;
				}
			}
			break;
		case BATTERY_PERCENTAGE:
		    //limite de 0.00-100%
		    if(Value > 1000) Value = 1000;

		    if (Value == 1000) {
		        //valoare baterie plina
		        displayBuffer[SegmentsGroups.DigitGroup_Battery[0]] = 0;
		        displayBuffer[SegmentsGroups.DigitGroup_Battery[1]] = 0;
		        displayBuffer[SegmentsGroups.DigitGroup_Battery[2]] = 1;
		    } else {
		        //valori de forma xy.z
		        displayBuffer[SegmentsGroups.DigitGroup_Battery[0]] = (uint8_t)(Value % 10);
		        displayBuffer[SegmentsGroups.DigitGroup_Battery[1]] = ((uint8_t)(Value / 10) % 10) | 0x80;
		        displayBuffer[SegmentsGroups.DigitGroup_Battery[2]] = (uint8_t)(Value / 100);

		        //stingem digitul din fata
		        if (((uint8_t)(Value / 100)) == 0){
		        	displayBuffer[SegmentsGroups.DigitGroup_Battery[2]] |= 0x0F;
		        }
		    }
		    break;
		case TEMPERATURE:
			//limite de 0-60 grade Celsius
			if(Value > 999) Value = 999;

			//valoarea va iesi de forma XY
			displayBuffer[SegmentsGroups.DigitGroup_Temperature[0]] = (uint8_t)((Value / 10) % 10);
			displayBuffer[SegmentsGroups.DigitGroup_Temperature[1]] = (uint8_t)((Value / 100) % 10);

			//stingem primul digit daca e 0
			if(((uint8_t)((Value / 100) % 10)) == 0){
				displayBuffer[SegmentsGroups.DigitGroup_Temperature[1]] |= 0x0F;
			}
	        break;
	    default:
		    break;
	}
}

void Segments_Update(void){
	I2c_StatusType status = I2c_GetStatus(I2C_USED_CHANNEL);
	switch (i2c_system_state){
		case INITIALIZING:
			if ((status == I2C_CH_IDLE) || (status == I2C_CH_FINISHED)){
				switch (index) {
					case 0:
						// -- Seteaza modul Shutdown cu Reset Feature Register
						AS1115_Async_Write(SHUTDOWN, 0x00);
						index++;
						break;
					case 1:
						AS1115_Async_Write(FEATURE, 0x02);
						index++;
						break;
					case 2:
						// -- Seteaza Luminozitatea Globala la 7 Segment Display-uri
						AS1115_Async_Write(GLOBAL_INTENSITY, 0x0F);
						index++;
						break;
					case 3:
						// -- Seteaza cati pini folosim de la dig0 pana la dig7 [ex: 0x00 - dig0 | 0x03 - dig0 -> dig3]
						AS1115_Async_Write(SCAN_LIMIT, 0x07);
						//aici era 3 pentru teste pe PCB
						index++;
						break;
					case 4:
						// -- Seteaza pana la ce pin folosim decodificare pe digits [ex: 0x03 - 00000011 - Decodifica pe dig0 si dig1, ne luam dupa pozitia bitilor de la LSB la MSB]
						AS1115_Async_Write(DECODE_MODE, 0xFF);
						index++;
						break;
					case 5:
						// -- Seteaza Normal Mode fara modificari la Feature Register
						AS1115_Async_Write(SHUTDOWN, 0x81);
						index++;
						messages_sent_since_init = 0;
						break;
					default:
						break;
				}
			}
			break;

		case I2C_ERROR:
			I2c_DeInit();
			Port_SetPinMode(SCL_PIN_IDX, PORT_MUX_AS_GPIO);
			recover_clk_count = 0;
			Gpt_StartTimer(GPT_RECOVER_CHANNEL, GPT_RECOVER_CLOCKS);
			break;
		case I2C_RECOVERING:
			if(Gpt_GetTimeRemaining(GPT_RECOVER_CHANNEL) == 0U){
				if (recover_clk_count < RECOVER_CLK_COUNT) {
					Dio_WriteChannel(SCL_PIN_PCR, (Dio_LevelType)(recover_clk_count % 2U));
					recover_clk_count++;
					Gpt_StartTimer(GPT_RECOVER_CHANNEL, GPT_RECOVER_CLOCKS);
				}
				else{
					recover_clk_count++;
					Port_SetPinMode(SCL_PIN_IDX, PORT_MUX_ALT3);
					I2c_Init(NULL_PTR);

					i2c_error_flag = false;
					index = 0;
					indexDigits = 0;
				}
			}
			break;
		case OPERATIONAL:
			if ((status == I2C_CH_IDLE) || (status == I2C_CH_FINISHED)){
				messages_sent_since_init ++;
				// afisam date
				switch (indexDigits) {
					case 0:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT0), displayBuffer[indexDigits]);
						indexDigits++;
						break;
					case 1:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT1), displayBuffer[indexDigits]);
						indexDigits++;
						break;
					case 2:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT2), displayBuffer[indexDigits]);
						indexDigits++;
						break;
					case 3:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT3), displayBuffer[indexDigits]);
						indexDigits++;
						break;
					case 4:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT4), displayBuffer[indexDigits]);
						indexDigits++;
						break;
					case 5:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT5), displayBuffer[indexDigits]);
						indexDigits++;
						break;
					case 6:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT6), displayBuffer[indexDigits]);
						indexDigits++;
						break;
					case 7:
						AS1115_Async_Write((AS1115Registers_t)(DIGIT7), displayBuffer[indexDigits]);
						indexDigits = 0;
						break;
				}
			}
			break;
	}
	Segments_State_Update();
}

static void Segments_State_Update(void){
	I2c_StatusType status;

	switch(i2c_system_state){
		case INITIALIZING:
			status = I2c_GetStatus(I2C_USED_CHANNEL);
			if ( i2c_error_flag == true ) {
				i2c_system_state = I2C_ERROR;
			}
			else if ((status == I2C_CH_IDLE) || (status == I2C_CH_FINISHED)){
				if ( (i2c_error_flag == false) && (index == 6) ) {
					i2c_system_state = OPERATIONAL;
				}
			}
			break;
		case I2C_ERROR:
			i2c_system_state = I2C_RECOVERING;
			break;
		case I2C_RECOVERING:
			if(recover_clk_count == RECOVER_CLK_COUNT + 1U){
				i2c_system_state = INITIALIZING;
			}
			break;
		case OPERATIONAL:
			status = I2c_GetStatus(I2C_USED_CHANNEL);
			if ( i2c_error_flag == true ) {
				i2c_system_state = I2C_ERROR;
			}
			else if(messages_sent_since_init >= MESSAGES_UNTIL_FORCED_REINIT){
				messages_sent_since_init = 0;
				i2c_error_flag = false;
				index = 0;
				indexDigits = 0;
				i2c_system_state = INITIALIZING;
			}
			break;
	}
}

void Segments_TimeoutTest(void){
	uint8_t stare = 0;
	uint8_t pin = 0;
	Port_SetPinMode(SCL_PIN_IDX, PORT_MUX_AS_GPIO);
	while(1){
		switch(stare){
		case 0:
			Gpt_StartTimer(GPT_TIMEOUT_CHANNEL, GPT_TIMEOUT_CLOCKS);
			stare=1;
			break;
		case 1:
			if(Gpt_GetTimeRemaining(GPT_TIMEOUT_CHANNEL) == 0U){
				Dio_WriteChannel(SCL_PIN_PCR, (Dio_LevelType)(pin));
				pin = 1 - pin;
				stare = 0;
			}
			break;
		}
	}
}

#ifdef __cplusplus
}
#endif

/** @} */
