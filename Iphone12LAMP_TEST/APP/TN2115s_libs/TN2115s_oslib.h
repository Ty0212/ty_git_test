#include "macros.h"
#ifndef TN2115s_H__
#define TN2115s_H__

/*###################################################################
Section:
						Library Exported User Functions and Variables
###################################################################*/

/*--------Exported Functions---------*/
//Global
void 			init_core_components(void);																				//must be called before calling other library functions
#define 	osLaunchRTOS()		xTaskCreate( (TaskFunction_t)osSYSCORE_task, "SYSCORE", configMINIMAL_STACK_SIZE, NULL, 11, &SYSCORE_id );\
														xTaskCreate( (TaskFunction_t)osSYSAUX_task, "SYSAUX", configMINIMAL_STACK_SIZE, NULL, 10, &SYSAUX_id );\
														vTaskStartScheduler()														
//NFC																									
bool 			NFC_Passthrough_TX(uint8_t data[], uint8_t len);									//function for implementing type4 tx functions. data[]: type4 data to transmit; 
																																						//len: number of bytes to transmit. return: true indicates success. false indicates failure.
uint8_t 	NFC_Passthrough_RX(uint8_t data[]);																//function for implementing type4 rx functions. data[]: received type4 data.; 
																																						//return: number of bytes received. 0 indicates that no type4 data received.
void 			NFC_HARV_AHC(bool onoff);																					//function for controlling automatic NFC energy harvesting. The harvesting will start when NFC is ready. default is enabled.
void 			NFC_HARV_force_AHC(void);																					//function for forcely enabling AHC regardless of NFC status. 
bool 			isNFC_field_on(void);																							//function returns the detection result of NFC field
//FLASH
void 			FLASH_lock (bool lock);																						//function for lock/unlock the code rom. always lock the rom when not intending to write
//Registers
void 			reg_update_system(uint8_t reg, uint8_t value);										//function for writing the system register
uint8_t 	reg_get_value(uint8_t reg);																				//function for reading the system register
//IIC 
void 			I2C_enable(I2C_INIT * i2c_init);																	//HW i2c initiator. a user buffer address could be provided for data rx/tx. 
																																						//if left zero(NULL), a default internal buffer will be used instead.
//SoftI2C
void 			SoftI2C_Init(SoftI2C_Typedef *ops);
uint8_t 	i2c_CheckDevice(SoftI2C_Typedef *ops,uint8_t _Address);
uint8_t 	i2c_master_send(SoftI2C_Typedef *ops,uint8_t slaveAddr,uint8_t* pBuffer,uint16_t usize);
uint8_t 	i2c_master_receive(SoftI2C_Typedef *ops,uint8_t slaveAddr,uint8_t* pBuffer,uint16_t usize);
uint8_t 	i2c_mem_write(SoftI2C_Typedef *ops,uint8_t slaveAddr,uint16_t regAddr,uint16_t MemAddressSize,uint8_t* pBuffer,uint16_t usize);
uint8_t 	i2c_mem_read(SoftI2C_Typedef *ops,uint8_t slaveAddr,uint16_t regAddr,uint8_t MemAddressSize,uint8_t* pBuffer,uint16_t usize);
																																						//Only slave is implemented, so isMaster must be set to false.
//GPIO
void 			GPIO_SET_FUNC_MODE(uint16_t mask);																//set pin to special function mode
void 			GPIO_SET_INPUT_MODE(uint16_t mask);																//set pin to input mode
void 			GPIO_SET_OUTPUT_MODE(uint16_t mask);															//set pin to output mode
void 			GPIO_SET_TEST_MODE(uint16_t mask);
void 			GPIO_SET_PIN(uint16_t mask);																			//set pin output to high
void 			GPIO_CLR_PIN(uint16_t mask);																			//set pin output to low
void 			GPIO_TOG_PIN(uint16_t mask);
bool 			GPIO_GET_PIN(uint16_t mask);																			//get input pin value
void 			EXTI_EnableRisingTrig(uint16_t mask);
void 			EXTI_EnableFallingTrig(uint16_t mask);
void 			EXTI_EnableRFTrig(uint16_t mask);
bool 			EXIT_GET_INTFLG(uint16_t mask);
//UART
void 			UART_init(uint32_t baud);																					//UART init function. baud: the desired baudrate
bool 			UART_tx_byte(uint8_t data);																				//TX one byte. return: true - successful, false - TX is unavailable
uint8_t 	UART_rx_byte(void);																								//read the RX buffer
void 			UART_tx_buf_poll(uint8_t * buf, uint8_t len);											//TX a buffer of data using block mode(polling)
bool 			UART_tx_buf_int(uint8_t * txbuf, uint8_t len);										//TX a buffer of data using non-block mode(interrupt). return: true - successsful
																																						//false - another buffer is being transmitted.
