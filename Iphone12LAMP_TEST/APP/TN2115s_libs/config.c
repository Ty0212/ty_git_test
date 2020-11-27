#include "project.h"

/**********************************Configurations***************************************/

#ifdef RDP_ACTIVE
#undef RDP_ACTIVE
#endif

#ifdef TAG_MEM_CFG
#undef TAG_MEM_CFG
#endif

/*System ROM read-out protection switch. Uncomment to turn on.*/
//#define RDP_ACTIVE																																		

/*TAG eeprom default values, should follow Type2 Tag memory layout rules. */
const uint8_t def_tag[32]  __attribute__((at(0x60000780))) = {											
												0x46, 0x53, 0x54, 0x4e, 0x31, 0x30, 0x6d, 0x20,
												0x64, 0x48, 0x00, 0x00, 0xe1, 0x10, 0xfc, 0x00,
												0x03, 0x03, 0xd0, 0x00, 0x00, 0xfe, 0x00, 0x00,
												0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*Configure TAG memory location, 0 = EEPROM, 1 = RAM */
#define		TAG_MEM_CFG			0

/*FW version is set here, maximum 20bytes long. The two version strings must match*/
/*Each updated version must have an unique FW version value. This can be read out in OTA mode.*/
volatile uint8_t FW_VER_0[] __attribute__((at(0x00002000))) = __DATE__ __TIME__;
volatile uint8_t FW_VER_1[] __attribute__((at(0x00007FD0))) = __DATE__ __TIME__;



/**********************************DO NOT MODIFY BELOW***************************************/

#ifdef	RDP_ACTIVE
#define RDP_WORD		0xffffffff
#else
#define RDP_WORD		0x00000000
#endif

#if (TAG_MEM_CFG == 0)
uint8_t	 *	tag_in_ram 	__attribute__((section("ER_IROM1")))	= 0;
#elif (TAG_MEM_CFG == 1)
uint32_t		tag_mem[16] __attribute__( ( section( "NoInit"),zero_init) );	
uint8_t	 *	tag_in_ram 	__attribute__((section("ER_IROM1"))) 	= (uint8_t *)tag_mem;
#endif

const uint32_t rdp_word0 __attribute__((at(0x00001FFC))) = RDP_WORD;
const uint32_t rdp_word1 __attribute__((at(0x00003FFC))) = RDP_WORD;
const uint32_t rdp_word2 __attribute__((at(0x00005FFC))) = RDP_WORD;
const uint32_t rdp_word3 __attribute__((at(0x00007FFC))) = RDP_WORD;

extern void __main(void);
const void * app_addr __attribute__((at(0x000002020))) = (void *)__main;

uint16_t * rc_setting_frq = (uint16_t *)TAG_RCCAL_BASE;
uint8_t * def_sreg = (uint8_t *)TAG_REG_EEPROM_BASE;

uint32_t SystemCoreClock = 8000000UL;
