        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  // Exception vector table
  // This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  // The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset: 
		 
		 CMU_BASE=0x400c8000 //base address of CMU
		 CMU_HFPERCLKENO=0x044 // offset from base
		 CMU_HFPERCLKEN0_GPIO =13 // BIT REPRESENTING GPIO
		 
		 // load CMU base address
		 ldr r1, cmu_base_addr
		 
		 // load current value of HFPERCLK ENABLE
		 ldr r2, [r1, #CMU_HFPERCLKKENO]
		 
		 // set bit for GPIO clk
		 mov r3, #1
		 lsl r3, r3, #CMU_HFPERCLKKEN0_GPIO
		 orr r2, r2, r3
		 
		 // store new value
		 str r2, [r1, # CMU_HFPERCLK0]
		 
		 
		 // Enable output
		 ldr r1, #0x2 //drive strength
		 ldr r2, GPIO_PA_CTRL // ctrl_register adress
		 str r1, [r2,#0] // load drive strength into ctrl_register
		
		 ldr r1, #0x55555555 // set pushpulldrive
		 ldr r2, GPIO_PA_MODEH //adress for setting bit 8-15 port A
		 str r1,[r2,#0] // set pushpulldrive bit 8-15 port A
		 
		 
		 ldr r1, #0x00000000
		 ldr r2, GPIO_PA_DOUT
		 str r1,[r2,#0]
		 
cmu_base_addr:
		 .long CMU_BASE
		 
		 
		 // Enable input
		 
		 
	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  
		
	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

