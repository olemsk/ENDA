	

           
     
               .syntax unified
               
                      .include "efm32gg.s" //Contains common constants
         
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
                     
         
         
         
                /////////////////////////////////////////////////////////////////////////////
                //
                // GPIO ENABLE
                ////////////////////////////////////////////////////////////////////////////
         
                // Constants in emf32gg.s
         
        ldr r1, =CMU_BASE                    // load CMU base address
         
        ldr r2, [r1, #CMU_HFPERCLKEN0]       // load current value of HFPERCLK ENABLE
         
        mov r3, #1                           // set bit for GPIO clk
        lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
        orr r2, r2, r3
         
        str r2, [r1, #CMU_HFPERCLKEN0]       // store new value
         
         
                ///////////////////////////////////////////////////////////////////////////
                //
                // SET DRIVE STRENGTH to 0x2
                //////////////////////////////////////////////////////////////////////////
        ldr r1, =GPIO_PA_BASE      // load drive strength base address
        mov r2, #2                 // set bit value
        str r2, [r1, #GPIO_CTRL]   // store value
         
                ////////////////////////////////////////////////////////////////////////////
                //
                //SET pins 8-15(LEDs) to output
                ////////////////////////////////////////////////////////////////////////////
        ldr r1, =GPIO_PA_BASE      // Load pin out location
        ldr r2, =0x55555555        // Set bit value for outputs
        str r2, [r1, #GPIO_MODEH]  // Store value
         
         
                ////////////////////////////////////////////////////////////////////////////
                //
                //Set 0-7 to input and enable internal pull-up
                ///////////////////////////////////////////////////////////////////////////
         
        ldr r1, =GPIO_PC_BASE     // Load PC base address
         
        ldr r2, =0x33333333       // Set bit value for inputs
        str r2, [r1, #GPIO_MODEL] // Store value
     
        mov r3, 0xff              // Set bit value for internal pull up
        str r3, [r1, #GPIO_DOUT]  // Store value
     
                /////////////////////////////////////////////////////////////////////////////
                //
                //GPIO Interupt setup
                ////////////////////////////////////////////////////////////////////////////
        ldr r1, =GPIO_BASE                  // Load base address
        ldr r2, =0x22222222                 // Load value
        str r2, [r1, #GPIO_EXTIPSELL]       // Store value
         
         
        mov r2, 0xff                        // Set interupt on 1->0 Transition
        str r2, [r1, #GPIO_EXTIFALL]        //
         
        str r2, [r1, #GPIO_EXTIRISE]        // Set interupt on 0->1 Transistion
         
        str r2, [r1, #GPIO_IEN]             // Enable interupt generation
         
         
         
         
        ldr r1, =ISER0                      // Load ISER0
        movw r2, 0x802
        str r2, [r1, #0]                    // Enable interupt handling
         
         
        ldr r1, =SCR                        //Load SCR
        mov r2, #6                          // move 6 in r2
        str r2, [r1, #0]                    // Store 6 in SCR
               
        wfi                                 // Wait for interupt
         
                /////////////////////////////////////////////////////////////////////////////
                //
                // GPIO handler
                // The CPU will jump here when there is a GPIO interrupt
                //
                /////////////////////////////////////////////////////////////////////////////
               
                .thumb_func
        gpio_handler:
                ldr r1, =GPIO_BASE                 // Load GPIO base address
                ldr r2, [r1, #GPIO_IF]             // Load the source of the interupt register
                str r2, [r1, #GPIO_IFC]            // and store it to GPIO_IFC
               
                ldr r1, =GPIO_PA_BASE              // Load PA address
                ldr r2, =GPIO_PC_BASE              // Load PC Address
                ldr r3, [r2, #GPIO_DIN]            // Load current value of the buttons
                lsl r3, r3, #8                     // Shift the value eight bits to the left
                str r3, [r1, #GPIO_DOUT]           // Store the shifted value in the outputs, effectively
                                                   // changing the lights corresponing to the current state of the inputs
               
                bx lr
                /////////////////////////////////////////////////////////////////////////////
               
                .thumb_func
        dummy_handler:  
                b .  // do nothing

