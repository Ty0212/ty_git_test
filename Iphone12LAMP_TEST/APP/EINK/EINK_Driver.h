/**********Description:		  FOR Eink Driver *********************/
//Name              Eink_Driver.h
//Author:			      CD_Chen
//Last Modified:		6-201-2019
//Copyright:		    FUSENS Micro.

#ifndef EINKDRIVER_H
#define EINKDRIVER_H

#include "project.h"

#define SPI_3BUS

/******Eink *******/
#ifdef SPI_3BUS
//ÇÙÍ·
/* 
									SM1			SM2			SM3
OFF     000		  	0x0000	0x0000	0x0000
WHITE		111 			0xFFFF	0xFFFF	0xFFFF
RED			001 			0x9249	0x2924	0x2492
GREEN		010		  	0x4924	0x2492	0x9249
BLUE		100 			0x2492	0x9249	0x4924
YELLOW	011				0xB6DB	0x1B6D	0x6DB6
MAGENTA	101				0xDB6D	0x2DB6	0xB6DB
CYAN		110				0x6DB6	0x36DB	0xDB6D
*/
#define BLACK			0x0000		
#define WHITE			0xffff 
#define RED				001	
#define GREEN			010	
#define BLUE			100	
#define YELLOW		011	
#define MAGENTA		101
#define CYAN			110


#define RGBLED_OFF		SPI_48SendData(0x0000,0x0000,0x0000)		
#define RGBLED_WHITE	SPI_48SendData(0xffff,0xffff,0xffff)		
#define RGBLED_RED		SPI_48SendData(0x9249,0x2924,0x2492)   		//RED	 	 		001
#define RGBLED_GREEN	SPI_48SendData(0x4924,0x2492,0x9249)    	//GREEN  		010
#define RGBLED_BLUE	  SPI_48SendData(0x2492,0x9249,0x4924) 			//BLUE	 		100

#define RGBLED_Y	 	 	SPI_48SendData(0xB6DB,0x1B6D,0x6DB6) 		  //YELLOW	 	011
#define RGBLED_M	 	 	SPI_48SendData(0xDB6D,0x2DB6,0xB6DB) 		  //MAGENTA	 	101
#define RGBLED_C	  	SPI_48SendData(0x6DB6,0x36DB,0xDB6D) 		  //CYAN		 	110

#define LED1		GPIO_PIN_DATA
#define LED2		GPIO_PIN_RXD
#define LED3		GPIO_PIN_SIOSCL
#define LED4		GPIO_PIN_SIOSDA

//#define	PIN_OE		GPIO_PIN_6
#define	PIN_CLK		GPIO_PIN_SIOSS//GPIO_PIN_9  CLK
#define	PIN_SDI		GPIO_PIN_SIOTXD //GPIO_PIN_7  TX
#define	PIN_LE		GPIO_PIN_SIOCLK//GPIO_PIN_10 CS/LE

#define PIN_KEY		GPIO_PIN_TXD
#define PIN_MIC_IN	GPIO_PIN_SIORXD

#define EINK_VCC_EN_PIN    		GPIO_PIN_BUSY

#endif
#define KEY_STATE	GPIO_GET_PIN(PIN_KEY)//°´¼ü×´Ì¬
#define MIC_STATE GPIO_GET_PIN(PIN_MIC_IN)//Éù¿Ø
  
void EINK_PINMODE_INIT(void);
void SPI_SendData(uint32_t data,uint8_t len);
void SPI_48SendData(uint32_t SM1,uint32_t SM2,uint32_t SM3);

void  GuitarDisplay(void);

void  GuitarBox_On(void);
void  GuitarBox_Off(void);

void  GuitarLED(void);

void  MusicLED(void);
void  MusicLamp(void);

void  RunningWaterLED(void);
void  RunningWaterWhiteLED(void);

void RGBLED_PWM(uint32_t SM1,uint32_t SM2,uint32_t SM3,uint8_t duty);

void  MusicLamp_V2(void);
void  MusicLED_V2(void);
void MIC_TEST(void);
void SPI_SendColorData(uint32_t color);
#endif
