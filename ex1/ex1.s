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
		 
		 // load CMU base address
		 ldr r1, cmu_base_addr
		 
		 // load current value of HFPERCLK ENABLE
		 ldr r2, [r1, #CMU_HFPERCLKEN0]
		 
		 // set bit for GPIO clk
		 mov r3, #1
		 lsl r3, r3, #13
		 orr r2, r2, r3
		 
		 // store new value
		 str r2, [r1, #CMU_HFPERCLKEN0]

		  // Enable output
		 mov r1, #0x2 //drive strength
		 ldr r2, =GPIO_PA_BASE // ctrl_register adress
		 str r1, [r2,#GPIO_CTRL] // load drive strength into ctrl_register
		
		 ldr r1, =0x55555555 // set pushpulldrive

		 str r1,[r2,#GPIO_MODEH] // set pushpulldrive bit 8-15 port A
	
		 
		 ldr r3, =0x33333333  // value to set pin 0-7 to input
		 ldr r4, =GPIO_PC_BASE // value of GPIO_PC_BASE
		 str r3, [r4, #GPIO_MODEL] // Set pin 0-7 to input

		 mov r3, #0xFF  // Value for enabling internal pull-up
		 str r3, [r4, #GPIO_DOUT] //set enable internal pull-up
		 
	
		 ldr r1, =GPIO_BASE
		 ldr r2, =0x22222222
		 str r2, [r1, GPIO_EXTIPSELL]
		 mov r2, #0xFF
		 str r2, [r1, GPIO_EXTIFALL]
		 str r2, [r1, GPIO_EXTIRISE]
		 str r2, [r1, GPIO_IEN]

		 ldr r3, =ISER0
		 ldr r2, =0x802
		 str r2, [r3, #0]

		 ldr r1, =SCR
		 mov r2, #6
		 str r2,[r1,#0]

		 wfi

	
		
		 
		 

  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:
		 ldr r5, =GPIO_BASE
		 ldr r6, [r5, GPIO_IF]
		 str r6,[r5, GPIO_IFC]
		 
		
		 ldr r1, =GPIO_PA_BASE
		 ldr r2, =GPIO_PC_BASE
		 ldr r3, [r2, #GPIO_DIN] // load value from keyboard
		 lsl r3, r3, #8 // leftshift 8 places
		 str r3, [r1, #GPIO_DOUT] // store value in PA_DOUT, setting value of ligth to 0-enabling light


	
	
		 

		 

	
		bx lr
		 
		 
cmu_base_addr:
		 .long CMU_BASE
		 
		 
		 // Enable input
		 
		 
	      b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	//

	          .thumb_func
        dummy_handler:  
                b .  // do nothing