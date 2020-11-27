/**********Description:		  FOR Eink Driver *********************/
//Name              Eink_Driver.c
//Author:			      CD_Chen
//Last Modified:		6-201-2019
//Copyright:		    FUSENS Micro.

#include "project.h"
// GPIO　INIT
//uint32_t const RGBLED_UPDATA[14]=
//{
//	0xffff,		//SM1 ALL ON
//	0xfff9,
//	0xffa9,
//	0xfe49,		         
//	0xf249,		
//	0x9249,		//SM2		
//	0xfffa,
//	0xffE4,	
//	0xff24,
//	0xf9e4,
//	0x2924,		//SM3
//	0xe4ff,
//	0x3f9f,
//	0xfff2
//};
uint32_t const RGBLED_UPDATA[11]=
{
	0x0000,		//SM1 ALL ON
	
	0x0001,
	0x0009,
	0x0049,		         
	0x0249,		
	0x9249,
	
	0x0004,
	0x0024,	
	0x0124,
	0x0924,
	0x2924,		
};

void EINK_PINMODE_INIT(void)
{
	//VCC
	GPIO_SET_OUTPUT_MODE(EINK_VCC_EN_PIN);
	
	//LED 
	GPIO_SET_OUTPUT_MODE(LED1 );  
	GPIO_SET_OUTPUT_MODE(LED2 );
	GPIO_SET_OUTPUT_MODE(LED3 );
	GPIO_SET_OUTPUT_MODE(LED4 );
	
	//SM1610
	GPIO_SET_OUTPUT_MODE(PIN_CLK );
	GPIO_SET_OUTPUT_MODE(PIN_SDI );
	GPIO_SET_OUTPUT_MODE(PIN_LE );	
	
	//GPIO_VCC INIT
	GPIO_SET_PIN(EINK_VCC_EN_PIN);
	
  //GPIO_LED INIT	
	GPIO_SET_PIN(LED1);
	GPIO_SET_PIN(LED2);
	GPIO_SET_PIN(LED3);
	GPIO_SET_PIN(LED4);
	
	//GPIO_SM1610 INIT
	GPIO_CLR_PIN(PIN_CLK);
	GPIO_CLR_PIN(PIN_SDI);
	GPIO_CLR_PIN(PIN_LE);
	//GPIO_KEY GPIO_MIC1
	GPIO_SET_INPUT_MODE(PIN_KEY);	//触摸按键
	GPIO_SET_INPUT_MODE(PIN_MIC_IN);//声控
}

//32bit
void SPI_SendData(uint32_t data,uint8_t len)
{
	uint8_t delay,i;
	GPIO_CLR_PIN(PIN_CLK);
	GPIO_CLR_PIN(PIN_LE);
	for(i=0;i<len;i++)
	{
		if(data&0x80000000)
			GPIO_SET_PIN(PIN_SDI);//SER=dat>>7;
		else
			GPIO_CLR_PIN(PIN_SDI);//SER=dat>>7;
		
		GPIO_SET_PIN(PIN_CLK);//SRCLK=1;
		delay=3;
		while(delay--);	
		GPIO_CLR_PIN(PIN_CLK);//SRCLK=0;				
		data <<= 1;
	}

	GPIO_SET_PIN(PIN_LE);//RCLK=1;
	delay=3;
	while(delay--);		
	GPIO_CLR_PIN(PIN_LE);//RCLK=0;	
}
//48bit
void SPI_48SendData(uint32_t SM1,uint32_t SM2,uint32_t SM3)
{
	uint8_t delay;
	uint32_t data;
	GPIO_CLR_PIN(PIN_CLK);
	GPIO_CLR_PIN(PIN_SDI);
	GPIO_CLR_PIN(PIN_LE);
	data=SM3;
	for(int i=0;i<16;i++)
	{
		if(data&0x8000)
			GPIO_SET_PIN(PIN_SDI);//SER=dat>>7;
		else
			GPIO_CLR_PIN(PIN_SDI);//SER=dat>>7;
		
		GPIO_SET_PIN(PIN_CLK);//SRCLK=1;
		delay=3;
		while(delay--);	
		GPIO_CLR_PIN(PIN_CLK);//SRCLK=0;				
		data <<= 1;
	}

//	data=0x0000;
	data=SM2;
	for(int i=0;i<16;i++)
	{
		if(data&0x8000)
			GPIO_SET_PIN(PIN_SDI);//SER=dat>>7;
		else
			GPIO_CLR_PIN(PIN_SDI);//SER=dat>>7;
		
		GPIO_SET_PIN(PIN_CLK);//SRCLK=1;
		delay=3;
		while(delay--);	
		GPIO_CLR_PIN(PIN_CLK);//SRCLK=0;				
		data <<= 1;
	}
	data=SM1;
	for(int i=0;i<16;i++)
	{
		if(data&0x8000)
			GPIO_SET_PIN(PIN_SDI);//SER=dat>>7;
		else
			GPIO_CLR_PIN(PIN_SDI);//SER=dat>>7;
		
		GPIO_SET_PIN(PIN_CLK);//SRCLK=1;
		delay=3;
		while(delay--);	
		GPIO_CLR_PIN(PIN_CLK);//SRCLK=0;				
		data <<= 1;
	}
	GPIO_SET_PIN(PIN_LE);//RCLK=1;
	delay=3;
	while(delay--);		
	GPIO_CLR_PIN(PIN_LE);//RCLK=0;	
}
void  GuitarDisplay(void)
{
	uint32_t time=0,count=0;
	RGBLED_OFF;
	GuitarBox_Off();
	while(1)
	{
		if(time >= 500)
		{
			if(time==500)
			{
				if(++count>7){
				count=1;}
			}
			GPIO_CLR_PIN(LED1);
			GPIO_SET_PIN(LED2);
			GPIO_SET_PIN(LED3);
			GPIO_CLR_PIN(LED4);
			switch(count)
			{
				case 1:
					RGBLED_WHITE;
					break;
				case 2:
					RGBLED_RED;
					break;	
				case 3:
					RGBLED_GREEN;
					break;
				case 4:
					RGBLED_BLUE;
					break;
				case 5:
					RGBLED_Y;
					break;
				case 6:
					RGBLED_M;
					break;
				case 7:
					RGBLED_C;
					break;
				default:	
					RGBLED_OFF;
					break;
			}
		}else{
			GPIO_SET_PIN(LED1);
			GPIO_CLR_PIN(LED2);
			GPIO_CLR_PIN(LED3);
			GPIO_SET_PIN(LED4);
		}
		if(++time > 1000)			
				time = 0;	
		if(!KEY_STATE)
		{
			break;
		}	
	}	
}

