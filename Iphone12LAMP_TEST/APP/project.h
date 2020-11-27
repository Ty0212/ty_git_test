#ifndef project_H
#define project_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "..\..\..\Device_desc\TN2115s1.h"
#include "TN2115s_oslib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Eink_Driver.h"


/******MOTOR*******/
#define MOTOR_A_PIN                     GPIO_PIN_BUSY    
#define MOTOR_B_PIN                     GPIO_PIN_DATA                                          
   
#define MOTOR_PWR_OFF()                 GPIO_SET_INPUT_MODE(MOTOR_A_PIN );\
                                        GPIO_SET_INPUT_MODE(MOTOR_B_PIN)
#define MOTOR_PWR_ON()                  GPIO_SET_OUTPUT_MODE(MOTOR_A_PIN );\
                                        GPIO_SET_OUTPUT_MODE(MOTOR_B_PIN)
                                          
#define MOTOR_INIT()                    MOTOR_PWR_OFF();\
																				GPIO_CLR_PIN(MOTOR_A_PIN );\
                                        GPIO_CLR_PIN(MOTOR_B_PIN)
                                          
#ifdef LOCK_REVERSE   
#define MOTOR_DIR_CCW()                 GPIO_SET_PIN(MOTOR_A_PIN);\
                                        GPIO_CLR_PIN(MOTOR_B_PIN)
#define MOTOR_DIR_CW()                  GPIO_SET_PIN(MOTOR_B_PIN);\
                                        GPIO_CLR_PIN(MOTOR_A_PIN)                                           
#else
#define MOTOR_DIR_CW()                  GPIO_SET_PIN(MOTOR_A_PIN);\
                                        GPIO_CLR_PIN(MOTOR_B_PIN)
#define MOTOR_DIR_CCW()                 GPIO_SET_PIN(MOTOR_B_PIN);\
                                        GPIO_CLR_PIN(MOTOR_A_PIN) 
#endif   
                                     
																		 


// Library Component Configuration
extern uint8_t 								components_cfg;							// required, configurator indicating which components are enabled

#endif
