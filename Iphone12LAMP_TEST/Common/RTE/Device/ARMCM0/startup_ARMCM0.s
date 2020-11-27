;Description:		FOR M0 SOC simulation
;Author:			CD_Chen
;Last Modified:		3-20-2018
;Copyright:		    FUSENS Micro.



Stack_Size      EQU     0x200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

Heap_Size       EQU     0x000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table 

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              
                DCD     Reset_Handler             
                DCD     0              
                DCD     HardFault_Handler        
                DCD     0                         
                DCD     0                        
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     SVC_Handler                          
                DCD     0                         
                DCD     0                         
                DCD     PendSV_Handler           
                DCD     0    

                ; External Interrupts
                DCD     UART_IRQ            
                DCD     SPI_IRQ           
                DCD     osI2C_IRQ
				DCD     osNFCTX_IRQ           
                DCD     osNFCRX_IRQ  
				DCD		osNFCFIELD_IRQ
				DCD     osTIM32_IRQ         
                DCD     0          
                DCD     0          
                DCD     0          
                DCD     0           
                DCD     0          
                DCD     0           
                DCD     0          
                DCD     0          
                DCD     0         
                DCD     0        
                DCD     0            
                DCD     0            
                DCD     0           
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     0                         
                DCD     0                        
                DCD     0                         
                DCD     0                         
                DCD     0       
                DCD     0                         
                DCD     0          
                DCD     0            
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
		IMPORT  bootldr
		IMPORT	app_addr
				
				LDR     R0, =bootldr
				BLX     R0
                LDR     R0, =app_addr
				LDR		R0, [R0]
                BX      R0
                ENDP

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP
					
Default_Handler PROC
				
				EXPORT 	UART_IRQ 					[WEAK]
				EXPORT  SPI_IRQ						[WEAK]	
				EXPORT	osI2C_IRQ					[WEAK]
				EXPORT	osNFCTX_IRQ					[WEAK]
				EXPORT	osNFCRX_IRQ					[WEAK]
				EXPORT	osNFCFIELD_IRQ				[WEAK]
				EXPORT	osTIM32_IRQ					[WEAK]
UART_IRQ            
SPI_IRQ           
osI2C_IRQ           
osNFCTX_IRQ           
osNFCRX_IRQ 
osNFCFIELD_IRQ
osTIM32_IRQ

				B		.

				ENDP

				ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap 
	
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
               

                ALIGN

                ENDIF


                END
