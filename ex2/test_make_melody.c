#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"

//Include song files
#include "Beep1.c"
#include "Beep2.c"
#include "mcg.c"
#include "bond.c"
#include "explosion.c"
int counter = 0;

bool isFinished = true;

void start_LET(void);
void stop_LET(void);

int Beep1_length = 1409;
int Beep2_length = 1409;
int mcglength= 24576;
int bondlength = 156288; 
int explosionlength=4096;
void control_music(uint32_t inn)
{	
	const uint16_t *song; // 
	  int songlength; // 
	if(isFinished) // For controlling when a song i finished
{
	switch(inn){
	
		case 1:
			song = Beep1; // Set song to be played
			songlength = Beep1_length; // Set songlength
			isFinished = false;	//Started new song, is therefore not finished
			break;
	
		case 2:
			
			song = Beep2;
			songlength = Beep2_length;
			isFinished=false;
			break;

		case 3:
			song= mcg;
			songlength= mcglength;		
			isFinished=false;
			break;
		case 4:
			song= bond;
			songlength=bondlength;
			isFinished = false;
			break;

		
		case 5:
			song=explosion;
			songlength=explosionlength;
			isFinished=false;
			break;
		default:
			
			stopDAC();
			isFinished=true;
					
			return;
			break;
		}
}
	
	if ( counter > songlength){ 
		*GPIO_PA_DOUT= 0xFF<<8; // Turn off all lights
		
		counter = 0;		// Restore counter value to 0, ready for new song
		isFinished = true;	// Ready for new song
		*GPIO_IEN = 0xFF; 	// Enable interrupt from GPIO
		stopDAC();		// Turn of DAC for no unwanted sound and power savement
		
		*SCR=0x6;		// Enable deep-sleep
	return;}
		
				
		*GPIO_PA_DOUT=0x00;	// Turn on lights, music is playing
		*DAC0_CH0DATA = song[counter] ;	// Send sound sample to DAC
		*DAC0_CH1DATA = song[counter] ;	// Send sound sample to DAC
		counter++;			// Next time, new sample
		isFinished=false;		// Song is not finished
		*GPIO_IEN = 0x0; 		// Disable interrupt from GPIO to prevent unvanted sound from DAC
		
		return;
	
	
		
		

};




