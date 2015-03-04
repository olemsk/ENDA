#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#include "Beep1.c"

#include "Beep2.c"
/*
#include "mcg2.c"
*/
int counter = 0;

bool play_beep_1(void);
bool play_beep_2(void);
/*
void play_mcg(int counter);
*/


void control_music(uint32_t song)
{


switch(song)
{

case 0xFD:
if(play_beep_1())
{return;}
break;

case 0xFB:
if (play_beep_2())
{return;}
break;
/*
case 0xF7:
play_mcg(0);
break;
*/
default:


return;

}



}



bool play_beep_1(void)
{

int length = 7585;
  if(counter == length)
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



bool play_beep_2(void)
{

int length = 7585;
  if(counter == length)
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


/*
void play_mcg(int counter)
{

int length = sizeof(mcg)/sizeof(mcg[0]);
  if(counter == length)
    {	*DAC0_CH0DATA = 0 ;
  	*DAC0_CH1DATA = 0;
      return;
		
    }
  uint16_t  temp= mcg[counter];
	 
	*DAC0_CH0DATA = temp ;
  	*DAC0_CH1DATA = temp;
	counter +=1;


};
*/


