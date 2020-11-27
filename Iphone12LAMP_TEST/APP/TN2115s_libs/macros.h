#ifndef __MACROS_H__
#define __MACROS_H__

/*###################################################################
Section:
						Macros
###################################################################*/
/*--------Library Global Macros---------*/
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

#define TAG_EEPROM_BASE	  			((uint32_t)0x60000000U)
#define TAG_RAM_BASE	    			((uint32_t)0x80000000U)
#define TAG_RSV_BASE						((uint32_t)0x60000800U - sizeof(RSVDATA))
#define	TAG_ID_BASE							TAG_RSV_BASE
#define	TAG_RCCAL_BASE					(TAG_RSV_BASE + sizeof(CHIPID))
#define TAG_REG_EEPROM_BASE			(TAG_RSV_BASE + sizeof(RSVDATA) - 16)

/*--------NFC Macros---------*/
//TAG state machine
#define IDLE        0
#define HALT        1
#define READY0      2
#define READY1      3
#define CLI1_DONE0  4
#define CLI1_DONE1  5
#define ACTIVE0     6
#define ACTIVE1     7

//Harvester Current 
#define	CUR1X					0x00
#define CUR0_5X				0x20
#define CUR2X					0x40


/*--------Readout Protection Macros---------*/
//#define RDP_ACTIVE		0xffffffff

/*--------GPIO Macros---------*/
#define		 GPIO_PIN_PWRGOOD								(1<<0)
#define		 GPIO_PIN_BUSY									(1<<1)
#define		 GPIO_PIN_DATA									(1<<2)
#define		 GPIO_PIN_SWDIO									(1<<3)
#define		 GPIO_PIN_SWDCLK								(1<<4)
#define		 GPIO_PIN_TXD										(1<<5)
#define		 GPIO_PIN_RXD										(1<<6)
#define		 GPIO_PIN_SIOTXD								(1<<7)
#define		 GPIO_PIN_SIORXD								(1<<8)
#define		 GPIO_PIN_SIOSS									(1<<9)
#define		 GPIO_PIN_SIOCLK								(1<<10)
#define		 GPIO_PIN_SIOSCL								(1<<11)
#define		 GPIO_PIN_SIOSDA								(1<<12)

/*--------HW IIC Macros---------*/
#define I2C_IDLE					0

#define I2C_RD_RQST				10
#define I2C_RD_DONE				12

#define I2C_WR_RQST				20
#define I2C_WR_DONE				22


/*###################################################################
Section:
						Type Definitions
###################################################################*/
/*--------HW IIC---------*/
typedef struct
{
	uint8_t *     i2c_rx_buf;
	uint8_t *     i2c_tx_buf;
  uint16_t      i2c_rxed_bytes;
  uint16_t      i2c_txed_bytes;
	uint16_t			i2c_totx_bytes;
	uint16_t			max_buf;
}I2C_RTX;

typedef struct
{
	bool			isMaster;
	uint8_t * i2c_rx_buf;
	uint8_t		max_buf_len;
	uint8_t		i2c_addr;
	
}I2C_INIT;

/*--------SW SPI---------*/
typedef struct{
	bool 			isMaster;
	uint8_t		mode;
	uint16_t	SPIM_MISO_PIN;
	uint16_t	SPIM_MOSI_PIN;
	uint16_t 	SPIM_CS_PIN;	
	uint16_t	SPIM_CLK_PIN;
	
}SPI_INIT;

/*--------Reserved data structure---------*/
typedef struct{
  uint8_t       type[10];
  uint8_t       year;
  uint8_t       week;
	uint8_t       batch_number[5];
	uint8_t       pad_number;
  uint8_t       pos_x;
  uint8_t       pos_y;
	uint8_t       pad[12];
}CHIPID;

typedef struct{
	uint32_t std_mem_top;
	uint32_t usr_rsv_mem_top;
	uint32_t sys_rsv_mem_top;
	uint32_t cfg_rsv_mem_top;
	uint32_t checksum;
	uint8_t	 pad[28];
	
}TAG_MEM_CFG;

typedef struct{
  CHIPID        uid;
  uint16_t      RC_cal[16];
  TAG_MEM_CFG   mem_cfg;
  uint8_t       SYS_cfg[16];
    
}RSVDATA;

#define I2C_MEMSIZE_8BIT            (1)
#define I2C_MEMSIZE_16BIT           (2)

typedef struct
{

	uint16_t pin_scl;
	uint16_t pin_sda;

} SoftI2C_Typedef;
/*###################################################################
Section:
						RTOS macros
###################################################################*/




#endif


