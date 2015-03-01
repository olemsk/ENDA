#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.c"




 


  uint32_t  var_1 = 0x000;
bool var_2 = false;

int find_sound(uint32_t inn);
int play_sound(uint32_t sound);
void play_melody(uint32_t sound);
void play_mario(void);
void play_peer_gynt(void);
void play_smoke(void);
void play_natal(void);
void play_LTS(void);
bool select_mode(uint32_t inn);



/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  
  *TIMER1_IFC = 1;
 
  
  
  if(var_2)
{
  *GPIO_PA_DOUT=*GPIO_PC_DIN <<8;
  
  play_sound(find_sound(*GPIO_PC_DIN));
  
  
}

  else
{
  *GPIO_PA_DOUT=0xFE;
  play_melody(*GPIO_PC_DIN);


}

  
       

}




int find_sound(uint32_t inn);

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
  
  *GPIO_IFC = *GPIO_IF;
  var_1 = find_sound((*GPIO_PC_DIN));
  var_2 ^= select_mode(*GPIO_PC_DIN);
  *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
    
     
}


int find_sound(uint32_t inn);

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
   
  *GPIO_IFC = *GPIO_IF;
  var_1 = find_sound((*GPIO_PC_DIN));
  var_2 ^= select_mode(*GPIO_PC_DIN);
   *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;

  
}

bool select_mode(uint32_t inn)
{

  if(inn ==  0xFE)
    {
      return true;
    }
  return false;


}