void  GuitarBox_On(void)
{
		GPIO_CLR_PIN(LED1);
		GPIO_CLR_PIN(LED2);
		GPIO_CLR_PIN(LED3);
		GPIO_CLR_PIN(LED4);
}
void  GuitarBox_Off(void)
{
		GPIO_SET_PIN(LED1);
		GPIO_SET_PIN(LED2);
		GPIO_SET_PIN(LED3);
		GPIO_SET_PIN(LED4);
}

void  GuitarLED(void)
{

	uint32_t dataSM1,dataSM2,dataSM3;
	uint32_t SMRED=0x0007;
	dataSM1=0x0000;
	dataSM2=0x0000;
	dataSM3=0x0000;
	SMRED=0x0003;
	for(int i=0;i<5;i++)
	{
		vTaskDelay(100);
		if(i==4)
			SMRED|=0xE000;
		dataSM1|=SMRED;
		dataSM3|=SMRED;
		SPI_48SendData(dataSM1,dataSM2,dataSM3);
		SMRED<<=3;
		dataSM1=0x0000;
		dataSM3=0x0000;
		GPIO_CLR_PIN(LED1);
		GPIO_SET_PIN(LED2);
		GPIO_SET_PIN(LED3);
		GPIO_CLR_PIN(LED4);
		if(!KEY_STATE)
		{
			break;
		}
	}
	SMRED=0x0007;
	for(int i=0;i<5;i++)
	{
		vTaskDelay(100);
		if(i==4)
			SMRED|=0xE000;
		dataSM2|=SMRED;
		SPI_48SendData( dataSM1, dataSM2, dataSM3);
		SMRED<<=3;
		dataSM2=0x0000;
		dataSM3=0x0000;
		GPIO_SET_PIN(LED1);
		GPIO_CLR_PIN(LED2);
		GPIO_CLR_PIN(LED3);
		GPIO_SET_PIN(LED4);
		if(!KEY_STATE)
		{
			break;
		}	
	}
}

