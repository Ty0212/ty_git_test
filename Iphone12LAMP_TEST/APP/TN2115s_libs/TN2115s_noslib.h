#include "macros.h"
#ifndef TN2115s_H__
#define TN2115s_H__

/*###################################################################
Section:
						Gloabal Switches
###################################################################*/



/*###################################################################
Section:
						Library Exported User Functions and Variables
###################################################################*/

/*--------Exported Functions---------*/
//Global
void init_core_components(void);													//must be called before calling other library functions
//NFC
void nosNFC_RTX_task(void);																//must be called within a infinite loop
bool NFC_Passthrough_TX(uint8_t data[], uint8_t len);			//function for implementing type4 tx functions. data[]: type4 data to transmit; len: number of bytes to transmit. return: true indicates success. false indicates failure.
uint8_t NFC_Passthrough_RX(uint8_t data[]);								//function for implementing type4 rx functions. data[]: received type4 data.; return: number of bytes received. 0 indicates that no type4 data received.
void HARV_EN(void);																				//function to enable energy harvesting 
void HARV_DIS(void);																			//function to disable energy harvesting 
//FLASH
void FLASH_lock (bool lock);															//function for lock/unlock the code rom. always lock the rom when not intending to write
//Registers
void reg_update_system(uint8_t reg, uint8_t value);				//function for writing the system register
uint8_t reg_get_value(uint8_t reg);												//function for reading the system register
//HW_IIC
void HW_IIC_init(uint8_t * i2c_buf_adr);									// HW i2c initiator. a user buffer address could be provided for data rx/tx. if left zero(NULL), a default internal buffer will be used instead.
//SYS
void nosSYS_SLP_task(void);
//GPIO
void GPIO_SET_FUNC_MODE(uint16_t mask);
void GPIO_SET_INPUT_MODE(uint16_t mask);
void GPIO_SET_OUTPUT_MODE(uint16_t mask);
void GPIO_SET_PIN(uint16_t mask);
void GPIO_CLR_PIN(uint16_t mask);
bool GPIO_GET_PIN(uint16_t mask);
//UART
void UART_init(void);
void UART_tx(uint8_t data);
// SW SPI Master
void 			SPI_init(uint8_t mode);													// SW SPI Master initialization. mode: SPI working mode(polarity/phase)
uint8_t 	SPI_rtx_byte(uint8_t tx_data);									// SW SPI tx and rx a byte of data
void 			SPI_tx_byte(uint8_t tx_data);										// SW SPI tx a byte
uint8_t 	SPI_rx_byte(uint8_t rx_data);										// SW SPI rx a byte
uint8_t * SPI_rtx_buf(uint8_t tx_data[], uint8_t rx_data[], uint16_t len);	// SW SPI tx and rx a buffer of data
void 			SPI_tx_buf(uint8_t tx_data[], uint16_t len);		// SW SPI tx a buffer of data
uint8_t * SPI_rx_buf(uint8_t rx_data[], uint16_t len);		// SW SPI rx a buffer of data
/*--------Callbacks: Implemented in the user's code-------*/ 
// NFC
void NFC_RX_Callback(void);																//optional, called each time after a command is received
void NFC_TX_Callback(void);																//optional, called each time after a response finished transmitting
void NFC_FIELD_OFF_Callback(void);												//optional, called each time the NFC field turns down
void NFC_FIELD_ON_Callback(void);													//optional, called each time the NFC field turns up
// HW IIC
bool HW_I2C_RD_RQST_Callback(I2C_RTX *);									//required, called each time a data read request is received on the IIC. user must provide the data to be read in the I2C_RTX structure
void HW_I2C_WR_DONE_Callback(I2C_RTX *);									//required, called each time a write is done. the received data is stored in the I2C_RTX structure
void HW_I2C_RD_DONE_Callback(I2C_RTX *);									//optional, called each time a read is done. the transmitted data is in the I2C_RTX structure
/*--------Exported Variables------------------*/
// NFC variables
extern  uint8_t	 nfc_a_tag_state;													// Tag current state machine status
extern  uint8_t *  nfc_eeprom;														// Tag EEPROM in 8bit
extern  uint32_t * nfc_eeprom_32;													// Tag EEPROM in 32bit
// SYS
extern  bool		user_must_wake;														// required, indicate if the user's code is done so the chip can enter sleep							
/*--------Configurator Variables: Implemented in the user's code------------*/ 
// Default HW Configuration
extern const uint8_t 					def_sreg[16];								// optional, default register values. Config using: const uint8_t def_sreg[16] __attribute__((at(TAG_REG_EEPROM_BASE))) = {};
extern const uint8_t 					def_tag[32];								// optional, default tag content. Config using: const uint8_t def_tag[32] __attribute__((at(TAG_EEPROM_BASE))) = {};
// Readout Protection
extern const uint32_t 				rdp_word0;									// optional, by default RP is disabled. Enable using: const uint32_t rdp_word0 __attribute__((at(0x00001FFC))) = RDP_ACTIVE; 								 
extern const uint32_t 				rdp_word1;									// optional, by default RP is disabled. Enable using: const uint32_t rdp_word1 __attribute__((at(0x00003FFC))) = RDP_ACTIVE;
extern const uint32_t 				rdp_word2;									// optional, by default RP is disabled. Enable using: const uint32_t rdp_word2 __attribute__((at(0x00005FFC))) = RDP_ACTIVE;
extern const uint32_t 				rdp_word3;									// optional, by default RP is disabled. Enable using: const uint32_t rdp_word3 __attribute__((at(0x00007FFC))) = RDP_ACTIVE;
// RTOS Related Variables


/*###################################################################
Section:
						Library Exported Internal Functions and Variables
###################################################################*/

void nosI2C_IRQ(void);
void nosUART_IRQ(void);
void nosSPI_IRQ(void);

#endif
