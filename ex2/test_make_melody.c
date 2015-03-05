#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"
#include "Beep1_Henrik.c"
#include "Beep2_Henrik.c"

int counter = 0;
bool play_beep_1(void);
bool play_beep_2(void);






void control_music(uint32_t inn)
{
	const uint16_t *song; // vektor med sangene
	 const uint32_t *songlength; // m� lages i sound filene

	switch(inn){
	
		case 0xFD:
			song = Beep1;
			songlength = &Beep1_length;	
			break;
	
		case 0xFB:
			song = Beep2;
			songlength = Beep2_length;
			break;

		default:
			song = Beep1;
			songlength= Beep1_length;
			return;}

	if ( counter == songlength -1){
		counter = 0;
	return;}

	else{
		*DAC0_CH0DATA = song[counter] ;
		*DAC0_CH1DATA = song[counter] ;
		counter++;}
};




/*
bool play_beep_1(void)
{
	int length = 7585;
	if(counter == length){
		*DAC0_CH0DATA = 0 ;
		*DAC0_CH1DATA = 0;
		counter=0;
		return true;}

	uint16_t temp= Beep1[counter];
	*DAC0_CH0DATA = temp ;
	*DAC0_CH1DATA = temp;
	counter +=1;
	return false;
}; // to semikolon or not to semikolon p� slutten av funksjon?
*/

/*
bool play_beep_2(void)
{
	int length = 7585;
	if(counter == length){ 
		*DAC0_CH0DATA = 0 ;
		*DAC0_CH1DATA = 0;
		counter = 0;
		return true;}

	uint16_t temp= Beep2[counter];
	*DAC0_CH0DATA = temp ;
	*DAC0_CH1DATA = temp;
	counter +=1;
	return false;
};
*/
/*
void play_mcg(int counter)
{
	int length = sizeof(mcg)/sizeof(mcg[0]);
	if(counter == length){ 
		*DAC0_CH0DATA = 0 ;
		*DAC0_CH1DATA = 0;
		return;}
	uint16_t temp= mcg[counter];
	*DAC0_CH0DATA = temp ;
	*DAC0_CH1DATA = temp;
	counter +=1;
};
*/