//红色灯在白色长亮做流水灯
void  RunningWaterLED(void)
{
	uint32_t time=0;
	GuitarBox_Off();
	while(1)
	{
		if(++time>2000)
			time=0;
		if(time<200){
			SPI_48SendData( 0xfff9, 0xffff,0xfff2);		
		} 
		else if(time<400){
				SPI_48SendData( 0xffAf, 0xffff,0xff9f);
		} 
		else if(time<600){
				SPI_48SendData( 0xfE7f, 0xffff,0xfaff);
		}
		else if(time<800){
				SPI_48SendData( 0xf3ff, 0xffff,0xE7ff);
		} 
		else if(time<1000){
				SPI_48SendData( 0x9fff, 0xffff,0x3fff);
		}
		else if(time<1200){
				SPI_48SendData( 0xffff, 0xfffa,0xfff2);
		}
		else if(time<1400){
			SPI_48SendData( 0xffff, 0xffE7,0xff9f);	
		} 
		else if(time<1600){
				SPI_48SendData( 0xffff, 0xff3f,0xfaff);
		} 
		else if(time<1800){
				SPI_48SendData( 0xffff, 0xf9ff,0xE7ff);
		}
		else if(time<2000){
				SPI_48SendData( 0xffff, 0xEfff,0x3fff);
		} 
		if(time % 500 ==0)
		{
			GuitarBox_On();
		}
		else if(time %100==0)
		{
			GuitarBox_Off();
		}
		if(!KEY_STATE)
		{
			break;
		}	
	}
}
//白色灯在红色长亮做流水灯
void  RunningWaterWhiteLED(void)
{
	uint32_t time=0;
	GuitarBox_Off();
	while(1)
	{
		if(++time>2000)
			time=0;
		if(time<200){
				SPI_48SendData(0x924F,0x2924,0x249E);
		} 
		else if(time<400){
				SPI_48SendData(0x92e9,0x2924,0x24f2);
		} 
		else if(time<600){
				SPI_48SendData(0x93A9,0x2924,0x2e92);
		}
		else if(time<800){
				SPI_48SendData(0x9E49,0x2924,0x3a92);
		} 
		else if(time<1000){
				SPI_48SendData(0xFe49,0x2924,0xE492);
		}
		else if(time<1200){
				SPI_48SendData(0x9249,0x2927,0xE492);
		}
		else if(time<1400){
				SPI_48SendData(0x9249,0x293a,0x3a92);	
		} 
		else if(time<1600){
				SPI_48SendData(0x9249,0x29e4,0x2e92);
		} 
		else if(time<1800){
				SPI_48SendData(0x9249, 0x2f24,0x24f2);
		}
		else if(time<2000){
				SPI_48SendData(0x9249, 0x3924,0x249E);
		} 
		if(time % 500 ==0)
		{
			GuitarBox_On();
		}
		else if(time %100==0)
		{
			GuitarBox_Off();
		}
		if(!KEY_STATE)
		{
			break;
		}	
	}
}

void  MusicLamp_V2(void)
{
	uint8_t	cnt=0;
	bool c=0;
	uint32_t count=0;
	uint32_t RGBLED_DATA;
	RGBLED_OFF;
	GuitarBox_Off();	
	while(1)
	{
			if(!MIC_STATE)
			{
					count++;
				if(count>=10)
					count = 10;
//				while(!(MIC_STATE));
			}	
			else if(++cnt>2)
			{
					cnt = 0;
					if(count)
						count--;
			}				
		if(count)
			{	
				if(count <= 5){
					RGBLED_DATA = RGBLED_UPDATA[count];
					if(c==1)
					{
						SPI_48SendData(RGBLED_DATA,0x0000,0x0000);
						GuitarBox_Off();
						c=0;
					}
					else
					{
						SPI_48SendData(RGBLED_DATA,0x0000,0xFFFF);
						GuitarBox_On();
						c=1;
					}
				}
				else if(count <= 10)
				{
					RGBLED_DATA = RGBLED_UPDATA[count];
					if(c==1)
					{
						SPI_48SendData(0x9249,RGBLED_DATA,0x0000);
						GuitarBox_Off();
						c=0;
					}
					else{
						SPI_48SendData(0x9249,RGBLED_DATA,0xFFFF);
						GuitarBox_On();
						c=1;
					}
				}
			}
			else 
			{
				RGBLED_OFF;
				GuitarBox_Off();
			}
		vTaskDelay(100);	
		if(!KEY_STATE)
		{
			break;
		}	
	}
}
/*****MIC CHABNGE COLOR****
*
*
**/
void  MusicLED_V2(void)
{
	uint8_t	COLOUR =0;
	while(1)
	{
		if(!MIC_STATE)
		{
			GuitarBox_On();
			switch(++COLOUR)
			{
				case 1:
					RGBLED_WHITE;
					break;
				case 2:
					RGBLED_RED;
					break;	
				case 3:
					RGBLED_GREEN;
					break;
				case 4:
					RGBLED_BLUE;						
					break;
				case 5:
					RGBLED_Y;
					break;	
				case 6:
						RGBLED_M;
					break;
				default:
					RGBLED_C;
					COLOUR = 0;		
					break;
			}
		}
		else 
		{
			RGBLED_OFF;
			GuitarBox_Off();
		}
		vTaskDelay(500);
		if(!KEY_STATE)
		{
			break;
		}	
	}
}

/*****MIC TEST*****
*	OFF	  -- NO MIC 
*	GREEN -- MIC 
*/
void MIC_TEST(void)
{
	while(1)
	{
		if(!MIC_STATE)
		{
			GuitarBox_On();
			RGBLED_GREEN;
		}
		else//OFF
		{
			GuitarBox_Off();
			RGBLED_OFF;
		}
		vTaskDelay(100);	
		if(!KEY_STATE)
		{
			break;
		}	
	}
}
