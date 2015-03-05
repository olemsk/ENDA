#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"





uint32_t TEMP = 0xFFF; 

int find_sound(uint32_t inn);





int play_sound(uint32_t sound)
{
	if ( sound != 1000){
  		for(int i = 0; i < sound; i++){
			*DAC0_CH0DATA ^= TEMP;
  			*DAC0_CH1DATA ^= TEMP;}}  
    
	return 0;
	stopDAC();
	stop_LET();
};



int find_sound(uint32_t inn)
{
	int sound = 1000;
	switch(inn){
 		case 0xFD:
   			sound = 340 ; //C#
   			break;
		case 0xFB:
   			sound = 380 ; //D#
   			break;
 		case 0xF7:
   			sound = 460; //F#
 	  		break;
 		case 0xEF:
   			sound = 510; // G#
	   		break;
		case 0xDF:
  			sound = 580; // A#
	   		break;
 		case 0xBF:
   			sound = 690; // C#
	   		break;
 		case 0x7F:
   			sound = 770; // D#
	   		break;
		default:
			sound = 1000;
			return sound;}
	return sound;
};




