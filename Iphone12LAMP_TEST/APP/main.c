/**********Description:		  FOR M0 SOC simulation*********************/
//Author:			      ty
//Last Modified:		10-10-2020
//Copyright:		    FUSENS Micro.

#include "project.h"

TaskHandle_t		 		SYSCORE_id;																		// CORE task handle
TaskHandle_t		 		SYSAUX_id;																		// AUX task handle
TaskHandle_t		 		Main_id;																			// user's task handle

uint8_t nfc_rx_buf[128] __attribute__( ( section( "NoInit"),zero_init) );																					// NFC buffer for rx
uint8_t nfc_tx_buf[128] __attribute__( ( section( "NoInit"),zero_init) );																					// NFC buffer for tx

void osMain_task(void);
uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];//  __attribute__( ( section( "NoInit"),zero_init) );

uint8_t     					state=1;

int main(void)
{	
	init_core_components();																					// initiate the key system components
	
	NFC->OPCTRL = NFC_OPCTRL_OPERMODE_EEPRO;  
	
	EINK_PINMODE_INIT();
	xTaskCreate( (TaskFunction_t)osMain_task, "Main", 
	configMINIMAL_STACK_SIZE, NULL, 9, &Main_id );									// create the user's task	
	osLaunchRTOS();																									// create key system tasks and launch the RTOS
	while(1);																												// should never reach here
}

void osMain_task()																								// user's task
{  
	vTaskDelay(100);
	GuitarBox_Off();
	while(1)																												
	{		
		switch(state)
		{
			case 1:
				MIC_TEST();
			break;
			case 2:
				MusicLamp_V2();
			break;			
			case 3:
				MusicLED_V2();			
			break;	
			default:
				RGBLED_OFF;
				GuitarBox_Off();
			break;				
		}	
		
		if(!KEY_STATE)
		{
			RGBLED_OFF;
			GuitarBox_Off();
			if(++state>3)
			{
				state=0;
			}
			while(!(KEY_STATE));
		}	
	}
}


void NFC_RX_Callback()																															
{
	if (NFC_Passthrough_RX(nfc_rx_buf))																								
	{
		nfc_tx_buf[0] = 0x00;                                                        
		nfc_tx_buf[1] = 0x00;	
		NFC_Passthrough_TX(nfc_tx_buf, 2);
	}	
}
	
void NFC_TX_Callback()	
{

}

void NFC_FIELD_ON_Callback()
{

}	

__attribute__((section("RW_IRAM1"))) void NFC_FIELD_OFF_Callback()
{


}	

bool 			I2C_SLV_RD_RQST_Callback(I2C_RTX * i2c_rtx)
{
	return false;
}

void 			I2C_SLV_WR_DONE_Callback(I2C_RTX * i2c_rtx)
{
	
}	

void 			I2C_SLV_RD_DONE_Callback(I2C_RTX * i2c_rtx)
{
	
}

