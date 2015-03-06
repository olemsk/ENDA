#include <stdint.h>
#include <stdbool.h>


#include "efm32gg.h"
/*
#include "Beep1_Henrik.c"
#include "Beep2_Henrik.c"
*/
#include "sounds.c"

void setupTimer(uint32_t period); 
#include "test_make_melody.c"
#define   SAMPLE_PERIOD   1709 
 
bool play_beep_1(void);
bool play_beep_2(void);

void control_music(uint32_t inn);  
 
 
bool var_2 = false;
uint32_t  var_1 = 0x000; 
uint32_t song = 0;





int find_sound(uint32_t inn);

bool select_mode(uint32_t inn);






/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  
	*TIMER1_IFC = 1; 
	startDAC();
	
		control_music(song);
	
};




int find_sound(uint32_t inn);

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
  	
	GPIO_handler();
};


int find_sound(uint32_t inn);

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
   	
	
	GPIO_handler();

};




void GPIO_handler()
{
	
switch (*GPIO_PC_DIN)
{	
	

	case 0xFD:
	*SCR=0x2;
	setupTimer(SAMPLE_PERIOD);
		
		
		song = 1;
							
		break;
	
	case 0xFB:
	*SCR=0x2;
	setupTimer(SAMPLE_PERIOD);
		
		
		song = 2;
	
	
		break;
	case 0xF7:
	*SCR=0x2;
	setupTimer(SAMPLE_PERIOD);
		
		
		song = 3;
	
	
		break;

	default:
	song=0;
	
	
	break;

}
*GPIO_IFC=0xFF;


}