void 			UART_tx_terminate(void);																					//terminate a non-blocking TX buffer transmission session
uint8_t 	UART_rx_chk(void);																								//check how many bytes received
bool 			UART_rx_get(uint8_t * rx_buf);																	  //get all received bytes

//SPI (Software master only now, slave mode is coming shortly)
void 			SPI_init(SPI_INIT * spi_init);																		// SPI initialization. isMaster: master/slave mode (only support master now)
																																						// mode: SPI working mode(polarity/phase)
																																						// Only mater is implemented, so isMaster must be set to true.
uint8_t 	SPIM_rtx_byte(uint8_t tx_data);																		// SPI tx and rx a byte of data
void 			SPIM_tx_byte(uint8_t tx_data);																		// SPI tx a byte
uint8_t 	SPIM_rx_byte(uint8_t rx_data);																		// SPI rx a byte
uint8_t * SPIM_rtx_buf(uint8_t tx_data[], uint8_t rx_data[], uint16_t len);	// SPI tx and rx a buffer of data
void 			SPIM_tx_buf(uint8_t tx_data[], uint16_t len);											// SPI tx a buffer of data
uint8_t * SPIM_rx_buf(uint8_t rx_data[], uint16_t len);											// SPI rx a buffer of data
//bool 			SPIS_tx_buf(uint8_t * txbuf, uint8_t len);											
//uint8_t 	SPIS_rx_chk(void);
//bool 			SPIS_rx_get(uint8_t * rx_buf);

//OTA update utility
void enter_OTA(void);																												// enter bootloader for NFC OTA

/*--------Callbacks: Implemented in the user's code-------*/ 
// NFC
void 			NFC_RX_Callback(void);																	//optional, called each time after a command is received
void 			NFC_TX_Callback(void);																	//optional, called each time after a response finished transmitting
void 			NFC_FIELD_OFF_Callback(void);														//optional, called each time the NFC field turns down
void 			NFC_FIELD_ON_Callback(void);														//optional, called each time the NFC field turns up
// IIC(support is on the way)
bool 			I2C_SLV_RD_RQST_Callback(I2C_RTX *);										//required, called each time a data read request is received on the IIC. user must provide the data to be read in the I2C_RTX structure
void 			I2C_SLV_WR_DONE_Callback(I2C_RTX *);										//required, called each time a write is done. the received data is stored in the I2C_RTX structure
/*--------Exported Variables------------------*/
// NFC variables
extern uint8_t	 							nfc_a_tag_state;										// Tag current state machine status
extern uint8_t *  						nfc_mem;													// Tag EEPROM in 8bit
extern uint32_t * 						nfc_mem_32;											// Tag EEPROM in 32bit
/*--------Configurator Variables: Implemented in the user's code------------*/ 
// Default HW Configuration
extern uint8_t *							def_sreg;										// optional, default register values. Config using: const uint8_t def_sreg[16] __attribute__((at(TAG_REG_EEPROM_BASE))) = {};
extern const 	uint8_t 				def_tag[32];								// optional, default tag content. Config using: const uint8_t def_tag[32] __attribute__((at(TAG_EEPROM_BASE))) = {};
extern uint8_t								*tag_in_ram;							// set the tag memory location. when equal to zero, tag locate in eeprom(false). Set to ram location to place memory in ram.
// Readout Protection
extern const uint32_t 				rdp_word0;									// optional, by default RP is disabled.  								 
extern const uint32_t 				rdp_word1;									// optional, by default RP is disabled. 
extern const uint32_t 				rdp_word2;									// optional, by default RP is disabled. 
extern const uint32_t 				rdp_word3;									// optional, by default RP is disabled. 
// RC OSC Constants
extern uint16_t * rc_setting_frq;													// required by UART and system timer 			
// System Information
extern RSVDATA * sysinfo;																	// System reserved information

/*###################################################################
Section:
						Library Exported Internal Functions and Variables
###################################################################*/

void 			osSYSCORE_task(void);
void 			osSYSAUX_task(void);
int32_t 	osTick_Setup (uint32_t freq);
void 			vApplicationIdleHook(void);
#endif
