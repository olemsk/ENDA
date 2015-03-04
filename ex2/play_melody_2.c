#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#include "Beep1.c"

//#include "Beep2.c"

int counter = 0;

bool play_beep_1(void);
//bool play_beep_2(void);



void control_music(uint32_t song)
{


switch(song)
{

case 0xFD:
if(play_beep_1()) // hente inn sang i variabel
		// inn sanglengde 
{return;}
break;

case 0xFB:
//if (play_beep_2())
{return;}
break;

default:


return;

}



}



bool play_beep_1(void)
{

int length = 7585;
  if(counter == length-1)
    {	 
	*DAC0_CH0DATA = 0 ;
  	*DAC0_CH1DATA = 0;
	counter=0;

  	
      return true;
		
    }
  uint16_t  temp= Beep1[counter];
	 
	*DAC0_CH0DATA = temp ;
  	*DAC0_CH1DATA = temp;
	
	counter +=1;
	return false;

};



/*bool play_beep_2(void)
{

int length = 7585;
  if(counter == length-1)
    {	*DAC0_CH0DATA = 0 ;
  	*DAC0_CH1DATA = 0;
	counter = 0;
      return true;
		
    }
  uint16_t  temp= Beep2[counter];
	 
	*DAC0_CH0DATA = temp ;
  	*DAC0_CH1DATA = temp;
	counter +=1;
	
	return false;
};
*/




